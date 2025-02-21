-- Create accounts table
CREATE TABLE IF NOT EXISTS accounts (
    username TEXT PRIMARY KEY,
    pin INTEGER NOT NULL,
    balance REAL NOT NULL
);

-- Create transactions table
CREATE TABLE IF NOT EXISTS transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    type TEXT NOT NULL,
    amount REAL NOT NULL,
    balance REAL NOT NULL,
    FOREIGN KEY(username) REFERENCES accounts(username)
);
