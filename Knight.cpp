#include <cmath>
#include "Knight.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include <cstring>

    Knight::Knight(const char* pieceColor, int posX, int posY,Board* chessboard) 
    : Piece("knight", pieceColor, posX, posY,chessboard){}

    Piece* Knight::clone() const {
        return new Knight(*this);
    }
    bool Knight::canMoveTo(int newX, int newY)  {
    int dx = abs(newX - positionX);
    int dy = abs(newY - positionY);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }
    bool Knight::move(int newX, int newY)  {
        // Проверка, дали новата позиция не е извън масата
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
            return false;
        }
       

        // движение г-образно движение
        if ((abs(newX - positionX) == 2 && abs(newY - positionY) == 1) || (abs(newX - positionX) == 1 && abs(newY - positionY) == 2)) {
            Piece* destinationPiece = board->getPieceAt(newX, newY);

            if (destinationPiece == nullptr || strcmp(destinationPiece->getColor(), getColor())!=0) {
                // логика за вземане на фигура
                if (destinationPiece != nullptr) {
                    board->removePiece(newX, newY);
                    Game::moveCount = -1;
                }
                
                positionX = newX;
                positionY = newY;
                return true;
            }
        }

        
        return false;
    
    }
