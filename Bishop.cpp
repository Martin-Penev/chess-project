#include "Bishop.hpp"
#include "Board.hpp"
#include <cmath>
#include <cstring>

    Bishop::Bishop(const char* pieceColor, int posX, int posY, Board* chessboard)
    : Piece("bishop", pieceColor, posX, posY, chessboard) {}

    Piece* Bishop::clone() const {
    return new Bishop(*this);
    }

    bool Bishop::move(int newX, int newY) {
    // Проверка, дали новата позиция не е извън масата
    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
        return false;
    }
    // Проверка, дали движението е диагонално
        if (abs(newX - positionX) == abs(newY - positionY)) {
            int xDir = (newX > positionX) ? 1 : -1;
            int yDir = (newY > positionY) ? 1 : -1;
            int x = positionX + xDir;
            int y = positionY + yDir;
            while (x != newX && y != newY) {
                if (board->getPieceAt(x, y) != nullptr)
                    return false; 
                x += xDir;
                y += yDir;
            }
            positionX = newX;
            positionY = newY;
            return true;
        }

        // Вземане на фигура на опонента
        if (board->getPieceAt(newX, newY) != nullptr) {
            if (strcmp(board->getPieceAt(newX, newY)->getColor() ,getColor())!=0) {
                board->removePiece(newX, newY);
                positionX = newX;
                positionY = newY;
                return true;
            }
        }
        return false;
    }
