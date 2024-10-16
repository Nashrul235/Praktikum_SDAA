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

// Fungsi untuk membagi linked list menjadi dua
void split(Helm* source, Helm** frontRef, Helm** backRef) {
    Helm* fast;
    Helm* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

// Merge dua list terurut (ascending harga)
Helm* sortedMergeAscPrice(Helm* a, Helm* b) {
    Helm* result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (a->harga <= b->harga) {
        result = a;
        result->next = sortedMergeAscPrice(a->next, b);
    } else {
        result = b;
        result->next = sortedMergeAscPrice(a, b->next);
    }
    return result;
}

// Merge dua list terurut (descending harga)
Helm* sortedMergeDescPrice(Helm* a, Helm* b) {
    Helm* result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (a->harga >= b->harga) {
        result = a;
        result->next = sortedMergeDescPrice(a->next, b);
    } else {
        result = b;
        result->next = sortedMergeDescPrice(a, b->next);
    }
    return result;
}

// Fungsi untuk Merge Sort (ascending harga)
void mergeSortAscPrice(Helm** headRef) {
    Helm* head = *headRef;
    Helm* a;
    Helm* b;

    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    split(head, &a, &b);

    mergeSortAscPrice(&a);
    mergeSortAscPrice(&b);

    *headRef = sortedMergeAscPrice(a, b);
}

// Fungsi untuk Merge Sort (descending harga)
void mergeSortDescPrice(Helm** headRef) {
    Helm* head = *headRef;
    Helm* a;
    Helm* b;

    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    split(head, &a, &b);

    mergeSortDescPrice(&a);
    mergeSortDescPrice(&b);

    *headRef = sortedMergeDescPrice(a, b);
}

// Fungsi untuk mendapatkan elemen tail (akhir) dari linked list
Helm* getTail(Helm* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

// Partition untuk Quick Sort berdasarkan nama helm (ascending)
Helm* partitionAscName(Helm* head, Helm* end, Helm** newHead, Helm** newEnd) {
    Helm* pivot = end;
    Helm* prev = nullptr;
    Helm* cur = head;
    Helm* tail = pivot;

    while (cur != pivot) {
        if (cur->nama.compare(pivot->nama) < 0) {  // Urutkan dari A-Z
            if (*newHead == nullptr) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Helm* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (*newHead == nullptr) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

// Partition untuk Quick Sort berdasarkan nama helm (descending)
Helm* partitionDescName(Helm* head, Helm* end, Helm** newHead, Helm** newEnd) {
    Helm* pivot = end;
    Helm* prev = nullptr;
    Helm* cur = head;
    Helm* tail = pivot;

    while (cur != pivot) {
        if (cur->nama.compare(pivot->nama) > 0) {  // Urutkan dari Z-A
            if (*newHead == nullptr) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Helm* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (*newHead == nullptr) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

// Rekursif Quick Sort untuk nama helm (ascending)
Helm* quickSortRecurAscName(Helm* head, Helm* end) {
    if (!head || head == end) return head;

    Helm* newHead = nullptr;
    Helm* newEnd = nullptr;
    Helm* pivot = partitionAscName(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Helm* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;
        newHead = quickSortRecurAscName(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecurAscName(pivot->next, newEnd);
    return newHead;
}

// Rekursif Quick Sort untuk nama helm (descending)
Helm* quickSortRecurDescName(Helm* head, Helm* end) {
    if (!head || head == end) return head;

    Helm* newHead = nullptr;
    Helm* newEnd = nullptr;
    Helm* pivot = partitionDescName(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Helm* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;
        newHead = quickSortRecurDescName(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecurDescName(pivot->next, newEnd);
    return newHead;
}

// Quick Sort wrapper untuk nama helm (ascending)
void quickSortAscName(Helm** headRef) {
    (*headRef) = quickSortRecurAscName(*headRef, getTail(*headRef));
}

// Quick Sort wrapper untuk nama helm (descending)
void quickSortDescName(Helm** headRef) {
    (*headRef) = quickSortRecurDescName(*headRef, getTail(*headRef));
}

// Fungsi untuk menambahkan helm baru
void tambahHelm() {
    string nama;
    int stok;
    float harga;
    
    cout << "Masukkan nama helm: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan stok helm: ";
    cin >> stok;
    cout << "Masukkan harga helm: ";
    cin >> harga;

    Helm* newHelm = new Helm();
    newHelm->nama = nama;
    newHelm->stok = stok;
    newHelm->harga = harga;
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

// Fungsi untuk menampilkan semua helm
void tampilHelm() {
    if (head == nullptr) {
        cout << "List helm kosong!" << endl;
        return;
    }

    Helm* temp = head;
    cout << left << setw(20) << "Nama Helm" << setw(10) << "Stok" << setw(10) << "Harga" << endl;
    while (temp != nullptr) {
        cout << left << setw(20) << temp->nama << setw(10) << temp->stok << setw(10) << temp->harga << endl;
        temp = temp->next;
    }
}

// Menu sorting
void sortingMenu() {
    int choice;
    cout << "\n=== Sorting Menu ===" << endl;
    cout << "1. Merge Sort Harga (Ascending)" << endl;
    cout << "2. Merge Sort Harga (Descending)" << endl;
    cout << "3. Quick Sort Nama Helm (A-Z)" << endl;
    cout << "4. Quick Sort Nama Helm (Z-A)" << endl;
    cout << "Pilih metode sorting: ";
    cin >> choice;

    switch (choice) {
        case 1:
            mergeSortAscPrice(&head);
            cout << "List helm telah diurutkan dengan Merge Sort (Harga Ascending)." << endl;
            break;
        case 2:
            mergeSortDescPrice(&head);
            cout << "List helm telah diurutkan dengan Merge Sort (Harga Descending)." << endl;
            break;
        case 3:
            quickSortAscName(&head);
            cout << "List helm telah diurutkan dengan Quick Sort (Nama A-Z)." << endl;
            break;
        case 4:
            quickSortDescName(&head);
            cout << "List helm telah diurutkan dengan Quick Sort (Nama Z-A)." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n=== Selamat Datang di Toko Helm ===" << endl;
        cout << "1. Tampilkan List Helm" << endl;
        cout << "2. Tambah Helm Baru" << endl;
        cout << "3. Sorting Helm" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilHelm();
                break;
            case 2:
                tambahHelm();
                break;
            case 3:
                sortingMenu();
                break;
            case 4:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 4);

    return 0;
}
