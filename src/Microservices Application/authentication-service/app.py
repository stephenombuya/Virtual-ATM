from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

def hash_pin(pin):
    return hashlib.sha256(pin.encode()).hexdigest()

def connect_db():
    return sqlite3.connect("atm.db")

@app.route('/login', methods=['POST'])
def login():
    data = request.json
    username = data.get("username")
    pin = data.get("pin")

    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute("SELECT pin FROM accounts WHERE username = ?", (username,))
    result = cursor.fetchone()
    conn.close()

    if result and result[0] == hash_pin(pin):
        return jsonify({"status": "success", "message": "Login successful!"})
    else:
        return jsonify({"status": "error", "message": "Invalid credentials!"}), 401

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5001, debug=True)
