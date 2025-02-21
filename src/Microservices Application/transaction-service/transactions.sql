CREATE TABLE IF NOT EXISTS transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    type TEXT CHECK(type IN ('Deposit', 'Withdraw')) NOT NULL,
    amount REAL NOT NULL,
    balance REAL NOT NULL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(username) REFERENCES accounts(username)
);
