#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tb_zero, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(0); });
    connect(ui->tb_one, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(1); });
    connect(ui->tb_two, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(2); });
    connect(ui->tb_three, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(3); });
    connect(ui->tb_four, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(4); });
    connect(ui->tb_five, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(5); });
    connect(ui->tb_six, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(6); });
    connect(ui->tb_seven, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(7); });
    connect(ui->tb_eight, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(8); });
    connect(ui->tb_nine, &QPushButton::clicked, this, [this]{ if(digit_cb_) digit_cb_(9); });

    connect(ui->tb_add, &QPushButton::clicked, this, [this]{ if(operation_cb_) operation_cb_(Operation::ADDITION); });
    connect(ui->tb_substract, &QPushButton::clicked, this, [this]{ if(operation_cb_) operation_cb_(Operation::SUBTRACTION); });
    connect(ui->tb_multiplicate, &QPushButton::clicked, this, [this]{ if(operation_cb_) operation_cb_(Operation::MULTIPLICATION); });
    connect(ui->tb_divide, &QPushButton::clicked, this, [this]{ if(operation_cb_) operation_cb_(Operation::DIVISION); });
    connect(ui->tb_power, &QPushButton::clicked, this, [this]{ if(operation_cb_) operation_cb_(Operation::POWER); });

    connect(ui->tb_equal, &QPushButton::clicked, this, [this]{ if(control_cb_) control_cb_(ControlKey::EQUALS); });
    connect(ui->tb_reset, &QPushButton::clicked, this, [this]{ if(control_cb_) control_cb_(ControlKey::CLEAR); });
    connect(ui->tb_ms, &QPushButton::clicked, this, [this]{ if(control_cb_) control_cb_(ControlKey::MEM_SAVE); });
    connect(ui->tn_mr, &QPushButton::clicked, this, [this]{ if(control_cb_) control_cb_(ControlKey::MEM_LOAD); });
    connect(ui->tb_mc, &QPushButton::clicked, this, [this]{ if(control_cb_) control_cb_(ControlKey::MEM_CLEAR); });
    connect(ui->tb_negate, &QPushButton::clicked, this, [this]{ if(control_cb_) control_cb_(ControlKey::PLUS_MINUS); });
    connect(ui->tb_backspace, &QPushButton::clicked, this, [this]{ if(control_cb_) control_cb_(ControlKey::BACKSPACE); });
    connect(ui->tb_extra, &QPushButton::clicked, this, [this]{ if(control_cb_) control_cb_(ControlKey::EXTRA_KEY); });

    connect(ui->cmb_controller, &QComboBox::currentIndexChanged, this, [this](int) {
        if (!controller_cb_) return;
        
        QString text = ui->cmb_controller->currentText();
        ControllerType type = ControllerType::DOUBLE;
        
        if (text == "double") type = ControllerType::DOUBLE;
        else if (text == "float") type = ControllerType::FLOAT;
        else if (text == "uint8_t") type = ControllerType::UINT8_T;
        else if (text == "int") type = ControllerType::INT;
        else if (text == "int64_t") type = ControllerType::INT64_T;
        else if (text == "size_t") type = ControllerType::SIZE_T;
        else if (text == "Rational") type = ControllerType::RATIONAL;
        
        controller_cb_(type);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetInputText(const std::string& text)
{
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text)
{
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text)
{
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text)
{
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key)
{
    if (key.has_value()) {
        ui->tb_extra->show();
        ui->tb_extra->setText(QString::fromStdString(key.value()));
    } else {
        ui->tb_extra->hide();
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int)> cb)
{
    digit_cb_ = std::move(cb);
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation)> cb)
{
    operation_cb_ = std::move(cb);
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey)> cb)
{
    control_cb_ = std::move(cb);
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType)> cb)
{
    controller_cb_ = std::move(cb);
}
