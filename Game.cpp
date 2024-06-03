#include "Game.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Pawn.hpp"
#include <iostream>
#include <cstring>
Game::Game() : whitePlayer("white"), blackPlayer("black"), whiteTurn(true),
    whiteLastStartX(-1), whiteLastStartY(-1), whiteLastEndX(-1), whiteLastEndY(-1),whiteRepetitionMove(0),
    blackLastStartX(-1), blackLastStartY(-1), blackLastEndX(-1), blackLastEndY(-1),blackRepetitionMove(0){
    setupBoard();
    
}

void Game::setupBoard() {
    
    board.placePiece(new Rook("white", 0, 0, &board), 0, 0);
    board.placePiece(new Knight("white", 1, 0, &board), 1, 0);
    board.placePiece(new Bishop("white", 2, 0, &board), 2, 0);
    board.placePiece(new Queen("white", 3, 0, &board), 3, 0);
    board.placePiece(new King("white", 4, 0, &board), 4, 0);
    board.placePiece(new Bishop("white", 5, 0, &board), 5, 0);
    board.placePiece(new Knight("white", 6, 0, &board), 6, 0);
    board.placePiece(new Rook("white", 7, 0, &board), 7, 0);
    for (int i = 0; i < 8; ++i) {
        board.placePiece(new Pawn("white", i, 1, &board), i, 1);
    }

    board.placePiece(new Rook("black", 0, 7, &board), 0, 7);
    board.placePiece(new Knight("black", 1, 7, &board), 1, 7);
    board.placePiece(new Bishop("black", 2, 7, &board), 2, 7);
    board.placePiece(new Queen("black", 3, 7, &board), 3, 7);
    board.placePiece(new King("black", 4, 7, &board), 4, 7);
    board.placePiece(new Bishop("black", 5, 7, &board), 5, 7);
    board.placePiece(new Knight("black", 6, 7, &board), 6, 7);
    board.placePiece(new Rook("black", 7, 7, &board), 7, 7);
    for (int i = 0; i < 8; ++i) {
        board.placePiece(new Pawn("black", i, 6, &board), i, 6);
    }
}

