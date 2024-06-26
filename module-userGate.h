#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "moduleGraph.h"
#include "module-validInput.h"
#include "GlobalVariables.h"
#include "module-history.h"
using namespace std;

int** graph = buatPeta();
// Place *currentVisitorPlace = NULL;

void addUser(string username, string password, string role, string statusTiket, int urutanUser, int jumlahTiket){
    DATABASE_USER[urutanUser][0] = username;
    DATABASE_USER[urutanUser][1] = password;
    DATABASE_USER[urutanUser][2] = role;
    DATABASE_USER[urutanUser][3] = statusTiket;

    PROFILES[urutanUser] = new Profile;
    PROFILES[urutanUser]->historyPlace = new History;
    PROFILES[urutanUser]->jumlahTiket = jumlahTiket;

    jumlahUser += 1;
}

bool isUsernameTaken(const string& username) {
    for (int i = 0; i < jumlahUser; ++i) {
        if (DATABASE_USER[i][0] == username) {
            return true;
        }
    }
    return false;
}


void printDatabaseUser(){
    for(int i = 0; i < jumlahUser; i++){
        cout << DATABASE_USER[i][0] << ", " << DATABASE_USER[i][1] << ", " << DATABASE_USER[i][2] << ", " << DATABASE_USER[i][3] << ", " << PROFILES[i]->jumlahTiket;
        cout << endl;
    }
}

// Register
void registerUser() {
    if (jumlahUser < MAX_USER) {
        
        const int max_pass_length = 100;
        char pass[max_pass_length];
        char ch;
        int i = 0;
        bool continueProgram = true;

        string username, password, role;
        while (continueProgram)
        {
            cout << "Masukkan username: ";
            username = inputOneWord();

            while(isUsernameTaken(username)){
                cout << "Username sudah digunakan!\nUsername: ";
                username = inputOneWord();
            }
            
            cout << "Masukkan password : ";
            // password = inputOneWord();
                        // password = inputOneWord();
            while(true){
                ch = getch();

                if (ch == '\r'){
                    pass[i] = '\0';
                    break;
                }

                else if (ch == '\b' && i > 0){
                    cout << "\b \b";
                    i--;
                } else if (i < max_pass_length - 1){
                    pass[i++] = ch;
                    cout << '*';
                }
            }

            cout << "\nMasukkan role\n\t1: pengunjung\n\t2: petugas \n";
            role = inputOneWord();
            
            while(role != "1" && role != "2"){
                cout << "Role tidak valid. Silakan pilih role yang sesuai." << endl;
                role = inputOneWord();
            }

            if (role == "1") {
                role = "pengunjung";

            } else if (role == "2") {
                role = "petugas";
            }
            continueProgram = false;
        }
        addUser(username, pass, role, "tidak ada", jumlahUser, 0);
        // PROFILES[jumlahUser]->jumlahTiket = 0;
        // PROFILES[jumlahUser]->currentVisitorPlace = NULL;
        cout << "Pengguna berhasil terdaftar." << endl;
        
    } else {
        cout << "Database pengguna penuh. Tidak bisa mendaftarkan pengguna baru." << endl;
    }
}

// login
void loginUser() {
    // const int max_pass_length = 100;
    // char pass[max_pass_length];
    const int max_pass_length = 100;
    char pass[max_pass_length];
    char ch;
    int counter = 0;

    string username, password;
    cout << "Masukkan username: ";
    username = inputOneWord();


    cout << "Masukkan password: ";
    // password = inputOneWord();
    while(true){
        ch = getch();

        if (ch == '\r'){
            pass[counter] = '\0';
            break;
        } else if (ch == '\b' && counter > 0){
            cout << "\b \b";
            counter--;
        } else if (counter < max_pass_length - 1){
            pass[counter++] = ch;
            cout << '*';
        }
    }

    for (int i = 0; i < jumlahUser; ++i) {
        if (DATABASE_USER[i][0] == username && DATABASE_USER[i][1] == pass) {
            cout << "Login berhasil. Selamat datang, " << username << "!" << endl;
            cout << "Role: " << DATABASE_USER[i][2] << endl;

            // saving user profile (username, password, role)
            userProfile[0] = DATABASE_USER[i][0]; // username
            userProfile[1] = DATABASE_USER[i][1]; // password
            userProfile[2] = DATABASE_USER[i][2]; // role
            userProfile[3] = DATABASE_USER[i][3]; // status tiket
            currUserIndex = i;

            USER_FOUND = true;
            break;
        }
    }

    if (!USER_FOUND) {
        cout << "\n(Login gagal. Silakan coba lagi)\n";
    }
}

// dashboard awal
void dashboardAwal(){
    int choice;
    while(true) {
        clearScreen();
        cout << "\nMENU AWAL" << endl;
        cout << "1. Daftar" << endl;
        cout << "2. Login" << endl;
        cout << "3. Keluar" << endl;
        
        cout << "Pilihan:\n";
        printDatabaseUser();
        cout << endl << endl;

        cout << "Pilihan Anda: ";
        choice = inputValidInt();

        switch (choice) {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                return;

            case 3:
                cout << "Terima kasih. Sampai jumpa!" << endl;
                IS_CONTINUE = false;
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}
