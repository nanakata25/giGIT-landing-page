#include "nakata.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>   // buat COORD, SetConsoleCursorPosition, dll


// Fungsi buat geser kursor di layar console
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//Fungsi untuk menggerakkan kursor ke ATAS 
void gerakAtas() {
    // cek dulu, kalau kursorBaris belum ada atau udah di baris paling atas (head),
    if (editor.kursorBaris != NULL && editor.kursorBaris->prev != NULL) {
        // pindahin pointer kursor ke baris sebelumnya
        editor.kursorBaris = editor.kursorBaris->prev;

        // update kursorY biar tampilannya ikut naik 1 baris
        editor.kursorY--;

        // panjang baris baru bisa beda dari baris sebelumnya,
        // sesuaikan kursorX biar nggak nunjuk ke posisi di luar baris
        if (editor.kursorX > editor.kursorBaris->panjang) {
            editor.kursorX = editor.kursorBaris->panjang;
        }
    }
}

void render() {
    // pindahin kursor visual ke pojok kiri atas, JANGAN clear screen
    gotoxy(0, 0);

    // jalan dari head sampai ujung
    Baris *baris = editor.head;
    int barisKe = 0;

    while (baris != NULL) {
        // pindah ke baris ke-`barisKe` di layar
        gotoxy(0, barisKe);

        // cetak isi baris ini
        printf("%s", baris->isiTeks);

        // tambahin spasi sampe ujung kolom biar karakter lama (dari render sebelumnya)
        // yang masih nyangkut di kanan ke-timpa
        int sisa = MAKS_KOLOM - baris->panjang;
        for (int i = 0; i < sisa; i++) {
            printf(" ");
        }

        // lanjut ke baris berikutnya
        baris = baris->next;
        barisKe++;
    }

    // bersihin baris-baris lama di bawah (kalau habis ngehapus baris,
    // kan jumlah totalBaris berkurang, sisa-sisa di bawah harus dihapus)
    // di sini kita bersihin sampai ke baris ke-totalBaris yang lama,
    // simpelnya cetak spasi sampai beberapa baris ke bawah
    for (int i = barisKe; i < editor.totalBaris + 5; i++) {
        gotoxy(0, i);
        for (int j = 0; j < MAKS_KOLOM; j++) {
            printf(" ");
        }
    }

    // terakhir, balikin kursor visual ke posisi yang bener
    gotoxy(editor.kursorX, editor.kursorY);
}

// Fungsi untuk menggerakkan kursor ke KIRI
void gerakKiri() {
    // jaga-jaga kalau dokumen masih kosong pisan (belum ada node)
    if (editor.kursorBaris == NULL) return;

    if (editor.kursorX > 0) {
        // masih ada karakter di sebelah kiri, geser aja kolomnya
        // cabang ini sama persis kayak versi statis, karena gerak dalam baris
        // nggak butuh linked list
        editor.kursorX--;
    }
    else if (editor.kursorBaris->prev != NULL) {
        // udah di kolom 0, tapi masih ada baris di atas
        // jadi loncat ke akhir baris atas (kayak text editor pada umumnya)
        editor.kursorBaris = editor.kursorBaris->prev;
        editor.kursorY--;
        editor.kursorX = editor.kursorBaris->panjang;
    }
    // kalau udah di pojok kiri atas (kolom 0 dan nggak ada prev), ya diem aja
}


//  Fungsi untuk menggerakkan kursor ke KANAN 
void gerakKanan() {
    // jaga-jaga kalau dokumen masih kosong pisan (belum ada node)
    if (editor.kursorBaris == NULL) return;

    if (editor.kursorX < editor.kursorBaris->panjang) {
        // masih ada karakter di sebelah kanan, geser kolomnya
        // ini teh sama kayak versi statis, cuma sumber panjangnya doang yang beda
        editor.kursorX++;
    }
    else if (editor.kursorBaris->next != NULL) {
        // udah di ujung kanan baris, tapi masih ada baris di bawah
        // jadi loncat ke awal baris berikutnya
        editor.kursorBaris = editor.kursorBaris->next;
        editor.kursorY++;
        editor.kursorX = 0;
    }
    // kalau udah di pojok kanan bawah, diem wkwk
}


void ketik_huruf(char c) {

    Baris *baris = editor.kursorBaris;

    int x = editor.kursorX;
    int len = baris->panjang;

    if (x > len)
        x = len;

    if (len < baris->kapasitas - 1) {

        // geser karakter ke kanan
        for (int i = len; i >= x; i--) {
            baris->isiTeks[i + 1] = baris->isiTeks[i];
        }

        // insert karakter
        baris->isiTeks[x] = c;

        // update panjang
        baris->panjang++;

        // geser kursor
        editor.kursorX++;
    }
}
