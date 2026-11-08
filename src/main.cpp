#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct {
    int kode;
    char nama[30];
    double tarifPerHari;
    int tersedia; // 1 = tersedia, 0 = sudah dibooking
} Kendaraan;

typedef struct {
    char kodeBooking[30];
    char namaPenyewa[30];
    char noHP[20];
    char noKTP[20];
    Kendaraan kendaraan;
    char tanggalAmbil[15];
    int lamaSewa;
    double totalBayar;
    char metode[30];
} Booking;

// Buffer bukti booking
char bufferBukti[20000];
int pos = 0;

// Makro untuk print ke layar + simpan ke buffer
#define PRINT_BUFFER(...) do { \
    pos += sprintf(bufferBukti+pos, __VA_ARGS__); \
    printf(__VA_ARGS__); \
} while(0)

// ===================== FUNGSI BANTU =====================

// Fungsi print harga ke layar
void printRupiah(double value){
    long n = (long)(value + 0.5);
    char temp[30];
    sprintf(temp,"%ld",n);
    int len = strlen(temp);
    for(int i=0;i<len;i++){
        printf("%c", temp[i]);
        if((len-i-1)%3==0 && i!=len-1) printf(".");
    }
    printf(",00");
}

// Fungsi print harga ke layar + buffer
void printRupiahBuffer(double value){
    long n = (long)(value + 0.5);
    char temp[30];
    sprintf(temp,"%ld",n);
    int len = strlen(temp);
    for(int i=0;i<len;i++){
        pos += sprintf(bufferBukti+pos,"%c", temp[i]);
        printf("%c", temp[i]);
        if((len-i-1)%3==0 && i!=len-1){
            pos += sprintf(bufferBukti+pos,".");
            printf(".");
        }
    }
    pos += sprintf(bufferBukti+pos,",00");
    printf(",00");
}

// Fungsi input uang tunai interaktif
long inputTunai(){
    char input[20]="";
    int len=0;
    char ch;

    printf("Masukkan Uang Bayar : Rp. ");

    while(1){
        ch=getch();
        if(ch==13) break; // Enter
        else if(ch==8 && len>0){ // Backspace
            len--;
            input[len]='\0';
        }
        else if(ch>='0' && ch<='9' && len<18){
            input[len++]=ch;
            input[len]='\0';
        }

        // Clear baris dan print ulang
        printf("\rMasukkan Uang Bayar : Rp.                    ");
        printf("\rMasukkan Uang Bayar : Rp. ");
        if(len>0){
            long num = atol(input);
            printRupiah(num);
        }
        fflush(stdout);
    }
    printf("\n");
    return atol(input);
}

// Baca satu baris teks (aman, tanpa sisa newline)
void bacaTeks(char *dest, int ukuran){
    fgets(dest, ukuran, stdin);
    dest[strcspn(dest,"\n")] = 0;
}

// Baca angka bulat
int bacaInt(){
    char tmp[30];
    bacaTeks(tmp, sizeof(tmp));
    return atoi(tmp);
}

// Cek apakah string hanya berisi digit dengan panjang tertentu
int cekDigit(const char *s, int panjang){
    if((int)strlen(s) != panjang) return 0;
    for(int i=0;s[i];i++) if(s[i]<'0' || s[i]>'9') return 0;
    return 1;
}

// Fungsi print rata tengah
void printCenter(const char *text, int width){
    int len = strlen(text);
    int pad = (width - len) / 2;
    for(int i=0;i<pad;i++){ printf(" "); pos += sprintf(bufferBukti+pos," "); }
    printf("%s\n", text);
    pos += sprintf(bufferBukti+pos,"%s\n", text);
}

