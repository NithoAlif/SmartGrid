#ifndef GREEDY_H
#define GREEDY_H

#include "smartgriddata.h"

const int big = 99999999;

void Greedy(SmartGridData *S);
void Greedy_Output(SmartGridData S, float *cost);
int Wajib_Max(SmartGridData S) ;
float TarifActive(SmartGridData S, Barang b, int n);
float TotalkWhSlot(SmartGridData S, int i);
float TotalkWh(SmartGridData S);
float TarifBarang(SmartGridData S, Barang b);
int Opsi_Min(SmartGridData S);

#endif // GREEDY_H
