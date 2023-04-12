#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")

#include<iostream>
#include<WinSock2.h>
#include<string>

int main()
{
    std::cout<<"Creating a server"<<std::endl;
    SOCKET wsocket;
    SOCKET new_wsocket;
    WSADATA wsaData;
    struct sockaddr_in server;
    int server_len;
    int BUFFER_SIZE = 30720;

    ///initialize
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {

        std::cout<<"couldnt initialize the server";
    }

    ///create a socket
    wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(wsocket == INVALID_SOCKET){
        std::cout<<"could'nt create socket";
    }

    ///bind socket to address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8000);
    server_len = sizeof(server);

    if(bind(wsocket, (SOCKADDR *)&server, server_len) != 0)
    {
        std::cout<<"Could not bind socket";
    }

    ///listen to address
    if(listen(wsocket,10)!=0)
    {
        std::cout<<" Could not start listening\n";
    }

    std::cout<<"Listening on 127.0.0.1:8000\n";

    while(true)
    {

        new_wsocket = accept(wsocket, (SOCKADDR *)&server, &server_len);
        if(new_wsocket == INVALID_SOCKET){
           std::cout<<"Could not accept \n";
        }

        ///read request
        char buff[30720] = {0};
        int bytes = recv(new_wsocket, buff, BUFFER_SIZE,0);
        if(bytes<0){
            std::cout<<"Could not read Client request  ";
        }
        std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
        std::string responce = "<html><h1>Hello world</h1></html>";
        serverMessage.append(std::to_string(responce.size()));
        serverMessage.append("\n\n");
        serverMessage.append(responce);

        int bytesSent =0;
        int totalBytesSent = 0;
        while(totalBytesSent < serverMessage.size()){
            bytesSent = send(new_wsocket, serverMessage.c_str(),serverMessage.size(),0);
            if(bytesSent <0){
                std::cout<<"Could not send responce  ";
            }
            totalBytesSent+=bytesSent;
        }
        std::cout<<"Sent responce to Client  \n";
        closesocket(new_wsocket);
    }
    closesocket(wsocket);
    WSACleanup();
    return 0;
}
