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

void pengunjungDashboardActive(){
    while(true){
        // cout << "\033[2J\033[1;1H";
        clearScreen();
        int choice;
        cout << "\n=== Kebun Binatang MyZoo ===\n";
        cout << "[Temmpat saat ini: " << currentVisitorPlace->name << "]\n";
        
        if(currentVisitorPlace->isKandang){
            cout << currentVisitorPlace->desc << "\n";
        }

        cout << "1. Lihat Map\n";
        cout << "2. Pergi ke-\n";
        cout << "3. Logout\n";
        cout << "4. Keluar Zoo\n";

        cin >> choice;

        switch(choice){
            case 1:
                int nomorTempat;
                cout << "-- List Lokasi ---\n";
                cout << "0. Kembali\n";
                
                for(int i = 0; i < V; i++){
                    cout << i+1 << ": " << PLACES[i]->name << "\n";
                }

                while(true){
                    cout << "Silahkan pilih nomor lokasi: ";
                    nomorTempat = inputValidInt() - 1;
                    
                    if(nomorTempat == -1){
                        break;

                    } else if(nomorTempat < V){
                        dijkstra(graph, currentVisitorPlace, PLACES[nomorTempat]);
                        string konfirm;
                        cout << "Pergi ke-" << PLACES[nomorTempat]->name << "? (y untuk ya): ";
                        cin >> konfirm;

                        if(konfirm == "y" || konfirm == "Y"){
                            currentVisitorPlace = PLACES[nomorTempat];
                            break;
                        }

                    } else {
                        cout << "Pilihan tidak valid\n";
                    }
                }
                break;

            case 2:
                
                cout << "-- List Lokasi ---\n";
                cout << "0. Kembali\n";
                for(int i = 0; i < V; i++){
                    cout << i+1 << ": " << PLACES[i]->name << "\n";
                }
                while(true){
                    cout << "Silahkan pilih nomor lokasi: ";
                    nomorTempat = inputValidInt() - 1;
                    
                    if(nomorTempat == -1){
                        break;

                    } else if(nomorTempat < V){
                        cout << "<< Pergi ke" << PLACES[nomorTempat]->name << " >>\n";
                        currentVisitorPlace = PLACES[nomorTempat];
                        break;

                    } else {
                        cout << "Pilihan tidak valid\n";
                    }
                }
                break;

            case 3:
                USER_FOUND = false;
                return;

            case 4:
                USER_FOUND = false;
                userProfile[3] = "tidak ada";
                DATABASE_USER[currUserIndex][3] = "tidak ada";
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
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
        // cout << "\033[2J\033[1;1H";
        clearScreen();
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
