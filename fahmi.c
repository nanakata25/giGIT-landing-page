#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Global.h"
#include "fahmi.h"
#include "rena.h"

char namaFile[100];
/*HAPUS BACKSPACE*/
void hapus_backspace() {
    Baris *baris = editor.kursorBaris;
    int x = editor.kursorX;
    int i;
 
    if (baris == NULL) return;
 
    /*di awal baris: gabung dengan baris atas*/
	if (x == 0) {
	    if (baris->prev == NULL) return;
	
	    Baris *atas = baris->prev;
	    int panjang_atas = atas->panjang;
	    int total = panjang_atas + baris->panjang;
	
	    /*menolak gabung kalau hasilnya melebihi batas */
	    if (total > MaksPanjangBaris) return;
	
	    /* realloc baris atas jika tidak muat */
	    if (total + 1 > atas->kapasitas) {
	        if (!reallocBaris(atas, total + 1)) return;
	    }
 		
 		/*menggabung isi baris bawah ke baris atas*/
        strcat(atas->isiTeks, baris->isiTeks);
        atas->panjang = total;
 
        /*memindah next baris1 ke baris3 dan prev baris3 ke baris1*/
        atas->next = baris->next;
        if (baris->next != NULL){
        	baris->next->prev = atas;
		}else{
			editor.tail = atas;
		}
            
        editor.kursorBaris = atas;
        editor.kursorX = panjang_atas;
        editor.totalBaris--;
 
        free(baris->isiTeks);
        free(baris);
    }
    /*di tengah baris*/
    else {
        if (x > baris->panjang) {
        	return;	
		}
 		
 		/*menggeser isi string*/
        for (i = x - 1; i < baris->panjang - 1; i++){
        	baris->isiTeks[i] = baris->isiTeks[i + 1];	
		}
 		
        baris->panjang--;
        baris->isiTeks[baris->panjang] = '\0';
        editor.kursorX--;
    }
}

/*SIMPAN FILE*/
void saveFile() {
    FILE *fp;
    Baris *current;
 
    if(strlen(namaFile) == 0) {
        printf("\nSimpan file dengan nama: ");
        fgets(namaFile, sizeof(namaFile), stdin);
        namaFile[strcspn(namaFile, "\n")] = '\0';
    }
 
    fp = fopen(namaFile, "w");
    if (fp == NULL){
        printf("Gagal menyimpan file!\n");
        return;
    }
 
    current = editor.head;
    while (current != NULL) {
        fprintf(fp, "%s\n", current->isiTeks);
        current = current->next;
    }
    fclose(fp);
}

/*Inisialisasi Awal dan FILE BARU*/
void newFile(){
    Baris *current = editor.head;
    Baris *next;
    Baris *node;
 
    while(current != NULL) {
        next = current->next;
        free(current->isiTeks);
        free(current);
        current = next;
    }
 
    node = buatNode();
    editor.head = node;
    editor.tail = node;
    editor.kursorBaris = node;
    editor.kursorX = 0;
    editor.kursorY = 0;
    editor.totalBaris = 1;
 
    namaFile[0] = '\0';
}

/*BUAT NODE BARU*/
Baris *buatNode() {
	/*membuat node untuk baris*/
    Baris *node = malloc(sizeof(Baris));
    if (node == NULL) return NULL;
    
    
    node->isiTeks = malloc(KapasitasAwal * sizeof(char));
    if (node->isiTeks == NULL){ 
	free(node); return NULL; 
	}
 
    node->isiTeks[0] = '\0';
    node->panjang = 0;
    node->kapasitas = KapasitasAwal;
    node->prev = NULL;
    node->next = NULL;
    return node;
}