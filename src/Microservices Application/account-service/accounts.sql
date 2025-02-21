CREATE TABLE IF NOT EXISTS accounts (
    username TEXT PRIMARY KEY,
    pin INTEGER NOT NULL,
    balance REAL DEFAULT 0.0
);
