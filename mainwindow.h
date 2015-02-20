#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include "greedy.h"

namespace Ui{
	class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		void setDataTable(int row);
		void setCalculationTable(int row);
		void setTariffGraph(SmartGridData SGD);
		void setColour(SmartGridData *SGD);
		void setStat(SmartGridData SGD);

	private slots:
        void on_buttonHelp_clicked();
        void on_buttonAbout_clicked();
		void on_buttonQuit_clicked();
		void on_buttonOpen_clicked();
		void on_buttonGraph_clicked();
        void on_buttonClose_clicked();
        void on_tableCalculation_itemSelectionChanged();
		void on_tableCalculation_itemClicked(QTableWidgetItem *item);
		void on_buttonOptimize_clicked();
		void on_buttonClear_clicked();

	private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
