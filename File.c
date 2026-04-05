#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "File.h"

void editFile();
void newFile();
void openFile();
void saveFile();

void editFile(){

}
void newFile(){
    int k;
    
    printf("\n=== New File ===\n");

    char text[100][100];

    printf("Masukkan Teks:");
    getchar();
    fgets(text, sizeof(text),stdin);

    printf("\n File baru telah dibuat\n");
}

void openFile(){
    FILE *fp;
    char namafile[100];
    char baca;

    printf("\n=== Open File ===\n");
    printf("Masukkan Nama File:");
    scanf("%s", namafile);

    fp = fopen(namafile,"r");

    if (fp == NULL){
        printf("File Tidak Ada!!\n");
        return;
    }
    
    

   
    fclose(fp);
    
}

void saveFile(){
    
}