#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datastorage.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QTableWidgetItem>
#include <QSpinBox>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QTabWidget>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentProductId(-1)
    , currentOrderId(-1)
    , currentSupplierId(-1)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("DropshippingApp.ico"));
    setupUI();
    refreshAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    setWindowTitle("Система управления дропшиппингом");
    resize(1000, 700);

    // Создаём вкладки
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    setupProductsTab();
    setupOrdersTab();
    setupSuppliersTab();

    tabWidget->addTab(productsTab, "Товары");
    tabWidget->addTab(ordersTab, "Заказы");
    tabWidget->addTab(suppliersTab, "Поставщики");
}

void MainWindow::setupProductsTab()
{
    productsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(productsTab);

    // Таблица товаров
    productsTable = new QTableWidget();
    productsTable->setColumnCount(5);
    productsTable->setHorizontalHeaderLabels({"ID", "Название", "Цена", "Остаток", "Поставщик"});
    productsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    productsTable->horizontalHeader()->setStretchLastSection(true);
    connect(productsTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onProductSelected);

    // Форма редактирования
    QGroupBox *productForm = new QGroupBox("Редактирование товара");
    QFormLayout *formLayout = new QFormLayout();

    productNameEdit = new QLineEdit();
    productPriceEdit = new QLineEdit();
    productStockEdit = new QLineEdit();
    productDescEdit = new QTextEdit();
    productDescEdit->setMaximumHeight(80);
    supplierCombo = new QComboBox();

    formLayout->addRow("Название:", productNameEdit);
    formLayout->addRow("Цена:", productPriceEdit);
    formLayout->addRow("Остаток:", productStockEdit);
    formLayout->addRow("Поставщик:", supplierCombo);
    formLayout->addRow("Описание:", productDescEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("Добавить");
    QPushButton *editBtn = new QPushButton("Обновить");
    QPushButton *deleteBtn = new QPushButton("Удалить");
    QPushButton *clearBtn = new QPushButton("Очистить");

    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(editBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(clearBtn);

    formLayout->addRow(buttonLayout);
    productForm->setLayout(formLayout);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(editBtn, &QPushButton::clicked, this, &MainWindow::editProduct);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteProduct);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearProductForm);

    layout->addWidget(productsTable);
    layout->addWidget(productForm);
}

void MainWindow::setupOrdersTab()
{
    ordersTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(ordersTab);

    // Таблица заказов
    ordersTable = new QTableWidget();
    ordersTable->setColumnCount(7);
    ordersTable->setHorizontalHeaderLabels({"ID", "Товар", "Клиент", "Телефон", "Кол-во", "Дата", "Статус"});
    ordersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ordersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ordersTable->horizontalHeader()->setStretchLastSection(true);
    connect(ordersTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onOrderSelected);

    // Форма редактирования
    QGroupBox *orderForm = new QGroupBox("Редактирование заказа");
    QFormLayout *formLayout = new QFormLayout();

    customerNameEdit = new QLineEdit();
    customerPhoneEdit = new QLineEdit();
    customerEmailEdit = new QLineEdit();
    productCombo = new QComboBox();
    quantitySpin = new QSpinBox();
    quantitySpin->setMinimum(1);
    quantitySpin->setMaximum(999);
    statusCombo = new QComboBox();
    statusCombo->addItems({"Новый", "В обработке", "Отправлен", "Доставлен", "Отменён"});

    formLayout->addRow("Клиент:", customerNameEdit);
    formLayout->addRow("Телефон:", customerPhoneEdit);
    formLayout->addRow("Email:", customerEmailEdit);
    formLayout->addRow("Товар:", productCombo);
    formLayout->addRow("Количество:", quantitySpin);
    formLayout->addRow("Статус:", statusCombo);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("Добавить");
    QPushButton *editBtn = new QPushButton("Обновить");
    QPushButton *deleteBtn = new QPushButton("Удалить");
    QPushButton *clearBtn = new QPushButton("Очистить");

    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(editBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(clearBtn);

    formLayout->addRow(buttonLayout);
    orderForm->setLayout(formLayout);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addOrder);
    connect(editBtn, &QPushButton::clicked, this, &MainWindow::editOrder);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteOrder);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearOrderForm);

    layout->addWidget(ordersTable);
    layout->addWidget(orderForm);
}

