/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** main
*/

#include <iostream>
#include <thread>
#include "Server.hpp"

int main(int argc, char * const *argv)
{
	Server server(1111);
	std::thread t(&Server::run, &server);
	t.join();
	return EXIT_SUCCESS;
}