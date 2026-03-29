#include <stdio.h>
#include <string.h>
#include "editor.h"

void ketik_huruf(char c) {
    int y = editor.kursorY;
    int x = editor.kursorX;

    int len = strlen(editor.isiTeks[y]);

	if (x > len) return;
    if (len >= MAKS_KOLOM - 1) return;

    for (int i = len; i >= x; i--) {
        editor.isiTeks[y][i + 1] = editor.isiTeks[y][i];
    }

    editor.isiTeks[y][x] = c;

}


