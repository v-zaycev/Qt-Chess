#include "Playing_field.h"


void Playing_field::make_move(int x0, int y0, int x1, int y1)
{

    if (field[x0][y0]->type==6&&abs(y0-y1)==2)
    {
        if(y1==6)
        {
            field[x1][y1]=field[x0][y0];
            field[x1][y1]->y=y1;
            field[x1][y1]->moved=1;
            field[x0][y1-1]=field[x0][7];
            field[x0][y1-1]->y=y1-1;
            field[x0][y1-1]->moved=1;
            field[x0][7]=nullptr;
            field[x0][y0]=nullptr;
        }
        else
        {
            field[x1][y1]=field[x0][y0];
            field[x1][y1]->y=y1;
            field[x1][y1]->moved=1;
            field[x0][y1+1]=field[x0][0];
            field[x0][y1+1]->y=y1+1;
            field[x0][y1+1]->moved=1;
            field[x0][0]=nullptr;
            field[x0][y0]=nullptr;
        }
    }
    else
    {
        if (field[x1][y1] != nullptr)
        {
            field[x1][y1]->alive = 0;
            field[x1][y1] = field[x0][y0];
            field[x0][y0] = nullptr;
            field[x1][y1]->x = x1;
            field[x1][y1]->y = y1;
        }
        else
        {
            field[x1][y1] = field[x0][y0];
            field[x0][y0] = nullptr;
            field[x1][y1]->x = x1;
            field[x1][y1]->y = y1;
        }
        if (field[x1][y1]->type == 1)
        {
            if (field[x1][y1]->color==0&&x1==0)
                field[x1][y1]->type = set_type();
            if (field[x1][y1]->color==1&&x1==7)
                field[x1][y1]->type = set_type();
        }


        field[x1][y1]->moved=1;
    }




    clear_possible();
    moving_color=(moving_color+1)%2;
    return;
}

Playing_field::Playing_field()
{
    for (int i = 0; i < 16; i++)
    {
        white[i].color = 0;
        black[i].color = 1;
    }

    white[0].type = black[0].type = 6;
    white[1].type = black[1].type = 5;
    white[2].type = black[2].type = white[3].type = black[3].type = 4;
    white[4].type = black[4].type = white[5].type = black[5].type = 3;
    white[6].type = black[6].type = white[7].type = black[7].type = 2;
    for (int i = 8; i < 16; ++i)
        black[i].type = white[i].type = 1;

    for (int i = 0; i < 8; ++i)
    {
        field[1][i] = &black[i + 8];
        field[6][i] = &white[i + 8];
    }

    field[0][0] = &black[2];
    field[0][7] = &black[3];
    field[0][2] = &black[4];
    field[0][5] = &black[5];
    field[0][1] = &black[6];
    field[0][6] = &black[7];
    field[0][3] = &black[1];
    field[0][4] = &black[0];

    field[7][0] = &white[2];
    field[7][7] = &white[3];
    field[7][2] = &white[4];
    field[7][5] = &white[5];
    field[7][1] = &white[6];
    field[7][6] = &white[7];
    field[7][3] = &white[1];
    field[7][4] = &white[0];

    for (int i = 2; i < 6; ++i)
        for (int j = 0; j < 8; ++j)
            field[i][j] = nullptr;

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 8; ++j)
            if (field[i][j] != nullptr)
            {
                field[i][j]->x = i;
                field[i][j]->y = j;
            }
    for (int i = 6; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (field[i][j] != nullptr)
            {
                field[i][j]->x = i;
                field[i][j]->y = j;
            }
}

bool Playing_field::check_pawn(const figure& f, int x1, int y1)
{
    if (f.color == 0 && (f.y == y1 && f.x - 1 == x1 && field[x1][y1] == nullptr ||
        field[x1][y1] != nullptr&&field[x1][y1]->color != f.color&&abs(f.y - y1) == 1 && x1 + 1 == f.x ||
        f.x - x1 == 2 && f.y == y1 && f.x == 6 && field[x1][y1] == nullptr&&field[x1+1][y1] == nullptr)
        ||
        f.color == 1 && (f.y == y1 && f.x + 1 == x1 && field[x1][y1] == nullptr ||
            field[x1][y1] != nullptr&&field[x1][y1]->color != f.color&&abs(f.y - y1) == 1 && x1 - 1 == f.x ||
            x1 - f.x == 2 && f.y == y1 && f.x == 1 && field[x1][y1] == nullptr&& field[x1-1][y1] == nullptr))
        return true;
    return false;
}

