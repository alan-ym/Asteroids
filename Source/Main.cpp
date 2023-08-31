#include "Game.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
	try
	{
		Game game;
		game.run();
	}
	catch (const std::runtime_error& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}
