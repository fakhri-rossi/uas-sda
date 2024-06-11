#pragma once

#include <iostream>
#include <limits>
#include <limits.h>
#include <string>

using namespace std;
const int V = 12;
int jumlahKandang = 0;


struct Place{
    int index;
    string name;
    bool isKandang;
    string desc;
};

struct Track{
    Place *node;
    Track *next;
};

struct Track* createTrack(Place *place){
    Track *newTrack = new Track;
    newTrack->node = place;
    newTrack->next = NULL;

    return newTrack;
}

void tambahTrack(Track *trackHead, Place *place){
    Track *newTrack = new Track;
    Track *currTrack = trackHead;
    newTrack->node = place;
    newTrack->next = NULL;

    while(currTrack->next != NULL){
        currTrack = currTrack->next;
    }

    currTrack->next = newTrack;
}

struct Track* copyTrack(Track *sumber){
    Track *currTrack;
    Track *newTrackHead = new Track;
    currTrack = newTrackHead;
    newTrackHead->node = sumber->node;
    newTrackHead->next = NULL;

    while(sumber->next != NULL){
        currTrack->next = new Track;
        currTrack = currTrack->next;
        sumber = sumber->next;

        currTrack->node = sumber->node;
        currTrack->next = NULL;
    }

    return newTrackHead;
}

struct Place* PLACES[V];

struct Place* createPlace(string name, bool iskandang, string desc){
    Place *place = new Place;
    place->index = jumlahKandang;
    place->name = name;
    place->isKandang = iskandang;
    place->desc = desc;
    PLACES[jumlahKandang] = place;

    jumlahKandang++;
    return place;
}

// void deleteTrack


int** buatPeta(){
    int** graph = new int*[V];
    for(int i = 0; i < V; i++){
        graph[i] = new int[V];
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 0;
        }
    }

    return graph;
}

void tambahEdge(int** map, Place *awal, Place *tujuan, int jarak){
    map[awal->index][tujuan->index] = jarak;
    map[tujuan->index][awal->index] = jarak;
}

int minDistance(int dist[], bool sptSet[]){
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++){
        if (sptSet[v] == false && dist[v] <= min){
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

// void printSolution(int dist[], int tujuan)
// {
//     cout << "Vertex \t Distance from Source" << endl;
//     for (int i = 0; i < V; i++){
//         cout << i << " \t\t\t\t" << dist[i] << endl;
//     }
// }

void printTrack(Track *trackHead){
    Track *currTrack = trackHead;
    
    cout << "Rute: " << currTrack->node->name;
    currTrack = currTrack->next;
    while(currTrack != NULL){
        cout << " -> " << currTrack->node->name;
        currTrack = currTrack->next;
    }
    cout << endl;
}

void dijkstra(int** graph, Place *start, Place *target)
{
    int src = start->index;
    int destination = target->index;
    int dist[V];

    bool sptSet[V];

    Track* tracks[V];

    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX, sptSet[i] = false;
    }

    dist[src] = 0;
    tracks[src] = createTrack(PLACES[src]);

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++){
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
                
                dist[v] = dist[u] + graph[u][v];
                tracks[v] = copyTrack(tracks[u]);
                tambahTrack(tracks[v], PLACES[v]);

            }
        }
    }

    cout << endl;
    cout << "Jarak terdekat dari " << PLACES[src]->name << " ke  " << PLACES[destination]->name << " : " << dist[destination] << "m" << endl;

    printTrack(tracks[destination]);
}

struct Place* gerbang = createPlace("Gerbang", false, "Tempat Masuk");
struct Place* pusat = createPlace("Pusat", false, "Pusat Kebun Binatang");

struct Place* domba = createPlace("Domba", true, "Domba, gibas atau biri-biri (Ovis aries) dalah mamalia ruminansia peliharaan yang biasanya dipelihara sebagai hewan ternak . Meskipun istilah domba dapat diterapkan pada spesies lain dalam genus Ovis , dalam penggunaan sehari-hari istilah ini hampir selalu mengacu pada domba peliharaan. Seperti semua ruminansia, domba adalah anggota ordo Artiodaktil, hewan berkuku genap . Berjumlah lebih dari satu miliar, domba domestik juga merupakan spesies domba yang paling banyak jumlahnya.");
struct Place* rusa = createPlace("Rusa", true, "Rusa, sambar, atau menjangan (bahasa Inggris: deer) adalah hewan mamalia pemamah biak (ruminan) yang termasuk famili Cervidae. Salah satu ciri khas rusa adalah adanya ranggah[1] dan bukan tanduk, yang merupakan pertumbuhan tulang yang berkembang setiap tahun (biasanya pada musim panas) terutama pada rusa jantan (walaupun ada beberapa pengecualian). Rusa jantan dari hampir semua spesies (kecuali rusa air ), serta rusa betina, tumbuh dan melepaskan ranggah baru setiap tahun. Ada sekitar 34 spesies rusa di seluruh dunia yang terbagi menjadi dua kelompok besar: kelompok rusa dunia lama yang termasuk subfamilia Muntiacinae dan Cervinae; serta kelompok rusa dunia baru, Hydropotinae dan Odocoilinae.");
struct Place* babi = createPlace("Babi", true, "Babi adalah sejenis hewan ungulata yang bermoncong panjang dan berhidung lemper dan merupakan hewan yang aslinya berasal dari Eurasia. Babi merupakan omnivora yang berarti mereka mengonsumsi daging maupun tumbuh-tumbuhan. Selain itu, babi termasuk salah satu mamalia yang paling cerdas, dan dilaporkan lebih pintar dan mudah dipelihara dibandingkan dengan anjing dan kucing.");

