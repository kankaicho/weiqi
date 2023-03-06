#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game.h"

#include "board_factory.h"
#include "player_factory.h""

#include <iostream>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPalette>
#define ON_BUG

#ifdef ON_BUG
    #include <iostream>
#endif

using namespace std;

int x_loc = 0, y_loc = 0, lastx = 0, lasty = 0;

int literal_num = 19;
int literal_size = 40;
int board_size = 820;
int background_border = 20;
int board_begloc_x = 40, board_begloc_y = 40;
int luozi = 5;
int rl_size = 15;
int piece_rad = 18;
int turn = 2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(board_size,board_size);
    this->setWindowTitle("GO");

    this->mgame.init(19,PLAYER_USER,PLAYER_USER);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make_start(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2)
{
    board_factory bf;
    board_ptr b1 = bf.produce_board(board_size);
    this->mgame.make_board(std::move(b1));

    player_factory pf;
    player_ptr p1 = pf.produce(player1);
    player_ptr p2 = pf.produce(player2);
    this->mgame.make_player(std::move(p1),std::move(p1));
#ifndef ON_BUG
    for(int i = 0; i < 19; i ++) {
        for(int j = 0; j < 19; j ++)
            cout << this->mgame.get_piecetype(i,j) << ' ';
        cout << '\n';
    }
#endif
}

void MainWindow::mousePressEvent(QMouseEvent* event) //下棋动作
{
#ifndef ON_BUG
    for(int i = 0; i < 19; i ++) {
        for(int j = 0; j < 19; j ++)
            cout << this->mgame.get_piecetype(i,j) << ' ';
        cout << '\n';
    }
#endif
    if(this->mgame.lazi(x_loc,y_loc,turn))
        turn ^= 1;
#ifdef ON_BUG
    this->mgame.debug_info();
#endif
    update();
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    x_loc = (event->position().x()-board_begloc_x+literal_size/2)/literal_size;
    y_loc = (event->position().y()-board_begloc_y+literal_size/2)/literal_size;
    update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    //绘制棋盘边界边框，棋盘内颜色
    QPainter painter(this); //画板
    painter.setRenderHint(QPainter::Antialiasing,true); //抗锯齿

    this->setAutoFillBackground(true);
    QPalette palette ; //画背景色
    palette.setColor(QPalette::Window, QColor("#B1723C"));
    this->setPalette(palette);

    centralWidget()->setMouseTracking(true);//接受鼠标的移动
    setMouseTracking(true);

    QPen pen = painter.pen();

    pen.setColor(QColor("#8D5822")); //棋盘边界边框
    pen.setWidth(7);
    painter.setPen(pen);

    QBrush brush; //画刷,棋盘内颜色
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    int beg_x = background_border;
    int beg_y = background_border;
    int end_x = beg_x+literal_size*literal_num;
    int end_y = beg_y+literal_size*literal_num;
    painter.drawRect(beg_x,beg_y,end_x,end_y);

    //绘制棋盘
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen); //黑线
    beg_x = board_begloc_x;
    beg_y = board_begloc_y;
    end_x = beg_x+literal_size*(literal_num-1);
    end_y = beg_y+literal_size*(literal_num-1);
    for(int i = 0; i < literal_num; ++i)
    {
        painter.drawLine(beg_x,beg_y+literal_size*i,end_x,beg_y+literal_size*i);
        painter.drawLine(beg_x+literal_size*i,beg_y,beg_x+literal_size*i,end_y);
    }


    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(beg_x+120-5,beg_y+120-5,10,10);
    painter.drawRect((beg_x+end_x)/2-5,beg_y+120-5,10,10);
    painter.drawRect(end_x-120-5,beg_y+120-5,10,10);
    painter.drawRect(beg_x+120-5,(beg_y+end_y)/2-5,10,10);
    painter.drawRect((beg_x+end_x)/2-5,(beg_y+end_y)/2-5,10,10);
    painter.drawRect(end_x-120-5,(beg_y+end_y)/2-5,10,10);
    painter.drawRect(beg_x+120-5,end_y-120-5,10,10);
    painter.drawRect((beg_x+end_x)/2-5,end_y-120-5,10,10);
    painter.drawRect(end_x-120-5,end_y-120-5,10,10);

    //循环遍历，画棋子
    painter.setPen(Qt::NoPen);  //去掉pen，避免画出的棋子边缘带线条
    for(int i = 0; i < literal_num; ++i)
    {
        for(int j = 0; j < literal_num; ++j)
        {
            if(mgame.get_piecetype(i,j) == blackpiece)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                //在第i行，第j列画一个圆形
                painter.drawEllipse(QPoint(i*literal_size+board_begloc_x,j*literal_size+board_begloc_x), piece_rad, piece_rad);
            }
            if(mgame.get_piecetype(i,j) == whitepiece)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(i*literal_size+board_begloc_x,j*literal_size+board_begloc_x), piece_rad, piece_rad);
            }
        }
    }

    //鼠标移动后，当前红方框标识
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    if(x_loc >= 0 && x_loc < literal_num && y_loc >= 0 && y_loc < literal_num)
    {
        int x_pos_c = x_loc*literal_size + board_begloc_x;
        int y_pos_c = y_loc*literal_size + board_begloc_y;
        int x_pos_l = x_pos_c - luozi;
        int x_pos_r = x_pos_c + luozi;
        int y_pos_d = y_pos_c - luozi;
        int y_pos_u = y_pos_c + luozi;
        painter.drawLine(x_pos_l-rl_size,y_pos_u,x_pos_l,y_pos_u);
        painter.drawLine(x_pos_l,y_pos_u,x_pos_l,y_pos_u+rl_size);
        painter.drawLine(x_pos_r,y_pos_u,x_pos_r+rl_size,y_pos_u);
        painter.drawLine(x_pos_r,y_pos_u,x_pos_r,y_pos_u+rl_size);
        painter.drawLine(x_pos_l-rl_size,y_pos_d,x_pos_l,y_pos_d);
        painter.drawLine(x_pos_l,y_pos_d-rl_size,x_pos_l,y_pos_d);
        painter.drawLine(x_pos_r,y_pos_d,x_pos_r+rl_size,y_pos_d);
        painter.drawLine(x_pos_r,y_pos_d-rl_size,x_pos_r,y_pos_d);
    }
    //lastx,lasty记录最后一个落子的位置
    //画最后一个落子位置

//    painter.drawLine((lasty+1)*40-6,(lastx+1)*40+20,(lasty+1)*40-1,(lastx+1)*40+20);
//    painter.drawLine((lasty+1)*40+1,(lastx+1)*40+20,(lasty+1)*40+6,(lastx+1)*40+20);
//    painter.drawLine((lasty+1)*40,(lastx+1)*40+14,(lasty+1)*40,(lastx+1)*40+19);
//    painter.drawLine((lasty+1)*40,(lastx+1)*40+21,(lasty+1)*40,(lastx+1)*40+26);


}
