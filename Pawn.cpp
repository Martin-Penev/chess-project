#include "Pawn.hpp"
#include "Board.hpp"
#include <iostream>
#include <cmath>
#include <cstring>

    Pawn::Pawn(const char* pieceColor, int posX, int posY,Board* chessboard) 
    : Piece("pawn", pieceColor, posX, posY,chessboard) {}

    Piece* Pawn::clone() const {
    return new Pawn(*this);
    }
    
    bool Pawn::move(int newX, int newY) {
    // Проверка, дали новата позиция не е извън масата
    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
        return false;

    int forwardDirection = (strcmp(color, "white") == 0) ? 1 : -1;
    
    // Проверка, дали позицията е свободна
    if (board->getPieceAt(newX, newY) == nullptr) {
        if (newX == positionX && newY == positionY + forwardDirection) {
            positionX = newX;
            positionY = newY;

            return true;
        }
        if ((strcmp(color, "white") == 0 && positionY == 1 && newY == 3) || (strcmp(color, "black") == 0 && positionY == 6 && newY == 4)) {
            if (newX == positionX && newY == positionY + 2 * forwardDirection) {
                positionX = newX;
                positionY = newY;
                return true;
            }
        }
    }
        // Вземане на фигура на опонента
        if (abs(newX - positionX) == 1 && newY == positionY + forwardDirection) {
             if (strcmp(board->getPieceAt(newX, newY)->getColor() ,getColor())!=0) {
                board->removePiece(newX, newY);
                positionX = newX;
                positionY = newY;
                 return true;
            }
        }
     
        return false;
    }