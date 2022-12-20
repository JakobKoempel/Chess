#include "chessobjects.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Piece::Piece(color team, Board *b) : team(team), board(b) {}

//common conditions for any move
bool Piece::canMove(color player, int r1, int c1, int r2, int c2){
    //to field held by same player
    if(board->getField(r2, c2) != NULL && board->getField(r2, c2)->team == player) return false;

    //wrong player
    if(board->getField(r1,c1)->team != player) return false;

    //from position out of bounce
    if(r1 >= 8 || r1 < 0 || c1 >= 8 || c1 < 0) return false;

    //to position out of bounce
    if(r2 >= 8 || r2 < 0 || c2 >= 8 || c2 < 0) return false;

    //from and to positions are the same
    if(r1 == r2 && c1 == c2) return false;

    return true;
}

//Rook
Rook::Rook(color player, Board *b) : Piece(player, b) {}
bool Rook::canMove(color player, int r1, int c1, int r2, int c2){
    if(!Piece::canMove(player, r1, c1, r2, c2)) return false;
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
    if(team == white) return "R 0";
    return "R 1";
}

//Queen
Queen::Queen(color player, Board *b) : Piece(player, b) {}
bool Queen::canMove(color player, int r1, int c1, int r2, int c2){
    if(!Piece::canMove(player, r1, c1, r2, c2)) return false;
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
    //neither in same row nor column then they should be diagonal
    //is not on same diagonal
    if(std::abs(r1-r2) != std::abs(c1-c2)) return false;
    //right diagonal
    if((r2 > r1  && c2 > c1) || (r1 > r2  && c1 > c2) ){
        int min_r = std::min(r1, r2);
        int min_c = std::min(c1, c2);
        int dif = std::abs(r1 - r2);
        for(int i = 1 ; i < dif ; i++){
            if(board->getField(min_r + i, min_c + i) != NULL) return false;
        }
        return true;
    }
    //left diagional
    int max_r = std::max(r1, r2);
    int min_c = std::min(c1, c2);
    int dif = std::abs(r1 - r2);
    for(int i = 1 ; i < dif ; i++){
        if(board->getField(max_r - i, min_c + i) != NULL) return false;
    }
    return true;
}
std::string Queen::toString(){
    if(team == white) return "Q 0";
    return "Q 1";
}
//Pawn
Pawn::Pawn(color player, Board *b) : Piece(player, b) {}
bool Pawn::canMove(color player, int r1, int c1, int r2, int c2){
    if(!Piece::canMove(player, r1, c1, r2, c2 )) return false;

    //black and white pawns walk in different directions
    int dir = team == white ? 1 : -1;
    //pawn wants to move 1 step
    if(r1 + dir == r2 && c1 == c2 && board->getField(r2, c2) != NULL) return false;
    
    //pawn wants to move 2 steps
    if(r1 + 2 * dir == r2 && c1 == c2 && 
        (r1 != 6 && r1 != 1 //must be on starting position
        || board->getField(r1 + dir, c1) != NULL //both fields ahead must be empty
        || board->getField(r2, c2) != NULL)
        ) return false;

    //pawn wants to take (r2 c2 being occupied by the same color is already checked in canCommonMove())
    if(r1 + dir == r2 && (c1 == c2 + 1 || c1 == c2 - 1) && board->getField(r2, c2) == NULL) return false;

    //else
    return true;
    
}
std::string Pawn::toString(){
    if(team == white) return "P 0";
    return "P 1";
}

//King
King::King(color player, Board *b) : Piece(player, b) {}
bool King::canMove(color player, int r1, int c1, int r2, int c2){
    if(!Piece::canMove(player, r1, c1, r2, c2 )) return false;

    int dif_r = std::abs(r1 - r2);
    int dif_c = std::abs(c1 - c2);
    //only one shift in any direction allowed
    if(dif_r > 1 || dif_c > 1) return false;

    return true;
}
std::string King::toString(){
    if(team == white) return "K 0";
    return "K 1";
}
//Knight
Knight::Knight(color player, Board *b) : Piece(player, b) {}
bool Knight::canMove(color player, int r1, int c1, int r2, int c2){
    if(!Piece::canMove(player, r1, c1, r2, c2 )) return false;
    int rdif = std::abs(r1 - r2);
    int cdif = std::abs(c1 - c2);
    if((rdif == 2 && cdif == 1) || (rdif == 1 && cdif == 2) ) return true;
    return false;
}
std::string Knight::toString(){
    if(team == white) return "N 0";
    return "N 1";
}

