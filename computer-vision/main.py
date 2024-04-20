from lib.server import SocketServer

HOST = ""
PORT = ""


def main():
    #TODO: computer vision stuff
    server = SocketServer("192.168.4.2", 8080)
    # server = SocketServer("0.0.0.0",8080)
    server.start()
    try:
        while True:
            client_socket, client_address = server.server_socket.accept()
            print(f"Connection from {client_address}")
            server.handle_client(client_socket, 20, 20)
            server.handle_client(client_socket, 20, 20)
            server.handle_client(client_socket, 20, 20)
            server.handle_client(client_socket, 20, 20)
            server.handle_client(client_socket, 20, 20)
            server.handle_client(client_socket, 20, 20)
    except KeyboardInterrupt:
        server.stop()


if __name__ == "__main__":
    main()
