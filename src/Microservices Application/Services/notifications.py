from flask import Flask, request, jsonify

app = Flask(__name__)

notifications = []

@app.route('/notify', methods=['POST'])
def send_notification():
    data = request.get_json()
    message = data.get("message")
    
    if message:
        notifications.append(message)
        return jsonify({"status": "Notification received"})
    return jsonify({"error": "No message provided"}), 400

@app.route('/notifications', methods=['GET'])
def get_notifications():
    return jsonify(notifications)

if __name__ == '__main__':
    app.run(port=5003, debug=True)
