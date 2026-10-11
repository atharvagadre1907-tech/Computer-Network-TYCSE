
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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
    int sockfd;
    string buffer;

    struct sockaddr_in servaddr;

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // Set server IP address
    if (inet_pton(AF_INET, "127.0.0.1",
                  &servaddr.sin_addr) <= 0)
    {
        perror("Invalid server address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr,
                sizeof(servaddr)) < 0)
    {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    cout << "Connected to TCP Server!" << endl;

    while (true)
    {
        // Client takes input
        cout << "Client: ";
        if (!getline(cin, buffer))
            break;

        // Send message to server
        if (!Chat::sendMessage(sockfd, buffer))
        {
            perror("Send failed");
            break;
        }

        // Receive server response
        if (!Chat::receiveMessage(sockfd, buffer))
        {
            cout << "Server disconnected." << endl;
            break;
        }

        cout << "Server: " << buffer << endl;

        // If either side says bye
        if (buffer == "bye")
        {
            cout << "Communication ended." << endl;
            break;
        }
    }

    close(sockfd);

    return 0;
}
