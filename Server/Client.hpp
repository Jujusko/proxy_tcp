#pragma once

#include "Includes.hpp"

class Client
{
    private:
    int         fdClient;
    int         dbSocket;

    int         portDb;

    public:
    Client(int sockid, std::string ip, int dbPort);
     int &GetId() ;
     int &GetSocketDB() ;
    ~Client();
    
    void CheckAction(fd_set &fds);
    void RecieveMessage();
    void SendMessage();
};

