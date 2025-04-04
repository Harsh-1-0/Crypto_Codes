import socket
import math

def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    gcd, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return gcd, x, y

def mod_inverse(e, phi):
    gcd, x, _ = extended_gcd(e, phi)
    if gcd != 1:
        raise ValueError("No modular inverse exists")
    return x % phi

def encrypt(message, e, n):
    return [pow(ord(char), e, n) for char in message]

def decrypt(ciphertext, d, n):
    return ''.join(chr(pow(char, d, n)) for char in ciphertext)

# Given values
p = 7
q = 11
n = p * q
phi_n = (p - 1) * (q - 1)
e = 13
d = mod_inverse(e, phi_n)

def server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("localhost", 12345))
    server_socket.listen(1)
    print("Server listening on port 12345...")
    
    conn, addr = server_socket.accept()
    print(f"Connection from {addr} established.")
    
    encrypted_message = conn.recv(1024).decode()
    encrypted_message = list(map(int, encrypted_message.split(',')))
    
    decrypted_message = decrypt(encrypted_message, d, n)
    print("Decrypted message:", decrypted_message)
    
    conn.close()
    server_socket.close()

def client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(("localhost", 12345))
    
    message = "Hello RSA"
    encrypted_message = encrypt(message, e, n)
    
    client_socket.send(','.join(map(str, encrypted_message)).encode())
    client_socket.close()

if __name__ == "__main__":
    choice = input("Start as server (s) or client (c)? ").strip().lower()
    if choice == 's':
        server()
    elif choice == 'c':
        client()
    else:
        print("Invalid choice.")
