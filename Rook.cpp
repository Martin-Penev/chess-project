#include "Rook.hpp"
#include "Board.hpp"
#include <cstring>
    
    Rook::Rook(const char* pieceColor, int posX, int posY,Board* chessboard) 
    : Piece("rook", pieceColor, posX, posY,chessboard){}

    Piece* Rook::clone() const {
    return new Rook(*this);
}
    
    bool Rook::move(int newX, int newY) {
    // Проверка, дали новата позиция не е извън масата
    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
        return false;
    }

     // Проверка, дали позицията е свободна
    if (board->getPieceAt(newX, newY) == nullptr) {
        
        if (newY == positionY && newX != positionX) {
            // Проверка, дали по пътя до съответната позиция няма фигура, която да я блокира
            int step = (newX > positionX) ? 1 : -1;
            for (int x = positionX + step; x != newX; x += step) {
                if (board->getPieceAt(x, newY) != nullptr) {
                    return false; 
                }
            }
            
            positionX = newX;
            positionY = newY;
            return true;
        }
        if (newX == positionX && newY != positionY) {       
            int step = (newY > positionY) ? 1 : -1;
            for (int y = positionY + step; y != newY; y += step) {
                if (board->getPieceAt(newX, y) != nullptr) {
                    return false; 
                }
            }
            positionX = newX;
            positionY = newY;
            return true;
        }
    }
     else {
        // Вземане на фигура на опонента
        if (strcmp(board->getPieceAt(newX, newY)->getColor() , color)!=0) {
            board->removePiece(newX, newY);
            positionX = newX;
            positionY = newY;
            return true;
        }
    }

    
    return false;
}