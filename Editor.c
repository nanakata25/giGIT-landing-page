#include <stdio.h>
#include <string.h>
#include "editor.h"

void ketik_huruf(char c) {
    int x = editor.kursorX;
	int y = editor.kursorY;
    
    int len = strlen(editor.isiTeks[x]);

	if (y > len) return;
    if (len >= MAKS_KOLOM - 1) return;

    for (int i = len; i >= y; i--) {
        editor.isiTeks[x][i + 1] = editor.isiTeks[x][i];
    }
    
    editor.isiTeks[x][y] = c;
    editor.kursorX++;
}
void hapus_backspace() {
    int y = editor.kursorY;
    int x = editor.kursorX;

    if (x == 0) {
        if (y == 0) return;

        int len_atas = strlen(editor.isiTeks[y - 1]);
        int len_sekarang = strlen(editor.isiTeks[y]);

        if (len_atas + len_sekarang >= MAKS_KOLOM - 1) return;

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
    }
}

void tekan_enter() {
    int y = editor.kursorY;
    int x = editor.kursorX;

    if (editor.totalBaris >= MAKS_BARIS) return;

    int len = strlen(editor.isiTeks[y]);

    if (x > len) return;

    for (int i = editor.totalBaris; i > y + 1; i--) {
        strcpy(editor.isiTeks[i], editor.isiTeks[i - 1]);
    }

    strcpy(editor.isiTeks[y + 1], &editor.isiTeks[y][x]);

    editor.isiTeks[y][x] = '\0';

    editor.totalBaris++;

    editor.kursorY++;
    editor.kursorX = 0;
}