//Bishop
Bishop::Bishop(color player, Board *b) : Piece(player, b) {}
bool Bishop::canMove(color player, int r1, int c1, int r2, int c2){
    if(!Piece::canMove(player, r1, c1, r2, c2 )) return false;
    //is not on same diagonal
    if(std::abs(r1-r2) != std::abs(c1-c2)) return false;
    //right diagonal
    if((r2 > r1  && c2 > c1) || (r1 > r2  && c1 > c2) ){
        int min_r = std::min(r1, r2);
        int min_c = std::min(c1, c2);
        int dif = std::abs(r1 - r2);
        for(int i = 1 ; i < dif ; i++){
            if(board->getField(min_r + i, min_c + i) != NULL) return false;
        }
        return true;
    }
    //left diagional
    int max_r = std::max(r1, r2);
    int min_c = std::min(c1, c2);
    int dif = std::abs(r1 - r2);
    for(int i = 1 ; i < dif ; i++){
        if(board->getField(max_r - i, min_c + i) != NULL) return false;
    }
    return true;
}
std::string Bishop::toString(){
    if(team == white) return "B 0";
    return "B 1";
}

//Board
void Board::initMappings(int r, int c, Piece *p){
    //position -> Piece mapping
    field[r][c] = p;
    //Piece -> position mapping
    r_pos[p] = r;
    c_pos[p] = c;
    //add piece to team
    if(p->team == white) white_team.push_back(p);
    else black_team.push_back(p);
}
Board::Board(){
    //all initlially NULL( are not NULL by default)
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            field[i][j] = NULL;
        }
    }
    //init white
    initMappings(0,0, new Rook(white, this));
    initMappings(0,1, new Knight(white, this));
    initMappings(0,2, new Bishop(white, this));
    initMappings(0,3, new Queen(white, this));
    initMappings(0,4, new King(white, this));
    initMappings(0,5, new Bishop(white, this));
    initMappings(0,6, new Knight(white, this));
    initMappings(0,7, new Rook(white, this));
    for(int i = 0 ; i < 8 ; i++){
        initMappings(1,i, new Pawn(white, this));
    }
    
    //init black
    initMappings(7,0, new Rook(black, this));
    initMappings(7,1, new Knight(black, this));
    initMappings(7,2, new Bishop(black, this));
    initMappings(7,3, new Queen(black, this));
    initMappings(7,4, new King(black, this));
    initMappings(7,5, new Bishop(black, this));
    initMappings(7,6, new Knight(black, this));
    initMappings(7,7, new Rook(black, this));
    for(int i = 0 ; i < 8 ; i++){
        initMappings(6,i, new Pawn(black, this));
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
        std::cout << i+1 << " | ";
        for(int j = 0 ; j < 8  ; j++){
            if(field[i][j] != NULL){
                std::cout << field[i][j]->toString() << " | " ;
            }else{
                std::cout << "   " << " | " ;
            }
        }
        std::cout << std::endl << "  |_____|_____|_____|_____|_____|_____|_____|_____|" << std::endl;
    }
    std::cout << "     A     B     C     D     E     F     G     H" << std::endl;
}
bool Board::move(color player, int r1, int c1, int r2, int c2){
    //field empty
    if(getField(r1, c1) == NULL) return false;

    //move can be applied
    if(field[r1][c1]->canMove(player, r1, c1, r2, c2)){
        raw_move(r1, c1, r2, c2);
        return true;
    } 
    return false;
}
//raw move method. No checks and therefore private.  bidirectional mapping (piece -<> position)
//must remain consistent. Therefore private method
void Board::raw_move(int r1, int c1, int r2, int c2){
    Piece *from = field[r1][c1];
    Piece *to = field[r2][c2];
    //if piece is taken, remove it from list
    white_team.erase(std::remove(white_team.begin(), white_team.end(), to), white_team.end());
    black_team.erase(std::remove(black_team.begin(), black_team.end(), to), black_team.end());
    //update piece -> mapping
    r_pos.erase(to);
    c_pos.erase(to);
    r_pos[from] = r2;
    c_pos[from] = c2;
    //update position -> piece mapping
    delete to;
    field[r2][c2] = from;
    field[r1][c1] = NULL; //no memory leak because field[r2][c2] has pointer to piece

}

//is player in check
bool Board::check(color player){
    //get position of king
    std::string k_name = player == white ? "K 0" : "K 1";
    int k_r, k_c;
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            if(getField(i, j) != NULL && getField(i, j)->toString() == k_name) {
                k_r = i;
                k_c = j;
            }
        }
    }
    //check if any enemy piece can reach king
    color enemy = player == white ? black : white;
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            if(getField(i, j) != NULL && getField(i, j)->canMove(enemy, i, j, k_r, k_c)) {
                return true;
            }
        }
    }
    return false;
}

//Getter
Piece *Board::getField(int r, int c){
    return field[r][c];
}
int Board::get_r(Piece *p){
    return r_pos.at(p);
}
int Board::get_c(Piece *p){
    return c_pos.at(p);
}
std::vector<Piece*> const &Board::get_white_team(){
    return white_team;
}
std::vector<Piece*> const &Board::get_black_team(){
    return black_team;
}