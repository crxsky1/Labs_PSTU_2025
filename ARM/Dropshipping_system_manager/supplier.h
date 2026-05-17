#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QString>

class Supplier
{
public:
    Supplier(int id = 0, const QString& name = "", const QString& contact = "",
             const QString& phone = "", const QString& address = "");

    int getId() const;
    void setId(int id);

    QString getName() const;
    void setName(const QString& name);

    QString getContact() const;
    void setContact(const QString& contact);

    QString getPhone() const;
    void setPhone(const QString& phone);

    QString getAddress() const;
    void setAddress(const QString& address);

private:
    int id;
    QString name;
    QString contact;
    QString phone;
    QString address;
};

#endif // SUPPLIER_H
