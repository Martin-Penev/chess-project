#include "King.hpp"
#include "Board.hpp"
#include <cmath>
#include <cstring>


   King::King(const char* pieceColor, int posX, int posY, Board* chessboard)
    : Piece("king", pieceColor, posX, posY, chessboard) {}

    Piece* King::clone() const {
    return new King(*this);
    }

    bool King::move(int newX, int newY)  {
        // Проверка, дали новата позиция не е извън масата
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
            return false;
     

        // Проверка дали се движи с по едно квадратче 
        if ( abs(newX - positionX)<= 1 && abs(newY - positionY) <= 1) {
            Piece* destinationPiece = board->getPieceAt(newX, newY);

            if (destinationPiece == nullptr || strcmp(destinationPiece->getColor() , getColor())!=0) {
                //вземане на фигура на опонента
                if (destinationPiece != nullptr) {
                    board->removePiece(newX, newY);
                }
                positionX = newX;
                positionY = newY;
                return true;
            }
        }
        
        
        return false;
    }
