#include "Queen.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include <cmath>
#include <cstring>
#include <iostream>

    Queen::Queen(const char* pieceColor, int posX, int posY, Board* chessboard) 
    : Piece("queen", pieceColor, posX, posY, chessboard) {}

    Piece* Queen::clone() const {
    return new Queen(*this);
    }
    bool Queen::canMoveTo(int newX, int newY)  {
    int dx = abs(newX - positionX);
    int dy = abs(newY - positionY);
    return (newX == positionX || newY == positionY || dx == dy);
    }
    bool Queen::move(int newX, int newY) {
        // Проверка, дали позицията е извън шахматната дъска
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
        {
            return false;
        }
        
        if ((newX == positionX || newY == positionY) 
            || (abs(newX - positionX) == abs(newY - positionY))) {
            
            if (newX == positionX || newY == positionY) { 
                int dir = (newX == positionX) ? ((newY > positionY) ? 1 : -1) : ((newX > positionX) ? 1 : -1);
                if (newX == positionX) {
                    for (int y = positionY + dir; y != newY; y += dir) {
                        if (board->getPieceAt(positionX, y) != nullptr)
                            return false; 
                    }
                } 
                else {
                    for (int x = positionX + dir; x != newX; x += dir) {
                        if (board->getPieceAt(x, positionY) != nullptr)
                            return false; 
                    }
                }
                
            }
             else { 
                int xDir = (newX > positionX) ? 1 : -1;
                int yDir = (newY > positionY) ? 1 : -1;
                int x = positionX + xDir;
                int y = positionY + yDir;
                while (x != newX && y != newY) {
                    if(board->getPieceAt(x, y) != nullptr){
                        return false; 
                    }
                    x += xDir;
                    y += yDir;
                }   
            }

            Piece* destinationPiece = board->getPieceAt(newX, newY);
            if (destinationPiece != nullptr) {
                if (strcmp(destinationPiece->getColor(), getColor())!=0) {
                    board->removePiece(newX, newY);
                    positionX = newX;
                    positionY = newY;
                    Game::moveCount = -1;
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                positionX = newX;
                positionY = newY;
                return true;
            }   
        }

        return false;
    }



