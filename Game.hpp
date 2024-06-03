#ifndef GAME_HPP
#define GAME_HPP
#include "Board.hpp"
#include "Player.hpp"
class Game{
private:
    Board board;
    Player whitePlayer;
    Player blackPlayer;
    bool whiteTurn;
    int whiteLastStartX;
    int whiteLastStartY;
    int whiteLastEndX;
    int whiteLastEndY;
    int whiteRepetitionMove;
    int blackLastStartX;
    int blackLastStartY;
    int blackLastEndX;
    int blackLastEndY;
    int blackRepetitionMove;

    
public:
    Game();
    static inline int moveCount = 0;
    void setupBoard();

    bool movePiece(int startX, int startY, int endX, int endY);

    void printBoard() const;
    bool isEndOfTheGame();
    bool suggestDraw();
    bool resign();
private:
    bool isPathClear(Piece* piece, int newX, int newY) const;
    bool isCheckmate() const;
    bool isStalemate();
    bool isDraw();
    bool insufficientMaterial();
    bool wouldEscapeCheck(Piece* piece, int endX, int endY) ;
    bool wouldDiscoverCheck(Piece* piece, int endX, int endY); 
    bool isChecked(int x,int y,const char* color) const;
    bool isValidMove(Piece* piece, int newX, int newY, bool isKingThere) const;
};

#endif