#pragma once
#include<iostream>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstdlib>
#include<fstream>

typedef struct
{
    int x, y;
    int alive = 1;
    int type;
        //1-pawn
        //2-knight
        //3-bishop
        //4-rook
        //5-queen
        //6-king
    int color;
        //0-white
        //1-black
    int moved = 0;
}figure;

class Playing_field
{
private:
    figure* field[8][8];
    //fig order: K Q R R B B Kn Kn P P P P P P P P
    figure black[16];
    figure white[16];

    int possible_sz = 0;
    std::pair<int, int>possible[30];

    bool check_pawn(const figure& f, int x1, int y1);

    bool check_knight(const figure& f, int x1, int y1);

    bool check_bishop(const figure& f, int x1, int y1);

    bool check_rook(const figure& f, int x1, int y1);

    bool check_queen(const figure& f, int x1, int y1);

    bool check_king(const figure& f, int x1, int y1);


public:


    int moving_color = 0;
    figure* selected=nullptr;

    Playing_field();

    bool check_check(int x, int y, int color);

    bool check_mate();

    bool check_move(figure *f, int x1, int y1);

    bool check_stalemate();

    void find_posssible_moves(int x, int y);

    void clear_possible();

    bool is_possible(int x, int y);

    void make_move(int x0, int y0, int x1, int y1);

    figure** get_field();

    void out_to_file();
};

int set_type();
