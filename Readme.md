# Diffie-Hellman Key Exchange Implementation

This project provides an implementation of the Diffie-Hellman key exchange protocol in three programming languages: **C++**, **Java**, and **Python**. The Diffie-Hellman protocol is a method for securely exchanging cryptographic keys over a public channel.

## Project Structure

The project is organized into three folders, each containing the implementation in a specific language:

### C++ Implementation
Located in the folder: `Diffie-Hellman\C++`

Files:
- **DHSetup.h**: Handles the setup of the Diffie-Hellman protocol, including generator selection and modular exponentiation.
- **GaloisField.h**: Implements arithmetic operations in a finite field.
- **User.h**: Represents a user participating in the key exchange.
- **Test.cpp**: Demonstrates the usage of the Diffie-Hellman protocol with encryption and decryption.

### Java Implementation
Located in the folder: `Diffie-Hellman\JAVA`

Files:
- **DHSetup.java**: Handles the setup of the Diffie-Hellman protocol.
- **GaloisField.java**: Implements finite field arithmetic.
- **User.java**: Represents a user in the protocol.
- **Test.java**: Demonstrates the protocol with encryption and decryption.

### Python Implementation
Located in the folder: `Diffie-Hellman\Python`

Files:
- **DHSetup.py**: Handles the setup of the Diffie-Hellman protocol.
- **FiniteField.py**: Implements arithmetic operations in a finite field.
- **User.py**: Represents a user in the protocol.
- **main.py**: Demonstrates the protocol with encryption and decryption.

## Features
- **Finite Field Arithmetic**: All implementations include support for modular arithmetic in a finite field.
- **Key Exchange**: Securely exchange keys between two users.
- **Encryption and Decryption**: Demonstrates how the shared key can be used for secure communication.

## How to Run

### C++
1. Compile the code using a C++ compiler (e.g., `g++`):
    ```bash
    g++ Test.cpp -o Test
    ```
2. Run the executable:
    ```bash
    ./Test
    ```

### Java
1. Compile the Java files:
    ```bash
    javac *.java
    ```
2. Run the `Test` class:
    ```bash
    java Test
    ```

### Python
1. Run the `main.py` script:
    ```bash
    python main.py
    ```

## Example Output
The output demonstrates:
- Public keys exchanged between two users.
- Encrypted messages using the shared key.
- Decrypted messages to verify the correctness of the protocol.

## Dependencies
- **C++**: Requires a C++11 or later compatible compiler.
- **Java**: Requires JDK 8 or later.
- **Python**: Requires Python 3.6 or later.
