#pragma once
#include "Includes.hpp"
class Client;

class Server
{
    private:
    std::vector<Client *> users;
    int                 bindedSocket;
    int                 servSocket;
    int                 port;
    std::string         ipAddress;

    int                 maxFD;
    fd_set              fdRead;
    int                 dbSocket;
    
    int                 dbPort;

    public:

    Server(int port, std::string ip, int portDb);
    void SetUpServer();
    void ServerWorking();
    void ConnectNewUser();

    ~Server();
};