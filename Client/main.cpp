#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;
int main(int argc, char** argv)
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
    server_address.sin_port = htons(atoi(argv[1]));
    server_address.sin_addr.s_addr = inet_addr(argv[2]);

    // connects the client to the server
    // socket fd, struct server_address, size of that struct
    int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    //check for error with the connection
    if(connection_status < 0)
        cout << "There was an error making a connection to the remote socket \n";

    //*********************************

    // 1) Send data to the server
    char client_message[256] = {0};
    cout << "Enter a message for the server: ";
    cin.getline(client_message, 256);
    send(network_socket, client_message, sizeof(client_message), 0);

    // receive data from the server
    char server_response[256] = {0};
    recv(network_socket, server_response, sizeof(server_response), 0);

    // print out the server's response
    cout << "The server has sent the data: " << server_response << "\n";

    // close the socket
    close(network_socket);

    return 0;
}