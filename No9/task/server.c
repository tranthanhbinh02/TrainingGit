#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int listenfd = -1;
    int connfd = -1;
    struct sockaddr_in server_addr;
    char recv_buffer[1024];

    // Initialize buffer
    memset(recv_buffer, 0, sizeof(recv_buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    // Create socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000);

    // Bind socket to address
    if (bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(listenfd, 3) < 0) {
        perror("listen failed");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 5000...\n");

    while (1) {
        // Accept incoming connection
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        if (connfd < 0) {
            perror("accept failed");
            continue;
        }

        // Read data from client
        ssize_t n = read(connfd, recv_buffer, sizeof(recv_buffer) - 1);
        if (n > 0) {
            recv_buffer[n] = '\0'; // Null-terminate the received data
            printf("Received from client: %s\n", recv_buffer);

            // Send acknowledgment to client
            const char *ack = "Message received!";
            write(connfd, ack, strlen(ack));
        }

        // Close connection
        close(connfd);
    }

    // Close listening socket
    close(listenfd);
    return 0;
}

