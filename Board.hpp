#ifndef BOARD_HPP
#define BOARD_HPP
#include "Piece.hpp"

class Board {
private:
    Piece* board[8][8]; 


public:
    Board();
    Board(const Board &);
    Board& operator=(const Board &);
    ~Board();

    void placePiece(Piece* piece, int posX, int posY);
    void removePiece(int posX, int posY);
    Piece* getPieceAt(int posX, int posY) const;
    void print() const;
};

#endif