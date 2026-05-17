#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "datastorage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!DataStorage::initStorage()) {
        QMessageBox::critical(nullptr, "Ошибка",
                              "Не удалось инициализировать хранилище данных:\n" +
                              DataStorage::getLastError());
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
