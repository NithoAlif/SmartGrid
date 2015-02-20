#ifndef SMARTGRIDDATA_H
#define SMARTGRIDDATA_H

#include <fstream>
#include <iostream>
#include <vector>
#include "barang.h"
using namespace std;

class SmartGridData{
	public:
		SmartGridData();
		SmartGridData(string s);
		virtual ~SmartGridData();
		int Getslot_waktu();
		int Getselang_tarif();
		int Getn_progresif();
		int Getn_barang();
		float GetkWh_max();
		vector<vector<int> > Gettarif();
		vector<int> Getselang();
		vector<float> GetkWh_mark();
		vector<Barang> Getl_barang();

	private:
		int slot_waktu;
		int selang_tarif;
		int n_progresif;
		int n_barang;
		float kWh_max;
		vector<vector<int> > tarif;
		vector<int> selang;
		vector<float> kWh_mark;
		vector<Barang> l_barang;
};

#endif // SMARTGRIDDATA_H
