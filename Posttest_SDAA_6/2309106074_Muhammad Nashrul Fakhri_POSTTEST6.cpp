#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stack>
#include <queue>
#include <cmath>

using namespace std;

struct Helm {
    string nama;
    int stok;
    float harga;
    Helm* next;
};

// Deklarasi fungsi
void readHelm();
int totalStok();
void tampilkanTotalNilaiStok();
void createHelm();
void updateHelm();
void deleteHelm();
void undoDeleteHelm();
void processQueueHelm();
string formatRupiah(float angka);

// Fungsi sorting dan searching
void sortHelmByNameAsc();
void sortHelmByNameDesc();
void sortHelmByPriceAsc();
void sortHelmByPriceDesc();
int fibonacciSearch(int stokCari);
int jumpSearch(float hargaCari);
int boyerMooreSearch(const string& text, const string& pattern);

// Deklarasi menu sorting dan searching
void menuSorting();
void menuSearching();

// Deklarasi fungsi tambahan
Helm* findHelmByPosition(int posisi);

// Linked list untuk helm
Helm* head = nullptr;
stack<Helm*> deletedHelmStack; // Stack untuk menyimpan helm yang dihapus
queue<Helm*> helmQueue; // Queue untuk menampilkan proses helm baru

Helm* findHelmByPosition(int posisi) {
    Helm* temp = head;
    int counter = 1;
    while (temp != nullptr && counter < posisi) {
        temp = temp->next;
        counter++;
    }
    return temp; // Mengembalikan helm pada posisi yang diinginkan
}

void readHelm() {
    int pilihan;
    cout << "\nMenu Tampilkan Helm:\n";
    cout << "1. Tampilkan List Helm\n";
    cout << "2. Tampilkan Total Stok Helm\n";
    cout << "3. Tampilkan Total Harga Keseluruhan Helm\n";
    cout << "Pilih menu: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1: {
            if (head == nullptr) {
                cout << "Tidak ada helm di toko." << endl;
                return;
            }
            Helm* temp = head;
            int nomor = 1;
            cout << "List Helm di Toko:" << endl;
            while (temp != nullptr) {
                cout << nomor++ << ". " << temp->nama << " - Stok: " << temp->stok
                     << " - Harga: " << formatRupiah(temp->harga) << endl;
                temp = temp->next;
            }
            break;
        }
        case 2: {
            int total = totalStok();
            cout << "Total Stok Semua Helm: " << total << endl;
            break;
        }
        case 3: {
            tampilkanTotalNilaiStok();
            break;
        }
        default:
            cout << "Pilihan tidak valid!" << endl;
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

void createHelm() {
    Helm* newHelm = new Helm();

    cout << "Masukkan nama helm baru: ";
    cin.ignore();  // ignore newline character left in the buffer
    getline(cin, newHelm->nama);
    cout << "Masukkan stok helm: ";
    cin >> newHelm->stok;
    cout << "Masukkan harga helm: ";
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

    helmQueue.push(newHelm); // Menambahkan helm ke antrian
    cout << "Helm baru berhasil ditambahkan!" << endl;
}