void MainWindow::setupSuppliersTab()
{
    suppliersTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(suppliersTab);

    // Таблица поставщиков
    suppliersTable = new QTableWidget();
    suppliersTable->setColumnCount(5);
    suppliersTable->setHorizontalHeaderLabels({"ID", "Название", "Контакт", "Телефон", "Адрес"});
    suppliersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    suppliersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    suppliersTable->horizontalHeader()->setStretchLastSection(true);
    connect(suppliersTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onSupplierSelected);

    // Форма редактирования
    QGroupBox *supplierForm = new QGroupBox("Редактирование поставщика");
    QFormLayout *formLayout = new QFormLayout();

    supplierNameEdit = new QLineEdit();
    supplierContactEdit = new QLineEdit();
    supplierPhoneEdit = new QLineEdit();
    supplierAddressEdit = new QLineEdit();

    formLayout->addRow("Название:", supplierNameEdit);
    formLayout->addRow("Контактное лицо:", supplierContactEdit);
    formLayout->addRow("Телефон:", supplierPhoneEdit);
    formLayout->addRow("Адрес:", supplierAddressEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("Добавить");
    QPushButton *editBtn = new QPushButton("Обновить");
    QPushButton *deleteBtn = new QPushButton("Удалить");
    QPushButton *clearBtn = new QPushButton("Очистить");

    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(editBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(clearBtn);

    formLayout->addRow(buttonLayout);
    supplierForm->setLayout(formLayout);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addSupplier);
    connect(editBtn, &QPushButton::clicked, this, &MainWindow::editSupplier);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteSupplier);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearSupplierForm);

    layout->addWidget(suppliersTable);
    layout->addWidget(supplierForm);
}

// ============= МЕТОДЫ ДЛЯ ТОВАРОВ =============

void MainWindow::loadProducts()
{
    productsTable->setRowCount(0);
    QList<Product> products = DataStorage::loadProducts();
    QList<Supplier> suppliers = DataStorage::loadSuppliers();

    productsTable->setRowCount(products.size());

    for (int i = 0; i < products.size(); ++i) {
        const Product& p = products[i];
        productsTable->setItem(i, 0, new QTableWidgetItem(QString::number(p.getId())));
        productsTable->setItem(i, 1, new QTableWidgetItem(p.getName()));
        productsTable->setItem(i, 2, new QTableWidgetItem(QString::number(p.getPrice(), 'f', 2)));
        productsTable->setItem(i, 3, new QTableWidgetItem(QString::number(p.getStock())));

        // Находим имя поставщика
        QString supplierName = "Не указан";
        for (const Supplier& s : suppliers) {
            if (s.getId() == p.getSupplierId()) {
                supplierName = s.getName();
                break;
            }
        }
        productsTable->setItem(i, 4, new QTableWidgetItem(supplierName));
    }
    productsTable->resizeColumnsToContents();
}

void MainWindow::addProduct()
{
    if (productNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название товара");
        return;
    }

    if (productPriceEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите цену товара");
        return;
    }

    Product p(
        DataStorage::getNextProductId(),
        productNameEdit->text(),
        productPriceEdit->text().toDouble(),
        supplierCombo->currentData().toInt(),
        productStockEdit->text().toInt(),
        productDescEdit->toPlainText()
    );

    if (DataStorage::saveProduct(p)) {
        QMessageBox::information(this, "Успех", "Товар добавлен");
        loadProducts();
        clearProductForm();
        updateProductCombo();
    } else {
        QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
    }
}

void MainWindow::editProduct()
{
    if (currentProductId < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите товар для редактирования");
        return;
    }

    if (productNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название товара");
        return;
    }

    Product p(
        currentProductId,
        productNameEdit->text(),
        productPriceEdit->text().toDouble(),
        supplierCombo->currentData().toInt(),
        productStockEdit->text().toInt(),
        productDescEdit->toPlainText()
    );

    if (DataStorage::updateProduct(p)) {
        QMessageBox::information(this, "Успех", "Товар обновлён");
        loadProducts();
        clearProductForm();
        updateProductCombo();
    } else {
        QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
    }
}

void MainWindow::deleteProduct()
{
    if (currentProductId < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите товар для удаления");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение",
                              "Удалить выбранный товар?") == QMessageBox::Yes) {
        if (DataStorage::deleteProduct(currentProductId)) {
            QMessageBox::information(this, "Успех", "Товар удалён");
            loadProducts();
            clearProductForm();
            updateProductCombo();
        } else {
            QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
        }
    }
}

