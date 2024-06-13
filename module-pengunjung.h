#pragma once
#include <iostream>
#include <conio.h>
using namespace std;
#include "module-history.h"
#include "GlobalVariables.h"
#include "module-validInput.h"
#include "module-queue.h"
#include "module-userGate.h"
#include "moduleGraph.h"

void goTo(Place *newPlace){
    PROFILES[currUserIndex]->currentVisitorPlace = newPlace;
    addPlace(PROFILES[currUserIndex]->historyPlace, newPlace);
}

// beli tiket
void buyTicket (string username) {
    // for (int i = 0; i < jumlahUser; i++) {
    //     if (DATABASE_USER[i][0] == username) {
    //         if (DATABASE_USER[i][3] == "menunggu diacc") {
    //             cout << "Anda sedang dalam antrian. Tidak dapat membeli tiket lagi." << endl;
    //             return;
    //         } 
    //         if (DATABASE_USER[i][3] == "belum dipakai") {
    //             cout << "Anda sudah memiliki tiket yang masih berlaku. Tidak dapat membeli tiket lagi." << endl;
    //             return;
    //         }
    //     }
    // }
    insertQueue(username);
    updateTicketStatus(username, "menunggu diacc");
}

void pengunjungDashboardActive(){
    while(true){
        clearScreen();
        int choice;
        cout << "\n=== Kebun Binatang MyZoo ===\n";
        cout << "[Tempat saat ini: " << PROFILES[currUserIndex]->currentVisitorPlace->name << "]\n";
        
        if(PROFILES[currUserIndex]->currentVisitorPlace->isKandang){
            cout << PROFILES[currUserIndex]->currentVisitorPlace->desc << "\n";
        }

        cout << "1. Lihat Map\n";
        cout << "2. Pergi ke-\n";
        cout << "3. Lihat tempat yang sudah dikunjungi\n";
        cout << "4. Logout\n";
        cout << "5. Keluar Zoo\n";

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
                        dijkstra(graph, PROFILES[currUserIndex]->currentVisitorPlace, PLACES[nomorTempat]);
                        string konfirm;
                        cout << "Pergi ke-" << PLACES[nomorTempat]->name << "? (y untuk ya): ";
                        cin >> konfirm;

                        if(konfirm == "y" || konfirm == "Y"){
                            goTo(PLACES[nomorTempat]);
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
                        goTo(PLACES[nomorTempat]);
                        break;

                    } else {
                        cout << "Pilihan tidak valid\n";
                    }
                }
                break;
            
            case 3:
                printHistory(PROFILES[currUserIndex]->historyPlace);
                break;

            case 4:
                USER_FOUND = false;
                return;

            case 5:
                USER_FOUND = false;
                userProfile[3] = "tidak ada";
                DATABASE_USER[currUserIndex][3] = "tidak ada";
                clearHistorylace(PROFILES[currUserIndex]->historyPlace);
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
                PROFILES[currUserIndex]->currentVisitorPlace = gerbang;
                cout << "<< Tiket Anda sekarang aktif >>" << endl;
                pushHistory(userProfile[0]);
                PROFILES[currUserIndex]->jumlahTiket--;
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
        clearScreen();
        if(userProfile[3] == "menunggu diacc"){
            cout << "\n Dashboard Pengunjung" << endl;
            cout << "\nSelamat datang di MyZoo \nHTM: Rp40.000" << endl;
            cout << "Tiket Anda: " << PROFILES[currUserIndex]->jumlahTiket << endl;
            cout << "<< Menunggu di-acc oleh petugas >>\n";
            cout << "0. Logout\n";

            cout << "Pilihan Anda: ";
            choice = inputValidInt();

            switch (choice) {
                case 0:
                    USER_FOUND = false;
                    return;

                default:
                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }

            // if(PROFILES[currUserIndex]->jumlahTiket > 0){
            //     cout << "2. Gunakan Tiket Masuk" << endl;
            // }
        } else{
            cout << "\n Dashboard Pengunjung" << endl;
            cout << "\nSelamat datang di MyZoo \nHTM: Rp40.000" << endl;
            cout << "Tiket Anda: " << PROFILES[currUserIndex]->jumlahTiket << endl;
            cout << "0. Logout" << endl;
            cout << "1. Beli Tiket Masuk" << endl;

            if(PROFILES[currUserIndex]->jumlahTiket > 0){
                cout << "2. Gunakan Tiket Masuk" << endl;
            }
            cout << "Pilihan Anda: ";
            choice = inputValidInt();

            switch (choice) {
                case 1:
                    buyTicket(userProfile[0]);
                    cout << "<< Menunggu di-acc oleh Petugas >>\n";
                    return;

                case 2:
                    if(PROFILES[currUserIndex]->jumlahTiket > 0){
                        useTicket(userProfile[0]);
                        return;
                    }
                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                    break;

                case 0:
                    USER_FOUND = false;
                    return;

                default:
                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        }
    }

}
