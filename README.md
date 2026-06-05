# Proyek Aplikasi Berbasis Library  

## Deskripsi
Proyek ini merupakan pembuatan aplikasi text editor sederhana berbasis CLI yang dikembangkan menggunakan bahasa C. Pada tahap awal, penyimpanan teks menggunakan array statis, kemudian dikembangkan menjadi struktur Doubly Linked List dengan Dynamic Memory Allocation untuk mendukung pengelolaan teks yang lebih fleksibel. Project ini juga menerapkan konsep navigasi kursor, manipulasi teks, serta operasi file.

## NIM & Nama Anggota Kelompok
- 009_Dyas Nakata Hilwan
- 016_M.Fahmi Hadi Wijaya
- 028_Rena Fiantina 

## Fitur
### Pengelolaan Teks
- Menambahkan karakter.
- Menghapus karakter.
- Membuat baris baru (Enter).
- Menggabungkan baris (Backspace pada awal baris).

### Navigasi Kursor
- Kursor kiri.
- Kursor kanan.
- Kursor atas.
- Kursor bawah.

### File Handling
- Membuka file teks (Open File).
- Membaca isi file ke dalam linked list.
- Menyimpan isi editor ke file (Save File). 

## Struktur Data
Aplikasi dibuat menggunakan struktur data Double Linked List dan Dynamic Character Array 
Doubly Linked List digunakan sebagai struktur utama penyimpanan data teks.
Representasi:

[Baris 1] ⇄ [Baris 2] ⇄ [Baris 3] ⇄ ...

Setiap node merepresentasikan satu baris teks dan saling terhubung menggunakan pointer next dan prev.

Isi teks pada setiap node disimpan menggunakan array karakter dinamis (char *).
Representasi:

Node Baris
 ├── isiTeks
 ├── panjang
 ├── kapasitas
 ├── prev
 └── next

Kapasitas penyimpanan dapat diperbesar menggunakan realloc() ketika jumlah karakter melebihi kapasitas yang tersedia.

## Cara Kerja Singkat
- Program menerima input dari pengguna.
- Input diproses sesuai fungsi yang dipanggil.
- Data teks disimpan dalam Doubly Linked List.
- Perubahan teks diperbarui secara langsung pada struktur data.
- Dokumen dapat disimpan ke file atau dibuka kembali dari file.

## Cara Menjalankan

Compile:

```bash
gcc main.c rena.c fahmi.c nakata.c -o main.exe
```

Run:

```bash
.\main.exe
```


