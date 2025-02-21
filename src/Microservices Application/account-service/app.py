from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('atm.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/balance/<username>', methods=['GET'])
def get_balance(username):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT balance FROM accounts WHERE username = ?", (username,))
    account = cur.fetchone()
    conn.close()
    
    if account:
        return jsonify({"balance": account["balance"]})
    return jsonify({"error": "User not found"}), 404

@app.route('/update_balance', methods=['POST'])
def update_balance():
    data = request.get_json()
    username = data.get('username')
    amount = data.get('amount')
    
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("UPDATE accounts SET balance = balance + ? WHERE username = ?", (amount, username))
    conn.commit()
    conn.close()
    
    return jsonify({"message": "Balance updated successfully"})

if __name__ == '__main__':
    app.run(port=5001, debug=True)
