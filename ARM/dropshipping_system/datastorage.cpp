#include "datastorage.h"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QCoreApplication>

QString DataStorage::lastError = "";

QString DataStorage::getDataPath()
{
    return QDir::homePath() + "/DropshippingData";
}

bool DataStorage::ensureDirectoryExists()
{
    QDir dir(getDataPath());
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            lastError = "Не удалось создать папку для данных";
            return false;
        }
    }
    return true;
}

// Объявляем функцию как статический метод класса
void DataStorage::addTestData()
{
    QList<Supplier> existingSuppliers = loadSuppliers();
    if (!existingSuppliers.isEmpty()) {
        return; // Данные уже есть
    }

    // Добавляем поставщиков (используем DataStorage::)
    Supplier s1(getNextSupplierId(), "ООО МегаДроп", "Иванов Иван", "+7-999-123-4567", "г. Москва");
    Supplier s2(getNextSupplierId(), "ИП Петров", "Петров Петр", "+7-999-765-4321", "г. СПб");
    Supplier s3(getNextSupplierId(), "ООО Быстрая доставка", "Сидорова Анна", "+7-999-555-1234", "г. Казань");

    DataStorage::saveSupplier(s1);
    DataStorage::saveSupplier(s2);
    DataStorage::saveSupplier(s3);

    // Добавляем товары
    Product p1(getNextProductId(), "Смартфон X100", 24999.99, 1, 50, "Новейший смартфон");
    Product p2(getNextProductId(), "Наушники Bluetooth", 3499.50, 1, 150, "Беспроводные наушники");
    Product p3(getNextProductId(), "Чехол для телефона", 599.00, 2, 300, "Силиконовый чехол");
    Product p4(getNextProductId(), "Портативный SSD 1TB", 8999.00, 3, 25, "Внешний SSD");

    DataStorage::saveProduct(p1);
    DataStorage::saveProduct(p2);
    DataStorage::saveProduct(p3);
    DataStorage::saveProduct(p4);

    // Добавляем заказы
    Order o1(getNextOrderId(), 1, "Алексей Смирнов", "+7-912-345-6789", 1, "2024-01-15", "Доставлен");
    Order o2(getNextOrderId(), 2, "Мария Иванова", "+7-923-456-7890", 2, "2024-01-16", "Отправлен");
    Order o3(getNextOrderId(), 1, "Дмитрий Козлов", "+7-934-567-8901", 1, "2024-01-17", "Новый");

    DataStorage::saveOrder(o1);
    DataStorage::saveOrder(o2);
    DataStorage::saveOrder(o3);
}

bool DataStorage::initStorage()
{
    if (!ensureDirectoryExists()) {
        return false;
    }

    // Создаём пустые файлы если их нет
    QString productsFile = getDataPath() + "/products.json";
    QString ordersFile = getDataPath() + "/orders.json";
    QString suppliersFile = getDataPath() + "/suppliers.json";

    if (!QFile::exists(productsFile)) {
        QFile file(productsFile);
        if (file.open(QIODevice::WriteOnly)) {
            file.write("[]"); // Пустой массив
            file.close();
        }
    }

    if (!QFile::exists(ordersFile)) {
        QFile file(ordersFile);
        if (file.open(QIODevice::WriteOnly)) {
            file.write("[]");
            file.close();
        }
    }

    if (!QFile::exists(suppliersFile)) {
        QFile file(suppliersFile);
        if (file.open(QIODevice::WriteOnly)) {
            file.write("[]");
            file.close();
        }
    }

    // Добавляем тестовые данные если файлы пустые
    if (loadProducts().isEmpty()) {
        addTestData();
    }

    return true;
}

// ============= ПРОДУКТЫ =============

QJsonObject DataStorage::productToJson(const Product& product)
{
    QJsonObject json;
    json["id"] = product.getId();
    json["name"] = product.getName();
    json["price"] = product.getPrice();
    json["supplierId"] = product.getSupplierId();
    json["stock"] = product.getStock();
    json["description"] = product.getDescription();
    return json;
}

