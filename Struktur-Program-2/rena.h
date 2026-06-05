#ifndef RENA_H
#define RENA_H
 
#include "Global.h"
 
int reallocBaris(Baris *baris, int kapasitasBaru);
void tekan_enter();
void gerakBawah();          /* FIX #3: tanpa parameter DataEditor* */
void openFile(char *namaFile);
 
#endif
