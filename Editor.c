#include <stdio.h>
#include <string.h>
#include "editor.h"
#include "Global.h"

static void wrap_baris (int y, char c);

void ketik_huruf(char c) {
    int x = editor.kursorX;
    int y = editor.kursorY;
    int len = strlen(editor.isiTeks[y]);

    if (x > len) x = len;

    // MASIH MUAT
    if (len < MAKS_KOLOM - 1) {
        for (int i = len; i >= x; i--) {
            editor.isiTeks[y][i + 1] = editor.isiTeks[y][i];
        }
        editor.isiTeks[y][x] = c;
        editor.kursorX++;
    }
    // PENUH
    else {
        if (x < len) {
            char last = editor.isiTeks[y][len - 1];
            // geser kanan dari len-1 turun ke x
            for (int i = len - 1; i > x; i--) {
                editor.isiTeks[y][i] = editor.isiTeks[y][i - 1];
            }
            editor.isiTeks[y][x] = c;
            editor.isiTeks[y][len] = '\0';
            wrap_baris(y, last);
            // kursor tetap di baris ini, maju 1
            editor.kursorX++;
        }
        else {
            // kursor di ujung, char baru carry ke baris bawah
            wrap_baris(y, c);
            editor.kursorY++;
            editor.kursorX = 1;
        }
    }
}
void hapus_backspace() {
    int y = editor.kursorY;
    int x = editor.kursorX;

    if (x == 0) {
        if (y == 0) return;

        int len_atas = strlen(editor.isiTeks[y - 1]);
        int len_sekarang = strlen(editor.isiTeks[y]);

         if (len_atas + len_sekarang >= MAKS_KOLOM - 1) {
            editor.kursorY--;
            editor.kursorX = len_atas;
            return;
        }

        strcat(editor.isiTeks[y - 1], editor.isiTeks[y]);

        for (int i = y; i < editor.totalBaris - 1; i++) {
            strcpy(editor.isiTeks[i], editor.isiTeks[i + 1]);
        }

        editor.isiTeks[editor.totalBaris - 1][0] = '\0';

        editor.totalBaris--;

        editor.kursorY--;
        editor.kursorX = len_atas;
    }
    else {
        int len = strlen(editor.isiTeks[y]);
        if (x > len) return;

        for (int i = x - 1; i < len; i++) {
            editor.isiTeks[y][i] = editor.isiTeks[y][i + 1];
        }

        editor.kursorX--;
        
        if (y + 1 < editor.totalBaris) {
        int len_sekarang = strlen(editor.isiTeks[y]);
        int len_bawah = strlen(editor.isiTeks[y + 1]);

        editor.isiTeks[y][len_sekarang] = editor.isiTeks[y + 1][0];
        editor.isiTeks[y][len_sekarang + 1] = '\0';

        for (int i = 0; i < len_bawah; i++) {
            editor.isiTeks[y + 1][i] = editor.isiTeks[y + 1][i + 1];
        }

        if (strlen(editor.isiTeks[y + 1]) == 0) {
            for (int i = y + 1; i < editor.totalBaris - 1; i++) {
                strcpy(editor.isiTeks[i], editor.isiTeks[i + 1]);
            }
            editor.isiTeks[editor.totalBaris - 1][0] = '\0';
            editor.totalBaris--;
        }
    }
}
}

void tekan_enter() {
    int y = editor.kursorY;
    int x = editor.kursorX;

    if (editor.totalBaris >= MAKS_BARIS - 1) return;

    int len = strlen(editor.isiTeks[y]);

    if (x > len) return;

    for (int i = editor.totalBaris; i > y; i--) {
        strcpy(editor.isiTeks[i], editor.isiTeks[i - 1]);
    }

    strcpy(editor.isiTeks[y + 1], &editor.isiTeks[y][x]);

    editor.isiTeks[y][x] = '\0';

    editor.totalBaris++;
    editor.kursorY++;
    editor.kursorX = 0;
}

void wrap_baris (int y, char c) {
    if (editor.totalBaris >= MAKS_BARIS) return;

    for (int i = editor.totalBaris; i > y + 1; i--){
        strcpy(editor.isiTeks[i], editor.isiTeks[i - 1]);
    }
    editor.totalBaris++;

    editor.isiTeks[y + 1][0] = '\0';

    editor.isiTeks[y + 1][0] = c;
    editor.isiTeks[y + 1][1] = '\0';
}

