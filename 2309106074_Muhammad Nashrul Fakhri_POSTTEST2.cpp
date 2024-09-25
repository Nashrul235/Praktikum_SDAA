#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Helm { //implementasi struck data helm menggunakan string, integer dan float
    string nama;
    int stok;
    float harga;
};


Helm helmList[6] = { //implementasi array data helm menggunakan helmlist terdapat nama helm, stok dan harga
    {"KYT Kyoto R", 10, 500000.0},
    {"Cargoss", 8, 350000.0},
    {"R-Six", 15, 400000.0},
    {"Zeus", 12, 550000.0},
    {"Nhk", 20, 600000.0},
    {"Jitsu", 7, 450000.0}
};


int jumlahHelm = 6; //implementasi array total jumlah helm


void readHelm(Helm *helmList, int jumlahHelm) { //implementasi prosedur membaca helm
    cout << "List Helm di Toko:" << endl;
    for (int i = 0; i < jumlahHelm; i++) {
        cout << i + 1 << ". " << helmList[i].nama << " - Stok: " << helmList[i].stok 
             << " - Harga: " << helmList[i].harga << endl;
    }
}


int totalStok(Helm *helmList, int jumlahHelm) { //implementasi fungsi menghitung total stock helm
    int total = 0;
    for (int i = 0; i < jumlahHelm; i++) {
        total += helmList[i].stok;
    }
    return total;
}


void createHelm(Helm *helmList, int &jumlahHelm) { // implementasi Prosedur menambah helm 
    cout << "Masukkan nama helm baru: ";
    cin.ignore();
    getline(cin, helmList[jumlahHelm].nama);
    cout << "Masukkan stok helm: ";
    cin >> helmList[jumlahHelm].stok;
    cout << "Masukkan harga helm: ";
    cin >> helmList[jumlahHelm].harga;
    jumlahHelm++;
    cout << "Helm baru berhasil ditambahkan!" << endl;
}


void updateHelm(Helm *helmList, int jumlahHelm) { // implementasi prosedur mengubah helm
    int nomor;
    cout << "Masukkan nomor helm yang ingin diupdate: ";
    cin >> nomor;
    if (nomor > 0 && nomor <= jumlahHelm) {
        cout << "Masukkan nama helm baru: ";
        cin.ignore();
        getline(cin, helmList[nomor - 1].nama);
        cout << "Masukkan stok helm baru: ";
        cin >> helmList[nomor - 1].stok;
        cout << "Masukkan harga helm baru: ";
        cin >> helmList[nomor - 1].harga;
        cout << "Data helm berhasil diupdate!" << endl;
    } else {
        cout << "Nomor helm tidak valid!" << endl;
    }
}


void deleteHelm(Helm *helmList, int &jumlahHelm) { // implementasi Prosedur menghapus helm
    int nomor;
    cout << "Masukkan nomor helm yang ingin dihapus: ";
    cin >> nomor;
    if (nomor > 0 && nomor <= jumlahHelm) {
        for (int i = nomor - 1; i < jumlahHelm - 1; i++) {
            helmList[i] = helmList[i + 1];
        }
        jumlahHelm--;
        cout << "Helm berhasil dihapus!" << endl;
    } else {
        cout << "Nomor helm tidak valid!" << endl;
    }
}


string formatRupiah(float angka) { // implementasi Fungsi untuk memformat angka menjadi format mata uang (berfungsi output integer memiliki bilangan banyak tidak eror)
    stringstream ss;
    ss << fixed << setprecision(0) << angka; 
    string hasil = ss.str();

    // Menambahkan pemisah ribuan
    int n = hasil.length() - 3;
    while (n > 0) {
        hasil.insert(n, ".");
        n -= 3;
    }
    return "Rp" + hasil;
}


void tampilkanTotalNilaiStok(Helm *helmList, int jumlahHelm) { // implenetasi Prosedur untuk menampilkan harga keseluruhan helm
    float totalNilai = 0;
    for (int i = 0; i < jumlahHelm; i++) {
        totalNilai += helmList[i].stok * helmList[i].harga;
    }
    cout << "Total nilai semua stok helm: " << formatRupiah(totalNilai) << endl;
}

int main() { // implementasi struck menu utama toko helm
    int pilihan;
    do {
        cout << "\n=== Selamat Datang di Toko Helm Sepit, Anda sebagai Admin ===" << endl;
        cout << "1. Tampilkan List Helm" << endl;
        cout << "2. Tambah Helm Baru" << endl;
        cout << "3. Update Helm" << endl;
        cout << "4. Hapus Helm" << endl;
        cout << "5. Tampilkan Total Stok Helm" << endl;
        cout << "6. Tampilkan Total Nilai Semua Stok Helm" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                readHelm(helmList, jumlahHelm); // implementasi fungsi array membaca helm
                break;
            case 2:
                createHelm(helmList, jumlahHelm); // implementasi fungsi array menambah helm
                break;
            case 3:
                updateHelm(helmList, jumlahHelm); // implementasi fungsi array mengubah helm
                break;
            case 4:
                deleteHelm(helmList, jumlahHelm); // implementasi fungsi arrau menghapus helm
                break;
            case 5:
                cout << "Total stok helm: " << totalStok(helmList, jumlahHelm) << endl; // implementasi fungsi array menampilkan stok helm
                break;
            case 6:
                tampilkanTotalNilaiStok(helmList, jumlahHelm); // implementasi fungsi array menampilkan jumlah harga keseluruhan
                break;
            case 7:
                cout << "Keluar dari program." << endl; // implementasi fungsi array keluar
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 8);

    return 0;
}
