import socket

SERVER_HOST = "127.0.0.1"
SERVER_PORT = 5000
BUFFER_SIZE = 2048

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.bind((SERVER_HOST, SERVER_PORT))


while(True):
    clientSocket = s.recvfrom(BUFFER_SIZE)

    clientMsg = f"Message from Client: {clientSocket[0]}"
    clientIP  = f"Client IP Address: {clientSocket[1]}"
    
    print(clientMsg)
    print(clientIP)

    #Sending a reply to client
    s.sendto(str.encode("test"), clientSocket[1])