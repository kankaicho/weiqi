#include "startmenu.h"
#include "mainwindow.h"
#include "./ui_startmenu.h"

startmenu::startmenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startmenu)
{
    ui->setupUi(this);
    connect(ui->enter_btn,&QPushButton::clicked,this,&startmenu::on_enterBtn_clicked);
}

startmenu::~startmenu()
{
    delete ui;
}

void startmenu::on_enterBtn_clicked()
{
    int board_size = 19;

    PLAYER_TYPE p1 = PLAYER_BOT;
    PLAYER_TYPE p2 = PLAYER_USER;

    this->close();
    MainWindow* w = new MainWindow();
    w->make_start(board_size,p1,p2);
    w->show();
}

