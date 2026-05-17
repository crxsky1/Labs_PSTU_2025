#include "order.h"
#include <QDateTime>

Order::Order(int id, int productId, const QString& customerName,
             const QString& customerPhone, const QString& customerAddress,
             int quantity, const QString& orderDate, const QString& status)
    : id(id), productId(productId), customerName(customerName),
      customerPhone(customerPhone), customerAddress(customerAddress),
      quantity(quantity),
      orderDate(orderDate.isEmpty() ? QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") : orderDate),
      status(status) {}

int Order::getId() const { return id; }
void Order::setId(int id) { this->id = id; }

int Order::getProductId() const { return productId; }
void Order::setProductId(int id) { productId = id; }

QString Order::getCustomerName() const { return customerName; }
void Order::setCustomerName(const QString& name) { customerName = name; }

QString Order::getCustomerPhone() const { return customerPhone; }
void Order::setCustomerPhone(const QString& phone) { customerPhone = phone; }

QString Order::getCustomerAddress() const { return customerAddress; }
void Order::setCustomerAddress(const QString& address) { customerAddress = address; }

int Order::getQuantity() const { return quantity; }
void Order::setQuantity(int qty) { quantity = qty; }

QString Order::getOrderDate() const { return orderDate; }
void Order::setOrderDate(const QString& date) { orderDate = date; }

QString Order::getStatus() const { return status; }
void Order::setStatus(const QString& status) { this->status = status; }
