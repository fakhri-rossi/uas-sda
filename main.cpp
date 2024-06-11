#include <iostream>
using namespace std;
#include <limits.h>
#include <string>

#include "GlobalVariables.h"


#include "module-validInput.h"

#include "moduleGraph.h"

// int** graph = buatPeta();
#include "module-userGate.h"

#include "module-petugas.h"

#include "module-pengunjung.h"

// Place *currentVisitorPlace = NULL;

#include "module-history.h"


void initApp(){
    addUser("syahrul", "123", "pengunjung", "tidak ada", jumlahUser);
    addUser("aa", "123", "pengunjung", "belum dipakai", jumlahUser);
    addUser("arul", "123", "petugas", "-", jumlahUser);
    tambahEdge(graph, gerbang, pusat, 10);

    tambahEdge(graph, pusat, domba, 15);
    tambahEdge(graph, domba, rusa, 7);
    tambahEdge(graph, rusa, babi, 4);
    tambahEdge(graph, domba, babi, 11);

    tambahEdge(graph, pusat, singa, 23);
    tambahEdge(graph, singa, harimau, 47);
    tambahEdge(graph, harimau, macan, 6);
    tambahEdge(graph, singa, macan, 5);
    tambahEdge(graph, singa, jerapah, 12);

    tambahEdge(graph, pusat, gedungPertunjukan, 50);
    tambahEdge(graph, gedungPertunjukan, akuarium, 2);
    tambahEdge(graph, gedungPertunjukan, lumba, 6);
}


int main(){
    initApp();
    while(IS_CONTINUE){
        dashboardAwal();
        if(USER_FOUND){
            
            if(userProfile[2] == "pengunjung"){
                if(userProfile[3] == "aktif"){
                    pengunjungDashboardActive();

                } else {
                    pengunjungDashboard();

                }
                // pengunjungDashboard();
            } else if (userProfile[2] == "petugas"){
                petugasDashboard();
            }
        }
    }
    cout << "Enter untuk lanjutkan";
    cin.get();
    return 0;
}