#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"
#include "Board.hpp"

class Bishop : public Piece {
public:
    Bishop(const char* pieceColor, int posX, int posY, Board* chessboard);

    bool move(int newX, int newY) override;
     virtual Piece* clone() const override;
};

#endif