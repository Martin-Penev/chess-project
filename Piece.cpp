#include "Piece.hpp"
#include <iostream>
#include <cstring>
Piece::Piece(const char* typeVal,const char* colorVal,int x,int y,Board* chessboard):type(new char[strlen(typeVal)]+1),color(new char[strlen(colorVal)+1]),positionX(x),positionY(y),board(chessboard)
{
    strcpy(this->type,typeVal);
    strcpy(this->color,colorVal);
}
Piece::Piece(const Piece &other):type(new char[strlen(other.type)]+1),color(new char[strlen(other.color)+1]),positionX(other.positionX),positionY(other.positionY),board(other.board)
{
    strcpy(this->type, other.type);
    strcpy(this->color, other.color);

}
Piece &Piece::operator=(const Piece &other){
    if(this!=&other)
    {
        delete[] type;
        delete[] color;
        type = new char[strlen(other.type) + 1]{};
        color= new char[strlen(other.color) + 1]{};
        strcpy(type, other.type);
        strcpy(color,other.color);
        positionX=other.positionX;
        positionY=other.positionY;
        board=other.board;
    }
    return *this;
}
Piece::~Piece(){
    delete[] type;
    delete[] color;
}
const char* Piece::getColor() const {
    return color;
}
const char* Piece::getType() const{
    return type;
}

void Piece::setPosition(int x, int y) {
    positionX = x;
    positionY = y;
}
int Piece::getPositionX() const{
    return positionX;
}
int Piece::getPositionY() const{
    return positionY;
}