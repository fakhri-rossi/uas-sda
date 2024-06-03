#include <iostream>
using namespace std;

const int MAX_USER = 10;
const int MAX_COLUMN = 4;

int jumlahUser = 0;

// nyimpen data semua user
string DATABASE_USER[MAX_USER][MAX_COLUMN];

// buat nyimpan data current user
string userProfile[MAX_COLUMN];

// tempatSaatIni akan nyusul

// function buat nyimpen data user baru ke database
void addUser(string username, string password, string role, string statusTiket, int urutanUser){
    DATABASE_USER[urutanUser][0] = username;
    DATABASE_USER[urutanUser][1] = password;
    DATABASE_USER[urutanUser][2] = role;
    DATABASE_USER[urutanUser][3] = statusTiket;

    jumlahUser += 1;
}

void printDatabaseUser(){
    for(int i = 0; i < jumlahUser; i++){
        cout << DATABASE_USER[i][0] << ", " << DATABASE_USER[i][1] << ", " << DATABASE_USER[i][2] << ", " << DATABASE_USER[i][3];
        cout << endl;
    }
}

void initApp(){
    addUser("syahrul", "123", "pengunjung", "tidak ada", jumlahUser);
    addUser("arul", "123", "petugas", "-", jumlahUser);
}

int main(){
    initApp();
    printDatabaseUser();

    return 0;
}