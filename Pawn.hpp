#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"
#include "Board.hpp"

class Pawn : public Piece {
public:
    Pawn(const char* pieceColor, int posX, int posY, Board* chessboard);
    bool move(int newX, int newY) override;
     virtual Piece* clone() const override;
};

#endif