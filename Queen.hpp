#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"
#include "Board.hpp"

class Queen : public Piece {
public:
    Queen(const char* pieceColor, int posX, int posY, Board* chessboard);
    bool move(int newX, int newY) override;
    virtual Piece* clone() const override;
};

#endif