bool Game::movePiece(int startX, int startY, int endX, int endY) {

    Piece* piece = board.getPieceAt(startX, startY);
    if (piece == nullptr) {
        std::cout << "No piece at the starting position." << std::endl;
        return false;
    }

    if ((whiteTurn && strcmp(piece->getColor(), "white")!=0) || (!whiteTurn && strcmp(piece->getColor() , "black")!=0)) {
        std::cout << "It's not your turn." << std::endl;
        return false;
    }

    const char* currentPlayerColor = whiteTurn ? "white" : "black";
    Piece* king = nullptr;

    // Намиране на краля
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* piece = board.getPieceAt(x, y);
            if (piece != nullptr && strcmp(piece->getType(), "king") == 0 && strcmp(piece->getColor(), currentPlayerColor) == 0) {
                
                king = piece;
                break;
            }
        }
    }



    if (isChecked(king->getPositionX(), king->getPositionY(), currentPlayerColor)||wouldDiscoverCheck(piece, endX, endY)) {
        
        if (!wouldEscapeCheck(piece, endX, endY)) {
            std::cout << "You must move out of check." << std::endl;
            return false;
        }
    }



    if (piece->move(endX, endY)) {

        
        board.placePiece(piece, endX, endY);
        board.removePiece(startX, startY);
        board.setLastMove(startX, startY, endX, endY);
        whiteTurn = !whiteTurn; // смяна на хода

        if (strcmp(piece->getType(), "pawn") != 0) {
            moveCount++;            
        }
        if (whiteTurn) {
            if(startX==whiteLastEndX&&startY==whiteLastEndY&&endX==whiteLastStartX&&endY==whiteLastStartY)
            {
                whiteRepetitionMove++;
            }
            else{
                whiteRepetitionMove=0;
                blackRepetitionMove=0;
            }
            whiteLastStartX = startX;
            whiteLastStartY = startY;
            whiteLastEndX = endX;
            whiteLastEndY = endY;
        } 
        else {
            if(startX==blackLastEndX&&startY==blackLastEndY&&endX==blackLastStartX&&endY==blackLastStartY)
            {
                blackRepetitionMove++;
            }
            else{
                whiteRepetitionMove=0;
                blackRepetitionMove=0;
            }
            blackLastStartX = startX;
            blackLastStartY = startY;
            blackLastEndX = endX;
            blackLastEndY = endY;
        }
        return true;
    } 
    else {
        std::cout << "Invalid move." << std::endl;
        return false;
    }
}
bool Game::wouldEscapeCheck(Piece* piece, int endX, int endY)  {
    int startX = piece->getPositionX();
    int startY = piece->getPositionY();
    Piece* capturedPiece = board.getPieceAt(endX, endY);

    piece->setPosition(endX, endY);
    board.placePiece(piece, endX, endY);
    board.removePiece(startX, startY);

    const char* currentPlayerColor = whiteTurn ? "white" : "black";
    Piece* king = nullptr;

    // намиране на краля
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* piece = board.getPieceAt(x, y);
            if (piece != nullptr && strcmp(piece->getType(), "king") == 0 && strcmp(piece->getColor(), currentPlayerColor) == 0) {
                
                king = piece;
                break;
            }
        }
    };
    bool isResolved = !isChecked(king->getPositionX(), king->getPositionY(), piece->getColor());

    piece->setPosition(startX, startY);
    board.placePiece(piece, startX, startY);
    if (capturedPiece) {
        board.placePiece(capturedPiece, endX, endY);
    } else {
        board.removePiece(endX, endY);
    }

    return isResolved;
}
bool Game::wouldDiscoverCheck(Piece* piece, int endX, int endY) {

    int startX = piece->getPositionX();
    int startY = piece->getPositionY();
    Piece* capturedPiece = board.getPieceAt(endX, endY);

    if (isValidMove(piece, endX, endY, false)){
        piece->setPosition(endX, endY);
        board.placePiece(piece, endX, endY);
        board.removePiece(startX, startY);
    }
    else {
        return false;
    }
    

    const char* currentPlayerColor = whiteTurn ? "white" : "black";
    Piece* king = nullptr;

    // намиране на краля
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* piece1 = board.getPieceAt(x, y);

            if (piece1 != nullptr && strcmp(piece1->getType(), "king") == 0 && strcmp(piece1->getColor(), currentPlayerColor) == 0) {
                king = piece1;
                break;
            }
        }
    };

    bool isStillChecked = isChecked(king->getPositionX(), king->getPositionY(), piece->getColor());

    piece->setPosition(startX, startY);
    board.placePiece(piece, startX, startY);
    if (capturedPiece) {
        board.placePiece(capturedPiece, endX, endY);
    } else {
        board.removePiece(endX, endY);
    }

    return isStillChecked;
}
void Game::printBoard() const {
       
   board.print();
    std::cout << "Turn: " << (whiteTurn ? "White" : "Black") << std::endl;
}
bool Game::isEndOfTheGame() {
    if(isCheckmate())
    {
        std::cout<<"Checkmate! Game over.";
        return true;
    }
    if(isStalemate())
    {
        std::cout<<"Stalemate! Game over.";
        return true;
    }
    if(moveCount>=100)
    {
        std::cout<<"50-move rule draw";
        return true;
    }
    if(insufficientMaterial())
    {
        std::cout<<"Game drawn by insufficient material! Game over.";
        return true;
    }
    if(whiteRepetitionMove>=3&&blackRepetitionMove>=3){
        std::cout<<"Game over. Repetition!";
        return true;
    }
    
    return false;
}
bool Game::suggestDraw() {
    char response;
    std::cout << (whiteTurn ? "White" : "Black") << " player suggests a draw. \n";
    std::cout << (whiteTurn ? "Black" : "White") << " player, do you accept the draw? (y/n): ";
    std::cin >> response;
    return response == 'y';
}
bool Game::resign(){
    char response;
    std::cout << (whiteTurn ? "White" : "Black") << " player, do you want to resign?:(y/n) \n";
    std::cin >> response;
    return response == 'y';

}
bool Game::isCheckmate() const {
    const char* currentPlayerColor = whiteTurn ? "white" : "black";
    Piece* king = nullptr;

    // намиране на краля
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* piece = board.getPieceAt(x, y);
            if (piece != nullptr && strcmp(piece->getType(), "king") == 0 && strcmp(piece->getColor(), currentPlayerColor) == 0) {
                
                king = piece;
                break;
            }
        }
    }

    // Проверка дали кралят е в шах
    if (isChecked(king->getPositionX(), king->getPositionY(), currentPlayerColor)) {
        // Проверка дали кралят има легален ход
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int newX = king->getPositionX() + dx;
                int newY = king->getPositionY() + dy;
                if ( isValidMove(king,newX, newY, false) && !isChecked( newX, newY,currentPlayerColor)) {
                    // Кралят има опция да се спаси
                    return false;
                }
            }
        }

        
        return true;
    }

    
    return false;
}
bool Game::insufficientMaterial(){
    int whitePiecesCount=0;
    int blackPiecesCount=0;
    bool whiteBishopInGame=false;
    bool whiteKnightInGame=false;
    bool blackBishopInGame=false;
    bool blackKnightInGame=false;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
        {
            Piece* piece=board.getPieceAt(i,j);
            if(piece!=nullptr)
            {
                if(strcmp(piece->getColor(),"white")==0)
                {
                    whitePiecesCount++;
                    if(strcmp(piece->getType(),"bishop")==0)
                    {
                        whiteBishopInGame=true;
                    }
                    if(strcmp(piece->getType(),"knight")==0)
                    {
                        whiteKnightInGame=true;
                    }
                }
                else if(strcmp(piece->getColor(),"black")==0){
                    blackPiecesCount++;
                    if(strcmp(piece->getType(),"bishop")==0)
                    {
                        blackBishopInGame=true;
                    }
                    if(strcmp(piece->getType(),"knight")==0)
                    {
                        blackKnightInGame=true;
                    }
                }

            }
            
        }
    }
    if (whitePiecesCount == 1 && blackPiecesCount == 1) {
        return true;
    }

    if (whitePiecesCount == 2 && blackPiecesCount == 1 && (whiteBishopInGame || whiteKnightInGame)) {
        return true;
    }
    if (blackPiecesCount == 2 && whitePiecesCount == 1 && (blackBishopInGame || blackKnightInGame)) {
        return true;
    }

    return false;
}
bool Game::isStalemate() {
    const char* currentPlayerColor = whiteTurn ? "white" : "black";

    // Намиране на позицията на краля
    int kingX = -1, kingY = -1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPieceAt(i, j);
            if (piece!=nullptr && strcmp(piece->getColor(), currentPlayerColor) == 0 && strcmp(piece->getType(), "king") == 0) {
                kingX = i;
                kingY = j;
                break;
            }
        }
    }

    // проверка за легален ход
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPieceAt(i, j);
            if (piece!=nullptr && strcmp(piece->getColor(), currentPlayerColor) == 0) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                         if (isValidMove(piece,x, y,false)) {
                            if (!wouldDiscoverCheck(piece, x, y)) {
                                return false;
                            }
                            
                        }

                        
                    }
                }
            }
        }
    }
    return !isChecked(kingX, kingY, currentPlayerColor);
}

