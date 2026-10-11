#include<iostream>
#include<string>
#include<cstring>
#include<winsock2.h>
#include<ws2tcpip.h>
#define port 8080

using namespace std;

class Chat
{
    public:
    void sendMessage(SOCKET sockfd, char message[100],
                     sockaddr_in serverAddr)
    {
        sendto(sockfd, message, strlen(message), 0,
               (sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    void receiveMessage(SOCKET sockfd, char message[100],
                        sockaddr_in &serverAddr, int &len)
    {
        int n = recvfrom(sockfd, message, 99, 0,
                         (sockaddr*)&serverAddr, &len);

        if(n > 0)
            message[n] = '\0';
        else
            message[0] = '\0';
    }
};

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sockfd;
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(sockfd == INVALID_SOCKET)
    {
        cout << "\nSocket creation failed";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr = {};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(port);

    char buffer[100];
    int len = sizeof(serverAddr);
    Chat c1;

    while(true)
    {
        cout << "\nClient: ";
        cin.getline(buffer, 100);

        c1.sendMessage(sockfd, buffer, serverAddr);

        if(strcmp(buffer, "bye") == 0)
        {
            cout << "\nClient ended communication!";
            break;
        }

        c1.receiveMessage(sockfd, buffer, serverAddr, len);

        cout << "\nServer (lowercase): " << buffer;
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}