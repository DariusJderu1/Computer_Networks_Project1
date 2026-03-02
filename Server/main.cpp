#include<iostream>
#include<string>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>
using namespace std;
void executes_server_client_connection(int fd_new_server, struct sockaddr_in client_info)
{
    // Receive the message from the client
    char client_message[256] = {0};
    recv(fd_new_server, client_message, sizeof(client_message), 0);

    // Print a message with the client's message and ports
    string server_message = string(client_message) + " | Client IP: " +
        inet_ntoa(client_info.sin_addr) + " | Client port: " + to_string(ntohs(client_info.sin_port)) +
            " | Server IP: " + "127.0.0.1" + " | Server port: " + to_string(8080);
    cout << "Message from client: " << server_message << "\n";

    // send the message back to the client
    send(fd_new_server, server_message.c_str(), server_message.size(), 0);

    //close the server socket
    close(fd_new_server);
}
int main()
{
    // create the server socket - a file descriptor
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bind the socket to our specified IP and port (which must be known for the client to connect)
    const int bind_return_value = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if(bind_return_value < 0)
    {
        cout << "Binding failed";
        return 0;
    }

    // listen to clients - transforms the socket in the "server mode" - only listens, doesn't initiate connections
    const int listen_return_value = listen(server_socket, 5);
    if(listen_return_value < 0)
    {
        cout << "Listening failed";
        return 0;
    }
    else
        cout << "The server is waiting for clients\n";

    while(true)
    {
        // accepting requests from clients (and keeping their info)
        // fd_new_server is the socket (file descriptor) assigned
        // for the communication with the current client
        struct sockaddr_in client_info;
        socklen_t client_info_size = sizeof(struct sockaddr_in);
        int fd_new_server = accept(server_socket, (struct sockaddr*)&client_info, &client_info_size);
        if(fd_new_server < 0)
            cout << "Connection to client failed";
        else
            cout << "Client connected\n";


        thread t(executes_server_client_connection, fd_new_server, client_info);

        t.detach();
    }

    return 0;
}
