#include "King.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include <cmath>
#include <cstring>

   King::King(const char* pieceColor, int posX, int posY, Board* chessboard)
    : Piece("king", pieceColor, posX, posY, chessboard) {}

    Piece* King::clone() const {
    return new King(*this);
}
    bool King::canMoveTo(int newX, int newY)
    {
        int dx = abs(newX - positionX);
        int dy = abs(newY - positionY);
        return (dx <= 1 && dy <= 1);
    }

    bool King::move(int newX, int newY)  {
        // проверка дали фигурата е извън дъската
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
            return false;
     

        // проверка на валидността на движението
        if ( abs(newX - positionX)<= 1 && abs(newY - positionY) <= 1) {
            Piece* destinationPiece = board->getPieceAt(newX, newY);

            if (destinationPiece == nullptr ||strcmp( destinationPiece->getColor() , getColor())!=0) {
                if (destinationPiece != nullptr) {
                    board->removePiece(newX, newY);
                    Game::moveCount = -1;
                }
                positionX = newX;
                positionY = newY;
                board->setKingMoved(color);
                
                return true;
            }
        }
        if (abs(newX - positionX) == 2 && abs(newY - positionY) == 0) {
        if (board->canCastle(color, newX, newY)) {
            // движение на краля
            positionX = newX;
            positionY = newY;
            board->setKingMoved(color);

            // движение на топа
            if (newX == 6) {
                board->placePiece(board->getPieceAt(7, positionY), 5, positionY);
                board->removePiece(7, positionY);
            } else if (newX == 2) {
                board->placePiece(board->getPieceAt(0, positionY), 3, positionY);
                board->removePiece(0, positionY);
            }
            
            return true;
        }
    }

        
        return false;
    }

