#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#include "Global.h"
#include "Editor.h"
#include "cursor.h"
#include "file.h"

DataEditor editor;

int main() {
    newFile(); //ini untuk inisialisasi awal

    int ch, ch2;

    while (1) {
        render();

        ch = getch();

        // =====================
        // EXIT
        // =====================
        if (ch == 27 || ch == 17) break; // ESC atau Ctrl+Q

        // =====================
        // CTRL SHORTCUT
        // =====================
        else if (ch == 14) { // Ctrl+N
            newFile();
        }
        else if (ch == 15) { // Ctrl+O
            openFile();
        }
        else if (ch == 19) { // Ctrl+S
            saveFile();
        }

        // =====================
        // ENTER & BACKSPACE
        // =====================
        else if (ch == 13) {
            tekan_enter();
        }
        else if (ch == 8) {
            hapus_backspace();
        }

        // =====================
        // ARROW KEY
        // =====================
        else if (ch == 0 || ch == 224) {
    ch2 = getch();
    switch (ch2) {
        case 72: gerakAtas(); break;
        case 80: gerakBawah(); break;
        case 75: gerakKiri(); break;
        case 77: gerakKanan(); break;
    }
        }
        // =====================
        // INPUT KARAKTER
        // =====================
        else if (ch >= 32 && ch <= 126) {
            ketik_huruf((char)ch);
        }
    }

    return 0;
}