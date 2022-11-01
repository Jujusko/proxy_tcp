#include "Includes.hpp"

Client::Client(int id, std::string ip, int port)
{
    struct sockaddr_in  adr;

    fdClient = id;

    dbSocket = Socket(AF_INET, SOCK_STREAM, 0);

    
    FillSockaddr(adr, port);
    InetAton(ip.c_str(), &adr.sin_addr);
    Connect(dbSocket, (struct sockaddr *)&adr, sizeof adr);
    fcntl(dbSocket, F_SETFL, O_NONBLOCK);

}

 int &Client::GetId()
{
    return this->fdClient;
}

 int &Client::GetSocketDB() 
{
    return this->dbSocket;
}

Client::~Client()
{
}


void Client::CheckAction(fd_set &rfds)
{
    if (FD_ISSET(fdClient, &rfds))
    {
        SendMessage();
    }
    if (FD_ISSET(dbSocket, &rfds))
    {
        RecieveMessage();
    }
    
}

void Client::RecieveMessage()
{
    char buf[BUFFER_SIZE] = { 0 };
    ssize_t nread;

    nread = recv(dbSocket, buf, BUFFER_SIZE - 1, MSG_NOSIGNAL);
    if (nread == -1)
    {
        throw std::runtime_error(std::string("Recv: ") + strerror(errno));
    }
    send(fdClient, buf, nread, 0);
}

void Client::SendMessage()
{
    char buf[BUFFER_SIZE] = { 0 };
    ssize_t nread;

    try
    {
        nread = recv(fdClient, buf, BUFFER_SIZE - 1, MSG_NOSIGNAL);
        if (nread == -1)
        {
            throw std::runtime_error(std::string("Recv: ") + strerror(errno));
        }
        else if (nread == 0)
        {
            throw fdClient;
        }
        AddQueryToLog(buf, nread);    
        send(dbSocket, buf, nread, 0);
    }
    catch(const std::exception& e)
    {
        throw fdClient;
    }
}