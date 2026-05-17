#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datastorage.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
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
#include <QtGlobal>
#include <QDateTime>
#include <QDebug>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentProductId(-1)
    , currentOrderId(-1)
    , currentSupplierId(-1)
{
    ui->setupUi(this);
    setupUI();
    refreshAll();
    updateStatistics();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    setWindowTitle("Система управления дропшиппингом");
    resize(1200, 800);

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    setupProductsTab();
    setupOrdersTab();
    setupSuppliersTab();
    setupStatisticsTab();

    tabWidget->addTab(productsTab, "📦 Товары");
    tabWidget->addTab(ordersTab, "📋 Заказы");
    tabWidget->addTab(suppliersTab, "🏢 Поставщики");
    tabWidget->addTab(statisticsTab, "📊 Статистика");
}

void MainWindow::setupProductsTab()
{
    productsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(productsTab);

    // Панель фильтрации и группировки
    QHBoxLayout *filterLayout = new QHBoxLayout();

    QLabel *filterLabel = new QLabel("Категория:");
    categoryFilterCombo = new QComboBox();
    categoryFilterCombo->addItem("Все товары");

    groupProductsCheck = new QCheckBox("Группировать одинаковые товары от разных поставщиков");
    groupProductsCheck->setChecked(false);

    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(categoryFilterCombo);
    filterLayout->addStretch();
    filterLayout->addWidget(groupProductsCheck);

    connect(categoryFilterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int){ refreshProductsDisplay(); });
    connect(groupProductsCheck, &QCheckBox::toggled,
            [this](bool){ refreshProductsDisplay(); });

    // Таблица товаров
    productsTable = new QTableWidget();
    productsTable->setColumnCount(6);
    productsTable->setHorizontalHeaderLabels({"ID", "Название", "Цена", "Остаток", "Поставщик", "Категория"});
    productsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    productsTable->horizontalHeader()->setStretchLastSection(true);
    productsTable->verticalHeader()->setVisible(false);
    connect(productsTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onProductSelected);

    // Форма редактирования
    QGroupBox *productForm = new QGroupBox("Редактирование товара");
    QFormLayout *formLayout = new QFormLayout();

    // Поле для ID
    QHBoxLayout *idLayout = new QHBoxLayout();
    QLabel *idLabel = new QLabel("ID товара:");
    productIdEdit = new QLineEdit();
    productIdEdit->setReadOnly(false);
    productIdEdit->setMaximumWidth(100);
    QLabel *idWarningLabel = new QLabel("⚠️ Внимание! Изменение ID может повлиять на заказы");
    idWarningLabel->setStyleSheet("color: #ff9800; font-size: 9px;");
    idWarningLabel->setVisible(false);

    idLayout->addWidget(idLabel);
    idLayout->addWidget(productIdEdit);
    idLayout->addWidget(idWarningLabel);
    idLayout->addStretch();

    productNameEdit = new QLineEdit();
    productPriceEdit = new QLineEdit();
    productStockEdit = new QLineEdit();
    productDescEdit = new QTextEdit();
    productDescEdit->setMaximumHeight(80);
    supplierCombo = new QComboBox();

    QComboBox *categoryCombo = new QComboBox();
    categoryCombo->addItems({"Электроника", "Для дома", "Аксессуары", "Одежда", "Другое"});
    categoryCombo->setEditable(true);

    formLayout->addRow(idLayout);
    formLayout->addRow("Название:", productNameEdit);
    formLayout->addRow("Цена:", productPriceEdit);
    formLayout->addRow("Остаток:", productStockEdit);
    formLayout->addRow("Категория:", categoryCombo);
    formLayout->addRow("Поставщик:", supplierCombo);
    formLayout->addRow("Описание:", productDescEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("➕ Добавить");
    QPushButton *editBtn = new QPushButton("✏ Обновить");
    QPushButton *deleteBtn = new QPushButton("🗑 Удалить");
    QPushButton *clearBtn = new QPushButton("🧹 Очистить");

    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(editBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(clearBtn);

    formLayout->addRow(buttonLayout);
    productForm->setLayout(formLayout);

    connect(addBtn, &QPushButton::clicked, [this, categoryCombo]() {
        int customId = productIdEdit->text().toInt();
        addProductWithCategoryAndId(categoryCombo->currentText(), customId);
    });
    connect(editBtn, &QPushButton::clicked, [this, categoryCombo, idWarningLabel]() {
        int customId = productIdEdit->text().toInt();
        editProductWithCategoryAndId(categoryCombo->currentText(), customId, idWarningLabel);
    });
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteProduct);
    connect(clearBtn, &QPushButton::clicked, [this, idWarningLabel]() {
        clearProductForm();
        idWarningLabel->setVisible(false);
    });

    layout->addLayout(filterLayout);
    layout->addWidget(productsTable);
    layout->addWidget(productForm);
}

