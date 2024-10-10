#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;

struct Helm { 
    string nama;
    int stok;
    float harga;
    Helm* next;
};

Helm* head = nullptr;

stack<Helm*> deletedHelmStack; // implementasi stack menyimpan data helm yang dihapus
queue<Helm*> helmQueue; // implementasi queue menampilkan proses helm baru

void readHelm() { 
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

    helmQueue.push(newHelm); // implementasi queue menambhakan helm ke antrian
    cout << "Helm baru berhasil ditambahkan!" << endl;
}

void updateHelm() { 
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
        deletedHelmStack.push(temp);  // impelemntasi stack memproses data helm yang dihapus
        cout << "Helm berhasil dihapus!" << endl;
        return;
    }

    for (int i = 1; i < nomor && temp != nullptr; i++) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp != nullptr) {
        prev->next = temp->next;
        deletedHelmStack.push(temp);  // implementasi stack memproses data helm yang dihapus
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
    
    Helm* restoredHelm = deletedHelmStack.top(); // implementasi stack mengembalikkan data helm
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

    cout << "Helm yang dihapus berhasil dikembalikan!" << endl; // implementasi stack output berhasil mengembalikkan data helm yang terhapus
}

void processQueueHelm() {
    if (helmQueue.empty()) { 
        cout << "Tidak ada helm baru yang menunggu." << endl;
        return;
    }

    cout << "Proses helm terbaru yang ditambahkan ke toko:" << endl;
    while (!helmQueue.empty()) {
        Helm* helm = helmQueue.front(); // implementasi queue memproses helm yang baru ditambhakan
        helmQueue.pop(); 
        cout << helm->nama << " berhasil diproses." << endl; // implementasi queue hasil output tampilan proses helm yang baru ditambahkan
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

int main() { 
    int pilihan;
    do {
        cout << "\n=== Selamat Datang di Toko Helm Sepit, Anda sebagai Admin ===" << endl;
        cout << "1. Tampilkan List Helm" << endl;
        cout << "2. Tambah Helm Baru" << endl;
        cout << "3. Update Helm" << endl;
        cout << "4. Hapus Helm" << endl;
        cout << "5. Tampilkan Total Stok Helm" << endl;
        cout << "6. Tampilkan Total Harga Keseluruhan Stok Helm" << endl;
        cout << "7. Undo Hapus Helm (Stack)" << endl;
        cout << "8. Proses Helm Baru (Queue)" << endl;
        cout << "9. Keluar" << endl;
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
                undoDeleteHelm(); 
                break;
            case 8:
                processQueueHelm(); 
                break;
            case 9:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 9);

    return 0;
}
