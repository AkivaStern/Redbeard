#include "GameController.h"
#include <fstream>


int main()
{
    try {
        
        GameController game;
        game.run();
    }

    catch (std::exception& e)
    {
        std::ofstream of("LOG.txt");
        of << e.what();
    }

    return EXIT_SUCCESS;
}
