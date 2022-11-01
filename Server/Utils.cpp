#include "Includes.hpp"

int Socket(int domain, int type, int protocol)
{
    int res = socket(domain, type, protocol);

    if (res == -1)
    {
        throw std::runtime_error(std::string("Socket: ") + strerror(errno));
    }

    int a = 1;
    setsockopt(res, SOL_SOCKET, SO_REUSEADDR, &a,
     (socklen_t)sizeof (a));
        
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int res = bind(sockfd, addr, addrlen);
    if (res == -1)
    {
        throw std::runtime_error(std::string("Socket error: ") + strerror(errno));
    }
}

void FillSockaddr(sockaddr_in &adr, int port)
{
    bzero(&adr, sizeof adr);
    
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
}

int Listen(int sockfd, int backlog)
{
    int res = listen(sockfd, backlog);
    if (res == -1)
    {
        throw std::runtime_error(std::string("Listen error: ") + strerror(errno));
    }
    return res;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int res = accept(sockfd, addr, addrlen);
    if (res == -1)
    {
        throw std::runtime_error(std::string("Accept error: ") + strerror(errno));
    }
    return res;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int res = connect(sockfd, addr, addrlen);
    if (res == -1)
    {
        throw std::runtime_error(std::string("Connect error: ") + strerror(errno));
    }
    return res;
}

void InetAton(const char *cp, struct in_addr *inp)
{
    if (inet_aton(cp, inp) == -1)
    {
        throw std::runtime_error(std::string("inet_aton: ") + strerror(errno));
    }
}

void AddQueryToLog(char *str, ssize_t symbols)
{
	std::ofstream logFile;
	logFile.open("log.txt", std::ios::app);
	if (!logFile.is_open())
    {
		throw std::runtime_error(std::string("log.txt: ") + strerror(errno));
	}
    logFile << "------------------------------------------------------------\n";
    for (int i = 0; i < (int)symbols; i++)
    {
        if (std::isprint(str[i]) || str[i] == '\n' 
        || str[i] == '\t')
        {
            logFile << str[i];
        }
    }
    logFile << '\n';
	logFile.close();
}
