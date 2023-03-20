#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QPushButton>
#include <QString>

namespace Ui {
class startmenu;
}

class startmenu : public QWidget
{
    Q_OBJECT

public:
    explicit startmenu(QWidget *parent = nullptr);
    void init();
    ~startmenu();

private slots:
    void on_enterBtn_clicked();

private:
    Ui::startmenu *ui;
};

#endif // STARTMENU_H
