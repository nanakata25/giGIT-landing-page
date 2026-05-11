#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "Global.h"
#include "file.h"
#include "Editor.h"
#include "cursor.h"

char namaFileAktif[100];

void render(){
    char buffer[65536] = "";  
    char temp[256];

    system("cls");
    strcat(buffer, "============== TEXT EDITOR ==============\n");
    strcat(buffer, "Ctrl+N: New | Ctrl+O: Open | Ctrl+S: Save\n");
    strcat(buffer, "Arrow: Move | Enter 	   | Backspace\n");
    strcat(buffer, "Ctrl+Q / ESC: Exit\n");
    strcat(buffer, "=========================================\n\n");

    for (int i = 0; i < editor.totalBaris; i++) {
        snprintf(temp, sizeof(temp), "%s\n", editor.isiTeks[i]);
        if (strlen(buffer) + strlen(temp) < sizeof(buffer) - 1) {
            strcat(buffer, temp);
        }
    }

    //fputs(buffer, stdout); 
    printf("%s", buffer);
    gotoxy(editor.kursorX, editor.kursorY + 6);

    fflush(stdout);
}

/*void editFile(){
    newFile();
}*/


void newFile(){
    editor.totalBaris = 1;
    editor.kursorX = 0;
    editor.kursorY = 0;
    
    for ( int i = 0; i < MAKS_BARIS; i++) {
        editor.isiTeks[i][0] = '\0';
        editor.isWrap[i] = 0;
    }

	namaFileAktif[0] = '\0';
    system("cls");
}

void openFile(){
    FILE *fp;
    char nama[100]; 

    printf("\nBuka File: "); 
	fgets(nama, sizeof(nama), stdin); 
	nama[strcspn(nama, "\n")] = '\0'; 

    fp = fopen(nama, "r"); 
    if (fp == NULL) { 
        printf("ERROR File tidak ditemukan!\n");
        return;
    }
    for ( int i = 0; i < MAKS_BARIS; i++) { 
    editor.isWrap[i] = 0;
}

    strcpy(namaFileAktif, nama); 
    editor.totalBaris = 0; 

    while (editor.totalBaris < MAKS_BARIS && 
           fgets(editor.isiTeks[editor.totalBaris], MAKS_KOLOM, fp)) { 
            
            editor.isiTeks[editor.totalBaris]
		    [strcspn(editor.isiTeks[editor.totalBaris], "\n")] = '\0'; 
            editor.totalBaris++; 
            } 

    fclose(fp); 
    
    if (editor.totalBaris == 0) { 
    editor.totalBaris = 1;
    editor.isiTeks[0][0] = '\0'; 
    } 
}

void saveFile(){
    FILE *fp;
    if (strlen(namaFileAktif) == 0) { 
    	printf("\nSimpan file dengan nama:");
        fgets(namaFileAktif, sizeof(namaFileAktif), stdin); 
		namaFileAktif[strcspn(namaFileAktif, "\n")] = '\0';
    }

    fp = fopen(namaFileAktif, "w"); 
    if (fp == NULL) { 
        printf("[Error] Gagal menyimpan file!\n");
        return;
    }

    for ( int i = 0; i < editor.totalBaris; i++) { 
    	fprintf(fp, "%s\n", editor.isiTeks[i]);
	}

    fclose(fp); 
}
