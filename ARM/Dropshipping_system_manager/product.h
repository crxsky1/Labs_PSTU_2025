#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product(int id = 0, const QString& name = "", double price = 0.0,
            int supplierId = 0, int stock = 0, const QString& desc = "",
            const QString& category = "Другое");

    // Копирующий конструктор и оператор присваивания
    Product(const Product& other) = default;
    Product& operator=(const Product& other) = default;

    int getId() const;
    void setId(int id);

    QString getName() const;
    void setName(const QString& name);

    double getPrice() const;
    void setPrice(double price);

    int getSupplierId() const;
    void setSupplierId(int id);

    int getStock() const;
    void setStock(int stock);

    QString getDescription() const;
    void setDescription(const QString& desc);

    QString getCategory() const;
    void setCategory(const QString& category);

private:
    int id;
    QString name;
    double price;
    int supplierId;
    int stock;
    QString description;
    QString category;
};

#endif // PRODUCT_H
