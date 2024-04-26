#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

    // 1.1 - Open an HTML file and read it into our application
    FILE *html_data;
    html_data = fopen("index.html", "r");

    if (html_data == NULL) {
        perror("Failed to open HTML file");
        exit(EXIT_FAILURE);
    }

    char html_response[1024];
    fgets(html_response, 1024, html_data);
    fclose(html_data);

    // 1.3 - Create the HTTP response header
    char http_header[2048] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\n"; // Response header for HTML
    strcat(http_header, html_response);

    // 2.1 - Create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2.2 - Define the Address: It defines where our server is going to serve the data
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000); // Port Number = 9000
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;

    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }

    return 0;
}