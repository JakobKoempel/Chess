#include <iostream>
#include "chessobjects.h"

enum col{
    A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7
};
//front end notation to back end notation conversion
int ftb(int row){
    return row-1;
}

int main(){
    Board b = Board();
    b.move(white,0,0,3,0);
    b.move(white,3,0,3,4);
    b.move(white,3,4,6,4);
    b.move(white,6,4,6,3);
    b.print();
    return 0;
}