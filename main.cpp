#include <iostream>
using namespace std;

const int ukuran = 10;
const int MAX_USER = 10;
const int MAX_COLUMN = 4;

int jumlahUser = 0;
bool IS_CONTINUE = true;
bool USER_FOUND = false;

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

// valid input
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

// kondisi jika username sudah ada
bool isUsernameTaken(const string& username) {
    for (int i = 0; i < jumlahUser; ++i) {
        if (DATABASE_USER[i][0] == username) {
            return true;
        }
    }
    return false;
}

// Register
void registerUser() {
    if (jumlahUser < MAX_USER) {

        // const int max_pass_length = 100;
        // char pass[max_pass_length];

        string username, password, role;
        while (true)
        {
            cout << "Masukkan username: ";
            username = inputOneWord();

            while(isUsernameTaken(username)){
                cout << "Username sudah digunakan!\nUsername: ";
                username = inputOneWord();
            }
            
            cout << "Masukkan password : ";
            password = inputOneWord();

            cout << "\nMasukkan role\n\t1: pengunjung\n\t2: petugas ";
            role = inputOneWord();

            if (role == "1") {
                role = "pengunjung";
                break;

            } else if (role == "2") {
                role = "petugas";
                break;

            } else {
                cout << "Role tidak valid. Silakan pilih role yang sesuai." << endl;
                return;
            }
        }
        addUser(username, password, role, "tidak ada", jumlahUser);
        cout << "Pengguna berhasil terdaftar." << endl;
        
    } else {
        cout << "Database pengguna penuh. Tidak bisa mendaftarkan pengguna baru." << endl;
    }
}

// login
void loginUser() {
    const int max_pass_length = 100;
    char pass[max_pass_length];

    string username, password;
    cout << "Masukkan username: ";
    username = inputOneWord();


    cout << "Masukkan password: ";
    password = inputOneWord();

    for (int i = 0; i < jumlahUser; ++i) {
        if (DATABASE_USER[i][0] == username && DATABASE_USER[i][1] == password) {
            cout << "Login berhasil. Selamat datang, " << username << "!" << endl;
            cout << "Role: " << DATABASE_USER[i][2] << endl;

            // saving user profile (username, password, role)
            userProfile[0] = DATABASE_USER[i][0]; // username
            userProfile[1] = DATABASE_USER[i][1]; // password
            userProfile[2] = DATABASE_USER[i][2]; // role

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
        cout << "\nMENU AWAL" << endl;
        cout << "1. Daftar" << endl;
        cout << "2. Login" << endl;
        cout << "3. Keluar" << endl;
        
        cout << "(database array user):\n";
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
    if (isEmpty() == 0) {
        cout << "Menampilkan isi antrian:" << endl;
        for (int i = 0; i < q.top; i++) {
            cout << "Nama pengunjung: " << q.isi[i] << " berada di posisi ke-" << i << endl;
        }
    } else {
        cout << "Maaf, tidak ada data dalam antrian." << endl;
    }
}

// update status tiket
void updateTicketStatus(string username, string status) {
    for (int i = 0; i < jumlahUser; i++) {
        if (DATABASE_USER[i][0] == username) {
            DATABASE_USER[i][3] = status;
            break;
        }
    }
}

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
                cout << "Tiket Anda sekarang aktif." << endl;
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
                break;

            case 3:
                USER_FOUND = false;
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

// Terima Pembelian Tiket dan Beri Tiket
void terimaPembelianTiket () {
    if (isEmpty() == 0) {
        string namaPengunjung = q.isi[0];
        cout << "Tiket untuk customer " << namaPengunjung << " telah diproses." << endl;
        deleteQueue();
        updateTicketStatus(namaPengunjung, "belum dipakai");
    } else {
        cout << "Antrian kosong." << endl;
    }
}

// Tolak Pembelian Tiket
void tolakPembelianTiket () {
    if (isEmpty() == 0) {
        string namaPengunjung = q.isi[0];
        cout << "Tiket untuk customer " << namaPengunjung << " telah ditolak." << endl;
        deleteQueue();
        updateTicketStatus(namaPengunjung, "tidak ada");
    } else {
        cout << "Antrian kosong." << endl;
    }
}

// Kelola Antrian
void kelolaAntrian() {
    int choice;
    bool run = true;
    while(run) {
        cout << "\n Antrian di Locket:" << endl;
        displayQueue();
        cout << "1. Terima Pembelian Tiket dan Beri Tiket" << endl;
        cout << "2. Tolak Pembelian" << endl;
        cout << "3. Hapus Antrian" << endl;
        cout << "4. Kembali" << endl;
        
        cout << "Pilihan Anda: ";
        choice = inputValidInt();

        switch (choice) {
            case 1:
                terimaPembelianTiket();
                break;

            case 2:
                tolakPembelianTiket();
                return;

            case 3:
                createQueue();
                cout << "Antrian telah dihapus." << endl;
                return;

            case 4:
                cout << "Kembali ke halaman dashboard" << endl;
                run = false;
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

// Histori Pengunjung Terkahir
void historiPengunjungTerakhir() {
    cout << "Pengunjung Terakhir" << endl;
}

// dashboard petugas
void petugasDashboard() {
    int choice;
    while(true) {
        cout << "\n Dashboard Petugas" << endl;
        cout << "1. Kelola Antrian" << endl;
        cout << "2. Lihat histori pengunjung terakhir" << endl;
        cout << "3. Logout" << endl;
        
        cout << "Pilihan Anda: ";
        choice = inputValidInt();

        switch (choice) {
            case 1:
                kelolaAntrian();
                break;

            case 2:
                historiPengunjungTerakhir();
                return;

            case 3:
                USER_FOUND = false;
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}


int main(){
    initApp();
    while(IS_CONTINUE){
        dashboardAwal();

        if(USER_FOUND){
            if(userProfile[2] == "pengunjung"){
                pengunjungDashboard();
            } else if (userProfile[2] == "petugas"){
                petugasDashboard();
            }
        }
    }
    cout << "Enter untuk lanjutkan";
    cin.get();
    return 0;
}