bool Playing_field::check_knight(const figure& f, int x1, int y1)
{
    if ((abs(f.x - x1) == 1 && abs(f.y - y1) == 2||abs(f.x - x1) == 2 && abs(f.y - y1) == 1)
            && (field[x1][y1] == nullptr || field[x1][y1]->color != f.color))
        return true;

    return false;
}

bool Playing_field::check_bishop(const figure& f, int x1, int y1)
{
    if (!(abs(f.x - x1) == abs(f.y - y1)) || field[x1][y1] != nullptr&&field[x1][y1]->color == f.color)
        return false;
    else
    {
        int x_sign = (x1 - f.x) / abs(f.x - x1);
        int y_sign = (y1 - f.y) / abs(f.y - y1);
        for (int i = f.x + x_sign, j = f.y + y_sign; i != x1; i += x_sign, j += y_sign)
            if (field[i][j] != nullptr)
                return false;
    }
    return true;
}

bool Playing_field::check_rook(const figure& f, int x1, int y1)
{
    if (f.x != x1 && f.y != y1 || field[x1][y1] != nullptr&&field[x1][y1]->color == f.color)
        return false;
    else if (f.x - x1 != 0 && f.y - y1 == 0)
    {
        int x_sign = (x1 - f.x) / abs(f.x - x1);
        for (int i = f.x + x_sign; i != x1; i += x_sign)
            if (field[i][f.y] != nullptr)
                return false;
    }
    else if (f.x - x1 == 0 && f.y - y1 != 0)
    {
        int y_sign = (y1 - f.y) / abs(f.y - y1);
        for (int i = f.y + y_sign; i != y1; i += y_sign)
            if (field[f.x][i] != nullptr)
                return false;
    }
    return true;
}

bool Playing_field::check_queen(const figure& f, int x1, int y1)
{
    if (f.x == x1 || f.y == y1)
        return check_rook(f, x1, y1);
    else
        return check_bishop(f, x1, y1);
}

bool Playing_field::check_king(const figure& f, int x1, int y1)
{
    if (abs(f.x - x1) <= 1 && abs(f.y - y1) <= 1 && (field[x1][y1] == nullptr || field[x1][y1]->color != f.color))
        return true;
    return false;
}

bool Playing_field::check_check(int x, int y, int color)
{
    if (color == 0)
    {
        for (int i = 0; i < 16; ++i)
            if (black[i].alive)
                switch (black[i].type)
                {
                case 1:
                {
                    if (check_pawn(black[i], x, y))
                        return true;
                    break;
                }
                case 2:
                {
                    if (check_knight(black[i], x, y))
                        return true;
                    break;
                }
                case 3:
                {
                    if (check_bishop(black[i], x, y))
                        return true;
                    break;
                }
                case 4:
                {
                    if (check_rook(black[i], x, y))
                        return true;
                    break;
                }
                case 5:
                {
                    if (check_queen(black[i], x, y))
                        return true;
                    break;
                }
                case 6:
                {
                    if (check_king(black[i], x, y))
                        return true;
                    break;
                }
                }
    }
    else
    {
        for (int i = 0; i < 16; ++i)
            if (white[i].alive)
                switch (white[i].type)
                {
                case 1:
                {
                    if (check_pawn(white[i], x, y))
                        return true;
                    break;
                }
                case 2:
                {
                    if (check_knight(white[i], x, y))
                        return true;
                    break;
                }
                case 3:
                {
                    if (check_bishop(white[i], x, y))
                        return true;
                    break;
                }
                case 4:
                {
                    if (check_rook(white[i], x, y))
                        return true;
                    break;
                }
                case 5:
                {
                    if (check_queen(white[i], x, y))
                        return true;
                    break;
                }
                case 6:
                {
                    if (check_king(white[i], x, y))
                        return true;
                    break;
                }
                }
    }
    return false;
}

bool Playing_field::check_mate()
{
    if (moving_color == 0)
    {
        for (int l = 0; l < 16; ++l)
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j)
                    if (white[l].alive&&check_move(&white[l], i, j))
                        return false;

        return true;
    }
    else
    {
        for (int l = 0; l < 16; ++l)
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j)
                    if (black[l].alive&&check_move(&black[l], i, j))
                        return false;
        return true;
    }
}

