# 🚗 Booking Rental Kendaraan CLI

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

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
