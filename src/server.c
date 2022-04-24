#include "system.h"

static int server_socket;
//Server side is binding and listening
int serverWaitForConnection()
{
    char buffer[256];
    char server_message[256] = "You've reached the server";
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
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
    char buff[100];
    serverWaitForConnection(); //think about multithreading
    struct sockaddr_in newAddr; 

    while (1)
    {
        socklen_t size = sizeof(newAddr);
        printf("ok\n");
        int dataSock = accept(server_socket, (struct sockaddr*)&newAddr, &size);
        printf("ok\n");
        printf("%u\n", size);
        int readBytes;
        while ((readBytes = read(dataSock, buff, SERVER_RES_MAX_LENGTH - 1)) > 0)
        {
            buff[readBytes] = '\0';
        
        }
    
    }
    
    
}