#include "Pawn.hpp"
#include "Board.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Game.hpp"
#include <iostream>
#include <cmath>
#include <cstring>

    Pawn::Pawn(const char* pieceColor, int posX, int posY,Board* chessboard) 
    : Piece("pawn", pieceColor, posX, posY,chessboard) {}

    Piece* Pawn::clone() const {
    return new Pawn(*this);
    }
    bool Pawn::canMoveTo(int newX,int newY){
        int forwardDirection = (strcmp(color, "white") == 0) ? 1 : -1;

    // движение напред
    if (newX == positionX && newY == positionY + forwardDirection&& board->getPieceAt(newX,newY)==nullptr) {
        return true;
    }

    //  2 квадрата напред
    if(board->getPieceAt(newX,newY)==nullptr){
    if ((strcmp(color, "white") == 0 && positionY == 1 && newY == 3) ||
        (strcmp(color, "black") == 0 && positionY == 6 && newY == 4)) {
        return (newX == positionX && newY == positionY + 2 * forwardDirection);
    }}

    // взимане диагонално
    if (abs(newX - positionX) == 1 && newY == positionY + forwardDirection&&board->getPieceAt(newX,newY)!=nullptr&&strcmp(board->getPieceAt(newX,newY)->getColor(),color)!=0) {
        return true;
    }


    return false;
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
            board->setLastMove(positionX, positionY - forwardDirection, newX, newY);
            Game::moveCount = 0;
            return true;
        }
        if ((strcmp(color, "white") == 0 && positionY == 1 && newY == 3) || (strcmp(color, "black") == 0 && positionY == 6 && newY == 4)) {
            if (newX == positionX && newY == positionY + 2 * forwardDirection) {
                positionX = newX;
                positionY = newY;
                board->setLastMove(positionX, positionY - 2 * forwardDirection, newX, newY);
                Game::moveCount = 0;
                return true;
            }
        }
    }
     else {
        // Вземане на фигура на опонента
        if (abs(newX - positionX) == 1 && newY == positionY + forwardDirection) {
             if (strcmp(board->getPieceAt(newX, newY)->getColor() ,getColor())!=0) {
                board->removePiece(newX, newY);
                positionX = newX;
                positionY = newY;
                board->setLastMove(positionX - forwardDirection, positionY - forwardDirection, newX, newY);
                Game::moveCount = 0;
                return true;
            }
        }
     }
        //en-passant 
        int lastMoveFromX = board->getLastMoveFromX();
        int lastMoveFromY = board->getLastMoveFromY();
        int lastMoveToX = board->getLastMoveToX();
        int lastMoveToY = board->getLastMoveToY();
        Piece* lastMovedPiece = board->getPieceAt(lastMoveToX, lastMoveToY);

    if (abs(newX - positionX) == 1 && newY == positionY + forwardDirection &&
        lastMovedPiece != nullptr && strcmp(lastMovedPiece->getType(), "pawn") == 0 &&
        strcmp(lastMovedPiece->getColor(), color) != 0 &&
        abs(lastMoveFromY - lastMoveToY) == 2 &&
        lastMoveToY == positionY) {
        
        
        board->removePiece(lastMoveToX, lastMoveToY);
        positionX = newX;
        positionY = newY;
        board->setLastMove(positionX, positionY - forwardDirection, newX, newY);
        Game::moveCount = 0;
        return true;
    }

    return false;
    }
   