#pragma once
#include <iostream>
#include <string>
using namespace std;

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