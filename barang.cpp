#include "barang.h"

Barang::Barang(){ //ctor
}

Barang::~Barang(){ //dtor
}

void Barang::Setter(string _name, float _kWh, unsigned int _slot, unsigned _n_slot, unsigned int _release, unsigned int _deadline, unsigned int _priority, unsigned int _slotavail){ //ctor
	name = _name;
	kWh = _kWh;
	slot = _slot;
	n_slot = _n_slot;
	release =  _release;
	deadline = _deadline;
	priority = _priority;
    done = new unsigned [1];
    done[0] = 0;
    alocate = new unsigned int [_slotavail];
    for (int i=0; i<_slotavail; i++) {
        alocate[i] = 0;
    }
}

string Barang::Getname(){
	return name;
}

void Barang::Setname(string val){
	name = val;
}

float Barang::GetkWh(){
	return kWh;
}

void Barang::SetkWh(float val){
	kWh = val;
}

unsigned int Barang::Getslot(){
	return slot;
}

void Barang::Setslot(unsigned int val){
	slot = val;
}

unsigned int Barang::Getn_slot(){
	return n_slot;
}

void Barang::Setn_slot(unsigned int val){
	n_slot = val;
}

unsigned int Barang::Getrelease(){
	return release;
}

void Barang::Setrelease(unsigned int val){
	release = val;
}

unsigned int Barang::Getdeadline(){
	return deadline;
}

void Barang::Setdeadline(unsigned int val){
	deadline = val;
}

unsigned int Barang::Getpriority(){
	return priority;
}

void Barang::Setpriority(unsigned int val){
	priority = val;
}

void Barang::Aloc(int i){
    alocate[i] = 1;
}

unsigned int Barang::Get_aloc(int i){
    return alocate[i];
}

void Barang::DeAloc(int i){
    alocate[i] = 0;
}

unsigned int Barang::Done(){
    return done[0];
}
void Barang::Done0(){
	done[0] = 0;
}

void Barang::Set_Done(){
    done[0] = 1;
}