void MainWindow::setupOrdersTab()
{
    ordersTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(ordersTab);

    ordersTable = new QTableWidget();
    ordersTable->setColumnCount(8);
    ordersTable->setHorizontalHeaderLabels({"ID", "Товар", "Клиент", "Телефон", "Адрес", "Кол-во", "Дата", "Статус"});
    ordersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ordersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ordersTable->horizontalHeader()->setStretchLastSection(true);
    ordersTable->verticalHeader()->setVisible(false);
    connect(ordersTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onOrderSelected);

    QGroupBox *orderForm = new QGroupBox("Редактирование заказа");
    QFormLayout *formLayout = new QFormLayout();

    customerNameEdit = new QLineEdit();
    customerPhoneEdit = new QLineEdit();
    customerAddressEdit = new QLineEdit();
    customerEmailEdit = new QLineEdit();
    productCombo = new QComboBox();
    quantitySpin = new QSpinBox();
    quantitySpin->setMinimum(1);
    quantitySpin->setMaximum(999);
    statusCombo = new QComboBox();
    statusCombo->addItems({"Новый", "В обработке", "Отправлен", "Доставлен", "Отменён"});

    formLayout->addRow("Клиент:", customerNameEdit);
    formLayout->addRow("Телефон:", customerPhoneEdit);
    formLayout->addRow("Адрес:", customerAddressEdit);
    formLayout->addRow("Email:", customerEmailEdit);
    formLayout->addRow("Товар:", productCombo);
    formLayout->addRow("Количество:", quantitySpin);
    formLayout->addRow("Статус:", statusCombo);

    QLabel *infoLabel = new QLabel("ℹ️ При изменении статуса на 'Отправлен' товар будет списан со склада");
    infoLabel->setStyleSheet("color: #ff9800; font-size: 10px;");
    formLayout->addRow(infoLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("➕ Добавить");
    QPushButton *editBtn = new QPushButton("✏ Обновить");
    QPushButton *deleteBtn = new QPushButton("🗑 Удалить");
    QPushButton *clearBtn = new QPushButton("🧹 Очистить");

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

    suppliersTable = new QTableWidget();
    suppliersTable->setColumnCount(5);
    suppliersTable->setHorizontalHeaderLabels({"ID", "Название", "Контакт", "Телефон", "Адрес"});
    suppliersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    suppliersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    suppliersTable->horizontalHeader()->setStretchLastSection(true);
    suppliersTable->verticalHeader()->setVisible(false);
    connect(suppliersTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onSupplierSelected);

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
    QPushButton *addBtn = new QPushButton("➕ Добавить");
    QPushButton *editBtn = new QPushButton("✏ Обновить");
    QPushButton *deleteBtn = new QPushButton("🗑 Удалить");
    QPushButton *clearBtn = new QPushButton("🧹 Очистить");

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

void MainWindow::setupStatisticsTab()
{
    statisticsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(statisticsTab);

    QLabel *titleLabel = new QLabel("Статистика системы");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2196f3;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QPushButton *refreshBtn = new QPushButton("🔄 Обновить статистику");
    refreshBtn->setFixedWidth(200);
    connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::updateStatistics);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(refreshBtn);
    btnLayout->addStretch();
    layout->addLayout(btnLayout);

    // Общая статистика товаров
    QGroupBox *productsGroup = new QGroupBox("Общая статистика товаров");
    QGridLayout *productsLayout = new QGridLayout();

    totalProductsLabel = new QLabel("0");
    totalProductsLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #4caf50;");
    productsLayout->addWidget(new QLabel("📦 Суммарное количество товаров на складе:"), 0, 0);
    productsLayout->addWidget(totalProductsLabel, 0, 1);

    productsGroup->setLayout(productsLayout);
    layout->addWidget(productsGroup);

    // Статистика заказов
    QGroupBox *ordersGroup = new QGroupBox("Статистика заказов");
    QGridLayout *ordersLayout = new QGridLayout();

    totalOrdersLabel = new QLabel("0");
    totalOrdersLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    newOrdersLabel = new QLabel("0");
    newOrdersLabel->setStyleSheet("font-size: 16px; color: #ff9800;");

    processingOrdersLabel = new QLabel("0");
    processingOrdersLabel->setStyleSheet("font-size: 16px; color: #2196f3;");

    shippedOrdersLabel = new QLabel("0");
    shippedOrdersLabel->setStyleSheet("font-size: 16px; color: #4caf50;");

    deliveredOrdersLabel = new QLabel("0");
    deliveredOrdersLabel->setStyleSheet("font-size: 16px; color: #9c27b0;");

    cancelledOrdersLabel = new QLabel("0");
    cancelledOrdersLabel->setStyleSheet("font-size: 16px; color: #f44336;");

    ordersLayout->addWidget(new QLabel("📋 Всего заказов:"), 0, 0);
    ordersLayout->addWidget(totalOrdersLabel, 0, 1);
    ordersLayout->addWidget(new QLabel("🟠 Новые:"), 1, 0);
    ordersLayout->addWidget(newOrdersLabel, 1, 1);
    ordersLayout->addWidget(new QLabel("🔵 В обработке:"), 2, 0);
    ordersLayout->addWidget(processingOrdersLabel, 2, 1);
    ordersLayout->addWidget(new QLabel("🟢 Отправленные:"), 3, 0);
    ordersLayout->addWidget(shippedOrdersLabel, 3, 1);
    ordersLayout->addWidget(new QLabel("🟣 Доставленные:"), 4, 0);
    ordersLayout->addWidget(deliveredOrdersLabel, 4, 1);
    ordersLayout->addWidget(new QLabel("🔴 Отменённые:"), 5, 0);
    ordersLayout->addWidget(cancelledOrdersLabel, 5, 1);

    ordersGroup->setLayout(ordersLayout);
    layout->addWidget(ordersGroup);

    layout->addStretch();
}

// ============= МЕТОДЫ ДЛЯ ТОВАРОВ =============

void MainWindow::refreshProductsDisplay()
{
    productsTable->setRowCount(0);

    QList<Product> products;
    QString category = categoryFilterCombo->currentText();
    bool groupProducts = groupProductsCheck->isChecked();

    if (groupProducts) {
        products = DataStorage::getGroupedProductsByName();
    } else {
        products = DataStorage::loadProducts();
    }

    if (category != "Все товары") {
        QList<Product> filtered;
        for (const Product& p : products) {
            if (p.getCategory() == category) {
                filtered.append(p);
            }
        }
        products = filtered;
    }

    QList<Supplier> suppliers = DataStorage::loadSuppliers();

    productsTable->setRowCount(products.size());

    for (int i = 0; i < products.size(); ++i) {
        const Product& p = products[i];
        productsTable->setItem(i, 0, new QTableWidgetItem(QString::number(p.getId())));
        productsTable->setItem(i, 1, new QTableWidgetItem(p.getName()));
        productsTable->setItem(i, 2, new QTableWidgetItem(QString::number(p.getPrice(), 'f', 2)));
        productsTable->setItem(i, 3, new QTableWidgetItem(QString::number(p.getStock())));

        QString supplierName = "Не указан";
        for (const Supplier& s : suppliers) {
            if (s.getId() == p.getSupplierId()) {
                supplierName = s.getName();
                break;
            }
        }
        productsTable->setItem(i, 4, new QTableWidgetItem(supplierName));
        productsTable->setItem(i, 5, new QTableWidgetItem(p.getCategory()));
    }
    productsTable->resizeColumnsToContents();

    if (groupProducts) {
        statusBar()->showMessage("Включена группировка одинаковых товаров от разных поставщиков", 2000);
    }
}

void MainWindow::addProductWithCategoryAndId(const QString& category, int customId)
{
    if (productNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название товара");
        return;
    }

    int newId = customId;
    if (newId <= 0) {
        newId = DataStorage::getNextProductId();
    } else {
        QList<Product> existingProducts = DataStorage::loadProducts();
        for (const Product& p : existingProducts) {
            if (p.getId() == newId) {
                QMessageBox::warning(this, "Ошибка", "Товар с таким ID уже существует!");
                return;
            }
        }
    }

    Product p(
        newId,
        productNameEdit->text(),
        productPriceEdit->text().toDouble(),
        supplierCombo->currentData().toInt(),
        productStockEdit->text().toInt(),
        productDescEdit->toPlainText(),
        category
    );

    if (DataStorage::saveProduct(p)) {
        QMessageBox::information(this, "Успех", QString("Товар добавлен с ID: %1").arg(newId));
        refreshProductsDisplay();
        clearProductForm();
        updateProductCombo();
        updateCategoryFilter();
        updateStatistics();
    } else {
        QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
    }
}

void MainWindow::editProductWithCategoryAndId(const QString& category, int newId, QLabel* warningLabel)
{
    if (currentProductId < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите товар для редактирования");
        return;
    }

    int oldId = currentProductId;
    int finalId = newId;

    if (newId <= 0) {
        finalId = oldId;
    }

    if (finalId != oldId) {
        QList<Product> existingProducts = DataStorage::loadProducts();
        for (const Product& p : existingProducts) {
            if (p.getId() == finalId && finalId != oldId) {
                QMessageBox::warning(this, "Ошибка", "Товар с таким ID уже существует!");
                warningLabel->setVisible(true);
                return;
            }
        }

        int reply = QMessageBox::question(this, "Подтверждение",
            QString("Внимание! Вы меняете ID товара с %1 на %2.\n\n"
                    "Это может повлиять на существующие заказы, связанные с этим товаром.\n\n"
                    "Продолжить?").arg(oldId).arg(finalId),
            QMessageBox::Yes | QMessageBox::No);

        if (reply != QMessageBox::Yes) {
            return;
        }

        QList<Order> orders = DataStorage::loadOrders();
        for (Order& o : orders) {
            if (o.getProductId() == oldId) {
                o.setProductId(finalId);
                DataStorage::updateOrder(o);
            }
        }
    }

    Product p(
        finalId,
        productNameEdit->text(),
        productPriceEdit->text().toDouble(),
        supplierCombo->currentData().toInt(),
        productStockEdit->text().toInt(),
        productDescEdit->toPlainText(),
        category
    );

    if (finalId != oldId) {
        DataStorage::deleteProduct(oldId);
    }

    if (DataStorage::saveProduct(p)) {
        QString message = "Товар обновлён";
        if (finalId != oldId) {
            message += QString("\nID изменён с %1 на %2").arg(oldId).arg(finalId);
            message += "\nID в связанных заказах также обновлён!";
        }
        QMessageBox::information(this, "Успех", message);

        refreshProductsDisplay();
        clearProductForm();
        updateProductCombo();
        updateCategoryFilter();
        updateStatistics();
        if (warningLabel) warningLabel->setVisible(false);
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

    int reply = QMessageBox::question(this, "Подтверждение",
        QString("Удалить товар с ID %1?\n\nВнимание! Это действие также удалит все связанные заказы!").arg(currentProductId),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QList<Order> orders = DataStorage::loadOrders();
        for (const Order& o : orders) {
            if (o.getProductId() == currentProductId) {
                DataStorage::deleteOrder(o.getId());
            }
        }

        if (DataStorage::deleteProduct(currentProductId)) {
            QMessageBox::information(this, "Успех", "Товар и связанные заказы удалены");
            refreshProductsDisplay();
            clearProductForm();
            updateProductCombo();
            updateCategoryFilter();
            updateStatistics();
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
    if (productIdEdit) {
        productIdEdit->clear();
    }
    currentProductId = -1;
}

void MainWindow::onProductSelected()
{
    int row = productsTable->currentRow();
    if (row < 0) return;

    currentProductId = productsTable->item(row, 0)->text().toInt();

    if (productIdEdit) {
        productIdEdit->setText(QString::number(currentProductId));
    }

    productNameEdit->setText(productsTable->item(row, 1)->text());
    productPriceEdit->setText(productsTable->item(row, 2)->text());
    productStockEdit->setText(productsTable->item(row, 3)->text());

    QString supplierName = productsTable->item(row, 4)->text();
    int index = supplierCombo->findText(supplierName);
    if (index >= 0) {
        supplierCombo->setCurrentIndex(index);
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
        ordersTable->setItem(i, 4, new QTableWidgetItem(o.getCustomerAddress()));
        ordersTable->setItem(i, 5, new QTableWidgetItem(QString::number(o.getQuantity())));
        ordersTable->setItem(i, 6, new QTableWidgetItem(o.getOrderDate()));
        ordersTable->setItem(i, 7, new QTableWidgetItem(o.getStatus()));
    }
    ordersTable->resizeColumnsToContents();
}

void MainWindow::addOrder()
{
    if (customerNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя клиента");
        return;
    }

    if (customerAddressEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите адрес доставки");
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
        customerAddressEdit->text(),
        quantitySpin->value(),
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),
        statusCombo->currentText()
    );

    if (DataStorage::saveOrder(o)) {
        QMessageBox::information(this, "Успех", "Заказ добавлен");
        loadOrders();
        clearOrderForm();
        updateStatistics();
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

    QString oldStatus = "";
    QList<Order> orders = DataStorage::loadOrders();
    for (const Order& o : orders) {
        if (o.getId() == currentOrderId) {
            oldStatus = o.getStatus();
            break;
        }
    }

    QString newStatus = statusCombo->currentText();

    Order o(
        currentOrderId,
        productCombo->currentData().toInt(),
        customerNameEdit->text(),
        customerPhoneEdit->text(),
        customerAddressEdit->text(),
        quantitySpin->value(),
        "",
        newStatus
    );

    if (DataStorage::updateOrder(o)) {
        if (newStatus == "Отправлен" && oldStatus != "Отправлен") {
            DataStorage::updateProductStock(productCombo->currentData().toInt(), quantitySpin->value());
            QMessageBox::information(this, "Склад обновлён",
                "Товар списан со склада в количестве: " + QString::number(quantitySpin->value()));
        }

        QMessageBox::information(this, "Успех", "Заказ обновлён");
        loadOrders();
        refreshProductsDisplay();
        clearOrderForm();
        updateStatistics();
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

    if (QMessageBox::question(this, "Подтверждение", "Удалить выбранный заказ?") == QMessageBox::Yes) {
        if (DataStorage::deleteOrder(currentOrderId)) {
            QMessageBox::information(this, "Успех", "Заказ удалён");
            loadOrders();
            clearOrderForm();
            updateStatistics();
        } else {
            QMessageBox::critical(this, "Ошибка", DataStorage::getLastError());
        }
    }
}

void MainWindow::clearOrderForm()
{
    customerNameEdit->clear();
    customerPhoneEdit->clear();
    customerAddressEdit->clear();
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
    customerAddressEdit->setText(ordersTable->item(row, 4)->text());
    quantitySpin->setValue(ordersTable->item(row, 5)->text().toInt());
    statusCombo->setCurrentText(ordersTable->item(row, 7)->text());

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
        updateStatistics();
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
        updateStatistics();
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

    if (QMessageBox::question(this, "Подтверждение", "Удалить выбранного поставщика?") == QMessageBox::Yes) {
        if (DataStorage::deleteSupplier(currentSupplierId)) {
            QMessageBox::information(this, "Успех", "Поставщик удалён");
            loadSuppliers();
            clearSupplierForm();
            updateSupplierCombo();
            updateStatistics();
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

void MainWindow::updateStatistics()
{
    int totalStock = DataStorage::getTotalProductsCount();
    totalProductsLabel->setText(QString::number(totalStock));

    QList<Order> orders = DataStorage::loadOrders();
    totalOrdersLabel->setText(QString::number(orders.size()));

    int newOrders = 0, processing = 0, shipped = 0, delivered = 0, cancelled = 0;

    for (const Order& o : orders) {
        QString status = o.getStatus();
        if (status == "Новый") newOrders++;
        else if (status == "В обработке") processing++;
        else if (status == "Отправлен") shipped++;
        else if (status == "Доставлен") delivered++;
        else if (status == "Отменён") cancelled++;
    }

    newOrdersLabel->setText(QString::number(newOrders));
    processingOrdersLabel->setText(QString::number(processing));
    shippedOrdersLabel->setText(QString::number(shipped));
    deliveredOrdersLabel->setText(QString::number(delivered));
    cancelledOrdersLabel->setText(QString::number(cancelled));
}

void MainWindow::refreshAll()
{
    refreshProductsDisplay();
    loadOrders();
    loadSuppliers();
    updateSupplierCombo();
    updateProductCombo();
    updateCategoryFilter();
    updateStatistics();
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

void MainWindow::updateCategoryFilter()
{
    categoryFilterCombo->clear();
    categoryFilterCombo->addItem("Все товары");
    QStringList categories = DataStorage::getAllCategories();
    categoryFilterCombo->addItems(categories);
}
