#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product(int id = 0, const QString& name = "", double price = 0.0,
            int supplierId = 0, int stock = 0, const QString& desc = "");

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

private:
    int id;
    QString name;
    double price;
    int supplierId;
    int stock;
    QString description;
};

#endif // PRODUCT_H
