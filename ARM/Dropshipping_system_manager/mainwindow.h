#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QTabWidget>
#include <QGroupBox>
#include <QCheckBox>

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
    void addProductWithCategoryAndId(const QString& category, int customId);
    void editProductWithCategoryAndId(const QString& category, int customId, QLabel* warningLabel);
    void deleteProduct();
    void clearProductForm();
    void refreshProductsDisplay();

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
    void updateStatistics();

private:
    Ui::MainWindow *ui;

    QTabWidget *tabWidget;

    // Вкладка товаров
    QWidget *productsTab;
    QTableWidget *productsTable;
    QLineEdit *productIdEdit;          // Поле для редактирования ID
    QLineEdit *productNameEdit;
    QLineEdit *productPriceEdit;
    QLineEdit *productStockEdit;
    QTextEdit *productDescEdit;
    QComboBox *supplierCombo;
    QComboBox *categoryFilterCombo;
    QCheckBox *groupProductsCheck;
    int currentProductId;

    // Вкладка заказов
    QWidget *ordersTab;
    QTableWidget *ordersTable;
    QLineEdit *customerNameEdit;
    QLineEdit *customerPhoneEdit;
    QLineEdit *customerAddressEdit;
    QLineEdit *customerEmailEdit;
    QComboBox *productCombo;
    QSpinBox *quantitySpin;
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

    // Вкладка статистики
    QWidget *statisticsTab;
    QLabel *totalProductsLabel;
    QLabel *totalOrdersLabel;
    QLabel *newOrdersLabel;
    QLabel *processingOrdersLabel;
    QLabel *shippedOrdersLabel;
    QLabel *deliveredOrdersLabel;
    QLabel *cancelledOrdersLabel;

    void setupUI();
    void setupProductsTab();
    void setupOrdersTab();
    void setupSuppliersTab();
    void setupStatisticsTab();
    void refreshAll();
    void updateSupplierCombo();
    void updateProductCombo();
    void updateCategoryFilter();
};

#endif // MAINWINDOW_H
