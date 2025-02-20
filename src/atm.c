#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>
#include <pthread.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>

#define MAX_ATTEMPTS 3
#define TRANSACTIONS_PER_PAGE 5
int login_attempts = 0;
int current_page = 0;

GtkWidget *window, *main_menu, *balance_label, *entry_username, *entry_pin, *label_message, *transaction_label, *status_bar;
guint context_id;

// Hashing function for PINs
void hash_pin(const char *pin, char *hashed_pin) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)pin, strlen(pin), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_pin + (i * 2), "%02x", hash[i]);
    }
    hashed_pin[SHA256_DIGEST_LENGTH * 2] = '\0';
}

// Database initialization
void initialize_database() {
    sqlite3 *db;
    if (sqlite3_open("atm.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *create_accounts_table = "CREATE TABLE IF NOT EXISTS accounts ("
                                       "username TEXT PRIMARY KEY,"
                                       "pin TEXT,"
                                       "balance REAL);";
    sqlite3_exec(db, create_accounts_table, NULL, NULL, NULL);

    const char *create_transactions_table = "CREATE TABLE IF NOT EXISTS transactions ("
                                           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                           "username TEXT,"
                                           "type TEXT,"
                                           "amount REAL,"
                                           "balance REAL,"
                                           "FOREIGN KEY(username) REFERENCES accounts(username));";
    sqlite3_exec(db, create_transactions_table, NULL, NULL, NULL);
    sqlite3_close(db);
}

// Function to update the status bar
void update_status_bar(const char *message) {
    gtk_statusbar_push(GTK_STATUSBAR(status_bar), context_id, message);
}

// Secure Authentication with Attempt Limit
int authenticate(const char *username, const char *entered_pin) {
    if (login_attempts >= MAX_ATTEMPTS) {
        update_status_bar("Account locked. Try again later.");
        return 0;
    }

    sqlite3 *db;
    sqlite3_stmt *stmt;
    char stored_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    char hashed_pin[SHA256_DIGEST_LENGTH * 2 + 1];
    
    if (sqlite3_open("atm.db", &db) != SQLITE_OK) {
        return 0;
    }

    const char *query = "SELECT pin FROM accounts WHERE username = ?;";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }
    
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(stored_hash, (const char *)sqlite3_column_text(stmt, 0));
        hash_pin(entered_pin, hashed_pin);
        
        if (strcmp(stored_hash, hashed_pin) == 0) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            login_attempts = 0; // Reset on success
            update_status_bar("Login successful!");
            return 1;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    login_attempts++;
    update_status_bar("Invalid credentials!");
    return 0;
}

// Fetch and display transactions with pagination
void update_transaction_display(const char *username) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char statement[500] = "Recent Transactions:\n";
    char query[200];
    snprintf(query, sizeof(query), "SELECT type, amount, balance FROM transactions WHERE username = ? ORDER BY id DESC LIMIT %d OFFSET %d;", TRANSACTIONS_PER_PAGE, current_page * TRANSACTIONS_PER_PAGE);

    if (sqlite3_open("atm.db", &db) != SQLITE_OK) {
        return;
    }

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        return;
    }
    
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        char line[50];
        snprintf(line, sizeof(line), "%s: $%.2f (Balance: $%.2f)\n", 
                 sqlite3_column_text(stmt, 0),
                 sqlite3_column_double(stmt, 1),
                 sqlite3_column_double(stmt, 2));
        strcat(statement, line);
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    gtk_label_set_text(GTK_LABEL(transaction_label), statement);
}

void next_page(GtkWidget *widget, gpointer user_data) {
    current_page++;
    update_transaction_display((const char *)user_data);
}

void prev_page(GtkWidget *widget, gpointer user_data) {
    if (current_page > 0) {
        current_page--;
        update_transaction_display((const char *)user_data);
    }
}

// UI Setup
void setup_gui() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ATM System");
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    gtk_widget_set_size_request(window, 400, 300);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    transaction_label = gtk_label_new("Recent Transactions:\n");
    gtk_grid_attach(GTK_GRID(grid), transaction_label, 0, 0, 1, 1);

    GtkWidget *prev_button = gtk_button_new_with_label("Previous Page");
    gtk_grid_attach(GTK_GRID(grid), prev_button, 0, 1, 1, 1);
    g_signal_connect(prev_button, "clicked", G_CALLBACK(prev_page), NULL);

    GtkWidget *next_button = gtk_button_new_with_label("Next Page");
    gtk_grid_attach(GTK_GRID(grid), next_button, 0, 2, 1, 1);
    g_signal_connect(next_button, "clicked", G_CALLBACK(next_page), NULL);

    status_bar = gtk_statusbar_new();
    context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(status_bar), "Status Messages");
    gtk_grid_attach(GTK_GRID(grid), status_bar, 0, 3, 1, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    initialize_database();
    setup_gui();
    gtk_main();
    return 0;
}
