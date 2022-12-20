#include <cassert>
#include <iostream>
#include <algorithm>
#include "chessobjects.h"

//
void mapping_consistency(Board &b){
    std::vector<Piece*> white_team = b.get_white_team();
    std::vector<Piece*> black_team = b.get_black_team();
    //every piece in Board::white_team must be in Board::field[]][]
    for(Piece *p : white_team){
        assert(b.getField(b.get_r(p), b.get_c(p)) == p);
    }
    //every piece in Board::black_team must be in Board::field[]][] and position -> piece map consistent
    for(Piece *p : black_team){
        assert(b.getField(b.get_r(p), b.get_c(p)) == p);
    }
    //every piece in Board::field[][] must be either NULL or in a team and piece -> position map consistent
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            Piece *p = b.getField(i, j);
            assert(p == NULL
                    || std::find(white_team.begin(), white_team.end(), p) != white_team.end()
                    || std::find(black_team.begin(), black_team.end(), p) != black_team.end()
                );
            if(p != NULL){
                assert(b.get_r(p) == i && b.get_c(p) == j);
            }
        }
    }

    std::cout << "mapping_consistency: success " << std::endl;
}


int main(){
    Board b = Board();
    b.move(white, 1, 0, 3, 0);
    b.move(black, 6, 1, 4, 1);
    b.move(white, 3, 0, 4, 1);
    b.print();
    mapping_consistency(b);
    return 1;
}