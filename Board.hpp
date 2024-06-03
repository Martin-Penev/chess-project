#ifndef BOARD_HPP
#define BOARD_HPP
#include "Piece.hpp"

class Board {
private:
    Piece* board[8][8]; 
    int lastMoveFromX;
    int lastMoveFromY;
    int lastMoveToX;
    int lastMoveToY;

    bool whiteKingMoved;
    bool blackKingMoved;
    bool whiteRookLeftMoved;
    bool whiteRookRightMoved;
    bool blackRookLeftMoved;
    bool blackRookRightMoved;

public:
    Board();
    Board(const Board &);
    Board& operator=(const Board &);
    ~Board();

    void placePiece(Piece* piece, int posX, int posY);

    void removePiece(int posX, int posY);

    Piece* getPieceAt(int posX, int posY) const;

    void setLastMove(int fromX, int fromY, int toX, int toY);
    int getLastMoveFromX() const;
    int getLastMoveFromY() const;
    int getLastMoveToX() const;
    int getLastMoveToY() const;

    void setKingMoved(const char* color);
    void setRookMoved(const char* color, int posX, int posY);
    bool canCastle(const char* color, int newX, int newY) const;
    void print() const;
};

#endif