void MainWindow::clearProductForm()
{
    productNameEdit->clear();
    productPriceEdit->clear();
    productStockEdit->clear();
    productDescEdit->clear();
    supplierCombo->setCurrentIndex(0);
    currentProductId = -1;
}

void MainWindow::onProductSelected()
{
    int row = productsTable->currentRow();
    if (row < 0) return;

    currentProductId = productsTable->item(row, 0)->text().toInt();
    productNameEdit->setText(productsTable->item(row, 1)->text());
    productPriceEdit->setText(productsTable->item(row, 2)->text());
    productStockEdit->setText(productsTable->item(row, 3)->text());

    // Устанавливаем поставщика в комбобоксе
    QString supplierName = productsTable->item(row, 4)->text();
    int index = supplierCombo->findText(supplierName);
    if (index >= 0) {
        supplierCombo->setCurrentIndex(index);
    }

    // Загружаем описание из БД
    QList<Product> products = DataStorage::loadProducts();
    for (const Product& p : products) {
        if (p.getId() == currentProductId) {
            productDescEdit->setText(p.getDescription());
            break;
        }
    }
}

// ============= МЕТОДЫ ДЛЯ ЗАКАЗОВ =============

void MainWindow::loadOrders()
{
    ordersTable->setRowCount(0);
    QList<Order> orders = DataStorage::loadOrders();
    QList<Product> products = DataStorage::loadProducts();

    ordersTable->setRowCount(orders.size());

    for (int i = 0; i < orders.size(); ++i) {
        const Order& o = orders[i];
        ordersTable->setItem(i, 0, new QTableWidgetItem(QString::number(o.getId())));

        // Находим название товара
        QString productName = "Не указан";
        for (const Product& p : products) {
            if (p.getId() == o.getProductId()) {
                productName = p.getName();
                break;
            }
        }
        ordersTable->setItem(i, 1, new QTableWidgetItem(productName));
        ordersTable->setItem(i, 2, new QTableWidgetItem(o.getCustomerName()));
        ordersTable->setItem(i, 3, new QTableWidgetItem(o.getCustomerPhone()));
        ordersTable->setItem(i, 4, new QTableWidgetItem(QString::number(o.getQuantity())));
        ordersTable->setItem(i, 5, new QTableWidgetItem(o.getOrderDate()));
        ordersTable->setItem(i, 6, new QTableWidgetItem(o.getStatus()));
    }
    ordersTable->resizeColumnsToContents();
}

void MainWindow::addOrder()
{
    if (customerNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя клиента");
        return;
    }

    if (productCombo->currentData().toInt() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите товар");
        return;
    }

    Order o(
        DataStorage::getNextOrderId(),
        productCombo->currentData().toInt(),
        customerNameEdit->text(),
        customerPhoneEdit->text(),
        quantitySpin->value(),
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),
        statusCombo->currentText()
    );

    if (DataStorage::saveOrder(o)) {
        QMessageBox::information(this, "Успех", "Заказ добавлен");
        loadOrders();
        clearOrderForm();
    } else {
        QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
    }
}

void MainWindow::editOrder()
{
    if (currentOrderId < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите заказ для редактирования");
        return;
    }

    Order o(
        currentOrderId,
        productCombo->currentData().toInt(),
        customerNameEdit->text(),
        customerPhoneEdit->text(),
        quantitySpin->value(),
        "", // Дата остаётся старая
        statusCombo->currentText()
    );

    if (DataStorage::updateOrder(o)) {
        QMessageBox::information(this, "Успех", "Заказ обновлён");
        loadOrders();
        clearOrderForm();
    } else {
        QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
    }
}

void MainWindow::deleteOrder()
{
    if (currentOrderId < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите заказ для удаления");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение",
                              "Удалить выбранный заказ?") == QMessageBox::Yes) {
        if (DataStorage::deleteOrder(currentOrderId)) {
            QMessageBox::information(this, "Успех", "Заказ удалён");
            loadOrders();
            clearOrderForm();
        } else {
            QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
        }
    }
}

void MainWindow::clearOrderForm()
{
    customerNameEdit->clear();
    customerPhoneEdit->clear();
    customerEmailEdit->clear();
    productCombo->setCurrentIndex(0);
    quantitySpin->setValue(1);
    statusCombo->setCurrentIndex(0);
    currentOrderId = -1;
}

