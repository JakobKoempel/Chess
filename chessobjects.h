#include <string>
#include <unordered_map>
#include <vector>

enum color{
    white, black
};

class Piece;

class Board{
    public:
        Board();
        ~Board();
        void print();
        bool check(color player);
        bool checkmate(color player);
        bool move(color player, int r1, int c1, int r2, int c2);
        Piece *getField(int r, int c);
        int get_r(Piece *p);
        int get_c(Piece *p);
        std::vector<Piece*> const &get_white_team();
        std::vector<Piece*> const &get_black_team();
    private:
        Piece *field[8][8]; //position -> pieces mapping
        std::unordered_map<Piece*, int> r_pos; //pieces -> position mapping
        std::unordered_map<Piece*, int> c_pos;
        std::vector<Piece*> white_team;
        std::vector<Piece*> black_team;
        void initMappings(int r, int c, Piece *p); //init bidrectional mapping from piece* <-> position
        void raw_move(int r1, int c1, int r2, int c2); //raw move method (no checks)
};

class Piece{
    public :
        Piece(color team, Board *b); 
        virtual bool canMove(color player, int r1, int c1, int r2, int c2);
        virtual std::string toString() = 0;
        const color team;
    protected :
        Board *board;
};

class Rook : public Piece{
    public :
        Rook(color team, Board *b);
        bool canMove(color player, int r1, int c1, int r2, int c2);
        std::string toString();
};

class Queen : public Piece{
    public :
        Queen(color team, Board *b);
        bool canMove(color player, int r1, int c1, int r2, int c2);
        std::string toString();
};

class Pawn : public Piece{
    public :
        Pawn (color team, Board *b);
        bool canMove(color player, int r1, int c1, int r2, int c2);
        std::string toString();
};

class King : public Piece{
    public :
        King(color team, Board *b);
        bool canMove(color player, int r1, int c1, int r2, int c2);
        std::string toString();
};

class Knight : public Piece{
    public :
        Knight(color team, Board *b);
        bool canMove(color player, int r1, int c1, int r2, int c2);
        std::string toString();
};

class Bishop : public Piece{
    public :
        Bishop(color team, Board *b);
        bool canMove(color player, int r1, int c1, int r2, int c2);
        std::string toString();
};
