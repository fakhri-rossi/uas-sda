#pragma once
#include <iostream>
#include <iostream>
using namespace std;
#include "GlobalVariables.h"

// sistem antrian (queue)
struct queue {
    int top;
    string isi[ukuran];
} q;

void createQueue () {
    q.top = 0;
}

int isEmpty () {
    if (q.top == 0) {
        return 1;
    } else {
        return 0;
    }
}

int isFull () {
    if (q.top >= ukuran) {
        return 1;
    } else {
        return 0;
    }
}

void insertQueue(string namaPengunjung) {
    if (isFull() == 1) {
        cout << "Maaf, antrian sudah penuh." << endl;
    } else {
        q.isi[q.top] = namaPengunjung;
        cout << "Tiket untuk " << q.isi[q.top] << " sudah masuk dalam antrian." << endl;
        q.top++;
    }
}

void deleteQueue() {
    if (isEmpty() == 1) {
        cout << "Maaf, antrian kosong." << endl;
    } else {
        string pop = q.isi[0];
        cout << "Tiket untuk pengunjung " << pop << " sudah keluar dari antrian." << endl;
        for (int i = 0; i < q.top - 1; i++) {
            q.isi[i] = q.isi[i + 1];
        }
        q.top--;
    }
}

void displayQueue() {
    cout << "Antrian di Loket:\n";
    if (isEmpty() == 0) {
        for (int i = 0; i < q.top; i++) {
            cout << "[" << i+1 << "]: " << q.isi[i] << endl;
        }
        cout << endl;
    } else {
        cout << "<< kosong >>" << endl;
    }
}

// update status tiket
void updateTicketStatus(string username, string status) {
    for (int i = 0; i < jumlahUser; i++) {
        if (DATABASE_USER[i][0] == username) {
            DATABASE_USER[i][3] = status;
            if(status != "menunggu diacc"){
                PROFILES[i]->jumlahTiket++;
            }
            break;
        }
    }
}