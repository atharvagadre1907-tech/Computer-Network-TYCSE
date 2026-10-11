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
    void sendMessage(SOCKET sockfd, char message[100])
    {
        send(sockfd, message, strlen(message), 0); //0=default sending behavior
    }
    void receiveMessage(SOCKET sockfd, char message[100])
    {
        int n = recv(sockfd, message, 99, 0);

        if(n>0)
        {
            message[n]='\0';
        }
    }
};

int main()
{
    //Step 1: Initialize winsock using WSAStartup before program can use its socket functions
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa); 
    //Step 2: Create a socket
    SOCKET sockfd; //SOCKET is a datatype defined by Windows Winsock library. sockfd is a file descriptor used to listen for incoming connections and connfd is a file descriptor used to store new socket created during accept()
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //socket() creates a socket and returns file descriptor which is stored in sockfd. 
    //AF_INET = specifies IPv4 family, SOCK_STREAM = specifies a stream socket used in TCP communication, IPPROTO_TCP = specifies TCP as the protocol

    if (sockfd == INVALID_SOCKET)
    {
        cout<<"\nSocket creation failed";
        return 1;
    }

    //Step 3: Declare server and client addresses as instances of the structure socketaddr_in which has info like ipv4 address, port no, etc.
    sockaddr_in serverAddr, clientAddr;
    serverAddr = {};
    clientAddr = {}; //initialize both of them to empty to avoid garbage addresses

     //Step 4: Configure server's IP address settings and port number before server starts listening 
     serverAddr.sin_family = AF_INET;
     serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Use your server's IP address
     serverAddr.sin_port = htons(port); //htons(host to network short) converts the port number from host byte order to the standardized network byte order (big-endian), so it is interpreted consistently across machines.

     //Step 5: Connect the socket with IP address and port no
     if (connect(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //bind() needs file descriptor, the address to bind to, size of the address structure
     {
        cout<<"\nConnection failed";
        return 1;
     }

     //Step 6: Chat
     char buffer[100]; //receive from client and send to client
     Chat c1;
     while(true)
     {
        cout<<"\nClient: ";
        cin.getline(buffer, 100);
        c1.sendMessage(sockfd, buffer);
        if(strcmp(buffer, "bye")==0)
        {
            cout<<"\nClient ended the communication!";
            break;
        }
        c1.receiveMessage(sockfd, buffer);
        cout<<"\nServer: "<<buffer;
        if (strcmp("bye", buffer)==0)
        {
            cout<<"\nServer ended communication!";
            break;
        }
     }
     return 0;
}