
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qlist.h"
#include "math.h"

int fact(int n)
{
    return (n==0?1:n*fact(n-1));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    group.setExclusive(false);
    QList<QPushButton*> buttons = ui->groupBox->findChildren<QPushButton*>();
    for (int i=0; i<buttons.size();i++)
    {
        group.addButton(buttons[i], i);
    }
    connect(&group, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(buttonClickedSlot(QAbstractButton*)));
}


void MainWindow::buttonClickedSlot(QAbstractButton* button)
{
    bool isOperand = false;
    button->text().toInt(&isOperand);
    if (isOperand || button->text()==".")
    {
        actionOperand(button);
        return;
    }
    actionOperator(button);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionOperand (QAbstractButton* button)
{
    ui->down->setText(ui->down->text()+button->text());
}

void MainWindow::actionOperator(QAbstractButton* button)
{
    if (button->text()=="CE")
    {
        if (ui->down->text()=="")
        {
            currentOperand=0;
            currentOperator="";
            ui->up->setText("");
        }
        else
            ui->down->setText("");
        return;
    }
    if (button->text()=="Backspace")
    {
        if (ui->down->text()!="")
        {
            QString help = ui->down->text();
            help.chop(1);
            ui->down->setText(help);
        }
        return;
    }
    double current = ui->down->text().toDouble();
    if (button->text()=="x^2" || button->text()=="|x|" || button->text()=="n!" || button->text()=="+/-")
    {
        /*QString curOp = QString::number(currentOperand)=="0"?"":QString::number(currentOperand);
        if (button->text()=="+/-")
            ui->up->setText(curOp + currentOperator + "-("+ui->down->text()+")");
        if (button->text()=="x^2")
            ui->up->setText(curOp + currentOperator + "sqr("+ui->down->text()+")");
        if (button->text()=="|x|")
            ui->up->setText(curOp + currentOperator + "abs("+ui->down->text()+")");
        if (button->text()=="n!")
            ui->up->setText(curOp + currentOperator + "fact("+ui->down->text()+")");*/

        if (button->text()=="+/-")
            current*=-1;
        if (button->text()=="x^2")
            current*=current;
        if (button->text()=="|x|")
            current=abs(current);
        if (button->text()=="n!")
            current=fact(current);
        ui->down->setText(QString::number(current));
        if (!currentOperand)
            ui->up->setText("");
        return;
    }
    if (currentOperator!="")
    {
        if (ui->down->text()!="")
        {
            if (currentOperator=="/")
            {
                currentOperand/=!current?1:current;
            }
            if (currentOperator=="X")
            {
                currentOperand*=current;
            }
            if (currentOperator=="-")
            {
                currentOperand-=current;
            }
            if (currentOperator=="+")
            {
                currentOperand+=current;
        }
        }
        if (button->text()!="=")
        {
            ui->up->setText(QString::number(currentOperand) + button->text());
            ui->down->setText("");
            currentOperator = button->text();
            return;
        }
        else
        {
            ui->up->setText(ui->up->text()+ui->down->text()+button->text());
            ui->down->setText(QString::number(currentOperand));
            currentOperator="";
            currentOperand=0;
        }
    }
    else
    {
        currentOperand=ui->down->text().toDouble();
        ui->up->setText(QString::number(currentOperand)+button->text());
        if (button->text()!="=")
        {
            ui->down->setText("");
            currentOperator=button->text();
            return;
        }
        ui->down->setText(QString::number(currentOperand));
    }
}


