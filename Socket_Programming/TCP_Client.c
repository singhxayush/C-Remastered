#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main() {

    system("clear");

    //Section: 1 - Create a socket
    // AF_INET (Address Family Internet) - AF_INET is used to specify that the socket will use IPv4 addresses.
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);


    //Section: 2 - Specify and address for the socket to connect
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    if(connection_status == -1) {
        printf("\n\033[1;31mERROR:\033[0m Connection Unsuccessful to the remote socket\n");
        return 0;
    }
    else {
        printf("\n\033[1;32mSUCCESS:\033[0m Connection successful to the remote socket\n");
    }


    //Section: 3 - Receiving data from the server
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // Print the data
    printf("\nSERVER_RESPONSE: %s\n", server_response);

    // Close the socket
    close(network_socket);

    return 0;
}