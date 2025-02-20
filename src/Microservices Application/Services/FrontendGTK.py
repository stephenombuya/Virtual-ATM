import gi
import requests

gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

ACCOUNT_SERVICE_URL = "http://127.0.0.1:5001"
TRANSACTION_SERVICE_URL = "http://127.0.0.1:5002"
NOTIFICATION_SERVICE_URL = "http://127.0.0.1:5003"

class ATMApp(Gtk.Window):
    def __init__(self):
        super().__init__(title="ATM System")
        self.set_border_width(10)
        self.set_default_size(400, 300)

        vbox = Gtk.VBox(spacing=6)
        self.add(vbox)

        self.label_message = Gtk.Label(label="Welcome! Please log in.")
        vbox.pack_start(self.label_message, False, False, 0)

        self.entry_username = Gtk.Entry()
        self.entry_username.set_placeholder_text("Username")
        vbox.pack_start(self.entry_username, False, False, 0)

        self.entry_pin = Gtk.Entry()
        self.entry_pin.set_placeholder_text("PIN")
        self.entry_pin.set_visibility(False)
        vbox.pack_start(self.entry_pin, False, False, 0)

        self.button_login = Gtk.Button(label="Login")
        self.button_login.connect("clicked", self.on_login_clicked)
        vbox.pack_start(self.button_login, False, False, 0)

        self.status_bar = Gtk.Label(label="Status: Ready")
        vbox.pack_start(self.status_bar, False, False, 0)

    def on_login_clicked(self, widget):
        username = self.entry_username.get_text()
        pin = self.entry_pin.get_text()
        
        response = requests.get(f"{ACCOUNT_SERVICE_URL}/balance/{username}")
        
        if response.status_code == 200:
            balance = response.json().get("balance", 0)
            self.label_message.set_text(f"Login Successful! Balance: ${balance}")
            self.update_status_bar("Login Successful!")
        else:
            self.label_message.set_text("Invalid Credentials!")
            self.update_status_bar("Login Failed!")

    def update_status_bar(self, message):
        requests.post(f"{NOTIFICATION_SERVICE_URL}/notify", json={"message": message})
        self.status_bar.set_text(f"Status: {message}")

if __name__ == "__main__":
    app = ATMApp()
    app.connect("destroy", Gtk.main_quit)
    app.show_all()
    Gtk.main()
