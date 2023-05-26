import socket

def send_request(host, port, request):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    client_socket.sendall(request.encode("utf-8"))

    response = client_socket.recv(1024).decode("utf-8")
    print(f"Response: {response}")

    client_socket.close()

send_request("127.0.0.1", 8080, "Hello, server!")  # Replace with your server's host and port

