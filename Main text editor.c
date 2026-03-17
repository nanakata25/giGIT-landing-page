#include <stdio.h>
#include <stdlib.h>

void newFile(){
    printf("\n=== New File ===\n");

    char text[100][100];
}

void openFile(){
    FILE *fp;
    char namafile[100][100];
    char baca;

    printf("\n=== Open File ===\n");
    printf("Masukkan Nama File:");
    scanf("%s", namafile);

    fp = fopen(namafile,"r+");

    if (fp == NULL){
        printf("File Tidak Ada!!\n");
        return;
    }
}

void saveFile(){
    
}