#include "Global.h"
#include "Editor.h"
#include "cursor.h"
#include "file.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// GERAK ATAS
void gerakAtas() {
    if (editor.kursorY > 0) {
        editor.kursorY--;

        // sesuaikan kolom agar tidak melebihi panjang baris
        int panjang = strlen(editor.isiTeks[editor.kursorY]);
        if (editor.kursorX > panjang) {
            editor.kursorX = panjang;
        }
    }
}

// GERAK BAWAH
void gerakBawah() {
    if (editor.kursorY < editor.totalBaris - 1) {
        editor.kursorY++;

        int panjang = strlen(editor.isiTeks[editor.kursorY]);
        if (editor.kursorX > panjang) {
            editor.kursorX = panjang;
        }
    }
}

// GERAK KIRI
void gerakKiri() {
    if (editor.kursorX > 0) {
        editor.kursorX--;
    }
    else if (editor.kursorY > 0) {
        // pindah ke akhir baris atas
        editor.kursorY--;
        editor.kursorX = strlen(editor.isiTeks[editor.kursorY]);
    }
}

// GERAK KANAN
void gerakKanan() {
    int panjang = strlen(editor.isiTeks[editor.kursorY]);

    if (editor.kursorX < panjang) {
        editor.kursorX++;
    }
    else if (editor.kursorY < editor.totalBaris - 1) {
        // pindah ke awal baris bawah
        editor.kursorY++;
        editor.kursorX = 0;
    }
}