bool Game::isChecked(int x, int y, const char* color) const {
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* opponentPiece = board.getPieceAt(i, j);
            if (opponentPiece != nullptr && strcmp(opponentPiece->getColor(), color) != 0) {
                if (isValidMove(opponentPiece, x, y, true)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::isValidMove(Piece* piece, int newX, int newY, bool isKingThere) const {
    // извън дъската проверка
    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
        return false;
    }

    if(!isKingThere){
        Piece* destinationPiece = board.getPieceAt(newX, newY);
        if (destinationPiece != nullptr && strcmp(destinationPiece->getColor(), piece->getColor()) == 0) {
            return false;
        }
    }
    
    if (!piece->canMoveTo(newX, newY)) {
        return false;
    }

    if (!isPathClear(piece, newX, newY)) {
        return false;
    }

    return true;
}
bool Game::isPathClear(Piece* piece, int newX, int newY) const {
    int startX = piece->getPositionX();
    int startY = piece->getPositionY();

    // права линия проверка
    if (startX == newX) {
        int direction = (newY > startY) ? 1 : -1;
        for (int y = startY + direction; y != newY; y += direction) {
            if (board.getPieceAt(startX, y) != nullptr) {
                return false;
            }
        }
    } else if (startY == newY) {
        int direction = (newX > startX) ? 1 : -1;
        for (int x = startX + direction; x != newX; x += direction) {
            if (board.getPieceAt(x, startY) != nullptr) {
                return false;
            }
        }
    }
    // диагонал проверка
    else if (abs(newX - startX) == abs(newY - startY)) {
        int xDirection = (newX > startX) ? 1 : -1;
        int yDirection = (newY > startY) ? 1 : -1;
        int x = startX + xDirection;
        int y = startY + yDirection;
        while (x != newX && y != newY) {
            if (board.getPieceAt(x, y) != nullptr) {
                return false;
            }
            x += xDirection;
            y += yDirection;
        }
    }

    return true;
}