#include <stdio.h>
#include <string.h>
#include "editor.h"
#include "Global.h"


/* ===== HELPER SHIFT ===== */

static void shift_kanan(int y, int x, int batas) {
    for (int i = batas; i >= x; i--) {
        editor.isiTeks[y][i + 1] = editor.isiTeks[y][i];
    }
}

static void shift_kiri(int y, int x) {
    int len = strlen(editor.isiTeks[y]);
    for (int i = x; i < len; i++) {
        editor.isiTeks[y][i] = editor.isiTeks[y][i + 1];
    }
}


/* ===== INTI EDITOR ===== */

void ketik_huruf(char c) {
    int x = editor.kursorX;
    int y = editor.kursorY;
    int len = strlen(editor.isiTeks[y]);

    if (x > len) x = len;

    // MASIH MUAT
    if (len < MAKS_KOLOM - 1) {
        shift_kanan(y, x, len);
        editor.isiTeks[y][x] = c;
        editor.kursorX++;
    }
    // PENUH
    else {
        if (x < len) {
            char last = editor.isiTeks[y][len - 1];

            shift_kanan(y, x + 1, len - 1);

            editor.isiTeks[y][x] = c;
            editor.isiTeks[y][len] = '\0';

            wrap_baris(y, last);
            editor.kursorX++;
        }
        else {
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
        else {
            editor.kursorY--;
            editor.kursorX = len_atas;
        }
    }

    // ===== TENGAH BARIS =====
    else {
        int len = strlen(editor.isiTeks[y]);
        if (x > len) return;

        shift_kiri(y, x - 1);
        editor.kursorX--;

        if (y + 1 < editor.totalBaris && editor.isWrap[y + 1] == 1) {
            int len_sekarang = strlen(editor.isiTeks[y]);
            int len_bawah = strlen(editor.isiTeks[y + 1]);

            if (len_bawah > 0) {
                editor.isiTeks[y][len_sekarang] = editor.isiTeks[y + 1][0];
                editor.isiTeks[y][len_sekarang + 1] = '\0';

                shift_kiri(y + 1, 0);
            }

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


void wrap_baris(int y, char c) {
    int sudah_insert = 0;

    while (1) {
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
            shift_kanan(y + 1, 0, len);
            next[0] = c;
            break;
        }
        else {
            char last = next[len - 1];

            shift_kanan(y + 1, 0, len - 1);

            next[0] = c;
            next[len] = '\0';

            c = last;
            y++;
        }
    }
}