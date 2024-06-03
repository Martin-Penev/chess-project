#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"
#include "Board.hpp"

class King : public Piece {
public:
    King(const char* pieceColor, int posX, int posY, Board* chessboard);

    bool move(int newX, int newY) override;
    bool canMoveTo(int x,int y)  override;
     virtual Piece* clone() const override;
};
#endif