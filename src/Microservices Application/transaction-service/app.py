from flask import Flask, request, jsonify, send_file
import sqlite3
import csv

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('atm.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/transactions/<username>', methods=['GET'])
def get_transactions(username):
    page = int(request.args.get('page', 0))
    limit = 5
    offset = page * limit
    
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT type, amount, balance FROM transactions WHERE username = ? ORDER BY id DESC LIMIT ? OFFSET ?", (username, limit, offset))
    transactions = cur.fetchall()
    conn.close()
    
    return jsonify([dict(tx) for tx in transactions])

@app.route('/transactions/export/<username>', methods=['GET'])
def export_transactions(username):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT id, type, amount, balance FROM transactions WHERE username = ? ORDER BY id DESC", (username,))
    transactions = cur.fetchall()
    conn.close()
    
    file_path = f"{username}_transactions.csv"
    with open(file_path, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["ID", "Type", "Amount", "Balance"])
        writer.writerows(transactions)
    
    return send_file(file_path, as_attachment=True)

@app.route('/transactions/add', methods=['POST'])
def add_transaction():
    data = request.get_json()
    username = data.get('username')
    tx_type = data.get('type')
    amount = data.get('amount')
    balance = data.get('balance')
    
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("INSERT INTO transactions (username, type, amount, balance) VALUES (?, ?, ?, ?)", (username, tx_type, amount, balance))
    conn.commit()
    conn.close()
    
    return jsonify({"message": "Transaction added successfully"})

if __name__ == '__main__':
    app.run(port=5002, debug=True)
