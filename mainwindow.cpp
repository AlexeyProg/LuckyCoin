#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_guessNumber->setEnabled(false);
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(setBet()));
    connect(ui->pushButton_setbalance,SIGNAL(clicked()),SLOT(setBalance()));
    connect(ui->pushButton_play,SIGNAL(clicked()),SLOT(play()));
}

void MainWindow::setBalance()
{
    mBalance = ui->lineEdit_setBalance->text().toInt();
    ui->lineEdit_setBalance->setEnabled(false);
}

void MainWindow::setBet()
{
    QString bet = ui->lineEdit_bet->text();

    if(bet.toInt() > mBalance)
    {
        QMessageBox::warning(this,"Error!","You haven't got enought balance!",QMessageBox::Default);
    }
    else
    {
        mBet = bet.toInt();
        ui->label_bet->setText("The bet is : " + QString::number(mBet));
        ui->lineEdit_guessNumber->setEnabled(true);
    }
}

void MainWindow::play()
{
    int your_turn = ui->lineEdit_guessNumber->text().toInt();
    int comp_turn = rand() % 10 + 1;
    ui->label_compDigit->setText(QString::number(comp_turn));
    int current_balance = mBalance;
    if (current_balance >= mBet)
    {
        if (your_turn == comp_turn)
        {
            ui->label_win->setText("You win!");
            mBalance = mBalance + mBet;
            ui->lineEdit_setBalance->setText(QString::number(mBalance));
        }
        else
        {
            ui->label_win->setText("You lose!");
            mBalance = mBalance - mBet;
            ui->lineEdit_setBalance->setText(QString::number(mBalance));
        }
    }
    else
    {
        QMessageBox::warning(this,"ERROR","Your bet > your balance");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
