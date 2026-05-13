#include "product.h"

Product::Product(int id, const QString& name, double price,
                 int supplierId, int stock, const QString& desc)
    : id(id), name(name), price(price), supplierId(supplierId),
      stock(stock), description(desc) {}

int Product::getId() const { return id; }
void Product::setId(int id) { this->id = id; }

QString Product::getName() const { return name; }
void Product::setName(const QString& name) { this->name = name; }

double Product::getPrice() const { return price; }
void Product::setPrice(double price) { this->price = price; }

int Product::getSupplierId() const { return supplierId; }
void Product::setSupplierId(int id) { supplierId = id; }

int Product::getStock() const { return stock; }
void Product::setStock(int stock) { this->stock = stock; }

QString Product::getDescription() const { return description; }
void Product::setDescription(const QString& desc) { description = desc; }
