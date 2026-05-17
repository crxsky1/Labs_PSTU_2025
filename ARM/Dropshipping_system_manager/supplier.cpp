#include "supplier.h"

Supplier::Supplier(int id, const QString& name, const QString& contact,
                   const QString& phone, const QString& address)
    : id(id), name(name), contact(contact), phone(phone), address(address) {}

int Supplier::getId() const { return id; }
void Supplier::setId(int id) { this->id = id; }

QString Supplier::getName() const { return name; }
void Supplier::setName(const QString& name) { this->name = name; }

QString Supplier::getContact() const { return contact; }
void Supplier::setContact(const QString& contact) { this->contact = contact; }

QString Supplier::getPhone() const { return phone; }
void Supplier::setPhone(const QString& phone) { this->phone = phone; }

QString Supplier::getAddress() const { return address; }
void Supplier::setAddress(const QString& address) { this->address = address; }
