#ifndef RENA_H
#define RENA_H

#include "Global.h"

void shift_kanan(Baris *baris, int x, int batas);
void shift_kiri(Baris *baris, int x);
void tekan_enter();
void gerakBawah();
void openFile(char* namaFile);

#endif