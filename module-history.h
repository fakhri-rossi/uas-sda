#pragma once
#include <string>
#include <iostream>
using namespace std;
const int MAX_HISTORY = 20;

struct HistoryStack {
    int top;
    string history[MAX_HISTORY];
} historyStack;

void createHistoryStack() {
    historyStack.top = -1;
}

bool isHistoryEmpty() {
    return historyStack.top == -1;
}

bool isHistoryFull() {
    return historyStack.top >= MAX_HISTORY - 1;
}

void pushHistory(string user) {
    if (isHistoryFull()) {
        cout << "Histori penuh, tidak dapat menambahkan." << endl;
    } else {
        historyStack.history[++historyStack.top] = user;
        cout << "Menambahkan ke histori: " << user << endl;
    }
}

void popHistory() {
    if (isHistoryEmpty()) {
        cout << "Histori kosong." << endl;
    } else {
        cout << "Menghapus dari histori: " << historyStack.history[historyStack.top--] << endl;
    }
}

void displayHistory() {
    if (isHistoryEmpty()) {
        cout << "Histori kosong." << endl;
    } else {
        cout << "Menampilkan histori pengunjung terakhir:" << endl;
        for (int i = historyStack.top; i >= 0; --i) {
            cout << historyStack.history[i] << endl;
        }
    }
}