#ifndef EDITOR_H
#define EDITOR_H

/* =========================================================
 * FILE: editor.h
 * PEMBUAT: Anggota 1 (Mesin & Logika Array)
 * FUNGSI: Deklarasi fungsi-fungsi untuk manipulasi teks 
 * di dalam array 2 dimensi.
 * ========================================================= */

// 1. Dipanggil saat user mengetik huruf biasa (a-z, angka, simbol, spasi)
void ketik_huruf(char huruf_baru);

// 2. Dipanggil saat user menekan tombol Backspace
void hapus_backspace();

// 3. Dipanggil saat user menekan tombol Enter
void tekan_enter();

// 4. (Opsional) Dipanggil saat user menekan tombol Delete
// void hapus_delete(); 

#endif