Product DataStorage::productFromJson(const QJsonObject& json)
{
    return Product(
        json["id"].toInt(),
        json["name"].toString(),
        json["price"].toDouble(),
        json["supplierId"].toInt(),
        json["stock"].toInt(),
        json["description"].toString()
    );
}

QList<Product> DataStorage::loadProducts()
{
    QList<Product> products;
    QString filePath = getDataPath() + "/products.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        lastError = "Не удалось открыть файл продуктов";
        return products;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        return products;
    }

    QJsonArray array = doc.array();
    for (const QJsonValue& value : array) {
        if (value.isObject()) {
            products.append(productFromJson(value.toObject()));
        }
    }

    return products;
}

bool DataStorage::saveProduct(const Product& product)
{
    QList<Product> products = loadProducts();

    // Проверяем, существует ли уже продукт с таким ID
    for (int i = 0; i < products.size(); ++i) {
        if (products[i].getId() == product.getId()) {
            products[i] = product; // Обновляем существующий
            return updateProduct(product);
        }
    }

    // Добавляем новый
    products.append(product);

    QJsonArray array;
    for (const Product& p : products) {
        array.append(productToJson(p));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/products.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        lastError = "Не удалось сохранить продукт";
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool DataStorage::updateProduct(const Product& product)
{
    QList<Product> products = loadProducts();
    bool found = false;

    for (int i = 0; i < products.size(); ++i) {
        if (products[i].getId() == product.getId()) {
            products[i] = product;
            found = true;
            break;
        }
    }

    if (!found) {
        lastError = "Продукт не найден для обновления";
        return false;
    }

    QJsonArray array;
    for (const Product& p : products) {
        array.append(productToJson(p));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/products.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        lastError = "Не удалось обновить продукт";
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool DataStorage::deleteProduct(int id)
{
    QList<Product> products = loadProducts();
    QList<Product> newProducts;

    for (const Product& p : products) {
        if (p.getId() != id) {
            newProducts.append(p);
        }
    }

    if (newProducts.size() == products.size()) {
        lastError = "Продукт не найден для удаления";
        return false;
    }

    QJsonArray array;
    for (const Product& p : newProducts) {
        array.append(productToJson(p));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/products.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        lastError = "Не удалось удалить продукт";
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

int DataStorage::getNextProductId()
{
    QList<Product> products = loadProducts();
    int maxId = 0;
    for (const Product& p : products) {
        if (p.getId() > maxId) {
            maxId = p.getId();
        }
    }
    return maxId + 1;
}

// ============= ЗАКАЗЫ =============

QJsonObject DataStorage::orderToJson(const Order& order)
{
    QJsonObject json;
    json["id"] = order.getId();
    json["productId"] = order.getProductId();
    json["customerName"] = order.getCustomerName();
    json["customerPhone"] = order.getCustomerPhone();
    json["quantity"] = order.getQuantity();
    json["orderDate"] = order.getOrderDate();
    json["status"] = order.getStatus();
    return json;
}

Order DataStorage::orderFromJson(const QJsonObject& json)
{
    return Order(
        json["id"].toInt(),
        json["productId"].toInt(),
        json["customerName"].toString(),
        json["customerPhone"].toString(),
        json["quantity"].toInt(),
        json["orderDate"].toString(),
        json["status"].toString()
    );
}

QList<Order> DataStorage::loadOrders()
{
    QList<Order> orders;
    QString filePath = getDataPath() + "/orders.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return orders;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        return orders;
    }

    QJsonArray array = doc.array();
    for (const QJsonValue& value : array) {
        if (value.isObject()) {
            orders.append(orderFromJson(value.toObject()));
        }
    }

    return orders;
}

bool DataStorage::saveOrder(const Order& order)
{
    QList<Order> orders = loadOrders();

    for (int i = 0; i < orders.size(); ++i) {
        if (orders[i].getId() == order.getId()) {
            orders[i] = order;
            return updateOrder(order);
        }
    }

    orders.append(order);

    QJsonArray array;
    for (const Order& o : orders) {
        array.append(orderToJson(o));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/orders.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool DataStorage::updateOrder(const Order& order)
{
    QList<Order> orders = loadOrders();
    bool found = false;

    for (int i = 0; i < orders.size(); ++i) {
        if (orders[i].getId() == order.getId()) {
            orders[i] = order;
            found = true;
            break;
        }
    }

    if (!found) return false;

    QJsonArray array;
    for (const Order& o : orders) {
        array.append(orderToJson(o));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/orders.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool DataStorage::deleteOrder(int id)
{
    QList<Order> orders = loadOrders();
    QList<Order> newOrders;

    for (const Order& o : orders) {
        if (o.getId() != id) {
            newOrders.append(o);
        }
    }

    if (newOrders.size() == orders.size()) {
        return false;
    }

    QJsonArray array;
    for (const Order& o : newOrders) {
        array.append(orderToJson(o));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/orders.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

int DataStorage::getNextOrderId()
{
    QList<Order> orders = loadOrders();
    int maxId = 0;
    for (const Order& o : orders) {
        if (o.getId() > maxId) {
            maxId = o.getId();
        }
    }
    return maxId + 1;
}

// ============= ПОСТАВЩИКИ =============

QJsonObject DataStorage::supplierToJson(const Supplier& supplier)
{
    QJsonObject json;
    json["id"] = supplier.getId();
    json["name"] = supplier.getName();
    json["contact"] = supplier.getContact();
    json["phone"] = supplier.getPhone();
    json["address"] = supplier.getAddress();
    return json;
}

Supplier DataStorage::supplierFromJson(const QJsonObject& json)
{
    return Supplier(
        json["id"].toInt(),
        json["name"].toString(),
        json["contact"].toString(),
        json["phone"].toString(),
        json["address"].toString()
    );
}

QList<Supplier> DataStorage::loadSuppliers()
{
    QList<Supplier> suppliers;
    QString filePath = getDataPath() + "/suppliers.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return suppliers;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        return suppliers;
    }

    QJsonArray array = doc.array();
    for (const QJsonValue& value : array) {
        if (value.isObject()) {
            suppliers.append(supplierFromJson(value.toObject()));
        }
    }

    return suppliers;
}

bool DataStorage::saveSupplier(const Supplier& supplier)
{
    QList<Supplier> suppliers = loadSuppliers();

    for (int i = 0; i < suppliers.size(); ++i) {
        if (suppliers[i].getId() == supplier.getId()) {
            suppliers[i] = supplier;
            return updateSupplier(supplier);
        }
    }

    suppliers.append(supplier);

    QJsonArray array;
    for (const Supplier& s : suppliers) {
        array.append(supplierToJson(s));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/suppliers.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool DataStorage::updateSupplier(const Supplier& supplier)
{
    QList<Supplier> suppliers = loadSuppliers();
    bool found = false;

    for (int i = 0; i < suppliers.size(); ++i) {
        if (suppliers[i].getId() == supplier.getId()) {
            suppliers[i] = supplier;
            found = true;
            break;
        }
    }

    if (!found) return false;

    QJsonArray array;
    for (const Supplier& s : suppliers) {
        array.append(supplierToJson(s));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/suppliers.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool DataStorage::deleteSupplier(int id)
{
    QList<Supplier> suppliers = loadSuppliers();
    QList<Supplier> newSuppliers;

    for (const Supplier& s : suppliers) {
        if (s.getId() != id) {
            newSuppliers.append(s);
        }
    }

    if (newSuppliers.size() == suppliers.size()) {
        return false;
    }

    QJsonArray array;
    for (const Supplier& s : newSuppliers) {
        array.append(supplierToJson(s));
    }

    QJsonDocument doc(array);
    QString filePath = getDataPath() + "/suppliers.json";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

int DataStorage::getNextSupplierId()
{
    QList<Supplier> suppliers = loadSuppliers();
    int maxId = 0;
    for (const Supplier& s : suppliers) {
        if (s.getId() > maxId) {
            maxId = s.getId();
        }
    }
    return maxId + 1;
}
