#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#include "rena.h"
#include "Global.h"


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

    //  ambil teks sesudah kursor
    char *sisa       = baris->isiTeks + x;
    int panjang_sisa = baris->panjang - x;

    //  buat node baru
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

    //  potong baris sekarang di posisi x
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

    //  pindah kursor ke node baru
    editor.kursorBaris = baru;
    editor.kursorX     = 0;
    editor.kursorY++;

    //  update totalBaris
    editor.totalBaris++;
}


/* ===== KURSOR BAWAH ===== */
void gerakBawah() {
    // Cek apakah ada baris di bawah
    if (editor.kursorBaris->next == NULL) return;

    // Pindah ke baris berikutnya
    editor.kursorBaris = editor.kursorBaris->next;

    // Sesuaikan kursorX kalau baris bawah lebih pendek
    if (editor.kursorX > editor.kursorBaris->panjang) {
        editor.kursorX = editor.kursorBaris->panjang;
    }
}

/* ===== OPEN FILE ===== */
void openFile(char* namaFile) {
    // Buka file untuk dibaca
    FILE* file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Error: File '%s' tidak ditemukan.\n", namaFile);
        return;
    }

    // Bersihkan editor lama
    Baris* current = editor.head;
    while (current != NULL) {
        Baris* next = current->next;
        free(current->isiTeks);
        free(current);
        current = next;
    }

    // Buat baris pertama kosong
    editor.head        = buatNode();
    editor.tail        = editor.head;
    editor.kursorBaris = editor.head;
    editor.kursorX     = 0;
    editor.totalBaris  = 1;

    char buffer[1024];

    // Baca baris pertama → isi node yang sudah ada
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        int len = strlen(buffer);

        // realloc kalau teks lebih panjang dari kapasitas awal
        if (len + 1 > editor.head->kapasitas) {
            char* temp = realloc(editor.head->isiTeks, len + 1);
            if (temp != NULL) {
                editor.head->isiTeks   = temp;
                editor.head->kapasitas = len + 1;
            }
        }

        strcpy(editor.head->isiTeks, buffer);
        editor.head->panjang = len;
    }

    // Baca baris berikutnya
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        int len = strlen(buffer);

        Baris* baru = buatNode();
        if (baru == NULL) break;

        // realloc kalau teks lebih panjang dari kapasitas awal
        if (len + 1 > baru->kapasitas) {
            char* temp = realloc(baru->isiTeks, len + 1);
            if (temp != NULL) {
                baru->isiTeks   = temp;
                baru->kapasitas = len + 1;
            }
        }

        strcpy(baru->isiTeks, buffer);
        baru->panjang = len;

        // Sambungkan ke akhir list
        baru->prev       = editor.tail;
        baru->next       = NULL;
        editor.tail->next = baru;
        editor.tail       = baru;
        editor.totalBaris++;
    }

    editor.kursorBaris = editor.head;
    editor.kursorX     = 0;

    fclose(file);
}