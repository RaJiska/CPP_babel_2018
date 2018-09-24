/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** main
*/

#include <iostream>
#include <thread>
#include "Server.hpp"
#include "NetworkMessage.hpp"

int main(int argc, char * const *argv)
{
	Server server(1111);
	std::thread t(&Server::run, &server);
	/*
	sleep(5);
	server.sendLol();
	*/
	t.join();
	return EXIT_SUCCESS;
}