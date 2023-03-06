#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "play_menu.h"

int main(int argc, char *argv[])
{

    int board_size = 19;

    PLAYER_TYPE p1 = PLAYER_BOT;
    PLAYER_TYPE p2 = PLAYER_USER;

//    get_start(board_size,p1,p2);

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GO_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.make_start(board_size,p1,p2);
    w.show();
    return a.exec();
}
