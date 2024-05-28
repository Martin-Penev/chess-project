#ifndef PIECE_HPP
#define PIECE_HPP
class Board;

class Piece
{
protected:
    char* type; 
    char* color; 
    int positionX; 
    int positionY; 
    Board* board;
public:
    Piece(const char* pieceType="none", const char* pieceColor="none", int posX=0, int posY=0,Board* board=nullptr);
    virtual bool move(int newX, int newY) = 0;
    const char* getColor() const ;
    const char* getType() const;
    virtual Piece* clone() const = 0; 
    Piece(const Piece&);
    Piece& operator=(const Piece&);
    virtual ~Piece();
};
#endif