bool Playing_field::check_move(figure *f, int x1, int y1)
{
    switch (f->type)
    {
    case 1:
    {
        if (!check_pawn(*f, x1, y1))
            return false;
        break;
    }
    case 2:
    {
        if (!check_knight(*f, x1, y1))
            return false;
        break;
    }
    case 3:
    {
        if (!check_bishop(*f, x1, y1))
            return false;
        break;
    }
    case 4:
    {
        if (!check_rook(*f, x1, y1))
            return false;
        break;
    }
    case 5:
    {
        if (!check_queen(*f, x1, y1))
            return false;
        break;
    }
    case 6:
    {
        if (!check_king(*f, x1, y1))
            return false;
        break;
    }
    }



    figure* temp = field[x1][y1];
    int fx=f->x, fy=f->y;
    if(temp!=nullptr)
        temp->alive=0;
    field[x1][y1] = f;
    f->x=x1;
    f->y=y1;
    field[fx][fy] = nullptr;
    bool res;
    if (f->color == 0)
        res = check_check(white[0].x, white[0].y, f->color);
    else
        res = check_check(black[0].x, black[0].y, f->color);

    if(temp!=nullptr)
        temp->alive=1;
    field[x1][y1] = temp;
    field[fx][fy] = f;
    f->x=fx;
    f->y=fy;

    return !res;
}

void Playing_field::find_posssible_moves(int x, int y)
{
    possible_sz=0;
    if (field[x][y] != nullptr)
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                if (check_move(field[x][y], i, j))
                {
                    possible[possible_sz++] = std::make_pair(i, j);
                    //++possible_sz;
                }
    if(field[x][y]!=nullptr&&field[x][y]->type==6&&field[x][y]->moved==0)
    {
        if(field[x][y]->color==0)
        {
            if (field[7][7]!=nullptr&&field[7][7]->type==4&&field[7][7]->moved==0&&field[7][6]==nullptr&&field[7][5]==nullptr&&!check_check(7,6,0)&&!check_check(7,5,0)&&!check_check(7,4,0))
                possible[possible_sz++]= std::make_pair(x,y+2);
            if (field[7][0]!=nullptr&&field[7][0]->type==4&&field[7][0]->moved==0&&field[7][1]==nullptr&&field[7][2]==nullptr&&field[7][3]==nullptr&&!check_check(7,3,0)&&!check_check(7,2,0)&&!check_check(7,4,0))
                possible[possible_sz++]= std::make_pair(x,y-2);
        }
        else
        {
            if (field[0][7]!=nullptr&&field[0][7]->type==4&&field[0][7]->moved==0&&field[0][6]==nullptr&&field[0][5]==nullptr&&!check_check(0,6,1)&&!check_check(0,5,1)&&!check_check(0,4,1))
                possible[possible_sz++]= std::make_pair(x,y+2);
            if (field[0][0]!=nullptr&&field[0][0]->type==4&&field[0][0]->moved==0&&field[0][1]==nullptr&&field[0][2]==nullptr&&field[0][3]==nullptr&&!check_check(0,3,1)&&!check_check(0,2,1)&&!check_check(0,4,1))
                possible[possible_sz++]= std::make_pair(x,y-2);
        }
    }

    return;
}

void Playing_field::clear_possible()
{
    possible_sz=0;
    selected=nullptr;
}

bool Playing_field::check_stalemate()
{
    if (moving_color == 0)
    {
        for (int k = 0; k < 16; ++k)
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j)
                    if (white[k].alive&&check_move(&white[k], i, j))
                        return false;
    }
    else
        for (int k = 0; k < 16; ++k)
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j)
                    if (black[k].alive&&check_move(&black[k], i, j))
                        return false;

    return true;
}

bool Playing_field::is_possible(int x, int y)
{
    for (int i=0;i<possible_sz;++i)
        if (x==possible[i].first&&y==possible[i].second)
            return true;
    return false;
}

int set_type() { return 5; }

figure** Playing_field::get_field()
{
    return &(field[0][0]);
}

void Playing_field::out_to_file()
{
    std::ofstream output("output.txt");
    if (!output.is_open())
        return;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if (field[i][j]==nullptr)
                output<<"-- ";
            else
            {
                if(field[i][j]->color==0)
                    output<<"W";
                else
                    output<<"B";
                switch(field[i][j]->type)
                {
                case 1:{output<<"P ";break;}
                case 2:{output<<"N ";break;}
                case 3:{output<<"B ";break;}
                case 4:{output<<"R ";break;}
                case 5:{output<<"Q ";break;}
                case 6:{output<<"K ";break;}
                }
            }
        }
        output<<std::endl;
    }
    return;
}
