
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 8080
#define MAXLINE 1024

// Class for sending and receiving messages
class Chat
{
public:
    static bool sendMessage(int sockfd, string message)
    {
        message += '\n';
        const char *data = message.c_str();
        size_t total = 0;
        size_t length = message.length();

        while (total < length)
        {
            ssize_t n = send(sockfd, data + total,
                             length - total, 0);

            if (n <= 0)
                return false;

            total += n;
        }

        return true;
    }

    static bool receiveMessage(int sockfd, string &message)
    {
        message.clear();
        char ch;

        while (message.length() < MAXLINE - 1)
        {
            ssize_t n = recv(sockfd, &ch, 1, 0);

            if (n <= 0)
                return false;

            if (ch == '\n')
                return true;

            message += ch;
        }

        return true;
    }
};

int main()
{
    int sockfd, connfd;
    string buffer;

    struct sockaddr_in servaddr, cliaddr;

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind socket to the port
    if (bind(sockfd, (struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Listen for client connections
    if (listen(sockfd, 5) < 0)
    {
        perror("Listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    cout << "TCP Server started..." << endl;
    cout << "Waiting for client..." << endl;

    socklen_t len = sizeof(cliaddr);

    // Accept client connection
    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);

    if (connfd < 0)
    {
        perror("Accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    cout << "Client connected!" << endl;

    while (true)
    {
        // Receive message from client
        if (!Chat::receiveMessage(connfd, buffer))
            break;

        cout << "Client: " << buffer << endl;

        // If client says bye
        if (buffer == "bye")
        {
            Chat::sendMessage(connfd, "bye");
            cout << "Client ended communication." << endl;
            break;
        }

        // Server takes input
        cout << "Server: ";
        if (!getline(cin, buffer))
            break;

        // Send response to client
        if (!Chat::sendMessage(connfd, buffer))
        {
            perror("Send failed");
            break;
        }

        // If server says bye
        if (buffer == "bye")
        {
            cout << "Server ending communication..." << endl;
            break;
        }
    }

    close(connfd);
    close(sockfd);

    return 0;
}