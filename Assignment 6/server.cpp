#include<iostream>
#include<string>
#include<cstring>
#include<cctype>
#include<winsock2.h>
#include<ws2tcpip.h>
#define port 8080

using namespace std;

class Chat
{
    public:
    void sendMessage(SOCKET sockfd, char message[100],
                     sockaddr_in clientAddr, int len)
    {
        sendto(sockfd, message, strlen(message), 0,
               (sockaddr*)&clientAddr, len);
    }

    void receiveMessage(SOCKET sockfd, char message[100],
                        sockaddr_in &clientAddr, int &len)
    {
        int n = recvfrom(sockfd, message, 99, 0,
                         (sockaddr*)&clientAddr, &len);

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

    sockaddr_in serverAddr = {}, clientAddr = {};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if(bind(sockfd, (sockaddr*)&serverAddr,
            sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "\nBind failed";
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    cout << "\nServer started...";
    cout << "\nWaiting for the client...";

    char buffer[100];
    int len = sizeof(clientAddr);
    Chat c1;

    while(true)
    {
        c1.receiveMessage(sockfd, buffer, clientAddr, len);

        cout << "\nClient: " << buffer;

        if(strcmp(buffer, "bye") == 0)
        {
            cout << "\nClient ended communication!";
            break;
        }

        for(int i = 0; buffer[i] != '\0'; i++)
            buffer[i] = tolower((unsigned char)buffer[i]);

        cout << "\nLowercase message: " << buffer;

        c1.sendMessage(sockfd, buffer, clientAddr, len);
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}