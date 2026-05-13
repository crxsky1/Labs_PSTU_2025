#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QIcon>
#include "datastorage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем иконку приложения (из файла)
    a.setWindowIcon(QIcon("DropshippingApp.ico")); // Иконка должна лежать рядом с .exe

    // Инициализация хранилища данных
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
