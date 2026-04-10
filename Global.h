#ifndef GLOBAL_H
#define GLOBAL_H

#define MAKS_BARIS 100
#define MAKS_KOLOM 100

typedef struct {
    char isiTeks[MAKS_BARIS][MAKS_KOLOM];
    int isWrap[MAKS_BARIS];
    int kursorX;
    int kursorY;
    int totalBaris;
} DataEditor;

extern DataEditor editor;

#endif
