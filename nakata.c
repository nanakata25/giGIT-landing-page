#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
 
#include "Global.h"
#include "nakata.h" 
#include "fahmi.h"
#include "rena.h" 

// Fungsi buat geser kursor di layar console
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//Fungsi untuk menggerakkan kursor ke ATAS 
void gerakAtas() {
    if (editor.kursorBaris != NULL && editor.kursorBaris->prev != NULL) { // cek dulu, kalau kursorBaris belum ada atau udah di baris paling atas (head),
        editor.kursorBaris = editor.kursorBaris->prev;  // pindahin pointer kursor ke baris sebelumnya

        editor.kursorY--;         // update kursorY biar tampilannya ikut naik 1 baris

        if (editor.kursorX > editor.kursorBaris->panjang) { // panjang baris baru bisa beda dari baris sebelumnya,
            editor.kursorX = editor.kursorBaris->panjang;  // sesuaikan kursorX biar nggak nunjuk ke posisi di luar baris
        }
    }
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


void ketik_huruf(char c){
    int i;
    Baris *baris = editor.kursorBaris;
    int x = editor.kursorX;
    int len = baris->panjang;
 
   if (len >= MaksPanjangBaris){
    tekan_enter();

    baris = editor.kursorBaris;
    x = editor.kursorX;
    len = baris->panjang;
}

    if (len >= baris->kapasitas - 1) {
    	if (!reallocBaris(baris, baris->kapasitas * 2)){
			return;
		}
    }
 
    for (i = len; i >= x; i--)
        baris->isiTeks[i + 1] = baris->isiTeks[i];
 
    baris->isiTeks[x] = c;
    baris->panjang++;
    editor.kursorX++;
}


//render tampilan
void render(){

    printf("\033[H\033[J");

    printf("============== TEXT EDITOR ==============\n");
    printf("Ctrl+N: New | Ctrl+O: Open | Ctrl+S: Save\n");
    printf("Arrow: Move | Enter        | Backspace\n");
    printf("Ctrl+Q / ESC: Exit\n");
    printf("=========================================\n\n");

    Baris *sekarang = editor.head;

    int y = 0;

    while(sekarang != NULL){

        printf("%s\n", sekarang->isiTeks);

        // Cari posisi Y kursor berdasarkan node aktif
        if(sekarang == editor.kursorBaris){
            editor.kursorY = y;
        }

        sekarang = sekarang->next;
        y++;
    }

    // Batasi X agar tidak melebihi panjang teks
    if(editor.kursorX > editor.kursorBaris->panjang){
        editor.kursorX = editor.kursorBaris->panjang;
    }

    // Header memakai 6 baris
    gotoxy(
        editor.kursorX,
        editor.kursorY + 6
    );

    fflush(stdout);
}
