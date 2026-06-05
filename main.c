#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#include "Global.h"
#include "nakata.h"
#include "fahmi.h"
#include "rena.h"

DataEditor editor;

int main() {
    int  ch, ch2;
    char namaFileBuka[100];

    newFile();
    
    while (1) {      
        render();
        ch = getch();

        /* ======================== EXIT ======================== */
        if (ch == 27 || ch == 17)
            break;

        /* ==================== CTRL SHORTCUT ==================== */
        else if (ch == 14) {
            newFile();
        }
        else if (ch == 15) {
            printf("\nBuka file: ");
            fgets(namaFileBuka, sizeof(namaFileBuka), stdin);
            namaFileBuka[strcspn(namaFileBuka, "\n")] = '\0';
            if (strlen(namaFileBuka) > 0) {
                openFile(namaFileBuka);
            }
        }
        else if (ch == 19) {
            saveFile();
        }

        /* ================= ENTER & BACKSPACE ================= */
        else if (ch == 13) {
            tekan_enter();
        }
        else if (ch == 8) {
            hapus_backspace();
        }

        /* ==================== ARROW KEY ==================== */
        else if (ch == 0 || ch == 224) {
            ch2 = getch();
            switch (ch2) {
                case 72: gerakAtas();  break;
                case 80: gerakBawah(); break;
                case 75: gerakKiri();  break;
                case 77: gerakKanan(); break;
            }
        }

        /* ================= INPUT KARAKTER ================= */
        else if (ch >= 32 && ch <= 126) {
            ketik_huruf((char)ch);
        }
    }

    return 0;
}