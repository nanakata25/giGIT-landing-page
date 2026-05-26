#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#include rena.h

/* ===== HELPER SHIFT ===== */
void shift_kanan(Baris *baris, int x, int batas) {
    for (int i = batas; i >= x; i--) {
        baris->isiTeks[i + 1] = baris->isiTeks[i];
    }
}

void shift_kiri(Baris *baris, int x) {
    int len = baris->panjang;
    for (int i = x; i < len; i++) {
        baris->isiTeks[i] = baris->isiTeks[i + 1];
    }
}


/* ===== TEKAN ENTER ===== */
void tekan_enter() {
    Baris *baris = editor.kursorBaris;
    int x = editor.kursorX;

    // 1. ambil teks sesudah kursor
    char *sisa       = baris->isiTeks + x;
    int panjang_sisa = baris->panjang - x;

    // 2. buat node baru
    Baris *baru = buatNode();
    if (baru == NULL) return;

    // realloc kalau sisa ga muat di kapasitas awal
    if (panjang_sisa + 1 > baru->kapasitas) {
        char *temp = realloc(baru->isiTeks, panjang_sisa + 1);
        if (temp == NULL) {
            free(baru->isiTeks);
            free(baru);
            return;
        }
        baru->isiTeks = temp;
        baru->kapasitas = panjang_sisa + 1;
    }

    // salin sisa teks ke node baru
    strcpy(baru->isiTeks, sisa);
    baru->panjang = panjang_sisa;

    // 3. potong baris sekarang di posisi x
    baris->isiTeks[x] = '\0';
    baris->panjang    = x;

    // 4. sambung node baru ke linked list
    baru->prev = baris;
    baru->next = baris->next;
    if (baris->next != NULL)
        baris->next->prev = baru;
    else
        editor.tail = baru;
    baris->next = baru;

    // 5. pindah kursor ke node baru
    editor.kursorBaris = baru;
    editor.kursorX     = 0;
    editor.kursorY++;

    // 6. update totalBaris
    editor.totalBaris++;
}


/* ===== KURSOR BAWAH ===== */

/* ===== OPEN FILE ===== */

