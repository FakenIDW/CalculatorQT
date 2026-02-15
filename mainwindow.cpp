#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QJSEngine>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , waitingForNewNumber(false)
{
    ui->setupUi(this);
    ui->display->setText("0");

    this->setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addDigit(const QString &digit)
{
    QString currentDisplay = ui->display->text();

    // Если ждем новое число ИЛИ специальные значения
    if (waitingForNewNumber ||
        currentDisplay == "Ошибка" ||
        currentDisplay == "0" ||
        currentDisplay == "Infinity" ||
        currentDisplay == "NaN") {

        ui->display->setText(digit);
        waitingForNewNumber = false;  // Сбрасываем флаг после использования
    } else {
        ui->display->setText(currentDisplay + digit);
    }
}

// Слоты для каждой цифры
void MainWindow::on_pushButton_clicked()
{
    addDigit("1");
}

void MainWindow::on_pushButton_1_clicked()
{
    addDigit("1");
}

void MainWindow::on_pushButton_2_clicked()
{
    addDigit("2");
}

void MainWindow::on_pushButton_3_clicked()
{
    addDigit("3");
}

void MainWindow::on_pushButton_4_clicked()
{
    addDigit("4");
}

void MainWindow::on_pushButton_5_clicked()
{
    addDigit("5");
}

void MainWindow::on_pushButton_6_clicked()
{
    addDigit("6");
}

void MainWindow::on_pushButton_7_clicked()
{
    addDigit("7");
}

void MainWindow::on_pushButton_8_clicked()
{
    addDigit("8");
}

void MainWindow::on_pushButton_9_clicked()
{
    addDigit("9");
}

void MainWindow::on_pushButton_10_clicked()
{
    addDigit("0");
}

void MainWindow::on_pushButton_plus_clicked()
{
    QString currentDisplay = ui->display->text();

    // Если ждем новое число (после результата)
    if (waitingForNewNumber) {
        // Используем текущий результат и добавляем оператор
        ui->display->setText(currentDisplay + "+");
        waitingForNewNumber = false;
    } else {
        addDigit("+");
    }
}

void MainWindow::on_pushButton_minus_clicked()
{
    QString currentDisplay = ui->display->text();

    if (waitingForNewNumber) {
        ui->display->setText(currentDisplay + "-");
        waitingForNewNumber = false;
    } else {
        addDigit("-");
    }
}

void MainWindow::on_pushButton_multy_clicked()
{
    QString currentDisplay = ui->display->text();

    if (waitingForNewNumber) {
        ui->display->setText(currentDisplay + "*");
        waitingForNewNumber = false;
    } else {
        addDigit("*");
    }
}

void MainWindow::on_pushButton_divide_clicked()
{
    QString currentDisplay = ui->display->text();

    if (waitingForNewNumber) {
        ui->display->setText(currentDisplay + "/");
        waitingForNewNumber = false;
    } else {
        addDigit("/");
    }
}

void MainWindow::on_pushButton_leftbracket_clicked()
{
    addDigit("(");
}

void MainWindow::on_pushButton_rightbracket_clicked()
{
    addDigit(")");
}


void MainWindow::on_pushButton_dot_clicked()
{
    QString currentDisplay = ui->display->text();

    // Если ждем новое число (после результата), начинаем с "0."
    if (waitingForNewNumber) {
        ui->display->setText("0.");
        waitingForNewNumber = false;
        return;
    }

    // Проверяем, есть ли уже точка в текущем числе
    // Ищем точку в последнем числе выражения

    // Разделяем выражение по операторам
    QStringList parts;
    if (currentDisplay.contains('+')) parts = currentDisplay.split('+');
    else if (currentDisplay.contains('-')) parts = currentDisplay.split('-');
    else if (currentDisplay.contains('*')) parts = currentDisplay.split('*');
    else if (currentDisplay.contains('/')) parts = currentDisplay.split('/');

    QString lastNumber;
    if (parts.isEmpty()) {
        lastNumber = currentDisplay;
    } else {
        lastNumber = parts.last();
    }

    // Если в последнем числе уже есть точка, не добавляем еще одну
    if (lastNumber.contains('.')) {
        return;
    }

    // Если дисплей пустой или заканчивается оператором
    if (currentDisplay.isEmpty() ||
        currentDisplay.endsWith('+') ||
        currentDisplay.endsWith('-') ||
        currentDisplay.endsWith('*') ||
        currentDisplay.endsWith('/')) {
        ui->display->setText(currentDisplay + "0.");
    } else {
        ui->display->setText(currentDisplay + ".");
    }
}


void MainWindow::on_pushButton_equal_clicked()
{
    QString expression = ui->display->text();

    QJSEngine engine;
    QJSValue result = engine.evaluate(expression);

    if (result.isError()) {
        ui->display->setText("Ошибка");
        qDebug() << "Ошибка:" << result.toString();
        waitingForNewNumber = true;
    } else {
        ui->display->setText(result.toString());
        waitingForNewNumber = true;
    }
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->display->setText("0");
     waitingForNewNumber = false;
}


void MainWindow::on_pushButton_percent_clicked()
{
    QString currentDisplay = ui->display->text();

    // Если дисплей пустой или содержит ошибку
    if (currentDisplay.isEmpty() ||
        currentDisplay == "Ошибка" ||
        currentDisplay == "Infinity" ||
        currentDisplay == "NaN") {
        return;
    }

    // Получаем последнее число из выражения
    QStringList parts;
    if (currentDisplay.contains('+')) parts = currentDisplay.split('+');
    else if (currentDisplay.contains('-')) parts = currentDisplay.split('-');
    else if (currentDisplay.contains('*')) parts = currentDisplay.split('*');
    else if (currentDisplay.contains('/')) parts = currentDisplay.split('/');

    QString lastNumber;
    QString expression;

    if (parts.isEmpty()) {
        // Если нет операторов, всё выражение - одно число
        lastNumber = currentDisplay;
        expression = "";
    } else {
        // Берем последнее число и выражение без него
        lastNumber = parts.last();
        expression = currentDisplay.left(currentDisplay.length() - lastNumber.length());
    }

    // Преобразуем в число и делим на 100
    bool ok;
    double number = lastNumber.toDouble(&ok);

    if (ok) {
        double percent = number / 100.0;
        QString percentStr = QString::number(percent, 'g', 12);

        // Собираем выражение обратно
        if (expression.isEmpty()) {
            ui->display->setText(percentStr);
        } else {
            ui->display->setText(expression + percentStr);
        }

        // Сбрасываем флаг ожидания нового числа
        waitingForNewNumber = false;
    }
}

