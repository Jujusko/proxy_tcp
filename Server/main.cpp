
#include "Includes.hpp"

int main(int ac, char *av[])
{
    if (ac == 4)
    {
        try
        {
            Server servr(std::stoi(av[1]), av[2], std::stoi(av[3]));
            servr.SetUpServer();
            servr.ServerWorking();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    std::cerr << "proxy port, ip, database port" << std::endl;
}