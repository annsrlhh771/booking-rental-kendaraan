# booking-rental-kendaraan

Aplikasi console (CLI) untuk sistem booking rental kendaraan, ditulis dengan C++17.

## Fitur
- Daftar 10 kendaraan dengan tarif harian
- Booking dengan validasi KTP 16 digit
- Perhitungan otomatis: diskon 10% (min. Rp500.000), PPN 11%
- Metode pembayaran: Tunai / Transfer / OVO / GoPay / Dana
- Cetak bukti booking ke file `BUKTIxxx.txt`
- Counter booking otomatis via `counter_booking.txt`

## Prasyarat
- Compiler C++17 (GCC/Clang/MSVC)
- Windows: MSYS2 UCRT64

## Build & Jalankan

```bash
g++ src/main.cpp -o src/main.exe
./src/main.exe