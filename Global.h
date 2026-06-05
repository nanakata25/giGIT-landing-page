#ifndef GLOBAL_H
#define GLOBAL_H
#define KapasitasAwal 8
#define MaksPanjangBaris 100


typedef struct Baris{
    char *isiTeks;          //pointer ke string untuk isi teks baris
    int panjang;            //jumlah char saat ini
    int kapasitas;          // kapasitas buffer yang dialokasikan
    struct Baris *prev;     // pointer ke baris sebelumnya
    struct Baris *next;     // pointer ke baris selanjutnya
} Baris;

typedef struct {
    Baris *head;            //pointer ke baris pertama
    Baris *tail;            // pointer ke baris terakhir
    Baris *kursorBaris;     // baris tempat kursor sekarang
    int kursorX;            // posisi kolom kursor (misal karakter ke-x)
    int kursorY;            // posisi baris kursor (misal di layar baris ke-y)
    int totalBaris;         // total jumlah baris dalam dokumen
} DataEditor;

extern DataEditor editor;

#endif
