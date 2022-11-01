#include "Includes.hpp"

Server::Server(int port, std::string ip, int portDb)
{
    this->port = port;
    dbPort = portDb;
    ipAddress = ip;

}

Server::~Server()
{
    for(std::vector<Client *>::iterator user = users.begin(); user != users.end(); user++)
    {
        delete(*user);
    }
    
    users.clear();
    close(servSocket);
}

void Server::SetUpServer()
{
    struct sockaddr_in  adr;

    servSocket = Socket(AF_INET, SOCK_STREAM, 0);
    
    
    FillSockaddr(adr, port);
    Bind(servSocket, (struct sockaddr *) &adr, sizeof adr);
    fcntl(servSocket, F_SETFL, O_NONBLOCK);

    maxFD = servSocket;
    Listen(servSocket, 5);
}

void Server::ServerWorking()
{
    std::cout << "Server created on port "<< port <<std::endl;
    ssize_t readstr;

    FD_ZERO(&fdRead);
    FD_SET(servSocket, &fdRead);

    fd_set fdReadCopy;

    while (true)
    {
        fdReadCopy = fdRead;
        select(maxFD + 1, &fdReadCopy, NULL, NULL, NULL);

        if (FD_ISSET(servSocket, &fdReadCopy))
        {
            ConnectNewUser();
        }
        for(std::vector<Client *>::iterator user = users.begin(); user != users.end(); user++)
        {
            try
            {
                (*user)->CheckAction(fdReadCopy);
            }
            catch(int id)
            {
                FD_CLR((*user)->GetId(), &fdRead);
                FD_CLR((*user)->GetSocketDB(), &fdRead);

                user = users.erase(user);
                std::cout << "user quit." << std::endl;
                delete (*user);
            }
            catch (std::exception &e)
            {
                throw e; 
            }
            if (user == users.end())
            {
                break;
            }
        }
    }
}

void Server::ConnectNewUser()
{
    int newFd = Accept(servSocket, NULL, NULL);
    Client *newClient = new Client(newFd, ipAddress, dbPort);
    
    users.push_back(newClient);

    fcntl(newFd, F_SETFL, O_NONBLOCK);
    FD_SET(newFd, &fdRead);
    FD_SET(newClient->GetSocketDB(), &fdRead);
    
    maxFD = MAX(maxFD, MAX(newClient->GetId(), newClient->GetSocketDB()));
    std::cout << "new user connected." << std::endl;
}