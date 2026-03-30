#include <stdio.h>
#include "editor.h"

int main() {

    int pilihan;

    do {
        printf("\n=== TEXT EDITOR ===\n");
        printf("1. Tampilkan Teks\n");
        printf("2. Insert Karakter\n");
        printf("3. Delete Karakter\n");
        printf("4. Kursor Kiri\n");
        printf("5. Kursor Kanan\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();

        switch(pilihan) {

            case 1:
                displayText();
                break;

            case 2:
                insertCharacter();
                break;

            case 3:
                deleteCharacter();
                break;

            case 4:
                moveLeft();
                break;

            case 5:
                moveRight();
                break;

            case 6:
                printf("Program selesai\n");
                break;

            default:
                printf("Menu tidak tersedia\n");
        }

    } while(pilihan != 6);

    return 0;
}