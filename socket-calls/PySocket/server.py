import socket

def start_server(host, port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    print(f"Server listening on {host}:{port}")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Accepted connection from {client_address[0]}:{client_address[1]}")

        request = client_socket.recv(1024).decode("utf-8")
        print(f"Received request: {request}")

        # Process the request and generate a response
        response = "Hello, client!"

        client_socket.sendall(response.encode("utf-8"))
        client_socket.close()

start_server("127.0.0.1", 8080)  # Replace with your desired host and port

