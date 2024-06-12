#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Place{
    int index;
    string name;
    bool isKandang;
    string desc;
};

const int ukuran = 10;
const int MAX_USER = 10;
const int MAX_COLUMN = 4;
// const int MAX_HISTORY = 20;

int jumlahUser = 0;
bool IS_CONTINUE = true;
bool USER_FOUND = false;

int currUserIndex;
// int jumlahKandang = 0;
// const int V = 12;

// nyimpen data semua user
string DATABASE_USER[MAX_USER][MAX_COLUMN];

// buat nyimpan data current user
string userProfile[MAX_COLUMN];

struct History{
    Place *places[12];
    int top = 0;
};

bool isPlaceVisited(History *history, Place *place){
    for(int i = 0; i < history->top; i++){
        if(history->places[i] == place){
            return true;
        }
    }
    return false;
}

void addPlace(History *history, Place *place){
    if(!isPlaceVisited(history, place)){
        if(history->top < 12){
            history->places[history->top] = place;
            history->top++;
        } else {
            cout << "Anda sudah mengunjungi semua tempat! Sungguh pecinta binatang!\n";
        }
    }
}

void clearHistorylace(History *history){
    for(int i = 0; i < history->top; i++){
        history->places[i] = NULL;
    }
    history->top = 0;
}

void printHistory(History *history){
    cout << "----------------------------\n";
    cout << "Tempat yang sudah dikunjungi\n";
    cout << "----------------------------\n";
    
    for(int i = 0 ; i < history->top; i++){
        cout << history->places[i]->name << endl;
    }

    if(history->top == 0){
        cout << "<< kosong >>";
    }

    cout << endl;
    string cntinue;
    cout << "y untuk Enter untuk Lanjutkan\n";
    cin >> cntinue;
}

struct Profile{
    int jumlahTiket;
    History *historyPlace; 
};

Profile *PROFILES [MAX_USER];
