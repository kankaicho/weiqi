#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define ON_BUG
#include <QMainWindow>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent* pevent);
    void mouseMoveEvent(QMouseEvent* mevent);
    void mousePressEvent(QMouseEvent* mevnet);
    void make_start(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2);
private:
    Ui::MainWindow *ui;
    game mgame;
};
#endif // MAINWINDOW_H
