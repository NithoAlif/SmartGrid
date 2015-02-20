#include "mainwindow.h"
#include "ui_mainwindow.h"

SmartGridData* pSGD;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    //setup form
    ui->setupUi(this);

    //inisialisasi tabel
    ui->tableData->setColumnWidth(0, 99);
    ui->tableData->setColumnWidth(1, 94);
    ui->tableData->setColumnWidth(2, 43);
    ui->tableData->setColumnWidth(3, 92);
    ui->tableData->setColumnWidth(4, 65);
    ui->tableData->setColumnWidth(5, 56);
    ui->tableData->setColumnWidth(6, 60);
	ui->tableCalculation->setColumnWidth(0, 100);

    //inisialisasi graf tarif
    ui->plotTariff->hide();
	ui->plotTariff->plotLayout()->insertRow(0);
	ui->plotTariff->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->plotTariff, "Electricity Price Graph"));
    ui->plotTariff->xAxis->setLabel("Time (Jam)");
    ui->plotTariff->xAxis->setRange(0, 24);
    ui->plotTariff->xAxis->setAutoTickStep(false);
    ui->plotTariff->xAxis->setTickStep(1);
    ui->plotTariff->yAxis->setLabel("Electricity Price (Rp/kWh)");
    ui->plotTariff->legend->setVisible(1);

	ui->buttonClose->hide();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::setDataTable(int row){
	int i;
	QString Qs;
	for (i=0; i<row; i++){
		ui->tableData->setItem(i, 0, new QTableWidgetItem(pSGD->Getl_barang()[i].Getname().c_str()));
		ui->tableData->setItem(i, 1, new QTableWidgetItem(Qs.setNum(pSGD->Getl_barang()[i].GetkWh())));
		ui->tableData->setItem(i, 2, new QTableWidgetItem(Qs.setNum(pSGD->Getl_barang()[i].Getslot())));
		ui->tableData->setItem(i, 3, new QTableWidgetItem(Qs.setNum(pSGD->Getl_barang()[i].Getrelease())));
		ui->tableData->setItem(i, 4, new QTableWidgetItem(Qs.setNum(pSGD->Getl_barang()[i].Getdeadline())));
		if (pSGD->Getl_barang()[i].Getpriority() == 1){
			ui->tableData->setItem(i, 5, new QTableWidgetItem("Wajib"));
		} else{
			ui->tableData->setItem(i, 5, new QTableWidgetItem("Opsional"));
		}
		ui->tableData->setItem(i,6,new QTableWidgetItem(Qs.setNum(pSGD->Getl_barang()[i].Getn_slot())));
	}
}

void MainWindow::setCalculationTable(int row){
	int i, j;
	for (i=0; i<row; i++){
		ui->tableCalculation->setItem(i, 0, new QTableWidgetItem(ui->tableData->item(i,0)->text()));
		for (j=1; j<ui->tableCalculation->columnCount(); j++){
			ui->tableCalculation->setItem(i, j, new QTableWidgetItem(""));
            ui->tableCalculation->item(i, j)->setBackgroundColor(QColor(247, 247, 247));
		}
	}
}

void MainWindow::setTariffGraph(SmartGridData SGD){
    int n, i, rr, gg, bb;
	QString Qs;
	QVector<double> x0(SGD.Getselang().size()), y0(SGD.Getselang().size());
	for (i=0; i<SGD.Getselang().size(); i++){
		if (SGD.Getselang()[i] == SGD.Getselang()[i-1]){
			x0[i] = SGD.Getselang()[i]+1;
		} else{
			x0[i] = SGD.Getselang()[i];
		}
	}
	for(n=0; n<SGD.Getn_progresif(); n++){
        rr = (n*11) % 255;
        gg = (n*37-15) % 255;
        bb = (n*91+50) % 255;
		ui->plotTariff->addGraph(ui->plotTariff->xAxis, ui->plotTariff->yAxis);
		ui->plotTariff->graph(n)->setPen(QPen(QColor(rr, gg, bb)));
		ui->plotTariff->graph(n)->setLineStyle(QCPGraph::lsLine);
		ui->plotTariff->graph(n)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
        ui->plotTariff->graph(n)->setName("< " + Qs.setNum(SGD.GetkWh_mark()[n]) + " kWh");
		for (i=0; i<SGD.Getselang().size(); i++){
			y0[i] = SGD.Gettarif()[n][i/2];
		}
		ui->plotTariff->graph(n)->setData(x0, y0);
	}
    ui->plotTariff->yAxis->setRange(0, SGD.GetkWh_mark()[n-1] + 100);
}

void MainWindow::setColour(SmartGridData *SGD){
    int i,j;

    for (i=0;i<SGD->Getn_barang();i++) {
		for (j=0;j<SGD->Getslot_waktu();j++) {
			if (SGD->Getl_barang()[i].Get_aloc(j)) {
				ui->tableCalculation->item(i, j+1)->setBackgroundColor(QColor(109, 142, 175));
			} else{
				ui->tableCalculation->item(i, j+1)->setBackgroundColor(QColor(247, 247, 247));
			}
		}
	}
}

