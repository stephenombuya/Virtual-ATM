# Virtual ATM - Monolithic Architecture 🏦

## Overview
The Virtual ATM system was originally developed as a monolithic application before transitioning to a microservices architecture. This version of the application integrates account management, transactions, and notifications into a single system.

## Tech Stack 🛠️
- **Backend:** C (GTK + SQLite)
- **Frontend:** GTK (C + Glade UI)
- **Database:** SQLite

---
## Installation & Setup 🚀
### 1️⃣ Clone the Repository
```sh
git clone https://github.com/stephenombuya/Virtual-ATM/tree/main/src/Monolithic%20Application
cd virtual-atm/monolithic
```

### 2️⃣ Compile the Application
```sh
gcc -o virtual_atm main.c `pkg-config --cflags --libs gtk+-3.0` -lsqlite3
```

### 3️⃣ Run the Application
```sh
./virtual_atm
```
This will start the Virtual ATM with a GTK-based frontend.

---
## Features 🌟
- **User Authentication** - Login with username and PIN.
- **Balance Inquiry** - View account balance.
- **Deposits & Withdrawals** - Add or withdraw funds.
- **Transaction History** - View recent transactions.
- **Notifications** - Status bar messages for login and transactions.
- **CSV Export** - Export transaction history.

---
## Database Schema 🗄️
The SQLite database (`atm.db`) consists of two tables:

### **Accounts Table**
| Column  | Type   | Description |
|---------|--------|-------------|
| username | TEXT | Primary Key |
| pin      | INT   | User PIN    |
| balance  | REAL  | Account balance |

### **Transactions Table**
| Column  | Type   | Description |
|---------|--------|-------------|
| id       | INTEGER | Primary Key |
| username | TEXT    | Foreign Key (Accounts) |
| type     | TEXT    | "Deposit" or "Withdraw" |
| amount   | REAL    | Transaction amount |
| balance  | REAL    | Balance after transaction |

---
## Contributing 🛠️
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-branch`).
3. Commit changes (`git commit -m 'Add feature'`).
4. Push to branch (`git push origin feature-branch`).
5. Open a Pull Request.

---
## License 📜
This project is licensed under the GNU License.
