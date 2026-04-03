#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void newFile(){
    printf("\n=== New File ===\n");

    char text[100][100];

    printf("Masukkan Teks:");
    getchar();
    fgets(text, sizeof(text),stdin);

    printf("\n File baru telah dibuat\n");
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

    printf("\nIsi File:\n");

    while ((ch = fgetc(fp)) != EOF){
        printf("%c", ch);
    }
    
    fclose(fp);
    
}

void saveFile(){
    
}