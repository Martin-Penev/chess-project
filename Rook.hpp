#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"
#include "Board.hpp"

class Rook : public Piece {
public:
    Rook(const char* pieceColor, int posX, int posY, Board* chessboard);
    bool move(int newX, int newY) override;
    bool canMoveTo(int x,int y) override;
     virtual Piece* clone() const override;
};

#endif