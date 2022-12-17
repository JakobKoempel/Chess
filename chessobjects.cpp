#include "chessobjects.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Piece::Piece(color player, Board *b) : player(player), board(b) {}

//Rook
Rook::Rook(color player, Board *b) : Piece(player, b) {}
bool Rook::canMove(int r1, int c1, int r2, int c2){
    //in same row
    if(r1 == r2){
        for(int min_c = std::min(c1, c2) + 1 ; min_c < std::max(c1, c2) ; min_c++){
            if(board->getField(r1, min_c) != NULL) return false;
        }
        return true;
    }
    //in same column
    if(c1 == c2){
        for(int min_r = std::min(r1, r2) + 1 ; min_r < std::max(r1, r2) ; min_r++){
            if(board->getField(min_r, c1) != NULL) return false;
        }
        return true;
    }
    //neither in same row nor column
    return false;
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
    //all initlially NULL(are not NULL by default)
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            field[i][j] = NULL;
        }
    }

    //init white
    field[0][0] = new Rook(white, this);
    field[0][1] = new Knight(white, this);
    field[0][2] = new Bishop(white, this);
    field[0][3] = new Queen(white, this);
    field[0][4] = new King(white, this);
    field[0][5] = new Bishop(white, this);
    field[0][6] = new Knight(white, this);
    field[0][7] = new Rook(white, this);
    for(int i = 1 ; i < 8 ; i++){
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
    //field empty
    if(field[r1][c1] == NULL) return false;

    //to field possessed by same player
    if(field[r2][c2] != NULL && field[r2][c2]->player == player) return false;

    //wrong player
    if(field[r1][c1]->player != player) return false;

    //from position out of bounce
    if(r1 >= 8 || r1 < 0 || c1 >= 8 || c1 < 0) return false;

    //to position out of bounce
    if(r2 >= 8 || r2 < 0 || c2 >= 8 || c2 < 0) return false;

    //from and to positions are the same
    if(r1 == r2 && c1 == c2) return false;

    //is move legal (piece specific)
    bool canMove = field[r1][c1]->canMove(r1, c1, r2, c2);
    if(!canMove) return false;

    //everything is okay. move can be applied
    field[r2][c2] = field[r1][c1];
    field[r1][c1] = NULL;
    return true;
}

Piece *Board::getField(int r, int c){
    return field[r][c];
}