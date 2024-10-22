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

// Implementasi Fibonacci Search untuk stok helm
int min(int x, int y) { return (x <= y) ? x : y; }

int fibonacciSearch(Helm* head, int stokCari) {
    if (!head) return -1;

    int n = 0;
    Helm* temp = head;
    while (temp) {
        n++;
        temp = temp->next;
    }

    int fibMm2 = 0;
    int fibMm1 = 1;
    int fibM = fibMm2 + fibMm1;

    while (fibM < n) {
        fibMm2 = fibMm1;
        fibMm1 = fibM;
        fibM = fibMm2 + fibMm1;
    }

    int offset = -1;
    Helm* current = head;

    while (fibM > 1) {
        int i = min(offset + fibMm2, n - 1);
        temp = head;
        for (int j = 0; j < i; ++j) {
            temp = temp->next;
        }

        if (temp->stok < stokCari) {
            fibM = fibMm1;
            fibMm1 = fibMm2;
            fibMm2 = fibM - fibMm1;
            offset = i;
        } else if (temp->stok > stokCari) {
            fibM = fibMm2;
            fibMm1 = fibMm1 - fibMm2;
            fibMm2 = fibM - fibMm1;
        } else {
            return i;
        }
    }

    temp = head;
    for (int j = 0; j < offset + 1; ++j) {
        temp = temp->next;
    }

    if (fibMm1 && temp->stok == stokCari) {
        return offset + 1;
    }

    return -1;
}

// Implementasi Jump Search untuk harga helm
int jumpSearch(Helm* head, float hargaCari) {
    if (!head) return -1;

    int n = 0;
    Helm* temp = head;

    while (temp) {
        n++;
        temp = temp->next;
    }

    int step = sqrt(n);
    int prev = 0;

    temp = head;
    Helm* blockStart = temp;
    while (temp && temp->harga < hargaCari) {
        prev = step;
        for (int i = 0; i < step && temp; ++i) {
            temp = temp->next;
        }
        if (prev >= n) {
            return -1;
        }
    }

    for (int i = prev; i < n && blockStart && blockStart->harga <= hargaCari; ++i) {
        if (blockStart->harga == hargaCari) {
            return i;
        }
        blockStart = blockStart->next;
    }

    return -1;
}

// Implementasi Boyer-Moore untuk pencarian nama helm
#define NO_OF_CHARS 256

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    int i;
    for (i = 0; i < NO_OF_CHARS; i++) badchar[i] = -1;
    for (i = 0; i < size; i++) badchar[(int)str[i]] = i;
}

int boyerMooreSearch(Helm* head, string pattern) {
    if (!head) return -1;

    int m = pattern.size();
    int badchar[NO_OF_CHARS];

    badCharHeuristic(pattern, m, badchar);

    Helm* temp = head;
    int pos = 0;

    while (temp) {
        string nama = temp->nama;
        int n = nama.size();
        int s = 0;

        while (s <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && pattern[j] == nama[s + j]) j--;

            if (j < 0) {
                return pos;
                s += (s + m < n) ? m - badchar[nama[s + m]] : 1;
            } else {
                s += max(1, j - badchar[nama[s + j]]);
            }
        }
        temp = temp->next;
        pos++;
    }

    return -1;
}

// Menu searching
void searchingMenu() {
    int choice, stokCari, hasilInt;
    float hargaCari;
    string patternCari;
    
    cout << "\n=== Searching Menu ===" << endl;
    cout << "1. Fibonacci Search Stok Helm" << endl;
    cout << "2. Jump Search Harga Helm" << endl;
    cout << "3. Boyer-Moore Search Nama Helm" << endl;
    cout << "Pilih metode searching: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Masukkan stok helm yang dicari: ";
            cin >> stokCari;
            hasilInt = fibonacciSearch(head, stokCari);
            if (hasilInt != -1) {
                cout << "Stok helm ditemukan pada posisi ke-" << hasilInt + 1 << endl;
            } else {
                cout << "Stok helm tidak ditemukan." << endl;
            }
            break;
        case 2:
            cout << "Masukkan harga helm yang dicari: ";
            cin >> hargaCari;
            hasilInt = jumpSearch(head, hargaCari);
            if (hasilInt != -1) {
                cout << "Harga helm ditemukan pada posisi ke-" << hasilInt + 1 << endl;
            } else {
                cout << "Harga helm tidak ditemukan." << endl;
            }
            break;
        case 3:
            cout << "Masukkan nama helm yang dicari: ";
            cin.ignore();
            getline(cin, patternCari);
            hasilInt = boyerMooreSearch(head, patternCari);
            if (hasilInt != -1) {
                cout << "Nama helm ditemukan pada posisi ke-" << hasilInt + 1 << endl;
            } else {
                cout << "Nama helm tidak ditemukan." << endl;
            }
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
    }
}

// Menu sorting
void sortingMenu() {
    int choice;
    cout << "\n=== Sorting Menu ===" << endl;
    cout << "1. Ascending berdasarkan Nama Helm" << endl;
    cout << "2. Descending berdasarkan Nama Helm" << endl;
    cout << "3. Ascending berdasarkan Harga Helm" << endl;
    cout << "4. Descending berdasarkan Harga Helm" << endl;
    cout << "Pilih metode sorting: ";
    cin >> choice;

    switch (choice) {
        case 1:
            quickSortAscName(&head);
            cout << "Data telah diurutkan berdasarkan Nama Helm (Ascending)." << endl;
            break;
        case 2:
            quickSortDescName(&head);
            cout << "Data telah diurutkan berdasarkan Nama Helm (Descending)." << endl;
            break;
        case 3:
            mergeSortAscPrice(&head);
            cout << "Data telah diurutkan berdasarkan Harga Helm (Ascending)." << endl;
            break;
        case 4:
            mergeSortDescPrice(&head);
            cout << "Data telah diurutkan berdasarkan Harga Helm (Descending)." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
    }
}

// Main menu
int main() {
    int pilihan;
    do {
        cout << "\n=== Selamat Datang di Toko Helm ===" << endl;
        cout << "1. Tampilkan List Helm" << endl;
        cout << "2. Tambah Helm Baru" << endl;
        cout << "3. Sorting Helm" << endl;
        cout << "4. Searching Helm" << endl;
        cout << "5. Keluar" << endl;
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
                searchingMenu();
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 5);

    return 0;
}
