#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <exception>
#include <algorithm>
#include <string>
#include <iomanip>
#include <utility>
#include <signal.h>
#include <stdexcept>
#include <fstream>

#include "Server.hpp"
#include "Client.hpp"

#undef MAX
#define MAX(x,y) ((x) > (y) ? (x) : (y))

#define BUFFER_SIZE 512

int     Socket(int domain, int type, int protocol);
void    Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void    FillSockaddr(sockaddr_in &adr, int port);
int     Listen(int sockfd, int backlog);
int     Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int     Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void    InetAton(const char *cp, struct in_addr *inp);
void    AddQueryToLog(char *str, ssize_t symbols);