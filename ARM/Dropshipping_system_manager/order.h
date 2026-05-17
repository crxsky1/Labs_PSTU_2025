#ifndef ORDER_H
#define ORDER_H

#include <QString>

class Order
{
public:
    Order(int id = 0, int productId = 0, const QString& customerName = "",
          const QString& customerPhone = "", const QString& customerAddress = "",
          int quantity = 1, const QString& orderDate = "", const QString& status = "Новый");

    int getId() const;
    void setId(int id);

    int getProductId() const;
    void setProductId(int id);

    QString getCustomerName() const;
    void setCustomerName(const QString& name);

    QString getCustomerPhone() const;
    void setCustomerPhone(const QString& phone);

    QString getCustomerAddress() const;
    void setCustomerAddress(const QString& address);

    int getQuantity() const;
    void setQuantity(int qty);

    QString getOrderDate() const;
    void setOrderDate(const QString& date);

    QString getStatus() const;
    void setStatus(const QString& status);

private:
    int id;
    int productId;
    QString customerName;
    QString customerPhone;
    QString customerAddress;
    int quantity;
    QString orderDate;
    QString status;
};

#endif // ORDER_H
