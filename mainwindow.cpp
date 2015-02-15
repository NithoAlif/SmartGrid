#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "smartgrid.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
	//ui->tableCalculation->setColumnWidth(0, 84);
	ui->tableCalculation->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_buttonAbout_clicked(){
    QMessageBox::about(this, tr("About"), tr("SmartGrid v1.0\n\nKontibutor:\n  -Bayu Rasyadi Putrautama\t(13513046)\n  -Raihannur Reztaputra\t(13513064)\n  -Nitho Alif Ibadurrahman\t(13513072)\n"));
}

void MainWindow::on_buttonQuit_clicked(){
    MainWindow::close();
}

void MainWindow::on_tableCalculation_itemSelectionChanged(){
    //if ((ui->tableCalculation->currentRow() == row) && (ui->tableCalculation->currentRow() == row))
	//ui->tableCalculation->item(ui->tableCalculation->currentRow(),ui->tableCalculation->currentColumn())->setSelected(1);
    //int i = ui->tableCalculation->currentRow();
    //int j = ui->tableCalculation->currentColumn();
    //ui->tableCalculation->item(0, 0)->background().setStyle(Qt::SolidPattern);
    //ui->tableCalculation->item(0, 0)->background().setColor(QColor(74, 120, 210, 255));
    //ui->tableCalculation->item(0,0)->setBackground(QBrush(QColor(74, 120, 210, 255), Qt::SolidPattern));
    //QMessageBox::about(this,tr("lol"),ui->tableCalculation->currentColumn());
   // ui->tableCalculation->item(1,1)->setSelected(1);
}

void MainWindow::on_buttonOpen_clicked(){

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
	if (!fileName.isEmpty()){
		fileInput.open(fileName.toStdString().c_str());
	} else{
		QMessageBox::critical(this, tr("Invalid file"), tr("The file you specified is either invalid or cannot be accessed!"));
	}
}
