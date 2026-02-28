#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
    // CLIENT SIDE

    // socket() - create a socket - file descriptor
    // type of IP (ipv4), type of protocol (tcp), default
    int network_socket;
    network_socket = socket(AF_INET,SOCK_STREAM,0);

    // specify an address for the socket
    // type of IP, server port, IP of server
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connects the client to the server
    // socket fd, struct server_address, size of that struct
    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    //check for error with the connection
    if(connection_status < 0)
        printf("There was an error making a connection to the remote socket \n");

    // receive data from the server
    char server_response[256];
    recv(network_socket, server_response, sizeof(server_response), 0);

    // print out the server's response
    printf("The server has sent the data: %s\n", server_response);

    // close the socket
    close(network_socket);

    return 0;
}