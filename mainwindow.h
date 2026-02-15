#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_divide_clicked();

    void on_pushButton_multy_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_leftbracket_clicked();

    void on_pushButton_rightbracket_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_dot_clicked();

    void on_pushButton_percent_clicked();

private:
    Ui::MainWindow *ui;
     void addDigit(const QString &digit);
      bool waitingForNewNumber;

};
#endif // MAINWINDOW_H
