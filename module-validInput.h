#pragma once
#include <iostream>
using namespace std;
#include <limits.h>
#include <string>

int inputValidInt(){
    int answer;
    cin >> answer;
    while(!cin){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Masukkan angka! Ulangi: ";
        cin >> answer;
    }
    cin.clear();
    cin.ignore(100, '\n');
    return answer;
}

string inputOneWord(){
    string answer;
    cin >> answer;
    cin.clear();
    cin.ignore(100, '\n');
    return answer;
}
