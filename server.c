#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
    char server_message[256] = "You have reached the server!";

    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bind the socket to our specified IP and port
    const int bind_return_value = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if(bind_return_value < 0)
    {
        printf("Binding failed");
        return 0;
    }

    const int listen_return_value = listen(server_socket, 5);
    if(listen_return_value < 0)
    {
        printf("Listening failed");
        return 0;
    }

    struct sockaddr_in client_info;
    int client_info_size = sizeof(struct sockaddr_in);
    int fd_new_server = accept(server_socket, (struct sockaddr*)&client_info, &client_info_size);

    if(fd_new_server < 0)
    {
        printf("Connection to client failed");
        return 0;
    }

    // send the message
    send(fd_new_server, server_message, sizeof(server_message), 0);

    //close the server socket
    close(server_socket);

    return 0;
}