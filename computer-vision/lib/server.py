import socket
import struct


class SocketServer:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def start(self):
        self.server_socket.bind((self.host, self.port))
        # one maximum client allowed
        self.server_socket.listen(1)
        print(f"Server listening on {self.host}:{self.port}")

    def handle_client(self, client_socket, command, amount):
        try:
            # Send data to the client
            client_socket.sendall(self.__pack_data(command, amount))
        except Exception as e:
            print(f"Error handling client: {e}")

    def stop(self):
        self.server_socket.close()

    def __pack_data(self, command, amount):
        return struct.pack("=BI", command, amount)
