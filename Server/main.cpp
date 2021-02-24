#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

using namespace sf;
using namespace std;

const int clientsCanJoin = 3;

vector<TcpSocket> clientsList(clientsCanJoin);
int clientsConnected = 0;

int main()
{
	TcpListener listener;
	listener.setBlocking(false);
	//SocketSelector selector;

	//selector.add(listener);

	//if (selector.wait(sf::seconds(10.f)))
	//{
	//	// received something
	//}
	//else
	//{
	//	// timeout reached, nothing was received...
	//}

	// bind the listener to a port
	while (clientsConnected < clientsCanJoin)
	{
		cout << clientsConnected << endl;
		//cout << "bam";
		if (listener.listen(53000) == Socket::Done)
		{
			if (listener.accept(clientsList[clientsConnected]) == Socket::Done)
			{
				cout << "Client " << clientsConnected << " connected" << endl;
				clientsConnected++;
			}
			else
			{
				cout << "LISTENER ACCEPT ERROR" << endl;
			}

		}
		else
		{
			cout << "LISTENER ERROR" << endl;
		}
	}
	


	

	getchar();
	return 0;
}