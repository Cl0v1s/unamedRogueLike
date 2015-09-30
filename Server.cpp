#include "Server.h"

Server::Server(const unsigned int port)
{
    _port = port;
    try
    {
        _listener = new UDPSocket(port);
    }
    catch(SocketException &e)
    {
        assert("Impossible d'ouvrir le socket.");
    }
    _clients = 0;
}

void Server::waitForClients()
{
    char msg[NETWORK_MAX_BUFFER + 1]; // Buffer for echo string + \0
    std::string sourceAddress;              // Address of datagram source
    unsigned short sourcePort;         // Port of datagram source
    int length = sock.recvFrom(msg, NETWORK_MAX_BUFFER, sourceAddress,
                                  sourcePort); //on récupère le mot de connexion
    msg[length] = '\0';
    if(msg == "ready to rock!")
     {
         cout << ok << endl;
     }

  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

Server::~Server()
{

}
