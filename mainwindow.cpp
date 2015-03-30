#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QSettings *set= new QSettings(qApp->applicationDirPath()+"/config.ini", QSettings::IniFormat);
    qDebug() << qApp->applicationDirPath();
    set->beginGroup("_Settings");
    qDebug() << set->value("Coast").toDouble();
    ui->CoastEdit->setText(QString::number(set->value("Coast").toDouble()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->label_3->setText(QString::number(arg1) + "шт * " + QString::number(ui->CoastEdit->text().toDouble()) + "коп = "+ QString::number(arg1 * ui->CoastEdit->text().toDouble()) +"грн");

}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->label_4->setText(arg1 + "грн - " + QString::number(ui->spinBox->value() * ui->CoastEdit->text().toDouble()) + "грн  = " + QString::number(arg1.toDouble() - (ui->spinBox->value() * ui->CoastEdit->text().toDouble()))+"грн");
}

void MainWindow::on_pushButton_clicked()
{
    paper+=ui->spinBox->value();

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QSettings *set= new QSettings(qApp->applicationDirPath()+"/config.ini", QSettings::IniFormat);
    qDebug() << qApp->applicationDirPath();
    set->beginGroup("_Settings");
    set->setValue("TotalPaper", QString::number(set->value("TotalPaper").toInt() + paper));
    double maney = (ui->spinBox->value() * ui->CoastEdit->text().toDouble());
    qDebug()<< ui->spinBox->value();
    set->setValue("TotalMoney", QString::number(set->value("TotalMoney").toDouble() +maney ));
    ui->spinBox->setValue(0);
    ui->lineEdit_2->setText("0");
    ui->label_3->clear();
    ui->label_4->clear();
    ui->statusBar->showMessage("За сессию всего распечатанно: "+QString::number(paper), 5000);

}

void MainWindow::on_SetCoastButton_clicked()
{
    if(ui->SetCoastButton->text()!= ""){
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QSettings *set= new QSettings(qApp->applicationDirPath()+"/config.ini", QSettings::IniFormat);
        qDebug() << qApp->applicationDirPath();
        set->beginGroup("_Settings");
        set->setValue("Coast", ui->newcoastlineedit->text());
        ui->CoastEdit->setText(ui->newcoastlineedit->text());
    }
}
