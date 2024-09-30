#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Helm { // impelemntasi node menggunakan struct pada helm
    string nama;
    int stok;
    float harga;
    Helm* next; // implementasi node *next berfungsi menyimpan data helm bertipe struck
};


Helm* head = nullptr; // implementasi node *head berfungsi menyimpan data helm pertama

void readHelm() { // implementasi traversal menampilkan helm
    if (head == nullptr) {
        cout << "Tidak ada helm di toko." << endl;
        return;
    }
    
    Helm* temp = head;
    int nomor = 1;
    cout << "List Helm di Toko:" << endl;
    while (temp != nullptr) {
        cout << nomor++ << ". " << temp->nama << " - Stok: " << temp->stok 
             << " - Harga: " << temp->harga << endl;
        temp = temp->next;
    }
}

int totalStok() { 
    int total = 0;
    Helm* temp = head;
    while (temp != nullptr) {
        total += temp->stok;
        temp = temp->next;
    }
    return total;
}

void createHelm() { // implementasi traversal menambah helm
    Helm* newHelm = new Helm();
    
    cout << "Masukkan nama helm baru: ";
    cin.ignore();
    getline(cin, newHelm->nama);
    cout << "Masukkan stok helm: ";
    cin >> newHelm->stok;
    cout << "Masukkan harga helm: "; // harga helm satuan 
    cin >> newHelm->harga;
    
    newHelm->next = nullptr;
    
    if (head == nullptr) {
        head = newHelm;
    } else {
        Helm* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newHelm;
    }
    
    cout << "Helm baru berhasil ditambahkan!" << endl;
}

void updateHelm() { // implementasi traversal mengubah helm
    int nomor;
    cout << "Masukkan nomor helm yang ingin diupdate: ";
    cin >> nomor;
    
    Helm* temp = head;
    for (int i = 1; i < nomor && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    if (temp != nullptr) {
        cout << "Masukkan nama helm baru: ";
        cin.ignore();
        getline(cin, temp->nama);
        cout << "Masukkan stok helm baru: ";
        cin >> temp->stok;
        cout << "Masukkan harga helm baru: ";
        cin >> temp->harga;
        cout << "Data helm berhasil diupdate!" << endl;
    } else {
        cout << "Nomor helm tidak valid!" << endl;
    }
}

void deleteHelm() { // implementasi traversal menghapus helm
    int nomor;
    cout << "Masukkan nomor helm yang ingin dihapus: ";
    cin >> nomor;
    
    if (head == nullptr) {
        cout << "List helm kosong!" << endl;
        return;
    }

    if (nomor == 1) {
        Helm* temp = head;
        head = head->next;
        delete temp;
        cout << "Helm berhasil dihapus!" << endl;
        return;
    }

    Helm* temp = head;
    Helm* prev = nullptr;
    for (int i = 1; i < nomor && temp != nullptr; i++) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp != nullptr) {
        prev->next = temp->next;
        delete temp;
        cout << "Helm berhasil dihapus!" << endl;
    } else {
        cout << "Nomor helm tidak valid!" << endl;
    }
}

string formatRupiah(float angka) { 
    stringstream ss;
    ss << fixed << setprecision(0) << angka; 
    string hasil = ss.str();

    int n = hasil.length() - 3;
    while (n > 0) {
        hasil.insert(n, ".");
        n -= 3;
    }
    return "Rp" + hasil;
}

void tampilkanTotalNilaiStok() { 
    float totalNilai = 0;
    Helm* temp = head;
    while (temp != nullptr) {
        totalNilai += temp->stok * temp->harga;
        temp = temp->next;
    }
    cout << "Total nilai semua stok helm: " << formatRupiah(totalNilai) << endl;
}

int main() { // Menu utama
    int pilihan;
    do {
        cout << "\n=== Selamat Datang di Toko Helm Sepit, Anda sebagai Admin ===" << endl;
        cout << "1. Tampilkan List Helm" << endl;
        cout << "2. Tambah Helm Baru" << endl;
        cout << "3. Update Helm" << endl;
        cout << "4. Hapus Helm" << endl;
        cout << "5. Tampilkan Total Stok Helm" << endl;
        cout << "6. Tampilkan Total Harga Keseluruhan Stok Helm" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                readHelm(); 
                break;
            case 2:
                createHelm(); 
                break;
            case 3:
                updateHelm(); 
                break;
            case 4:
                deleteHelm(); 
                break;
            case 5:
                cout << "Total stok helm: " << totalStok() << endl; 
                break;
            case 6:
                tampilkanTotalNilaiStok(); 
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 7);

    return 0;
}
