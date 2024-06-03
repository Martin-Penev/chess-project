#include "Game.hpp"
#include <iostream>

int main() {
    Game game;
    game.printBoard();

    int startX, startY, endX, endY;
    while (true) {
        if (game.isEndOfTheGame()) {
            break;
        }
        
        std::cout <<" (-1 -1 -1 -1) - suggestDraw\n";
        std::cout <<" (9 9 9 9) - resign\n";
        std::cout << "Enter the start and end positions (e.g., 1 1 2 2): ";

        
        std::cin >> startX >> startY >> endX >> endY;

        if (!(int)startX || !(int)startY || !(int)endX || !(int)endY) {
            std::cout << "Invalid input!" << std::endl;
            return 0;
        }
        
        if (startX == -1 && startY == -1 && endX == -1 && endY == -1) {
            if (game.suggestDraw()) {
                std::cout << "Draw agreed. Game over." << std::endl;
                break;
            } else {
                std::cout << "Draw rejected. Continue playing." << std::endl;
            }
        }
        if(startX ==9 && startY == 9 && endX == 9 && endY == 9)
        {
            if(game.resign())
            {
                std::cout<< "Game over.";
                break;
            }

        }
         else {
                game.movePiece(startX - 1, startY - 1, endX - 1, endY - 1);
                game.printBoard();
            
        }
    }

    return 0;
}