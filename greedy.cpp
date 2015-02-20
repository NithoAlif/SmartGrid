#include "greedy.h"


void Greedy(SmartGridData *S){
	int i,j,act,start,opt;
    float minim;

    //wajib
	start = Wajib_Max(*S);
	 if (start>=0){
		do{
			act = Wajib_Max(*S);
			if (act != -1){
				for (j=0; j<S->Getl_barang()[act].Getn_slot(); j++){
					minim = big;
					opt = 0;
					for (i=S->Getl_barang()[act].Getrelease()*2; i<S->Getl_barang()[act].Getdeadline()*2-S->Getl_barang()[act].Getslot(); i++){
						if (minim > TarifActive(*S, S->Getl_barang()[act], i)){
							minim = TarifActive(*S, S->Getl_barang()[act], i);
							opt = i;
                        }
                    }
					if (TarifActive(*S,S->Getl_barang()[act], opt) != big){
						for (i=opt; i<opt+S->Getl_barang()[act].Getslot(); i++)
                            S->Getl_barang()[act].Aloc(i);
                    }
                }
                S->Getl_barang()[act].Set_Done();
            }
        } while (Wajib_Max(*S)!=-1);
    }

    //opsional
	start = 0;
    do {
		act = Opsi_Min(*S);
		if (act != -1){
			for (j=0; j<S->Getl_barang()[act].Getn_slot(); j++){
				minim = big;
				for (i=S->Getl_barang()[act].Getrelease()*2; i<S->Getl_barang()[act].Getdeadline()*2-S->Getl_barang()[act].Getslot(); i++){
					if (minim > TarifActive(*S, S->Getl_barang()[act], i)){
						minim = TarifActive(*S, S->Getl_barang()[act], i);
						opt = i;
                    }
                }
				if (TarifActive(*S, S->Getl_barang()[act], opt) != big){
					for (i=opt; i<opt+S->Getl_barang()[act].Getslot(); i++)
                        S->Getl_barang()[act].Aloc(i);
                }
            }
            S->Getl_barang()[act].Set_Done();
        }
	} while (Opsi_Min(*S) != -1);
}

int Opsi_Min(SmartGridData S){
	int i, start, minim;
	start = 0;
	minim = start;
	for (i=start+1; i<S.Getn_barang(); i++){
        if (!S.Getl_barang()[i].Done() && S.Getl_barang()[i].Getslot()*S.Getl_barang()[i].Getn_slot()<=S.Getl_barang()[minim].Getslot()*S.Getl_barang()[minim].Getn_slot())
			minim = i;
    }
    if (S.Getl_barang()[minim].Done())
        return -1;
    else
        return minim;
}

int Wajib_Max(SmartGridData S){
	int i, start, maks;
	unsigned stop = 0;
	start = 0;
	while (!stop && start<S.Getn_barang()){
        if (!S.Getl_barang()[start].Done() && S.Getl_barang()[start].Getpriority())
			stop = true;
        else
            start++;
    }
	if (start < S.Getn_barang()){
		maks = start;
		for (i=start+1; i<S.Getn_barang(); i++){
            if (!S.Getl_barang()[i].Done() && S.Getl_barang()[i].Getpriority( )&& S.Getl_barang()[i].Getslot()*S.Getl_barang()[i].Getn_slot()>=S.Getl_barang()[maks].Getslot()*S.Getl_barang()[maks].Getn_slot())
				maks = i;
        }
        if (S.Getl_barang()[maks].Done())
            return -1;
        else
            return maks;
    } else
        return -1;
}

float TarifActive(SmartGridData S, Barang b, int n){
	int i, j, k, id;
	float temp = 0;
	for (i=n; i<n+b.Getslot(); i++){
        if (b.Get_aloc(i))
            return big;
    }
	for (i=n; i<n+b.Getslot(); i++){
        b.Aloc(i);
    }
	for (i=n; i<n+b.Getslot(); i++){
		if (TotalkWhSlot(S, i) > S.GetkWh_max()){
			temp = big;
        }
		for (k=0; k<S.Getselang_tarif(); k++){
			if (i>=S.Getselang()[2*k]*2-1 && i<S.Getselang()[2*k+1]*2-1){
				id = k;
            }
        }
		for (j=S.Getn_progresif()-1; j>=0; j--){
			if (TotalkWhSlot(S,i) <= S.GetkWh_mark()[j]){
				k = j;
            }
        }
		if (TotalkWhSlot(S,i) <= S.GetkWh_max())
			temp += b.GetkWh()*S.Gettarif()[k][id]/2;
    }
	for (i=n; i<n+b.Getslot(); i++){
        b.DeAloc(i);
    }
    return temp;
}

float TotalkWhSlot(SmartGridData S, int i){
	float temp = 0;
	for (int k=0; k<S.Getn_barang(); k++){
		if (S.Getl_barang()[k].Get_aloc(i)){
            temp+=S.Getl_barang()[k].GetkWh();
        }
    }
    return temp;
}

float TotalkWh(SmartGridData S){
	float temp = 0;
	for (int i=0; i<S.Getslot_waktu(); i++){
		temp += TotalkWhSlot(S, i);
	}
	return temp;
}

float TarifBarang(SmartGridData S, Barang b) {
	float temp = 0;
	int i, j, k, id;
	for (i=0; i<S.Getslot_waktu(); i++){
		if (b.Get_aloc(i)){
			for (k=0; k<S.Getselang_tarif(); k++){
				if (i>=S.Getselang()[2*k]*2-1 && i<S.Getselang()[2*k+1]*2-1){
					id = k;
                }
            }
			for (j=S.Getn_progresif()-1; j>=0; j--){
				if (TotalkWhSlot(S,i) <= S.GetkWh_mark()[j]){
					k = j;
                }
            }
			temp += b.GetkWh()*S.Gettarif()[k][id]/2;
        }
    }
    return temp;
}

void Greedy_Output(SmartGridData S,float *cost){
    int i;
    *cost = 0;
    for (i=0; i<S.Getn_barang(); i++){
		*cost += TarifBarang(S, S.Getl_barang()[i]);
    }
}
