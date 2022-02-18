#include "system.h"
//client side
int         my_curl(char *url)
{
    char header[] = "GET /  HTTP/1.0\r\nHost:  \r\n\r\n";
    struct hostent *name; 
    struct sockaddr_in client;
    int client_socket, charRead;
    char server_res[SERVER_RES_MAX_LENGTH + 1];
    //create the socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return SOCKET_ALLOCATION_FAILED;
    //alloc for the struct
    /*
    if (!(client = malloc(sizeof(struct sockaddr_in*))))
        return MEM_ALLOC_FAILED; */
    client.sin_family = AF_INET;
    client.sin_port = htons(SERVER_PORT);
    name = gethostbyname(url);
    printf("%d\n", *name->h_addr_list[0]);
    client.sin_addr  = *(struct in_addr *)inet_ntoa(*(struct in_addr*)name->h_addr_list[0]);
   
    //connect to the socket
    int connect_socket = connect(client_socket, (struct sockaddr *) &client, sizeof(client));
    if (connect_socket < 0)
        return CONNECTION_FAILED;
    int readBytes;
    printf("print\n");
    write(client_socket, &header, sizeof(header));
    while ((readBytes = recv(client_socket, server_res, SERVER_RES_MAX_LENGTH -1, 0)) > 0)
    {
        server_res[SERVER_RES_MAX_LENGTH] = '\0';
        printf("%s\n", server_res);
    }
    return (0);
}

int         main(int ac, char **av)
{
    int error_code;

  
    if (ac != 2 || !av[1])
    {
        printf("USAGEvoid [url]");
        exit(NO_ARG);
    }
  
    if (( error_code = my_curl(av[1])) < 0)
    {
        printf("error occured with code %d", error_code);
        return error_code;
    }
    printf("clean exit()\n");
    return (0);
}