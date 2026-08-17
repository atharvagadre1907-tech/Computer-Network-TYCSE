//Assignment 3 (subnet masks for each class- part1 1)
#include <iostream>
using namespace std;
int main()
{
    char class_type;
    string ip_add;
    int first_octet=0;
    int converted;
    cout<<"\nEnter IP address: ";
    cin>>ip_add;
    int len=ip_add.length();
    int i=0;
    while(ip_add[i]!='.')
    {
        converted=ip_add[i]-'0';
        first_octet=converted+(first_octet*10);
        i++;
    }
    cout<<"\nThe first octet obtained is: "<<first_octet;
    if(first_octet>=0&&first_octet<=127)
    {
        class_type='A';
    }
    else if(first_octet>=128&&first_octet<=191)
    {
        class_type='B';
    }
    else if(first_octet>=192&&first_octet<=223)
    {
        class_type='C';
    }
    else if(first_octet>=192&&first_octet<=223)
    {
        class_type='D';
    }
    else
    {
        class_type='E';
    }
    //definition of subnet and subnet masking
    cout<<"\nSubet: Small network created by diving a large network into multiple smaller networks.";
    cout<<"\nSubnet mask: It is a 32-bit number used to identify which part of address represents Network Id and Host Id.";
    cout<<"\nNo of networks=2^(no of network bits available)";
    switch (class_type)
    {
        case 'A':
        {
            cout<<"\n\nClass= A\nFirst Octet decimal range=0-127\nIP range=0.0.0.0-255.255.255.255\nSubnet mask=255.0.0.0\nHosts per network ID=2^24-2 ()\nNo of networks=2^7";
            cout<<"\nLoopback address: It is a special IP address used by computer to communicate with itself. It is mainly used for testing and troubleshooting TCP/IP protocol stack without sending data over physical network. Eg- 127.0.0.0-127.255.255.255";
            break;
        }
        case 'B':
        {
            cout<<"\n\nClass= B\nFirst Octet decimal range=128-191\nIP range=128.0.0.0-191.255.255.255\nSubnet mask=255.255.0.0\nHosts per network ID=2^16-2 ()\nNo of networks=2^14";
            break;
        }
        case 'C':
        {
            cout<<"\n\nClass= C\nFirst Octet decimal range=192-223\nIP range=192.0.0.0-223.255.255.255\nSubnet mask=255.255.255.0\nHosts per network ID=2^8-2 ()\nNo of networks=2^21";
            break;
        }
        case 'D':
        {
            cout<<"\n\nClass= D\nFirst Octet decimal range=224-239\nIP range=224.0.0.0-239.255.255.255\nSubnet mask=\nHosts per network ID=\nNo of networks=";
            break;
        }
        case 'E':
        {
            cout<<"\n\nClass= E\nFirst Octet decimal range=240-255\nIP range=240.0.0.0-225.255.255.255\nSubnet mask=\nHosts per network ID=\nNo of networks=";
            break;
        }
    }
    return 0;
}
