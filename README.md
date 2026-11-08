Oke siap! Ini dia **kode lengkap `README.md`** yang sangat lengkap, mengajarkan Git dari nol, dan pastinya bikin repo kamu terlihat sangat profesional. 

Tinggal **Copy semua teks di dalam kotak abu-abu di bawah ini**, lalu **Paste** ke file `README.md` kamu (timpa semua isi yang lama), lalu simpan (`Ctrl + S`).

---

### 📋 COPY SEMUA TEKS DI BAWAH INI:

```markdown
# 🚗 Booking Rental Kendaraan CLI

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-Active-success.svg)

Aplikasi berbasis *Command Line Interface* (CLI) untuk sistem booking rental kendaraan. Dibuat menggunakan **C++17** dengan antarmuka terminal yang interaktif, validasi input, dan pencetakan struk bukti penyewaan otomatis.

---

## ✨ Fitur Utama

- 🚘 **Katalog Kendaraan**: Menampilkan 10 pilihan kendaraan (Mobil & Motor) beserta tarif sewa per hari.
- 📝 **Validasi Input**: Memastikan input No. KTP valid (16 digit angka) dan lama sewa lebih dari 0 hari.
- 💰 **Perhitungan Otomatis**: 
  - Diskon 10% untuk penyewaan dengan harga dasar minimal Rp 500.000.
  - PPN 11% dihitung dari harga setelah diskon.
- 💳 **Metode Pembayaran**: Mendukung pembayaran Tunai (dengan kalkulasi kembalian) dan Non-Tunai (Transfer Bank, OVO, GoPay, Dana).
- 🖨️ **Cetak Struk Otomatis**: Menyimpan bukti booking ke dalam file `.txt` dengan format rapi.
- 🔄 **Counter Booking**: Nomor booking otomatis bertambah setiap kali ada transaksi baru.

---

## 🛠️ Prasyarat

Sebelum melakukan *build*, pastikan sistem kamu sudah terinstal:
- **Compiler C++** (GCC / MinGW-w64 / MSVC)
- **Terminal** yang mendukung (PowerShell, CMD, atau Bash)

### Windows (MSYS2 UCRT64)
Jika menggunakan MSYS2, buka terminal UCRT64 dan jalankan:
```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc
```

---

## 🚀 Cara Clone, Build & Menjalankan

Jika kamu baru pertama kali mengambil kode dari GitHub, ikuti panduan **Clone** di bawah ini. 

### 1. Clone Repositori (Mengunduh Proyek)
Buka terminal (CMD / PowerShell / Git Bash) di folder tempat kamu ingin menyimpan proyek, lalu jalankan:
```bash
git clone https://github.com/annsrlhh771/booking-rental-kendaraan.git
```
Setelah berhasil diunduh, masuk ke dalam foldernya:
```bash
cd booking-rental-kendaraan
```

### 2. Kompilasi Kode (Build)
Kompilasi file `main.cpp` menjadi file `.exe` menggunakan compiler C++:
```bash
g++ src/main.cpp -o src/main.exe
```

### 3. Jalankan Aplikasi
Setelah berhasil dikompilasi, jalankan programnya:
```bash
./src/main.exe
```
*(Untuk pengguna Linux/macOS, gunakan `./src/main`)*

---

## 📂 Struktur Proyek

```text
booking-rental-kendaraan/
├── src/
│   └── main.cpp          # Kode sumber utama (Entry Point)
├── .gitignore            # Konfigurasi file yang diabaikan Git
├── README.md             # Dokumentasi proyek
└── (File output .txt akan dibuat otomatis saat program berjalan)
```

---

## 📸 Tampilan Aplikasi (Preview)

```text
=== PROGRAM BOOKING RENTAL KENDARAAN ===
Masukkan nama penyewa : Budi
Masukkan no HP        : 08123456789

Daftar Kendaraan Tersedia:
 1. Toyota Avanza        Rp. 350.000,00 / hari
 2. Daihatsu Xenia       Rp. 330.000,00 / hari
...

Masukkan kode kendaraan        : 1
Toyota Avanza tersedia dan sudah dapat dibooking.
     Silakan isi tanggal ambil dan lama sewa.

Masukkan tanggal ambil (dd-mm-yyyy): 12-11-2026
Masukkan lama sewa (hari)      : 2
Masukkan No KTP (16 digit)     : 3201234567890001

============================================================
                  RENTAL KENDARAAN
============================================================
Kode Booking         : BK121126-001
Nama Penyewa         : Budi
Kendaraan            : Toyota Avanza
Lama Sewa            : 2 hari
------------------------------------------------------------
Total Bayar          : Rp. 777.000,00
============================================================
```

---

## 📚 Panduan Git Dasar (Untuk Developer/Pengguna)

Jika kamu ingin mengubah kode ini di komputer sendiri atau ingin berkontribusi, berikut adalah perintah dasar Git yang wajib diketahui.

### 1. Menarik Pembaruan (Pull)
Jika ada perubahan terbaru di GitHub (misalnya ada update kode), tarik perubahan tersebut ke komputermu:
```bash
git pull origin main
```

### 2. Menyimpan Perubahan (Commit)
Setelah kamu mengubah kode di VS Code, simpan perubahan tersebut ke dalam "snapshot" Git:
```bash
git add .
git commit -m "Pesan perubahan kamu di sini"
```

### 3. Mengirim Perubahan (Push)
Setelah di-commit, kirim perubahan dari komputermu ke repositori GitHub:
```bash
git push origin main
```

> 💡 **Tips Eksperimen:** Jika kamu ingin mengubah kode tanpa takut merusak kode utama, buat *branch* baru terlebih dahulu: `git checkout -b nama-branch-kamu`. Jika berhasil, baru gabungkan ke `main`.

---

## 🤝 Kontribusi

Kontribusi selalu terbuka! Jika kamu ingin menambahkan fitur atau memperbaiki bug:
1. Fork repositori ini.
2. Buat branch baru (`git checkout -b fitur/fitur-baru`).
3. Commit perubahanmu (`git commit -m 'Menambahkan fitur X'`).
4. Push ke branch (`git push origin fitur/fitur-baru`).
5. Buat Pull Request.

---

## 📄 Lisensi
Proyek ini dilisensikan di bawah [MIT License](LICENSE).
```

---

### 🚀 Langkah Terakhir: Upload ke GitHub

Setelah kamu paste dan simpan file `README.md` di VS Code, buka terminal dan jalankan 3 perintah ini untuk mengirim pembaruannya ke GitHub:

```bash
git add README.md
```
```bash
git commit -m "docs: mempercantik README dan menambahkan panduan Git"
```
```bash
git push
```

Setelah itu, **buka halaman GitHub kamu dan refresh**. Repo kamu sekarang akan terlihat sangat profesional dan mengajarkan orang lain cara menggunakan Git! 🎉
