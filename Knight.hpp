#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include "Board.hpp"

class Knight : public Piece {
public:
    Knight(const char* pieceColor, int posX, int posY, Board* chessboard);
    bool move(int newX, int newY) override;
    bool canMoveTo(int x,int y) override;
     virtual Piece* clone() const override;
};

#endif