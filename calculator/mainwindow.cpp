#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , input_number_("0")
    , active_number_(0.0)
    , current_operation_(Operation::NO_OPERATION)
    , memory_value_(0.0)
    , memory_has_value_(false)
{
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString& text) {
    input_number_ = NormalizeNumber(text);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::AddText(const QString& suffix) {
    if (current_operation_ == Operation::NO_OPERATION) {
        ui->l_formula->setText("");
    }

    QString newText = input_number_ + suffix;
    input_number_ = NormalizeNumber(newText);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::on_tb_zero_clicked()
{
    AddText("0");
}

void MainWindow::on_tb_one_clicked()
{
    AddText("1");
}

void MainWindow::on_tb_two_clicked()
{
    AddText("2");
}

void MainWindow::on_tb_three_clicked()
{
    AddText("3");
}

void MainWindow::on_tb_four_clicked()
{
    AddText("4");
}

void MainWindow::on_tb_five_clicked()
{
    AddText("5");
}

void MainWindow::on_tb_six_clicked()
{
    AddText("6");
}

void MainWindow::on_tb_seven_clicked()
{
    AddText("7");
}

void MainWindow::on_tb_eight_clicked()
{
    AddText("8");
}

void MainWindow::on_tb_nine_clicked()
{
    AddText("9");
}

void MainWindow::on_tb_comma_clicked()
{
    if (!input_number_.contains('.')) {
        AddText(".");
    }
}

void MainWindow::on_tb_negate_clicked(){
    if (input_number_.isEmpty()) {
        return;
    }

    if (input_number_.startsWith("-")) {
        input_number_ = input_number_.mid(1);
    } else {
        input_number_.prepend("-");
    }
    SetText(input_number_);
}


void MainWindow::on_tb_backspace_clicked()
{
    if (!input_number_.isEmpty()) {
        if (input_number_ == "-0") {
            input_number_ = input_number_.mid(1);
        }
        input_number_.chop(1);
        SetText(input_number_);
    }
}

QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

void MainWindow::SetOperation(MainWindow::Operation op) {
    if (current_operation_ != Operation::NO_OPERATION && !input_number_.isEmpty()) {
        QString firstNumber = QString::number(calculator_.GetNumber(), 'g', 15);
        QString formula = firstNumber + " " + OpToString(op);
        ui->l_formula->setText(formula);

        current_operation_ = op;

        input_number_ = "";
        ui->l_result->setText(QString::number(active_number_, 'g', 15));
        return;
    }

    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
        current_operation_ = op;
    }

    QString str = QString::number(calculator_.GetNumber(), 'g', 15);
    QString formula = str + " " + OpToString(op);
    ui->l_formula->setText(formula);
    input_number_ = "";
    ui->l_result->setText("0");
}

void MainWindow::on_tb_substract_clicked()
{
    SetOperation(Operation::SUBTRACTION);
}

void MainWindow::on_tb_power_clicked()
{
    SetOperation(Operation::POWER);
}

void MainWindow::on_tb_add_clicked()
{
    SetOperation(Operation::ADDITION);
}

void MainWindow::on_tb_multiplicate_clicked()
{
    SetOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_tb_divide_clicked()
{
    SetOperation(Operation::DIVISION);
}

void MainWindow::on_tb_equal_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }

    double secondNumber;
    if (input_number_.isEmpty()) {
        secondNumber = active_number_;
    } else {
        secondNumber = input_number_.toDouble();
    }

    QString secondNumberStr = QString::number(secondNumber, 'g', 15);
    ui->l_formula->setText(QString::number(calculator_.GetNumber(), 'g', 15) + " " + OpToString(current_operation_) + " " + secondNumberStr + " =");

    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(secondNumber);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(secondNumber);
        break;
    case Operation::POWER:
        calculator_.Pow(secondNumber);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(secondNumber);
        break;
    case Operation::DIVISION:
        if (secondNumber != 0.0) calculator_.Div(secondNumber);
        break;
    default:
        break;
    }

    active_number_ = calculator_.GetNumber();
    QString resultText = QString::number(active_number_, 'g', 15);
    ui->l_result->setText(resultText);
    ui->l_formula->setText("");
    input_number_.clear();
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::on_tb_reset_clicked()
{
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->setText("");
    SetText("0");
    calculator_.Set(0.0);
}

void MainWindow::on_tb_ms_clicked()
{
    memory_value_ = active_number_;
    memory_has_value_ = true;
    calculator_.Save();
    ui->l_memory->setText("M");
}

void MainWindow::on_tn_mr_clicked()
{
    if (memory_has_value_) {
        active_number_ = memory_value_;
        calculator_.Set(active_number_);
        QString resultText = QString::number(active_number_, 'g', 15);
        ui->l_result->setText(resultText);
        input_number_.clear();
        ui->l_memory->setText("M");
    }
}

void MainWindow::on_tb_mc_clicked()
{
    memory_value_ = 0.0;
    memory_has_value_ = false;
    calculator_.ClearMemory();
    ui->l_memory->setText("");
}
