#pragma once
#include <iostream>
#include <iostream>
using namespace std;
#include "module-history.h"
#include "GlobalVariables.h"
#include "module-validInput.h"
#include "module-queue.h"

// Terima Pembelian Tiket dan Beri Tiket
void terimaPembelianTiket () {
    if (isEmpty() == 0) {
        string namaPengunjung = q.isi[0];
        cout << "Tiket untuk customer " << namaPengunjung << " telah diproses." << endl;
        deleteQueue();
        updateTicketStatus(namaPengunjung, "belum dipakai");
    } else {
        cout << "Antrian kosong." << endl;
    }
}

// Tolak Pembelian Tiket
void tolakPembelianTiket () {
    if (isEmpty() == 0) {
        string namaPengunjung = q.isi[0];
        cout << "Tiket untuk customer " << namaPengunjung << " telah ditolak." << endl;
        deleteQueue();
        updateTicketStatus(namaPengunjung, "tidak ada");
    } else {
        cout << "Antrian kosong." << endl;
    }
}

// Kelola Antrian
void kelolaAntrian() {
    int choice;
    bool run = true;
    while(run) {
        // cout << "\033[2J\033[1;1H";
        clearScreen();
        cout << "\n Antrian di Locket:" << endl;
        displayQueue();
        cout << "1. Terima Pembelian Tiket dan Beri Tiket" << endl;
        cout << "2. Tolak Pembelian" << endl;
        cout << "3. Hapus Antrian" << endl;
        cout << "4. Kembali" << endl;
        
        cout << "Pilihan Anda: ";
        choice = inputValidInt();

        switch (choice) {
            case 1:
                terimaPembelianTiket();
                break;

            case 2:
                tolakPembelianTiket();
                return;

            case 3:
                createQueue();
                cout << "Antrian telah dihapus." << endl;
                return;

            case 4:
                cout << "Kembali ke halaman dashboard" << endl;
                run = false;
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

// dashboard petugas
void petugasDashboard() {
    int choice;
    while(true) {
        // cout << "\033[2J\033[1;1H";
        clearScreen();
        cout << "\n Dashboard Petugas" << endl;
        cout << "1. Kelola Antrian" << endl;
        cout << "2. Lihat histori pengunjung terakhir" << endl;
        cout << "3. Logout" << endl;
        
        cout << "Pilihan Anda: ";
        choice = inputValidInt();

        switch (choice) {
            case 1:
                kelolaAntrian();
                break;

            case 2:
                displayHistory();
                break;

            case 3:
                USER_FOUND = false;
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}