void MainWindow::onOrderSelected()
{
    int row = ordersTable->currentRow();
    if (row < 0) return;

    currentOrderId = ordersTable->item(row, 0)->text().toInt();
    QString productName = ordersTable->item(row, 1)->text();
    customerNameEdit->setText(ordersTable->item(row, 2)->text());
    customerPhoneEdit->setText(ordersTable->item(row, 3)->text());
    quantitySpin->setValue(ordersTable->item(row, 4)->text().toInt());
    statusCombo->setCurrentText(ordersTable->item(row, 6)->text());

    // Устанавливаем товар в комбобоксе
    int index = productCombo->findText(productName);
    if (index >= 0) {
        productCombo->setCurrentIndex(index);
    }
}

// ============= МЕТОДЫ ДЛЯ ПОСТАВЩИКОВ =============

void MainWindow::loadSuppliers()
{
    suppliersTable->setRowCount(0);
    QList<Supplier> suppliers = DataStorage::loadSuppliers();

    suppliersTable->setRowCount(suppliers.size());

    for (int i = 0; i < suppliers.size(); ++i) {
        const Supplier& s = suppliers[i];
        suppliersTable->setItem(i, 0, new QTableWidgetItem(QString::number(s.getId())));
        suppliersTable->setItem(i, 1, new QTableWidgetItem(s.getName()));
        suppliersTable->setItem(i, 2, new QTableWidgetItem(s.getContact()));
        suppliersTable->setItem(i, 3, new QTableWidgetItem(s.getPhone()));
        suppliersTable->setItem(i, 4, new QTableWidgetItem(s.getAddress()));
    }
    suppliersTable->resizeColumnsToContents();
}

void MainWindow::addSupplier()
{
    if (supplierNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название поставщика");
        return;
    }

    Supplier s(
        DataStorage::getNextSupplierId(),
        supplierNameEdit->text(),
        supplierContactEdit->text(),
        supplierPhoneEdit->text(),
        supplierAddressEdit->text()
    );

    if (DataStorage::saveSupplier(s)) {
        QMessageBox::information(this, "Успех", "Поставщик добавлен");
        loadSuppliers();
        clearSupplierForm();
        updateSupplierCombo();
    } else {
        QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
    }
}

void MainWindow::editSupplier()
{
    if (currentSupplierId < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите поставщика для редактирования");
        return;
    }

    Supplier s(
        currentSupplierId,
        supplierNameEdit->text(),
        supplierContactEdit->text(),
        supplierPhoneEdit->text(),
        supplierAddressEdit->text()
    );

    if (DataStorage::updateSupplier(s)) {
        QMessageBox::information(this, "Успех", "Поставщик обновлён");
        loadSuppliers();
        clearSupplierForm();
        updateSupplierCombo();
    } else {
        QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
    }
}

void MainWindow::deleteSupplier()
{
    if (currentSupplierId < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите поставщика для удаления");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение",
                              "Удалить выбранного поставщика?") == QMessageBox::Yes) {
        if (DataStorage::deleteSupplier(currentSupplierId)) {
            QMessageBox::information(this, "Успех", "Поставщик удалён");
            loadSuppliers();
            clearSupplierForm();
            updateSupplierCombo();
        } else {
            QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
        }
    }
}

void MainWindow::clearSupplierForm()
{
    supplierNameEdit->clear();
    supplierContactEdit->clear();
    supplierPhoneEdit->clear();
    supplierAddressEdit->clear();
    currentSupplierId = -1;
}

void MainWindow::onSupplierSelected()
{
    int row = suppliersTable->currentRow();
    if (row < 0) return;

    currentSupplierId = suppliersTable->item(row, 0)->text().toInt();
    supplierNameEdit->setText(suppliersTable->item(row, 1)->text());
    supplierContactEdit->setText(suppliersTable->item(row, 2)->text());
    supplierPhoneEdit->setText(suppliersTable->item(row, 3)->text());
    supplierAddressEdit->setText(suppliersTable->item(row, 4)->text());
}

// ============= ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ =============

void MainWindow::refreshAll()
{
    loadProducts();
    loadOrders();
    loadSuppliers();
    updateSupplierCombo();
    updateProductCombo();
}

void MainWindow::updateSupplierCombo()
{
    supplierCombo->clear();
    QList<Supplier> suppliers = DataStorage::loadSuppliers();
    for (const Supplier& s : suppliers) {
        supplierCombo->addItem(s.getName(), s.getId());
    }
}

void MainWindow::updateProductCombo()
{
    productCombo->clear();
    QList<Product> products = DataStorage::loadProducts();
    for (const Product& p : products) {
        productCombo->addItem(p.getName(), p.getId());
    }
}
