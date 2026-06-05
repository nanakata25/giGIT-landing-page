#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rena.h"
#include "fahmi.h"
 
int reallocBaris(Baris *baris, int kapasitasBaru) {
    char *temp = realloc(baris->isiTeks, kapasitasBaru);
    if (temp == NULL){
		return 0; // klo gagal
	}
	baris->isiTeks   = temp;
    baris->kapasitas = kapasitasBaru;
    return 1;  // klo berhasil
}

/* ===== TEKAN ENTER ===== */
void tekan_enter() {
    Baris *baris = editor.kursorBaris;
    int x = editor.kursorX;
 
    char *sisa = baris->isiTeks + x;
    int panjang_sisa = baris->panjang - x;
 
    Baris *baru = buatNode();
    if (baru == NULL) return;
 
    if (panjang_sisa + 1 > baru->kapasitas) {
        if (!reallocBaris(baru, panjang_sisa + 1)) { 
			free(baru->isiTeks); 
			free(baru); 
			return; 
		}
	}
 
    strcpy(baru->isiTeks, sisa);
    baru->panjang = panjang_sisa;
 
    baris->isiTeks[x] = '\0';
    baris->panjang = x;
 
    baru->prev = baris;
    baru->next = baris->next;
    if (baris->next != NULL){
    	baris->next->prev = baru;
	}else{
		editor.tail = baru;	
	}
    baris->next = baru;
 
    editor.kursorBaris = baru;
    editor.kursorX = 0;
    //editor.kursorY++;
    editor.totalBaris++;
}
 
/* ===== KURSOR BAWAH ===== */
void gerakBawah() {
    if (editor.kursorBaris->next == NULL) return;
 
    editor.kursorBaris = editor.kursorBaris->next;
 
    if (editor.kursorX > editor.kursorBaris->panjang){
    	editor.kursorX = editor.kursorBaris->panjang;	
	}
}
 
/* ===== BUKA FILE ===== */
void openFile(char *namaFile) {
    FILE *file;
    char  buffer[1024];
    Baris *current, *baru;
    int len;

    file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Error: File '%s' tidak ditemukan.\n", namaFile);
        return;
    }

    // bersihkan editor lama
    current = editor.head;
    while (current != NULL) {
        Baris *next = current->next;
        free(current->isiTeks);
        free(current);
        current = next;
    }

    // inisialisasi editor kosong
    editor.head        = buatNode();
    editor.tail        = editor.head;
    editor.kursorBaris = editor.head;
    editor.kursorX     = 0;
    editor.kursorY     = 0;
    editor.totalBaris  = 1;

    // baca baris pertama
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        len = strlen(buffer);

        if (len + 1 > editor.head->kapasitas) {
		    if (!reallocBaris(editor.head, len + 1)) {
		        fclose(file);
		        return;
		    }
		}

        strcpy(editor.head->isiTeks, buffer);
        editor.head->panjang = len;
    }

    // baca baris berikutnya
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        len = strlen(buffer);

        baru = buatNode();
        if (baru == NULL){
            break;
        }

        if (len + 1 > baru->kapasitas){
            reallocBaris(baru, len + 1);
        }

        strcpy(baru->isiTeks, buffer);
        baru->panjang = len;

        baru->prev        = editor.tail;
        baru->next        = NULL;
        editor.tail->next = baru;
        editor.tail       = baru;
        editor.totalBaris++;
    }

    editor.kursorBaris = editor.head;
    editor.kursorX     = 0;
    editor.kursorY     = 0;

    fclose(file);
}

