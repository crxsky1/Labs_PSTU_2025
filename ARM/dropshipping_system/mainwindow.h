#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>  // <-- ДОБАВИТЬ ЭТУ СТРОКУ!
#include <QTabWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Товары
    void addProduct();
    void editProduct();
    void deleteProduct();
    void loadProducts();
    void clearProductForm();

    // Заказы
    void addOrder();
    void editOrder();
    void deleteOrder();
    void loadOrders();
    void clearOrderForm();

    // Поставщики
    void addSupplier();
    void editSupplier();
    void deleteSupplier();
    void loadSuppliers();
    void clearSupplierForm();

    void onProductSelected();
    void onOrderSelected();
    void onSupplierSelected();

private:
    Ui::MainWindow *ui;

    QTabWidget *tabWidget;

    // Вкладка товаров
    QWidget *productsTab;
    QTableWidget *productsTable;
    QLineEdit *productNameEdit;
    QLineEdit *productPriceEdit;
    QLineEdit *productStockEdit;
    QTextEdit *productDescEdit;
    QComboBox *supplierCombo;
    int currentProductId;

    // Вкладка заказов
    QWidget *ordersTab;
    QTableWidget *ordersTable;
    QLineEdit *customerNameEdit;
    QLineEdit *customerPhoneEdit;
    QLineEdit *customerEmailEdit;
    QComboBox *productCombo;
    QSpinBox *quantitySpin;  // Теперь QSpinBox распознаётся
    QComboBox *statusCombo;
    int currentOrderId;

    // Вкладка поставщиков
    QWidget *suppliersTab;
    QTableWidget *suppliersTable;
    QLineEdit *supplierNameEdit;
    QLineEdit *supplierContactEdit;
    QLineEdit *supplierPhoneEdit;
    QLineEdit *supplierAddressEdit;
    int currentSupplierId;

    void setupUI();
    void setupProductsTab();
    void setupOrdersTab();
    void setupSuppliersTab();
    void refreshAll();
    void updateSupplierCombo();
    void updateProductCombo();
};

#endif // MAINWINDOW_H
