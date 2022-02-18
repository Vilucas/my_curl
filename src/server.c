#include "system.h"


//Server side is binding and listening
int server()
{
    char buffer[256];
    char server_message[256] = "You've reached the server";
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
        return SOCKET_ALLOCATION_FAILED;
    
    //define server address
    struct sockaddr_in server_address;
    server_address.sin_port = SERVER_PORT;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;

   if ((bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address))) == -1)
        return BIND_FAILED;
    listen(server_socket, 5);
    int client_socket = accept(server_socket, NULL, NULL);
    send(client_socket,server_message, sizeof(server_message), 0);

    return (0);
}

int main()
{
    server();
}