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
    int sockfd = -1;
    struct sockaddr_in server_addr;
    char send_buffer[1024];
    char recv_buffer[1024];

    // Initialize buffers
    memset(send_buffer, 0, sizeof(send_buffer));
    memset(recv_buffer, 0, sizeof(recv_buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Prompt user for input
    printf("Enter a word to send to the server: ");
    fgets(send_buffer, sizeof(send_buffer), stdin);

    // Remove newline character from fgets
    send_buffer[strcspn(send_buffer, "\n")] = 0;

    // Send data to server
    write(sockfd, send_buffer, strlen(send_buffer));

    // Receive data from server
    read(sockfd, recv_buffer, sizeof(recv_buffer) - 1);
    printf("Received from server: %s\n", recv_buffer);

    // Close socket
    close(sockfd);
    return 0;
}

