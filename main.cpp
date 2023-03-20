#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "startmenu.h"

int main(int argc, char *argv[])
{

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
    startmenu sm;
    sm.show();
    return a.exec();
}
