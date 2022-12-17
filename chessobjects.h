#include <string>

enum color{
    white, black
};

class Board;

class Piece{
    public :
        Piece(color player, Board *b); 
        virtual bool canMove(int r1, int c1, int r2, int c2) = 0;
        virtual std::string toString() = 0;
        const color player;
    protected :
        Board *board;
};

class Rook : public Piece{
    public :
        Rook(color player, Board *b);
        bool canMove(int r1, int c1, int r2, int c2);
        std::string toString();
};

class Queen : public Piece{
    public :
        Queen(color player, Board *b);
        bool canMove(int r1, int c1, int r2, int c2);
        std::string toString();
};

class Pawn : public Piece{
    public :
        Pawn (color player, Board *b);
        bool canMove(int r1, int c1, int r2, int c2);
        std::string toString();
};

class King : public Piece{
    public :
        King(color player, Board *b);
        bool canMove(int r1, int c1, int r2, int c2);
        std::string toString();
};

class Knight : public Piece{
    public :
        Knight(color player, Board *b);
        bool canMove(int r1, int c1, int r2, int c2);
        std::string toString();
};

class Bishop : public Piece{
    public :
        Bishop(color player, Board *b);
        bool canMove(int r1, int c1, int r2, int c2);
        std::string toString();
};

class Board{
    public:
        Board();
        ~Board();
        void print();
        bool checkmate(color player);
        bool move(color player, int r1, int c1, int r2, int c2);
        Piece *getField(int r, int c);
    private:
        Piece *field[8][8]; //array of pointers to Pieces. [row][col]
};