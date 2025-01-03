# ATM C Project with GTK+ GUI

This project implements a basic ATM (Automated Teller Machine) program using the GTK+ library for the graphical user interface. Users can log in with a username and PIN, view their balance, and potentially perform transactions (deposit or withdrawal) in future updates.

## Features

* Login functionality with username and PIN verification
* Database integration for storing user accounts and transactions (future implementation)
* User-friendly GTK+ GUI with basic styling

## Getting Started

### Prerequisites

This project requires the following dependencies:

* C compiler (gcc)
* GTK+ 3.0 libraries and development headers (`pkg-config`)

You can install these dependencies on most Linux distributions using your package manager. For example, on Ubuntu/Debian, you can run:

```bash
sudo apt install build-essential libgtk-3-dev
```

### Compiling and Running
  1. Clone this repository to your local machine.
  2. Open a terminal in the project directory.
  3. Run the following command to compile the program:
     ```bash
     make
     ```

  4. Run the program using the following command:
     ```bash
     ./atm
     ```

This will launch the ATM application.


### Project Structure
The project is organized with the following directory structure:

  - `atm.c`: Main program entry point.
  - `Makefile`: Makefile for compiling the program.


### Future Enhancements
- Implement transaction functionality (deposit and withdrawal)
- Error handling and validation for user input
- Add more features like balance inquiry and transaction history
- Enhance the GUI with more visual elements and user interaction


### Contributing
We welcome contributions to this project! If you have any bug fixes, improvements, or new features in mind, feel free to fork the repository and submit a pull request.


### License
This project is licensed under the GNU General Public License. See the `LICENSE` file for more details.
