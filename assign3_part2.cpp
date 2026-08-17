//Assignment 3 (subnetting- part 2)
#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
using namespace std;

int main()
{
    string ip;
    char c;
    string s_octet1, s_octet2, s_octet3, s_octet4;
    int def_octet1, def_octet2, def_octet3, def_octet4;
    int subnet_octet1, subnet_octet2, subnet_octet3, subnet_octet4;
    int subnets, hosts;
    cout<<"\nEnter ip address: ";
    cin>>ip;
    cout<<"\nEnter no of subnets: ";
    cin>>subnets;
    cout<<"\nEnter no of hosts in each subnet: ";
    cin>>hosts;
    int host_bits=0;
    int subnet_bits=0;
    while(hosts>pow(2, host_bits))
    {
        host_bits++;
    }
    int max_hosts=pow(2, host_bits)-2;
    cout<<"\nMaximum total no of hosts per subnet = "<<max_hosts;
    while(subnets>pow(2, subnet_bits))
    {
        subnet_bits++;
    }
    stringstream ss(ip);
    getline(ss, s_octet1, '.');
    getline(ss, s_octet2, '.');
    getline(ss, s_octet3, '.');
    getline(ss, s_octet4, '.');
    int octet1=stoi(s_octet1);
    int octet2=stoi(s_octet2);
    int octet3=stoi(s_octet3);
    int octet4=stoi(s_octet4);
    if(octet1>=0 && octet1<=127)
    {
        c='A';
    }
    else if(octet1>=128 && octet1<=191)
    {
        c='B';
    }
    else if(octet1>=192 && octet1<=223)
    {
        c='C';
    }
    else if(octet1>=224 && octet1<=239)
    {
        c='D';
    }
    else
    {
        c='E';
    }

    switch (c)
    {
        case 'A':
        {
            def_octet1=255;
            def_octet2=0;
            def_octet3=0;
            def_octet4=0;
            subnet_octet1=255;
            if(subnet_bits+host_bits<=24)
            {
                cout<<"\nSubnetting possible";
                subnet_octet1=255;
                if(subnet_bits<=8)
                {
                    subnet_octet2=255;
                    subnet_octet3=255;
                    subnet_octet4=256-pow(2, host_bits);
                }
                else if(subnet_bits>8 && subnet_bits<=16)
                {
                    subnet_octet3=256-pow(2, host_bits-8);
                    subnet_octet4=0;
                }
                else
                {
                    subnet_octet2=256-pow(2, host_bits-16);
                    subnet_octet3=0;
                    subnet_octet4=0;
                }
            }
            break;
        }
        case 'B':
        {
            def_octet1=255;
            def_octet2=255;
            def_octet3=0;
            def_octet4=0;
            if(subnet_bits+host_bits<=16)
            {
                cout<<"\nSubnetting possible";
                subnet_octet1=255;
                subnet_octet2=255;
                if(subnet_bits<=8)
                {
                    subnet_octet3=255;
                    subnet_octet4=256-pow(2, host_bits);
                }
                else
                {
                    subnet_octet3=256-pow(2, host_bits-8);
                    subnet_octet4=0;
                }
            }
            break;
        }
        case 'C':
        {
            def_octet1=255;
            def_octet2=255;
            def_octet3=255;
            def_octet4=0;
            if(subnet_bits+host_bits<=8)
            {
                cout<<"\nSubnetting possible";
                subnet_octet1=255;
                subnet_octet2=255;
                subnet_octet3=255;
                subnet_octet4=256-pow(2, host_bits);
            }
            break;
        }
    }
    int network_octet;
    int first_ip;
    int last_ip;
    int broadcast;
    for(int i=0; i<subnets; i++)
    {
        if(i==0)
        {
            network_octet=0;
            first_ip=network_octet+1;
            last_ip=network_octet+max_hosts;
            broadcast=network_octet+max_hosts+1;
        }
        cout<<"\n--------Subnet="<<i<<"--------";
        if(c=='A')
        {
            cout<<"\nNetwork address= "
                <<octet1<<"."
                <<network_octet<<"."
                <<octet3<<"."
                <<octet4;
            cout<<"\nFirst ip= "
                <<octet1<<"."
                <<first_ip<<"."
                <<octet3<<"."
                <<octet4;
            cout<<"\nLast ip= "
                <<octet1<<"."
                <<last_ip<<"."
                <<octet3<<"."
                <<octet4;
            cout<<"\nBroadcast address= "
                <<octet1<<"."
                <<broadcast<<"."
                <<octet3<<"."
                <<octet4;
        }
        else if(c=='B')
        {
            cout<<"\nNetwork address= "
                <<octet1<<"."
                <<octet2<<"."
                <<network_octet<<"."
                <<octet4;
            cout<<"\nFirst ip= "
                <<octet1<<"."
                <<octet2<<"."
                <<first_ip<<"."
                <<octet4;
            cout<<"\nLast ip= "
                <<octet1<<"."
                <<octet2<<"."
                <<last_ip<<"."
                <<octet4;
            cout<<"\nBroadcast address= "
                <<octet1<<"."
                <<octet2<<"."
                <<broadcast<<"."
                <<octet4;
        }
        else if(c=='C')
        {
            cout<<"\nNetwork address= "
                <<octet1<<"."
                <<octet2<<"."
                <<octet3<<"."
                <<network_octet;
            cout<<"\nFirst ip= "
                <<octet1<<"."
                <<octet2<<"."
                <<octet3<<"."
                <<first_ip;
            cout<<"\nLast ip= "
                <<octet1<<"."
                <<octet2<<"."
                <<octet3<<"."
                <<last_ip;
            cout<<"\nBroadcast address= "
                <<octet1<<"."
                <<octet2<<"."
                <<octet3<<"."
                <<broadcast;
        }
        network_octet=network_octet+pow(2, host_bits);
        first_ip=first_ip+pow(2, host_bits);
        last_ip=last_ip+pow(2, host_bits);
        broadcast=broadcast+pow(2, host_bits);
    }
    return 0;
}
