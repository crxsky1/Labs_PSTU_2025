#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QList>
#include <QString>
#include <QJsonObject>
#include "product.h"
#include "order.h"
#include "supplier.h"

class DataStorage
{
public:
    static bool initStorage();

    // Работа с продуктами
    static QList<Product> loadProducts();
    static bool saveProduct(const Product& product);
    static bool updateProduct(const Product& product);
    static bool deleteProduct(int id);
    static int getNextProductId();

    // Работа с заказами
    static QList<Order> loadOrders();
    static bool saveOrder(const Order& order);
    static bool updateOrder(const Order& order);
    static bool deleteOrder(int id);
    static int getNextOrderId();

    // Работа с поставщиками
    static QList<Supplier> loadSuppliers();
    static bool saveSupplier(const Supplier& supplier);
    static bool updateSupplier(const Supplier& supplier);
    static bool deleteSupplier(int id);
    static int getNextSupplierId();

    static QString getLastError() { return lastError; }

private:
    static QString lastError;
    static QString getDataPath();
    static bool ensureDirectoryExists();
    static void addTestData();  // <-- ДОБАВИТЬ ЭТУ СТРОКУ!

    // Вспомогательные методы для JSON
    static QJsonObject productToJson(const Product& product);
    static Product productFromJson(const QJsonObject& json);
    static QJsonObject orderToJson(const Order& order);
    static Order orderFromJson(const QJsonObject& json);
    static QJsonObject supplierToJson(const Supplier& supplier);
    static Supplier supplierFromJson(const QJsonObject& json);
};

#endif // DATASTORAGE_H
