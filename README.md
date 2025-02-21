# Virtual ATM - Complete Documentation 🏦

## Overview
The **Virtual ATM** is a software-based ATM system that allows users to manage their bank accounts, perform transactions, and receive notifications. It has been implemented in two different architectures:
1. **Monolithic Architecture** 🏗️
2. **Microservices Architecture** 🌐

Both implementations provide a functional ATM experience with features like authentication, balance inquiries, deposits, withdrawals, transaction history, and notifications.

---
## 1️⃣ Monolithic Version
### Features:
- Single application handling all functionalities.
- Integrated SQLite database for accounts and transactions.
- GTK-based graphical user interface.
- Status bar notifications for login, transactions, and errors.
- CSV export for transaction history.

### Tech Stack:
- **Programming Language:** C
- **Frontend:** GTK (GObject)
- **Database:** SQLite

### Setup Instructions:
```sh
git clone https://github.com/stephenombuya/Virtual-ATM
cd virtual-atm/monolithic
make
./virtual_atm
```

[See full Monolithic README](monolithic/README.md)

---
## 2️⃣ Microservices Version
### Features:
- Modular design with independent services:
  - **Account Service** (User authentication & balance management)
  - **Transaction Service** (Deposits, withdrawals, history management)
  - **Notification Service** (Real-time status updates)
  - **Frontend** (GTK-based UI communicating via APIs)
- REST API communication between services.
- Dockerized deployment.

### Tech Stack:
- **Backend:** Python (Flask, SQLite)
- **Frontend:** GTK (PyGObject)
- **Containerization:** Docker + Docker Compose

### Setup Instructions:
```sh
git clone https://github.com/your-username/virtual-atm.git
cd virtual-atm
docker-compose up --build
```

[See full Microservices README](microservices/README.md)

---
## Comparison: Monolithic vs Microservices ⚖️
| Feature | Monolithic | Microservices |
|---------|-----------|--------------|
| **Scalability** | Limited | High |
| **Maintainability** | Harder | Easier |
| **Performance** | Slower under load | Faster, optimized services |
| **Deployment** | Simple | Requires containerization |
| **Fault Isolation** | Low | High |

---
## Contribution Guide 🛠️
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit (`git commit -m 'Add feature'`).
4. Push the branch (`git push origin feature-branch`).
5. Open a Pull Request.

---
## License 📜
This project is licensed under the GNU License.
