#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Board.hpp"
#include <cstring>
#include <iostream>
#include <iomanip>
Board::Board(): whiteKingMoved(false), blackKingMoved(false), 
                 whiteRookLeftMoved(false), whiteRookRightMoved(false), 
                 blackRookLeftMoved(false), blackRookRightMoved(false) {

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
     lastMoveFromX = lastMoveFromY = lastMoveToX = lastMoveToY = -1;
}
Board::Board(const Board &other):whiteKingMoved(other.whiteKingMoved), blackKingMoved(other.blackKingMoved), 
                 whiteRookLeftMoved(other.whiteRookLeftMoved), whiteRookRightMoved(other.whiteRookRightMoved), 
                 blackRookLeftMoved(other.blackRookLeftMoved), blackRookRightMoved(other.blackRookRightMoved) 
{
 for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (other.board[i][j]) {
                board[i][j] = other.board[i][j]->clone();
            } else {
                board[i][j] = nullptr;
            }
        }
    }
    lastMoveFromX = other.lastMoveFromX;
    lastMoveFromY = other.lastMoveFromY;
    lastMoveToX = other.lastMoveToX;
    lastMoveToY = other.lastMoveToY;

}
Board& Board::operator=(const Board &other)
{
    if (this != &other) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (other.board[i][j]) {
                    board[i][j] = other.board[i][j]->clone();
                } else {
                    board[i][j] = nullptr;
                }
            }
        }

        whiteKingMoved = other.whiteKingMoved;
        blackKingMoved = other.blackKingMoved;
        whiteRookLeftMoved = other.whiteRookLeftMoved;
        whiteRookRightMoved = other.whiteRookRightMoved;
        blackRookLeftMoved = other.blackRookLeftMoved;
        blackRookRightMoved = other.blackRookRightMoved;
        lastMoveFromX = other.lastMoveFromX;
        lastMoveFromY = other.lastMoveFromY;
        lastMoveToX = other.lastMoveToX;
        lastMoveToY = other.lastMoveToY;
    }
    return *this;
}
Board::~Board() {

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}

void Board::placePiece(Piece* piece, int posX, int posY) {

    char* color=new char[strlen(piece->getColor())+1];
    strcpy(color,piece->getColor());
    char* type=new char[strlen(piece->getType())+1];
    strcpy(type,piece->getType());

     if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8) {
        removePiece(posX, posY); 

        if(strcmp(type,"pawn")==0 && strcmp(color, "white") == 0 && posY == 7 
        || strcmp(type,"pawn")==0 && strcmp(color, "black") == 0 && posY == 0){
            
        char promotionChoice;
        std::cout << "Promote pawn to (q)ueen, (r)ook, (b)ishop, or (k)night: ";
        std::cin >> promotionChoice;

        switch (promotionChoice) {
        case 'q':
            board[posX][posY]=new Queen(color, posX,posY, this);
            break;
        case 'r':
            board[posX][posY]=new Rook(color, posX,posY, this);
            break;
        case 'b':
            board[posX][posY]=new Bishop(color, posX,posY, this);
            break;
        case 'k':
            board[posX][posY]=new Knight(color, posX,posY, this);
            break;
        default:
            std::cout << "Invalid choice. Pawn promoted to Queen by default." << std::endl;
            board[posX][posY]=new Queen(color, posX,posY, this);
            break;
        }

        }
        else{
        board[posX][posY] = piece;
        }

    }
    delete [] color;
    delete [] type;
}

void Board::removePiece(int posX, int posY) {
     if (posX < 0 || posX >= 8 || posY < 0 || posY >= 8) {
        return;
    }
    if (board[posX][posY] != nullptr) {
        board[posX][posY] = nullptr;
    }
}

Piece* Board::getPieceAt(int posX, int posY) const {
    if (posX < 0 || posX >= 8 || posY < 0 || posY >= 8) {
        return nullptr;
    }
    
    return board[posX][posY];
}
void Board::setLastMove(int fromX, int fromY, int toX, int toY) {
    lastMoveFromX = fromX;
    lastMoveFromY = fromY;
    lastMoveToX = toX;
    lastMoveToY = toY;
}

int Board::getLastMoveFromX() const {
    return lastMoveFromX;
}

int Board::getLastMoveFromY() const {
    return lastMoveFromY;
}

int Board::getLastMoveToX() const {
    return lastMoveToX;
}

int Board::getLastMoveToY() const {
    return lastMoveToY;
}
void Board::setKingMoved(const char* color) {
    if (strcmp(color, "white") == 0) {
        whiteKingMoved = true;
    } else {
        blackKingMoved = true;
    }
}
void Board::setRookMoved(const char* color, int posX, int posY) {
    if (strcmp(color, "white") == 0) {
        if (posX == 0 && posY == 0) {
            whiteRookLeftMoved = true;
        } else if (posX == 7 && posY == 0) {
            whiteRookRightMoved = true;
        }
    } else {
        if (posX == 0 && posY == 7) {
            blackRookLeftMoved = true;
        } else if (posX == 7 && posY == 7) {
            blackRookRightMoved = true;
        }
    }
}
bool Board::canCastle(const char* color, int newX, int newY) const {
    if (strcmp(color, "white") == 0) {
        if (whiteKingMoved) return false;
        if (newX == 6 && newY == 0 && !whiteRookRightMoved) {
            for (int i = 5; i < 7; ++i) {
                if (board[i][0] != nullptr) return false;
            }
            return true;
        }
        if (newX == 2 && newY == 0 && !whiteRookLeftMoved) {
            for (int i = 1; i < 4; ++i) {
                if (board[i][0] != nullptr) return false;
            }
            return true;
        }
    } else {
        if (blackKingMoved) return false;
        if (newX == 6 && newY == 7 && !blackRookRightMoved) {
            for (int i = 5; i < 7; ++i) {
                if (board[i][7] != nullptr) return false;
            }
            return true;
        }
        if (newX == 2 && newY == 7 && !blackRookLeftMoved) {
            for (int i = 1; i < 4; ++i) {
                if (board[i][7] != nullptr) return false;
            }
            return true;
        }
    }
    return false;
}

void Board::print() const {
    for (char i = 'A'; i <= 'H'; ++i) {
        std::cout << std::setw(5) << i;
    }
    std::cout << std::endl;
    for (int y = 7; y >= 0; --y) {
        std::cout << y + 1 << " ";
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board[x][y];
            if (piece == nullptr) {
                std::cout << std::setw(5)<<". ";
            } else {
                char type;
                if(strcmp(piece->getType(),"king")==0)
                {
                    type='K';
                }
                else{
                    type = piece->getType()[0];
                }
                char color = (strcmp(piece->getColor(),"white")==0) ? 'W' : 'B';
                std::cout <<std::setw(3)<< color << type << " ";
            }
        }
        std::cout << y + 1 << std::endl;
    }
    for (char i = 'A'; i <= 'H'; ++i) {
        std::cout << std::setw(5) << i;
    }
    std::cout << std::endl;
}