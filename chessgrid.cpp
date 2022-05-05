#include "chessgrid.h"

ChessGrid::ChessGrid(QWidget *parent): QWidget(parent)
{
    fld= new Playing_field();

    saveBtn = new QPushButton("Save");
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnClick()));

    resetBtn = new QPushButton("Reset");
    connect(resetBtn, SIGNAL(clicked()), this,SLOT(resetBtnClick()));

    result = new QLabel("");
    result->setFont(QFont("Arial", 20, QFont::Bold));
    result->setAlignment(Qt::AlignCenter);

    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(0);
    for (int i = 0; i < 8; ++i)
       for(int j = 0; j<8; ++j)
        {
         squares[i][j] = new ClickLabel (this);
         squares[i][j]->setGeometry(0,0,80,80);
         squares[i][j]->setPos(i,j);
         connect(squares[i][j], SIGNAL(clicked(QMouseEvent*)),this, SLOT(labelClick(QMouseEvent*)));
         grid->addWidget(squares[i][j],i,j);
        }
    update_grid();

    QVBoxLayout *buttons = new QVBoxLayout();
    QHBoxLayout *window = new QHBoxLayout(this);
    buttons->addWidget(resetBtn);
    buttons->addWidget(result);
    buttons->addWidget(saveBtn);
    window->addLayout(buttons);
    window->addLayout(grid);

    setLayout(window);
}

ChessGrid::~ChessGrid()
{
    delete fld;
    for (int i=0;i<8;++i)
        for(int j=0;j<8;++j)
            delete squares[i][j];
    delete saveBtn;
    delete resetBtn;
    delete result;
}

void ChessGrid::update_grid()
{
    for (int i=0;i<8;++i)
        for(int j=0;j<8;++j)
        {
            if ((fld->get_field())[j+8*i]!=nullptr&&(fld->get_field())[j+8*i]==fld->selected)
                squares[i][j]->setStyleSheet("QLabel { background-color : yellow;}");
            else if (fld->is_possible(i,j))
                squares[i][j]->setStyleSheet("QLabel { background-color : green;}");
                    else  if((i+j)%2==1)
                        squares[i][j]->setStyleSheet("QLabel { background-color : #2F4538;}");
                        else
                        squares[i][j]->setStyleSheet("QLabel { background-color : lightGray;}");

            if((fld->get_field())[j+8*i]!=nullptr)
            {
                if ((fld->get_field())[j+8*i]->color==0)
                    switch((fld->get_field())[j+8*i]->type)
                    {
                    case 1:{squares[i][j]->setPixmap(QPixmap("figs\\wP.png"));break;}
                    case 2:{squares[i][j]->setPixmap(QPixmap("figs\\wN.png"));break;}
                    case 3:{squares[i][j]->setPixmap(QPixmap("figs\\wB.png"));break;}
                    case 4:{squares[i][j]->setPixmap(QPixmap("figs\\wR.png"));break;}
                    case 5:{squares[i][j]->setPixmap(QPixmap("figs\\wQ.png"));break;}
                    case 6:{squares[i][j]->setPixmap(QPixmap("figs\\wK.png"));break;}
                    }
                else
                    switch((fld->get_field())[j+8*i]->type)
                    {
                    case 1:{squares[i][j]->setPixmap(QPixmap("figs\\bP.png"));break;}
                    case 2:{squares[i][j]->setPixmap(QPixmap("figs\\bN.png"));break;}
                    case 3:{squares[i][j]->setPixmap(QPixmap("figs\\bB.png"));break;}
                    case 4:{squares[i][j]->setPixmap(QPixmap("figs\\bR.png"));break;}
                    case 5:{squares[i][j]->setPixmap(QPixmap("figs\\bQ.png"));break;}
                    case 6:{squares[i][j]->setPixmap(QPixmap("figs\\bK.png"));break;}
                    }
            }
            else
                squares[i][j]->setPixmap(QPixmap("figs\\blank.png"));
        }
}


void ChessGrid::labelClick (QMouseEvent *event)
{
    int i=((ClickLabel *)sender())->get_x(),j=((ClickLabel *)sender())->get_y();
    if (fld->selected==nullptr)
    {
        if ((fld->get_field())[j+8*i]!=nullptr&&(fld->get_field())[j+8*i]->color==fld->moving_color)
        {
            fld->selected=(fld->get_field())[j+8*i];
            fld->find_posssible_moves(i,j);
        }
    }
    else
    {
        if(fld->is_possible(i,j))
        {
            fld->make_move(fld->selected->x,fld->selected->y,i,j);
            if (fld->check_mate())
                switch(fld->moving_color)
                {
                case 0:{result->setText("Black\nwins");break;}
                case 1:{result->setText("White\nwins");break;}
                }
        }
        else
            fld->clear_possible();
    }
    update_grid();
    return;
}

void ChessGrid::resetBtnClick()
{
    delete fld;
    fld = new Playing_field();
    result->setText("");
    update_grid();
}

void ChessGrid::saveBtnClick()
{
    fld->out_to_file();
    return;
}


