# Virtual ATM - Microservices Architecture 🏦

## Overview
The Virtual ATM system is designed using a microservices architecture, allowing modular, scalable, and independent services for better performance and maintainability.

## Architecture 🏗️
The system consists of four main microservices:
1. **Account Service** - Manages user accounts, authentication, and balance.
2. **Transaction Service** - Handles deposits, withdrawals, and transaction history.
3. **Notification Service** - Provides real-time status updates.
4. **Frontend** - A GTK-based UI that interacts with the services through REST APIs.

Each service runs independently and communicates via HTTP requests.

---
## Tech Stack 🛠️
- **Backend:** Flask (Python)
- **Database:** SQLite
- **Frontend:** GTK (Python + PyGObject)
- **Containerization:** Docker + Docker Compose

---
## Installation & Setup 🚀
### 1️⃣ Clone the Repository
```sh
git clone https://github.com/stephenombuya/Virtual-ATM/tree/main/src/Microservices%20Application
cd virtual-atm
```

### 2️⃣ Run with Docker Compose
Ensure Docker and Docker Compose are installed, then run:
```sh
docker-compose up --build
```
This will start all microservices.

### 3️⃣ Access the Services
- **Account Service:** `http://localhost:5001`
- **Transaction Service:** `http://localhost:5002`
- **Notification Service:** `http://localhost:5003`
- **Frontend (GTK App):** Run `python3 frontend/app.py`

---
## API Endpoints ⚡

### **Account Service** (`http://localhost:5001`)
| Method | Endpoint | Description |
|--------|---------|-------------|
| GET    | `/balance/<username>` | Get user balance |
| POST   | `/deposit` | Deposit money |
| POST   | `/withdraw` | Withdraw money |

### **Transaction Service** (`http://localhost:5002`)
| Method | Endpoint | Description |
|--------|---------|-------------|
| GET    | `/transactions/<username>` | Get transaction history |
| GET    | `/transactions/<username>?page=<page>` | Paginated history |
| GET    | `/export/<username>` | Export history as CSV |

### **Notification Service** (`http://localhost:5003`)
| Method | Endpoint | Description |
|--------|---------|-------------|
| POST   | `/notify` | Send notification |

---
## Contributing 🛠️
1. Fork the repo
2. Create a feature branch (`git checkout -b feature-branch`)
3. Commit changes (`git commit -m 'Add feature'`)
4. Push to branch (`git push origin feature-branch`)
5. Open a Pull Request

---
## License 📜
This project is licensed under the GNU License.
