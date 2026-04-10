#include <stdio.h>
#include <string.h>
#include "editor.h"
#include "Global.h"


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

    // =====================
    // KURSOR DI AWAL BARIS
    // =====================
    if (x == 0) {
        if (y == 0) return;

        int len_atas = strlen(editor.isiTeks[y - 1]);
        int len_sekarang = strlen(editor.isiTeks[y]);

        // Kalau hasil ENTER → boleh gabung
        if (editor.isWrap[y] == 0) {
            if (len_atas + len_sekarang >= MAKS_KOLOM - 1) {
                editor.kursorY--;
                editor.kursorX = len_atas;
                return;
            }

            strcat(editor.isiTeks[y - 1], editor.isiTeks[y]);

            for (int i = y; i < editor.totalBaris - 1; i++) {
                strcpy(editor.isiTeks[i], editor.isiTeks[i + 1]);
                editor.isWrap[i] = editor.isWrap[i + 1];
            }

            editor.totalBaris--;

            editor.kursorY--;
            editor.kursorX = len_atas;
        }
        // Kalau hasil WRAP → jangan digabung
        else {
            editor.kursorY--;
            editor.kursorX = len_atas;
        }
    }

    // =====================
    // HAPUS DI TENGAH BARIS
    // =====================
    else {
        int len = strlen(editor.isiTeks[y]);
        if (x > len) return;

        // hapus 1 karakter
        for (int i = x - 1; i < len; i++) {
            editor.isiTeks[y][i] = editor.isiTeks[y][i + 1];
        }

        editor.kursorX--;

        // =====================
        // TARIK DARI BAWAH (HANYA JIKA WRAP)
        // =====================
        if (y + 1 < editor.totalBaris && editor.isWrap[y + 1] == 1) {
            int len_sekarang = strlen(editor.isiTeks[y]);
            int len_bawah = strlen(editor.isiTeks[y + 1]);

            if (len_bawah > 0) {
                // ambil 1 char dari bawah
                editor.isiTeks[y][len_sekarang] = editor.isiTeks[y + 1][0];
                editor.isiTeks[y][len_sekarang + 1] = '\0';

                // geser kiri baris bawah
                for (int i = 0; i < len_bawah; i++) {
                    editor.isiTeks[y + 1][i] = editor.isiTeks[y + 1][i + 1];
                }
            }

            // kalau baris bawah kosong → hapus
            if (strlen(editor.isiTeks[y + 1]) == 0) {
                for (int i = y + 1; i < editor.totalBaris - 1; i++) {
                    strcpy(editor.isiTeks[i], editor.isiTeks[i + 1]);
                    editor.isWrap[i] = editor.isWrap[i + 1];
                }
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
    editor.isWrap[y + 1] = 0;
    editor.kursorY++;
    editor.kursorX = 0;
}

void wrap_baris (int y, char c) {
        int sudah_insert = 0;

    while (1){
        if (y + 1 >= MAKS_BARIS) break;

        if (!sudah_insert && y + 1 < editor.totalBaris && editor.isWrap[y + 1] == 0) {
            for (int i = editor.totalBaris; i > y + 1; i--) {
                strcpy(editor.isiTeks[i], editor.isiTeks[i - 1]);
                editor.isWrap[i] = editor.isWrap[i - 1];
            }
            editor.totalBaris++;
            editor.isiTeks[y + 1][0] = '\0';
            editor.isWrap[y + 1] = 1;

            sudah_insert = 1;
        }

        if (y + 1 >= editor.totalBaris) {
            editor.totalBaris++;
            editor.isiTeks[y + 1][0] = '\0';
            editor.isWrap[y + 1] = 1;
        }

        char *next = editor.isiTeks[y + 1];
        int len = strlen(next);

        if (len < MAKS_KOLOM - 1) {
            for (int i = len; i >= 0; i--) {
                next[i + 1] = next[i];
            }
            next[0] = c;
            break;
        }
        else {
            char last = next[len - 1];
            for (int i = len - 1; i >= 0; i--) {
                next[i + 1] = next[i];
            }
            next[0] = c;
            next[len] = '\0';
            c = last;
            y++;
        }
    }
}

