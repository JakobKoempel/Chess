#include "chessobjects.h"
#include <cstdlib>
#include <iostream>

Piece::Piece(color player, Board *b) : player(player), board(b) {}

//Rook
Rook::Rook(color player, Board *b) : Piece(player, b) {}
bool Rook::canMove(int r1, int c1, int r2, int c2){
    return true;
}
std::string Rook::toString(){
    if(player == white) return "R 0";
    return "R 1";
}

//Queen
Queen::Queen(color player, Board *b) : Piece(player, b) {}
bool Queen::canMove(int r1, int c1, int r2, int c2){
    return true;
}
std::string Queen::toString(){
    if(player == white) return "Q 0";
    return "Q 1";
}
//Pawn
Pawn::Pawn(color player, Board *b) : Piece(player, b) {}
bool Pawn::canMove(int r1, int c1, int r2, int c2){
    return true;
}
std::string Pawn::toString(){
    if(player == white) return "P 0";
    return "P 1";
}

//King
King::King(color player, Board *b) : Piece(player, b) {}
bool King::canMove(int r1, int c1, int r2, int c2){
    return true;
}
std::string King::toString(){
    if(player == white) return "K 0";
    return "K 1";
}
//Knight
Knight::Knight(color player, Board *b) : Piece(player, b) {}
bool Knight::canMove(int r1, int c1, int r2, int c2){
    return true;
}
std::string Knight::toString(){
    if(player == white) return "N 0";
    return "N 1";
}

//Bishop
Bishop::Bishop(color player, Board *b) : Piece(player, b) {}
bool Bishop::canMove(int r1, int c1, int r2, int c2){
    return true;
}
std::string Bishop::toString(){
    if(player == white) return "B 0";
    return "B 1";
}

//Board
Board::Board(){
    //init white
    field[0][0] = new Rook(white, this);
    field[0][1] = new Knight(white, this);
    field[0][2] = new Bishop(white, this);
    field[0][3] = new Queen(white, this);
    field[0][4] = new King(white, this);
    field[0][5] = new Bishop(white, this);
    field[0][6] = new Knight(white, this);
    field[0][7] = new Rook(white, this);
    for(int i = 0 ; i < 8 ; i++){
        field[1][i] = new Pawn(white, this);
    }

    //init black
    field[7][0] = new Rook(black, this);
    field[7][1] = new Knight(black, this);
    field[7][2] = new Bishop(black, this);
    field[7][3] = new Queen(black, this);
    field[7][4] = new King(black, this);
    field[7][5] = new Bishop(black, this);
    field[7][6] = new Knight(black, this);
    field[7][7] = new Rook(black, this);
    for(int i = 0 ; i < 8 ; i++){
        field[6][i] = new Pawn(black, this);
    }

    //all other pointers to NULL (are not NULL by default)
    for(int i = 2 ; i < 6 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            field[i][j] = NULL;
        }
    }
}
Board::~Board(){
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            //delete NULL is nop
            delete field[i][j];
        }
    }
}
void Board::print(){
    std::cout << "_________________________________________________" << std::endl;
    for(int i = 7 ; i >= 0 ; i--){
        std::cout << "| ";
        for(int j = 0 ; j < 8  ; j++){
            if(field[i][j] != NULL){
                std::cout << field[i][j]->toString() << " | " ;
            }else{
                std::cout << "   " << " | " ;
            }
        }
        std::cout << std::endl << "|_____|_____|_____|_____|_____|_____|_____|_____|" << std::endl;
    }
}
bool Board::move(color player, int r1, int c1, int r2, int c2){
    if(field[r1][c1] == NULL) return false;
    if(field[r1][c1]->player != player) return false;
    return field[r1][c1]->canMove(r1, c1, r2, c2);
}