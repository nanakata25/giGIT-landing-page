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

}