void MainWindow::setStat(SmartGridData SGD){
	QString Qs;
	float totalCost;

	Greedy_Output(SGD, &totalCost);
	ui->label_total_kwhA->setText(Qs.setNum(TotalkWh(SGD)) + " kWh");
	ui->label_total_costA->setText("Rp " + Qs.setNum(totalCost));

}

void MainWindow::on_buttonHelp_clicked(){

}

void MainWindow::on_buttonAbout_clicked(){
    QMessageBox::about(this, tr("About"), tr("SmartGrid v1.0\n\nKontibutor:\n  -Bayu Rasyadi Putrautama\t(13513046)\n  -Raihannur Reztaputra\t(13513064)\n  -Nitho Alif Ibadurrahman\t(13513072)\n"));
}

void MainWindow::on_buttonQuit_clicked(){
    MainWindow::close();
}

void MainWindow::on_buttonOpen_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
	if (!fileName.isEmpty()){
		pSGD = new SmartGridData(fileName.toStdString());
		if (pSGD->Getn_barang() == 0){
			QMessageBox::critical(this, tr("Invalid file"), tr("The file you specified is invalid!"));
		} else{
            ui->plotTariff->clearGraphs();

			//setup data table
			ui->tableData->setRowCount(pSGD->Getn_barang());
			setDataTable(ui->tableData->rowCount());

			//setup calculation table
            ui->tableCalculation->setRowCount(ui->tableData->rowCount());
            setCalculationTable(ui->tableData->rowCount());
            ui->tableCalculation->horizontalHeader()->setVisible(true);

			//update ui
			QString Qs;
			ui->label_slot_waktuA->setText(Qs.setNum(pSGD->Getslot_waktu()));
			ui->label_selang_tarifA->setText(Qs.setNum(pSGD->Getselang_tarif()));
			ui->label_n_progresifA->setText(Qs.setNum(pSGD->Getn_progresif()));
			ui->label_kWh_maxA->setText(Qs.setNum(pSGD->GetkWh_max()) + " kWh");
			ui->buttonOptimize->setEnabled(true);
			ui->buttonClear->setEnabled(true);
			ui->buttonGraph->setEnabled(true);
			setTariffGraph(*pSGD);
		}
	} else{
		QMessageBox::critical(this, tr("Invalid file"), tr("The file you specified is invalid!"));
	}
}


void MainWindow::on_buttonGraph_clicked(){
	ui->plotTariff->show();
	ui->buttonClose->show();
}

void MainWindow::on_buttonClose_clicked(){
    ui->plotTariff->hide();
	ui->buttonClose->hide();
}

void MainWindow::on_tableCalculation_itemSelectionChanged()
{
/*    int i;
    for (i=0; i<ui->tableCalculation->selectedItems().size(); i++){
        if (pSGD->Getl_barang()[ui->tableCalculation->currentRow()].Get_aloc(ui->tableCalculation->currentColumn()-1) == 1){
            pSGD->Getl_barang()[ui->tableCalculation->currentRow()].DeAloc(ui->tableCalculation->currentColumn()-1);
        } else{
            pSGD->Getl_barang()[ui->tableCalculation->currentRow()].Aloc(ui->tableCalculation->currentColumn()-1);
        }
    }
    for (i=0; i<ui->tableCalculation->selectedItems().size(); i++){
        if (pSGD->Getl_barang()[ui->tableCalculation->currentRow()].Get_aloc(ui->tableCalculation->currentColumn()-1) == 1){
            ui->tableCalculation->selectedItems()[i]->setBackgroundColor(QColor(109, 142, 175));
        } else{
            ui->tableCalculation->selectedItems()[i]->setBackgroundColor(QColor(247, 247, 247));
        }
        //ui->tableCalculation->selectedItems()[i]->setSelected(false);
    }
*/
}

void MainWindow::on_tableCalculation_itemClicked(QTableWidgetItem *item){
	int i;
	if (ui->tableCalculation->item(item->row(), item->column()+pSGD->Getl_barang()[item->row()].Getslot()-1)!=NULL && item->column()!=0){
		if (!pSGD->Getl_barang()[item->row()].Get_aloc(item->column()+pSGD->Getl_barang()[item->row()].Getslot()-2) && !pSGD->Getl_barang()[item->row()].Get_aloc(item->column()-1)){
			for (i=item->column(); i<=item->column()+pSGD->Getl_barang()[item->row()].Getslot()-1; i++){
				pSGD->Getl_barang()[item->row()].Aloc(i-1);
			}
		}
		setColour(pSGD);
		setStat(*pSGD);
	}

}

void MainWindow::on_buttonOptimize_clicked(){
	int i, j;
	for (i=0; i<pSGD->Getn_barang(); i++){
		pSGD->Getl_barang()[i].Done0();
		for (j=0; j<pSGD->Getslot_waktu(); j++){
			pSGD->Getl_barang()[i].DeAloc(j);
		}
	}
	Greedy(pSGD);
	setColour(pSGD);
	setStat(*pSGD);
}

void MainWindow::on_buttonClear_clicked(){
	int i, j;
	for (i=0; i<pSGD->Getn_barang(); i++){
		pSGD->Getl_barang()[i].Done0();
		for (j=0; j<pSGD->Getslot_waktu(); j++){
			pSGD->Getl_barang()[i].DeAloc(j);
		}
	}
	setColour(pSGD);
	setStat(*pSGD);
}