void updateHelm() {
    int nomor;
    cout << "Masukkan nomor helm yang ingin diupdate: ";
    cin >> nomor;

    Helm* temp = findHelmByPosition(nomor);
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

void deleteHelm() {
    int nomor;
    cout << "Masukkan nomor helm yang ingin dihapus: ";
    cin >> nomor;

    if (head == nullptr) {
        cout << "List helm kosong!" << endl;
        return;
    }

    Helm* temp = head;
    Helm* prev = nullptr;

    if (nomor == 1) {
        head = head->next;
        deletedHelmStack.push(temp);  // Menyimpan helm yang dihapus ke stack
        cout << "Helm berhasil dihapus!" << endl;
        return;
    }

    for (int i = 1; i < nomor && temp != nullptr; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != nullptr) {
        prev->next = temp->next;
        deletedHelmStack.push(temp);  // Menyimpan helm yang dihapus ke stack
        cout << "Helm berhasil dihapus!" << endl;
    } else {
        cout << "Nomor helm tidak valid!" << endl;
    }
}

void undoDeleteHelm() {
    if (deletedHelmStack.empty()) {
        cout << "Tidak ada helm yang bisa di-undo." << endl;
        return;
    }

    Helm* restoredHelm = deletedHelmStack.top(); // Mengembalikan helm yang dihapus dari stack
    deletedHelmStack.pop();

    restoredHelm->next = nullptr;
    if (head == nullptr) {
        head = restoredHelm;
    } else {
        Helm* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = restoredHelm;
    }

    cout << "Helm yang dihapus berhasil dikembalikan!" << endl;
}

void processQueueHelm() {
    if (helmQueue.empty()) {
        cout << "Tidak ada helm baru yang menunggu." << endl;
        return;
    }

    cout << "Proses helm terbaru yang ditambahkan ke toko:" << endl;
    while (!helmQueue.empty()) {
        Helm* helm = helmQueue.front(); // Memproses helm yang baru ditambahkan
        helmQueue.pop();
        cout << helm->nama << " berhasil diproses." << endl;
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

// Fungsi sorting dan searching
void sortHelmByNameAsc() {
    // Implementasi Sorting Ascending Nama
}

void sortHelmByNameDesc() {
    // Implementasi Sorting Descending Nama
}

void sortHelmByPriceAsc() {
    // Implementasi Sorting Ascending Harga
}

void sortHelmByPriceDesc() {
    // Implementasi Sorting Descending Harga
}

// Fibonacci Search untuk stok
int fibonacciSearch(int stokCari) {
    Helm* temp = head;
    int index = 0;
    
    while (temp != nullptr) {
        if (temp->stok == stokCari) {
            return index + 1;  // Mengembalikan posisi helm (berbasis 1)
        }
        temp = temp->next;
        index++;
    }
    return -1; // Jika tidak ditemukan
}

// Jump Search untuk harga
int jumpSearch(float hargaCari) {
    sortHelmByPriceAsc(); // Mengurutkan helm berdasarkan harga

    int step = sqrt(totalStok()); // Menghitung jarak lompatan
    int prev = 0;
    Helm* temp = head;
    Helm* jump = head;
    
    while (jump != nullptr && jump->harga < hargaCari) {
        for (int i = 0; i < step && jump != nullptr; i++) {
            prev++;
            temp = jump;
            jump = jump->next;
        }
    }

    // Linear Search dalam blok
    while (temp != nullptr && temp->harga <= hargaCari) {
        if (temp->harga == hargaCari) {
            return prev;  // Mengembalikan posisi helm (berbasis 1)
        }
        temp = temp->next;
        prev++;
    }
    
    return -1; // Jika tidak ditemukan
}

// Boyer-Moore Search untuk nama
int boyerMooreSearch(const string& text, const string& pattern) {
    Helm* temp = head;
    int index = 0;

    while (temp != nullptr) {
        if (temp->nama.find(pattern) != string::npos) {
            return index + 1;  // Mengembalikan posisi helm (berbasis 1)
        }
        temp = temp->next;
        index++;
    }
    return -1; // Jika tidak ditemukan
}

void menuSorting() {
    int pilihan;
    cout << "\nMenu Sorting Helm:\n";
    cout << "1. Sortir berdasarkan Nama (Ascending)\n";
    cout << "2. Sortir berdasarkan Nama (Descending)\n";
    cout << "3. Sortir berdasarkan Harga (Ascending)\n";
    cout << "4. Sortir berdasarkan Harga (Descending)\n";
    cout << "Pilih menu: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            sortHelmByNameAsc();
            cout << "Helm berhasil diurutkan berdasarkan nama (Ascending)." << endl;
            break;
        case 2:
            sortHelmByNameDesc();
            cout << "Helm berhasil diurutkan berdasarkan nama (Descending)." << endl;
            break;
        case 3:
            sortHelmByPriceAsc();
            cout << "Helm berhasil diurutkan berdasarkan harga (Ascending)." << endl;
            break;
        case 4:
            sortHelmByPriceDesc();
            cout << "Helm berhasil diurutkan berdasarkan harga (Descending)." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
    }
}

void menuSearching() {
    int pilihan;
    cout << "\nMenu Searching Helm:\n";
    cout << "1. Cari berdasarkan Stok (Fibonacci Search)\n";
    cout << "2. Cari berdasarkan Harga (Jump Search)\n";
    cout << "3. Cari berdasarkan Nama (Boyer-Moore Search)\n";
    cout << "Pilih menu: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1: {
            int stokCari;
            cout << "Masukkan stok yang ingin dicari: ";
            cin >> stokCari;
            int hasil = fibonacciSearch(stokCari);
            if (hasil != -1) {
                cout << "Helm ditemukan pada posisi: " << hasil << endl;
            } else {
                cout << "Helm tidak ditemukan!" << endl;
            }
            break;
        }
        case 2: {
            float hargaCari;
            cout << "Masukkan harga yang ingin dicari: ";
            cin >> hargaCari;
            int hasil = jumpSearch(hargaCari);
            if (hasil != -1) {
                cout << "Helm ditemukan pada posisi: " << hasil << endl;
            } else {
                cout << "Helm tidak ditemukan!" << endl;
            }
            break;
        }
        case 3: {
            string namaCari;
            cout << "Masukkan nama helm yang ingin dicari: ";
            cin.ignore();
            getline(cin, namaCari);
            int hasil = boyerMooreSearch(namaCari, namaCari);
            if (hasil != -1) {
                cout << "Helm ditemukan pada posisi: " << hasil << endl;
            } else {
                cout << "Helm tidak ditemukan!" << endl;
            }
            break;
        }
        default:
            cout << "Pilihan tidak valid!" << endl;
    }
}

int main() {
    int pilihan;
    do {
        cout << "\nMenu Toko Helm:\n";
        cout << "1. Tampilkan Helm\n";
        cout << "2. Tambah Helm\n";
        cout << "3. Update Helm\n";
        cout << "4. Hapus Helm\n";
        cout << "5. Undo Penghapusan Helm\n";
        cout << "6. Proses Helm Baru\n";
        cout << "7. Menu Sorting\n";
        cout << "8. Menu Searching\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
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
                undoDeleteHelm();
                break;
            case 6:
                processQueueHelm();
                break;
            case 7:
                menuSorting();
                break;
            case 8:
                menuSearching();
                break;
            case 0:
                cout << "Terima kasih! Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);

    return 0;
}