// ===================== PROGRAM UTAMA =====================
int main() {
    srand(time(NULL));

    // ==================== 1. INISIALISASI ====================
    // Siapkan daftar kendaraan, tarif sewa, dan dataBooking
    Kendaraan daftarKendaraan[10] = {
        {1,"Toyota Avanza",350000,1},
        {2,"Daihatsu Xenia",330000,1},
        {3,"Honda Brio",300000,1},
        {4,"Toyota Innova",500000,1},
        {5,"Suzuki Ertiga",340000,1},
        {6,"Mitsubishi Xpander",420000,1},
        {7,"Honda Vario 160",100000,1},
        {8,"Yamaha NMAX",150000,1},
        {9,"Honda Scoopy",90000,1},
        {10,"Toyota Hiace",800000,1}
    };
    int jumlahKendaraan = 10;

    Booking dataBooking[MAX];
    int jumlahBooking = 0;

    int lanjutBooking = 1;

    do {
        // Reset bufferBukti dan data booking
        pos = 0;
        Booking bk;
        memset(&bk, 0, sizeof(bk));

        printf("\n=== PROGRAM BOOKING RENTAL KENDARAAN ===\n");

        // Input data penyewa (nama, no HP)
        printf("Masukkan nama penyewa : ");
        bacaTeks(bk.namaPenyewa, sizeof(bk.namaPenyewa));
        printf("Masukkan no HP        : ");
        bacaTeks(bk.noHP, sizeof(bk.noHP));

        // Baca nomor booking dari file counter (kalau belum ada, mulai dari 1)
        int nomorBooking = 1;
        FILE *fcounter = fopen("counter_booking.txt","r");
        if(fcounter){
            fscanf(fcounter,"%d",&nomorBooking);
            fclose(fcounter);
        }

        // Ambil tanggal dan waktu sekarang, lalu buat kode booking
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char bufferDate[20];
        sprintf(bufferDate,"%02d%02d%02d",tm.tm_mday,tm.tm_mon+1,tm.tm_year%100);
        sprintf(bk.kodeBooking,"BK%s-%03d",bufferDate,nomorBooking);

        // ==================== 2. INPUT KENDARAAN ====================
        // Tampilkan daftar kendaraan yang tersedia
        printf("\nDaftar Kendaraan Tersedia:\n");
        for(int i=0;i<jumlahKendaraan;i++){
            if(daftarKendaraan[i].tersedia){
                printf("%2d. %-20s Rp. ", daftarKendaraan[i].kode, daftarKendaraan[i].nama);
                printRupiah(daftarKendaraan[i].tarifPerHari);
                printf(" / hari\n");
            }
        }

        // Input kode kendaraan (ulangi sampai valid dan tersedia)
        int idxKendaraan = -1;
        while(1){
            printf("\nMasukkan kode kendaraan        : ");
            int kode = bacaInt();

            if(kode<1 || kode>jumlahKendaraan){
                printf("Kode kendaraan tidak valid!\n");
                continue;
            }
            if(!daftarKendaraan[kode-1].tersedia){
                printf("Kendaraan sudah dibooking, silakan pilih kendaraan lain!\n");
                continue;
            }
            idxKendaraan = kode-1;
            break;
        }

        // Pesan kendaraan tersedia (muncul sebelum mengisi tanggal ambil)
        printf("\n%s tersedia dan sudah dapat dibooking.\n",
               daftarKendaraan[idxKendaraan].nama);
        printf("     Silakan isi tanggal ambil dan lama sewa.\n\n");

        // Input tanggal ambil
        printf("Masukkan tanggal ambil (dd-mm-yyyy): ");
        bacaTeks(bk.tanggalAmbil, sizeof(bk.tanggalAmbil));

        // Input lama sewa (ulangi sampai > 0)
        while(1){
            printf("Masukkan lama sewa (hari)      : ");
            bk.lamaSewa = bacaInt();
            if(bk.lamaSewa > 0) break;
            printf("Lama sewa tidak valid!\n");
        }

        bk.kendaraan = daftarKendaraan[idxKendaraan];

        // ==================== 3. PROSES BIAYA ====================
        // Input No KTP (ulangi sampai 16 digit angka)
        while(1){
            printf("Masukkan No KTP (16 digit)     : ");
            bacaTeks(bk.noKTP, sizeof(bk.noKTP));
            if(cekDigit(bk.noKTP,16)) break;
            printf("Data KTP salah! Harus 16 digit angka, silakan ulangi.\n");
        }

        // Hitung harga dasar, diskon 10% (jika >= Rp 500.000), PPN 11%, total bayar
        double hargaDasar = bk.kendaraan.tarifPerHari * bk.lamaSewa;
        double diskon = (hargaDasar>=500000)? hargaDasar*0.10 : 0;
        double totalSetelahDiskon = hargaDasar - diskon;
        double ppn = totalSetelahDiskon * 0.11;
        double totalBayar = totalSetelahDiskon + ppn;
        bk.totalBayar = totalBayar;

        // ==================== 4. PEMBAYARAN ====================
        // Tampilkan rincian biaya
        PRINT_BUFFER("\n============================================================\n");
        PRINT_BUFFER("                  RENTAL KENDARAAN\n");
        PRINT_BUFFER("============================================================\n");
        PRINT_BUFFER("%-20s : %s\n","Kode Booking",bk.kodeBooking);
        PRINT_BUFFER("%-20s : %02d-%02d-%04d %02d:%02d:%02d\n","Tanggal Booking",
            tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
        PRINT_BUFFER("%-20s : %s\n","Nama Penyewa",bk.namaPenyewa);
        PRINT_BUFFER("%-20s : %s\n","No HP",bk.noHP);
        PRINT_BUFFER("%-20s : %s\n","No KTP",bk.noKTP);
        PRINT_BUFFER("------------------------------------------------------------\n");
        PRINT_BUFFER("%-20s : %s\n","Kendaraan",bk.kendaraan.nama);
        PRINT_BUFFER("%-20s : %s\n","Tanggal Ambil",bk.tanggalAmbil);
        PRINT_BUFFER("%-20s : %d hari\n","Lama Sewa",bk.lamaSewa);
        PRINT_BUFFER("%-20s : Rp. ","Tarif per Hari"); printRupiahBuffer(bk.kendaraan.tarifPerHari); PRINT_BUFFER("\n");
        PRINT_BUFFER("------------------------------------------------------------\n");
        PRINT_BUFFER("%-20s : Rp. ","Harga Dasar"); printRupiahBuffer(hargaDasar); PRINT_BUFFER("\n");
        PRINT_BUFFER("%-20s : Rp. ","Diskon 10%"); printRupiahBuffer(diskon); PRINT_BUFFER("\n");
        PRINT_BUFFER("%-20s : Rp. ","PPN (11%)"); printRupiahBuffer(ppn); PRINT_BUFFER("\n");
        PRINT_BUFFER("%-20s : Rp. ","Total Bayar"); printRupiahBuffer(totalBayar); PRINT_BUFFER("\n");
        PRINT_BUFFER("============================================================\n");

        // Input metode bayar (ulangi sampai 1 atau 2)
        int metode = 0;
        while(metode!=1 && metode!=2){
            printf("Pilih metode bayar [1. Tunai | 2. Transfer/E-Wallet]: ");
            metode = bacaInt();
        }

        int statusLunas = 0;
        long totalBulat = (long)(totalBayar + 0.5);

        if(metode==1){
            // ---- Tunai ----
            strcpy(bk.metode,"Tunai");
            long uangBayar;

            // Input uang bayar (ulangi sampai cukup)
            while(1){
                uangBayar = inputTunai();
                if(uangBayar < totalBulat){
                    printf("Pembayaran kurang! Silakan ulangi.\n");
                } else break;
            }
            PRINT_BUFFER("%-20s : %s\n","Metode Bayar","Tunai");
            PRINT_BUFFER("%-20s : Rp. ","Uang Bayar"); printRupiahBuffer(uangBayar); PRINT_BUFFER("\n");
            if(uangBayar == totalBulat){
                PRINT_BUFFER("%-20s : %s\n","Keterangan","Uang pas");
            } else {
                PRINT_BUFFER("%-20s : Rp. ","Kembalian"); printRupiahBuffer(uangBayar-totalBulat); PRINT_BUFFER("\n");
            }
            PRINT_BUFFER("%-20s : %s\n","Status","LUNAS");
            statusLunas = 1;
        } else {
            // ---- Transfer / E-Wallet ----
            // Input pilihan (ulangi sampai 1 sampai 4)
            int pilihan = 0;
            while(pilihan<1 || pilihan>4){
                printf("Pilih [1. Transfer Bank | 2. OVO | 3. GoPay | 4. Dana]: ");
                pilihan = bacaInt();
            }
            const char *namaMetode;
            switch(pilihan){
                case 1: namaMetode="Transfer Bank"; break;
                case 2: namaMetode="OVO"; break;
                case 3: namaMetode="GoPay"; break;
                default: namaMetode="Dana"; break;
            }
            strcpy(bk.metode,namaMetode);

            // Buat RefID pembayaran
            char refID[40];
            sprintf(refID,"PAY%s%03d-%03d",bufferDate,nomorBooking,rand()%1000);

            PRINT_BUFFER("%-20s : %s\n","Metode Bayar",namaMetode);
            PRINT_BUFFER("%-20s : %s\n","RefID Pembayaran",refID);
            PRINT_BUFFER("%-20s : Rp. ","Dibayar"); printRupiahBuffer(totalBayar); PRINT_BUFFER("\n");
            PRINT_BUFFER("%-20s : %s\n","Status","LUNAS");
            statusLunas = 1;
        }
        PRINT_BUFFER("============================================================\n");

        // ==================== 5. SIMPAN BOOKING ====================
        // Simpan pesanan, ubah status unit menjadi sudah dibooking
        if(statusLunas){
            daftarKendaraan[idxKendaraan].tersedia = 0;
            if(jumlahBooking < MAX) dataBooking[jumlahBooking++] = bk;
        }

        // Cetak bukti booking
        printCenter("Terima kasih telah menyewa kendaraan kami!",60);
        printCenter("Harap bawa KTP asli saat pengambilan unit",60);
        PRINT_BUFFER("============================================================\n");

        // Buat nama file bukti lalu buka file
        if(statusLunas){
            char namaFile[40];
            sprintf(namaFile,"BUKTI%03d.txt",nomorBooking);

            FILE *f = fopen(namaFile,"w");
            if(f){
                // File berhasil dibuka: simpan bukti, tampilkan pesan, update counter
                fprintf(f,"%s", bufferBukti);
                fclose(f);
                printf("Bukti booking berhasil disimpan di '%s'\n", namaFile);

                fcounter = fopen("counter_booking.txt","w");
                if(fcounter){
                    fprintf(fcounter,"%d", nomorBooking+1);
                    fclose(fcounter);
                }
            } else {
                // File gagal dibuka
                printf("Gagal membuat file bukti booking!\n");
            }
        }

        // Booking lagi? (y = kembali ke reset bufferBukti, n = selesai)
        char jawab[10];
        printf("\nApakah ingin melakukan booking lain? (y/n): ");
        bacaTeks(jawab, sizeof(jawab));
        lanjutBooking = (jawab[0]=='y' || jawab[0]=='Y');

    } while(lanjutBooking);

    printf("Program booking rental selesai. Terima kasih!\n");
    return 0;
}