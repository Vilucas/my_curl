#include "../includes/system.h"


//Server side is binding and listening
int serverWaitForConnection()
{
    int server_socket;
    char buffer[256];
    char server_message[256] = "You've reached the server";
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
        return SOCKET_ALLOCATION_FAILED;
    
    //define server address
    int sockfd, new_sock;
    struct sockaddr_in server_address;
    struct sockaddr_in new_addr;
    server_address.sin_port = SERVER_PORT;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;

   if ((bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address))) == -1)
        return BIND_FAILED;
    listen(server_socket, 5);
    socklen_t size = sizeof(new_addr);
    int numByte;
    
    printf("%s\n", "okok");
    int client_socket_new = accept(server_socket, (struct sockaddr*) &new_addr, &size);
  
    printf("%s\n", "okffok");
     numByte = read(client_socket_new, &buffer, 100);

    buffer[numByte] = '\0';
    printf("%s\n", buffer);
    return (0);
}

int main()
{
    printf("enr man");
    int err = serverWaitForConnection(); //think about multithreading
    printf("%d\n", err);
}