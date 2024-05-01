// MIA KOMLENAC NRT 18/22 
// SEMINARSKI RAD KVIZ PITANJA IZ RAZLICITIH OBLSATI

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Pitanje {
    char pitanje[150];
    char odgovor[50];
    int oblast;
    int brojBodova;
};

int* random3pitanja(int oblast, struct Pitanje *pitanja, int n); //funkcija za generisanje 3 pitanja iz jedne oblasti

int sadrziSeUNizu(int *niz, int element, int duzina); //funkcija koja proverava da li se pitanje ponavlja

//baza pitanja i odgovora
struct Pitanje pitanja[25] = {
        //geografija  = 1
        {"Koja je dubina najnize tacke na povrsini planete? (u metrima)","427",1, 3},
        {"Koja je najveca planina na svetu?","mont everest",1, 2},
        {"Koja je najveca pustinja na svetu?","antarktik",1, 3},
        {"Koliko iznosi najduza granica na svetu izmedju dve drzave (Kanada i SAD).(u kilometrima)","8.891",1, 4},
        {"Naziv najviseg vodopada na svetu je ________ vodopad.","Andjeoski",1, 2},

        //Istorija = 2
        {"Ko je bio osnivac Rimske Republike prema legendi?","romul",2, 3},
        {"Ko je bio lider tokom Americkog Gradjanskog rata na strani Unije?","abraham linkoln",2, 2},
        {"Koje godine je okončan Drugi svetski rat?","1945",2, 1},
        {"Ko je bio vodja Oktobarske revolucije u Rusiji 1917. godine?","vladimir lenjin",2, 2},
        {"Ko je bio vodja anti-apartheidskog pokreta u Juznoj Africi?","nelson mendela",2, 2},

        // Hemija = 3
        {"Koja je oznaka hemijskog elementa koji čini najveći procenat Zemljine kore ?","o",3, 1},
        {"Šta oznacava skraćenica DNA?","deoksiribonukleinska kiselina",3, 2},
        {"Koji je naziv za direktnu promenu iz cvrstog stanja u gasovito, bez prelaska kroz tecno stanje ?","sublimacija",3, 1},
        {"Reakcija u kojoj dolazi do istovremenog oksidacije i redukcije naziva se ________ reakicija.","redoks",3, 2},
        {"Reakcija koja oslobadja svetlost i toplotu je ___________ reakcija.","egzotermna",3, 1},

        // Umetnost =4
        {"Koja tehnika u slikarstvu koristi toplu smolu ili vosak za stvaranje slike?","enkaustika",4, 1},
        {"Koja je umetnicka tehnika gde se boje nanose na mokar papir, stvarajuci nezne i razlicite efekte?","akvarel",4, 2},
        {"Koji umetnik je poznat po radovima inspirisanim meksickom kulturom, uključujući sliku Autoportret s trnom?","frida kalo",4, 1},
        {"Koji pokret u umetnosti karakterise upotreba svakodnevnih predmeta u umetničkom kontekstu?","pop art",4, 2},
        {"Koji pokret u umetnosti naglasava geometrijske oblike i apstraktne ideje?","konstruktivizam",4, 1},


        //Biologija = 5
        {"Koji organ proizvodi insulin?","pankreas",5, 1},
        {"Koja vrsta biomolekula cini strukturu enzima?","proteini",5, 2},
        {"Koji organ je odgovoran za detoksikaciju krvi?","jetra",5, 1},
        {"Kako se naziva proces razmene gasova između pluca i krvi?","respiracija",5, 2},
        {"Koji enzim razlaze secer u ljudskom telu?","amilaza", 5 , 5},


};

int main() {
    int ukupniBodovi = 0;
    int izborOblasti[3], i,j;
    int oblast, index;
    int* pitanjaZaOblast;
    char odgovor[50], ime[50], c;
    char oblasti[5][21] = {"Geografija", "Istorija", "Hemija", "Umetnost", "Biologija"};
    FILE* fajl;



    printf("Unesite svoje ime:\n");
    gets(ime);
    fflush(stdin);
    printf("Od ponudjenih oblasti izaberite 3. Oblasti razdvojite enterom. Odgovore na pitanja pisite sve malim slovima! \n U slucaju da ne znate odgovor stavite opciju \"n\" \n");
    printf("1 - Geografija\n");
    printf("2 - Istorija\n");
    printf("3 - Hemija\n");
    printf("4 - Umetnost\n");
    printf("5 - Biologija\n\n\n");

    scanf("%d", &izborOblasti[0]);
    scanf("%d", &izborOblasti[1]);
    scanf("%d", &izborOblasti[2]);
    fflush(stdin);

    for (i = 0; i < 3; i++) {

        oblast = izborOblasti[i];
        // generise 3 pitanja za izabranu oblast 
        pitanjaZaOblast = random3pitanja(oblast, pitanja, 25);

        printf("Pitanja za oblast %s:\n", oblasti[oblast - 1]);
        for (j = 0; j < 3; j++) {
            // uzima pitanje iz date oblasti
            index = pitanjaZaOblast[j];
            printf("%s (%d bodova)\n", pitanja[index].pitanje, pitanja[index].brojBodova);


            printf("Unesite odgovor: ");
            gets(odgovor);
            fflush(stdin);

			//proverava odgovor i dodeljuje bodove
            if (strcmp(odgovor, pitanja[index].odgovor) == 0) {
                printf("Tacan odgovor! Osvojili ste %d bodova.\n", pitanja[index].brojBodova);
                ukupniBodovi += pitanja[index].brojBodova;
            } else if (strcmp(odgovor, "n") == 0){
                printf("Stavili ste opciju ne znam, niste izgubili bodove.\n");
            } else {
                ukupniBodovi -= 1;
                printf("Netacan odgovor. Izgubili ste 1 bod.\n");
            }
        }
        free(pitanjaZaOblast);
    }

	//rad sa datotekom

    fajl = fopen("rezultati.txt", "a+");
    if (fajl == NULL) {
        printf("Greska pri otvaranju fajla za upis rezultata.\n");
        exit(1);
    }

    fprintf(fajl, "%s\n%d\n \n", ime, ukupniBodovi);

    // printuje u konzolu
    rewind(fajl);
    while((c=fgetc(fajl)) != EOF) {
        printf("%c", c);
    }


    printf("Ukupan broj osvojenih bodova: %d\n", ukupniBodovi);

    printf("Igra zavrsena. Rezultati su upisani u 'rezultati.txt'.\n");

    fclose(fajl);

    return 0;
}

///FUNKCIJE

int* random3pitanja(int oblast, struct Pitanje *pitanja, int n) {
    int random, i;
    int *niz;
    srand(time(0));

    niz = (int *) malloc(3 * sizeof(int)); 

    if (niz == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        exit(1);
    }

    // 0 - 24
    // generise niz od 3 nasumicna broja bez ponavljanja pitanja iz iste oblasti
    for (i = 0; i < 3; i++) {

        do {
            random = rand() % n;
        } while (
                pitanja[random].oblast != oblast // da je iz iste oblasti
                || sadrziSeUNizu(niz, random, i + 1) == 1 // da se ne ponavljaju brojevi
                );
        niz[i] = random;
    }

    return niz;
}

// Vraca 1 ako je nadjen element u datom nizu, ako nije vraca 0
int sadrziSeUNizu(int *niz, int element, int duzina) {
    int i;
    for(i = 0; i < duzina; i++) {
        if (niz[i] == element) {
            return 1;
        }
    }

	return 0;
}