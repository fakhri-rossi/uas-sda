#pragma once
#include <iostream>
#include <iostream>
using namespace std;
#include "module-history.h"
#include "GlobalVariables.h"
#include "module-validInput.h"
#include "module-queue.h"
#include "module-userGate.h"
#include "moduleGraph.h"

// beli tiket
void buyTicket (string username) {
    for (int i = 0; i < jumlahUser; i++) {
        if (DATABASE_USER[i][0] == username) {
            if (DATABASE_USER[i][3] == "menunggu diacc") {
                cout << "Anda sedang dalam antrian. Tidak dapat membeli tiket lagi." << endl;
                return;
            } 
            if (DATABASE_USER[i][3] == "belum dipakai") {
                cout << "Anda sudah memiliki tiket yang masih berlaku. Tidak dapat membeli tiket lagi." << endl;
                return;
            }
        }
    }
    insertQueue(username);
    updateTicketStatus(username, "menunggu diacc");
}

// gunakan tiket
void useTicket(string username) {
    for (int i = 0; i < jumlahUser; i++) {
        if (DATABASE_USER[i][0] == username) {
            if (DATABASE_USER[i][3] == "belum dipakai") {
                DATABASE_USER[i][3] = "aktif";
                currentVisitorPlace = gerbang;
                cout << "Tiket Anda sekarang aktif." << endl;
                pushHistory(userProfile[0]);
                pengunjungDashboardActive();

            } else if (DATABASE_USER[i][3] == "aktif") {
                cout << "Tiket Anda sudah aktif." << endl;

            } else {
                cout << "Anda tidak memiliki tiket yang belum dipakai." << endl;

            }
            return;
        }
    }
}

// dashboard pengunjung
void pengunjungDashboard() {
    int choice;
    while(true) {
        for (int i = 0; i < jumlahUser; i++) {
            if (DATABASE_USER[i][0] == userProfile[0]) {
            cout << "\n Dashboard Pengunjung" << endl;
            cout << "\nSelamat datang di MyZoo \nHTM: Rp40.000" << endl;
            cout << "1. Beli Tiket Masuk" << endl;
            cout << "2. Gunakan Tiket Masuk (" << DATABASE_USER[i][3] << ")" << endl;
            cout << "3. Logout" << endl;
            }
        }

        cout << "Pilihan Anda: ";
        choice = inputValidInt();

        switch (choice) {
            case 1:
                buyTicket(userProfile[0]);
                break;

            case 2:
                useTicket(userProfile[0]);
                return;

            case 3:
                USER_FOUND = false;
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    
}
