
void hapus_backspace(){
    Baris *baris = editor.kursorBaris; //ponter untuk menyimpan posisi baris
    int x = editor.kursorX; //menyimpan posisi kolom kursor

    if (baris == NULL) return; //mengecek baris, kalau tidak ada maka berhenti

    //AWAL BARIS
    if (x == 0){ //ngecek apakah kursor berada di kolom pertama
        if (baris->prev == NULL) return; // cek apa ada baris di baris sebelumnya.

        Baris *atas = baris->prev; //membuat pointer untuk posisi kursor atau node baris paling atas.
        int panjang_atas = atas->panjang; //menghitung panjang baris atas
        int total = panjang_atas + baris->panjang; //mentotal antara panjang baris atas dan baris saat ini.

        // realloc baris atas kalau tidak muat
        if (total + 1 > atas->kapasitas) { // mengecek apakah kapasitas cukup atau tidak
            int kapasitasBaru = total + 1; //menentukan kapasitas baru untuk baris tersebut

            char *temp = realloc(atas->isiTeks, kapasitasBaru); //memperbesar memori kapasitas di pointer temp
            if (temp == NULL) return; //cek kalau realloc gagal
            atas->isiTeks = temp; //memindahkan alamat data ke lokasi memori terbaru  yang sudah di realloc
            atas->kapasitas = kapasitasBaru; //int kapasitas dari node baris tau ukuran terbaru dari baris tersebut
        }

        // gabung teks baris sekarang ke baris atas
        strcat(atas->isiTeks, baris->isiTeks); //menggabungkan isi string kalimat baris ke string atas
        atas->panjang = total; //mengupdate isi node atas menjadi isi terbaru

        // pindah kursor ke atas
        editor.kursorBaris = atas; //menandakan kursor berada di baris atas
        editor.kursorX = panjang_atas; //mengubah posisi kursor menyesuaikan dengan posisi huruf terakhir sebelum pindah
        //editor.kursorY--; // node

        hapus_node(baris);//menghapus node bawah yang sudah dipindah ke atas
    }

    //TENGAH BARIS
    else { //ketika kursor tidak di awal baris atau kolom 0
        if (x > baris->panjang) return; //verivikasi apakah posisi kursor melebihi jumlah baris atau tidak

        shift_kiri(baris, x - 1); //menggeser karakter ke kiri (setelah dihapus)
        baris->panjang--; //mengupdate panjang baris setelah ada yang dihapus
        baris->isiTeks[baris->panjang] = '\0'; //menjamin string berhenti di tempat yang benar
        editor.kursorX--; //menggeser posisi kursor ke huruf sebelumnya atau mundur satu kolom
    }
}

void saveFile() {
    FILE *fp; //FILE tipe data khusus file yg ada di library stdio.h dan fp sebagai pointer yg nunjuk ke FILE
    if(strlen(namaFileAktif) == 0){ //ini mengecek panjang string di file  yg dibuka, jika 0 berarti file belum di save dan lanjut ke bawah, jika > 0 maka skip.
    	printf("\nSimpan file dengan nama (jangan buat nama file dengan karakter /\:*?<>|): ");
        fgets(namaFileAktif, sizeof(namaFileAktif), stdin); //membaca input namafile dari user
        namaFileAktif[strcspn(namaFileAktif, "\n")] = '\0'; //menghapus tanda enter atau \n. 
    }

    fp = fopen(namaFileAktif, "w"); //pointer membuka file tadi dan menulis dari awal.
    if (fp == NULL){ //ini antisipasi jika  file salah buka.
        printf("Gagal menyimpan file!\n");
        return;
    }

    // traverse dari head ke tail
    Node *current = editor.head; //pointer current menunjuk ke node baris paling atas
    while(current != NULL) { //selama pointer tadi masih menunjuk ke valid berarti lanjut
        fprintf(fp, "%s\n", current->isiTeks); //menulis isi node baris yang ditunjuk ke file
        current = current->next; //pointer pindah baris berikutnya dan ini terus berulang sampai node kosong
    }

    fclose(fp);// menutup file yg dibuka 
}


/*tambahan: disini kenapa menggunakan "w" bukan "a", jadi alurnya ketika ada update dari user, maka isi yang lama itu dihapus dulu dan digantikan dengan 
isi baru, kalau pakai a bisa terjadi tumpang tindih dengan kalimat yang ada sebelumnya.*/

void newFile() {
    Node *current = editor.head; // membuat pointer baris pertama baru untuk file baru
    while (current != NULL) { //selama current masih ada isi baris maka akan terus me-loop (untuk menghapus)
        Node *next = current->next; //menyimpan alamat node baris berikutnya
        free(current->isiTeks);  // bebaskan array char dulu
        free(current);           // baru bebaskan node-nya
        current = next;
    }

    // buat 1 node baru sebagai baris pertama
    Node *node = buat_node();
    editor.head = node; //menjadikan node tersebut sebagai node baris pertama
    editor.tail = node; //menjadikan node tersebut sebagai node baris terakhir
    editor.kursorBaris = node; //meletakkan kursor baris pada baris pertama
    editor.kursorX = 0; //mengatur posisi kursor kolom menjadi 0
    editor.kursorY = 0; //mengatur posisi kursor baris menjadi 0
    editor.totalBaris = 1; //mencatat bahwa baris saat ini ada 1

    namaFileAktif[0] = '\0'; //menandakan bahwa file baru ini belum ada nama
    system("cls"); //
}

Baris *buatNode(){
    //1. alokasi memori untuk node baris
    Baris *node = malloc(sizeof(Baris)); //membuat/mengalokasikan memori menyesuaikan dengan struct baris
    if (node == NULL){ //mengecek apakah malloc gagal
        return 0;
    }
    //2. alokasi  memori  untuk char kolom
    node->isiTeks = malloc(kapasitas_awal * sizeof(char)); //malloc untuk isi teks sesuai dengan kapasitas awal yaitu 16
    if (node->isiTeks == NULL){ //mengecek malloc isiteks
        free(node); //kalau gagal berarti node itu di free atau dihapus
        return 0;
    }
    //3. isi nilai awal
    node->isiTeks[0] = '\0'; //mengisi kolom 0 dengan \0
    node->panjang = 0; //mengisi panjang dengan 0 karena belum ada karakter
    node->kapasitas = kapasitas_awal; //kapasitas diisi dengan kapasitas awal yaitu 16
    node->prev = NULL; //pointer ke baris sebelumnya null, karena belum ada yang ditunjuk
    node->next = NULL; //pointer ke baris berikutnya null, karena belum ada yang ditunjuk
    return node;
}


