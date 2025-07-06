
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void actionOperator(QAbstractButton *button);
    void actionOperand(QAbstractButton *button);

private slots:
    void buttonClickedSlot (QAbstractButton *);

private:
    Ui::MainWindow *ui;
    QButtonGroup group;
    QString currentOperator="";
    double currentOperand=0;
};

#endif // MAINWINDOW_H
