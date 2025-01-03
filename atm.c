#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

// Structures and Globals
typedef struct {
    char username[50];
    int pin;
    float balance;
} Account;

typedef struct {
    char type[10];  // "Deposit" or "Withdraw"
    float amount;
    float balance;
} Transaction;

Account user;
Transaction transactions[10];
int transaction_count = 0;
sqlite3 *db;

GtkWidget *window, *entry_username, *entry_pin, *label_message;
GtkWidget *main_menu, *balance_label, *statement_label;

// Database Functions
void initialize_database() {
    if (sqlite3_open("atm.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *create_accounts_table = "CREATE TABLE IF NOT EXISTS accounts (" 
                                         "username TEXT PRIMARY KEY," 
                                         "pin INTEGER," 
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
}

int authenticate(const char *username, int pin) {
    sqlite3_stmt *stmt;
    const char *query = "SELECT balance FROM accounts WHERE username = ? AND pin = ?;";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, pin);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user.balance = sqlite3_column_double(stmt, 0);
        strcpy(user.username, username);
        user.pin = pin;
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

void save_transaction(const char *type, float amount) {
    const char *query = "INSERT INTO transactions (username, type, amount, balance) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, user.username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, type, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, amount);
    sqlite3_bind_double(stmt, 4, user.balance);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void update_balance() {
    const char *query = "UPDATE accounts SET balance = ? WHERE username = ?;";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_double(stmt, 1, user.balance);
    sqlite3_bind_text(stmt, 2, user.username, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void view_statement(GtkWidget *widget, gpointer data) {
    char statement[500] = "Recent Transactions:\n";
    sqlite3_stmt *stmt;

    const char *query = "SELECT type, amount, balance FROM transactions WHERE username = ? ORDER BY id DESC LIMIT 10;";
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, user.username, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *type = (const char *)sqlite3_column_text(stmt, 0);
        float amount = (float)sqlite3_column_double(stmt, 1);
        float balance = (float)sqlite3_column_double(stmt, 2);
        char line[50];
        snprintf(line, sizeof(line), "%s: $%.2f (Balance: $%.2f)\n", type, amount, balance);
        strcat(statement, line);
    }

    sqlite3_finalize(stmt);
    gtk_label_set_text(GTK_LABEL(statement_label), statement);
}

// UI Enhancements
void apply_styles() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "button { background-color: #5cb85c; color: white; padding: 10px; border-radius: 5px; font-size: 14px; }\n"
        "label { font-size: 16px; margin: 10px; }\n",
        -1, NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void add_animations(GtkWidget *widget) {
    // Example placeholder for animation logic.
    // Animations like fade-in/out can be implemented with libraries like libclutter or GTK animations.
}

void login(GtkWidget *widget, gpointer data) {
    const char *username = gtk_entry_get_text(GTK_ENTRY(entry_username));
    int pin = atoi(gtk_entry_get_text(GTK_ENTRY(entry_pin)));

    if (authenticate(username, pin)) {
        gtk_label_set_text(GTK_LABEL(label_message), "Login Successful!");
        gtk_widget_hide(window);
        gtk_widget_show_all(main_menu);
    } else {
        gtk_label_set_text(GTK_LABEL(label_message), "Invalid Credentials!");
    }
}

void setup_gui() {
    // Existing code...
    apply_styles();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    initialize_database();
    setup_gui();

    gtk_widget_show_all(window);
    gtk_main();

    sqlite3_close(db);
    return 0;
}