struct Place* singa = createPlace("singa", true, "Singa (Sanskerta: Siṃha, atau nama ilmiahnya Panthera leo) adalah spesies hewan dari keluarga felidae atau keluarga kucing. Singa berada di benua Afrika dan sebagian di wilayah India. Singa merupakan hewan yang hidup berkelompok. Biasanya terdiri dari seekor jantan & banyak betina. Kelompok ini menjaga daerah kekuasaannya. Umur singa antara 10 sampai 15 tahun di alam bebas, tetapi dalam penangkaran memungkinkan lebih dari 20 tahun. Singa yang lebih muda akan merebut kepemimpinan dari singa yang lebih tua. Kebanyakan singa yang lebih muda akan memakan anak singa dari pemimpin sebelumnya.");
struct Place* harimau = createPlace("harimau", true, "Harimau (Panthera tigris) atau maung adalah spesies kucing terbesar yang masih hidup dari genus Panthera. Harimau memiliki ciri loreng yang khas pada bulunya, berupa garis-garis vertikal gelap pada bulu oranye, dengan bulu bagian bawah berwarna putih. Harimau adalah pemangsa puncak, mereka terutama memangsa ungulata seperti rusa dan babi celeng. Harimau adalah hewan teritorial dan umumnya merupakan pemangsa soliter yang penyendiri, tetapi tetap memiliki sisi sosial. Mereka tetap tinggal di area-area yang berdekatan, untuk mendukung kebutuhan makanan dan membesarkan keturunannya. Anak harimau tinggal bersama ibu mereka selama sekitar dua tahun, kemudian akan hidup mandiri dan meninggalkan daerah jelajah ibu mereka untuk membangun rumah mereka sendiri.");
struct Place* macan = createPlace("Macan Tutul", true, "Macan tutul atau harimau bintang ( Panthera pardus ) adalah salah satu dari lima spesies yang masih ada dalam genus Panthera. Ia memiliki bulu pucat kekuningan hingga emas tua dengan bintik-bintik gelap yang membentuk pola seperti mawar . Tubuhnya ramping dan berotot mencapai panjang 92–183 cm (36–72 inci) dengan panjang ekor 66–102 cm (26–40 inci) dan tinggi bahu 60–70 cm (24–28 inci). Jantan biasanya memiliki berat 30,9–72 kg (68–159 lb), dan betina 20,5–43 kg (45–95 lb).");
struct Place* jerapah = createPlace("jerapah", true, "Jerapah adalah mamalia berkuku besar Afrika yang termasuk dalam genus Giraffa. Ini adalah hewan darat tertinggi yang masih hidup dan pemamah biak terbesar di Bumi. Secara tradisional, jerapah dianggap sebagai satu spesies , Giraffa camelopardalis , dengan sembilan subspesies . Baru-baru ini, para peneliti mengusulkan untuk membagi mereka menjadi delapan spesies yang masih ada karena penelitian baru terhadap DNA mitokondria dan inti mereka , serta pengukuran morfologi. Tujuh spesies jerapah lainnya yang punah diketahui dari catatan fosil.");

struct Place* gedungPertunjukan = createPlace("Gedung Pertunjukan", false, "Gedung Pertunjukannn");
struct Place* akuarium = createPlace("Akuarium", true, "Di akuarium ini, silahkan lihat-lihat keindahan ikan ciptaan Tuhan! :)");
struct Place* lumba = createPlace("Lumba-Lumba", true, "Lumba-lumba adalah mamalia air yang sangat cerdas. Sistem alamiah yang melengkapi tubuh lumba-lumba sangat kompleks. Sehingga banyak teknologi yang terinspirasi dari lumba-lumba. Salah satu contoh adalah kulit lumba-lumba yang mampu memperkecil gesekan dengan air, sehingga lumba-lumba dapat berenang dengan sedikit hambatan air. Hal ini yang digunakan para perenang untuk merancang baju renang yang mirip kulit lumba-lumba.");