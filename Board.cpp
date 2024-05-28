#include "Board.hpp"
#include <cstring>
#include <iostream>
#include <iomanip>
Board::Board(){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
}
Board::Board(const Board &other){
 for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (other.board[i][j]) {
                board[i][j] = other.board[i][j]->clone();
            } else {
                board[i][j] = nullptr;
            }
        }
    }
}
Board& Board::operator=(const Board &other)
{
    if (this != &other) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (other.board[i][j]) {
                    board[i][j] = other.board[i][j]->clone();
                } else {
                    board[i][j] = nullptr;
                }
            }
        }
    }
    return *this;
}
Board::~Board() {

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}

void Board::placePiece(Piece* piece, int posX, int posY) {
     if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8) {
        removePiece(posX, posY); 
        board[posX][posY] = piece;
    }
}

void Board::removePiece(int posX, int posY) {
     if (posX < 0 || posX >= 8 || posY < 0 || posY >= 8) {
        return;
    }
    Piece* piece = board[posX][posY];
    if (piece != nullptr) {
        board[posX][posY] = nullptr;
    }
}

Piece* Board::getPieceAt(int posX, int posY) const {
    if (posX < 0 || posX >= 8 || posY < 0 || posY >= 8) {
        return nullptr;
    }
    return board[posX][posY];
}
void Board::print() const {
    
}