#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFF_LEN 4096

int main()
{
    int sock;
    struct hostent *server;
    struct sockaddr_in serv_addr;

    char request[] =
        "GET /posts/1 HTTP/1.1\r\n"
        "Host: jsonplaceholder.typicode.com\r\n"
        "Connection: close\r\n\r\n";

    char resp_buff[BUFF_LEN];

    // Resolve host
    server = gethostbyname("jsonplaceholder.typicode.com");
    if (!server) {
        printf("Error resolving host\n");
        return EXIT_FAILURE;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80); // HTTP port
    memcpy(&serv_addr.sin_addr.s_addr,
           server->h_addr,
           (size_t)server->h_length);

    // Connect
    if (connect(sock,
                (struct sockaddr*)&serv_addr,
                sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return EXIT_FAILURE;
    }

    // Send request
    send(sock, request, strlen(request), 0);

    // Read response
    size_t n;
    while ((n = (size_t)read(sock, resp_buff, sizeof(resp_buff) - 1)) > 0) {
        resp_buff[n] = '\0';
        printf("%s", resp_buff);
    }

    close(sock);
    return EXIT_SUCCESS;
}
