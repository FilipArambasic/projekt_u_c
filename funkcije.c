#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

static int brojFilmova = 0;
static int i;
static int j;
static int br = 0;

int izbornik() {

    int izbor = 0;
    static FILM* polje = NULL;

    printf("\n### IZBORNIK ###\n");
    printf("1. Unos novog filma\n");
    printf("2. Uredi podatke o filmu\n");
    printf("3. Ispis filmova\n");
    printf("4. Pretrazivanje filmova\n");
    printf("5. Sortiranje filmova\n");
    printf("6. Brisanje filma\n");
    printf("7. Izlaz\n");
    printf("#################\n");

    scanf("%d", &izbor);
    system("cls");

    switch (izbor) {
    case 1:
            ucitajFilm();
            if (brojFilmova == 0) {
                kreiranjeDat();
            }
            unesiFilm();
            break;

    case 2:
            urediPodatke();
            break;

    case 3:
            if (polje != NULL) {
                free(polje);
                polje = NULL;
            }
            polje = (FILM*)ucitajFilm();
            ispisiFilm(polje);
            break;

    case 4:
            while (izbor != 997) {
                izbor = izbornikPret();
            }
            break;

    case 5:
            while (izbor != 998) {
                izbor = izbornikSort();
            }
            break;

    case 6:
            if (polje == NULL) {
                printf("Nema unesenih filmova\n");
            }
            else {
                brisanjeFilma(polje);
            }
            break;

    case 7:
            printf("Izlaz iz programa.\n");
            return 999;
            break;

    default:
            printf("Nepoznata opcija, molimo odaberite ponovno.\n");
    }

    return izbor;

}

int izbornikPret() {

    int izbor = 0;
    FILM* polje = NULL;
    polje = (FILM*)ucitajFilm();

    printf("Pretraživanje:\n");
    printf("1. Naslov\n");
    printf("2. Godina\n");
    printf("3. Zanr\n");
    printf("4. Pogledani filmovi\n");
    printf("5. Natrag\n");

    scanf("%d", &izbor);
    system("cls");

    switch (izbor) {
    case 1:
            searchNaslov(polje);
            break;

    case 2:
            searchGodina(polje);
            break;

    case 3:
            searchZanr(polje);
            break;

    case 4:
            searchGledano(polje);
            break;

    case 5:
            return 997;

    default:
        printf("Nepoznata opcija, molimo odaberite ponovno.\n");
    }

    return izbor;

}

izbornikSort() {

    int izbor = 0;
    FILM* polje = NULL;
    polje = (FILM*)ucitajFilm();

    printf("Sortiraj po:\n");
    printf("1. Godini ulazno\n");
    printf("2. Godini silazno\n");
    printf("3. Natrag\n");

    scanf("%d", &izbor);
    system("cls");

    switch (izbor) {
    case 1:
            selectionSortGodinaUzl(polje);
            break;

    case 2:
            selectionSortGodinaSil(polje);
            break;

    case 3:
            return 998;
  
    default:
            printf("Nepoznata opcija, molimo odaberite ponovno.\n");
    }

    return izbor;

}

void kreiranjeDat() {

    FILE* fp = NULL;
    fp = fopen("filmovi.bin", "wb");

    if (fp == NULL) {
        perror("Greška pri otvaranju datoteke");
    }
    
    fwrite(&brojFilmova, sizeof(int), 1, fp);
    fclose(fp);

}

void unesiFilm() {

    FILE* fp = fopen("filmovi.bin", "ab");

    if (fp == NULL) {
        perror("Neuspješni unos");
        exit(1);
    }

    FILM noviFilm;

    printf("Unesite naslov filma: ");
    scanf(" %[^\n]", noviFilm.naslov);

    printf("Unesite godinu izdanja filma: ");
    scanf("%d", &noviFilm.godina);

    printf("Unesite žanr filma: ");
    scanf(" %[^\n]", noviFilm.zanr);

    printf("Unesite broj gledanja filma: ");
    scanf(" %[^\n]", noviFilm.gledano);

    fwrite(&noviFilm, sizeof(FILM), 1, fp);

    fclose(fp);

    printf("Film uspješno dodan.\n");
    
}

void* ucitajFilm() {

    FILE* fp = fopen("filmovi.bin", "rb");
    if (fp == NULL) {
        perror("Nema unesenih filmova\n");
        return NULL;
    }

    fread(&brojFilmova, sizeof(int), 1, fp);
    
    FILM* polje = NULL;
    polje = (FILM*)malloc(brojFilmova * sizeof(FILM));

    if (polje == NULL) {
        perror("Neuspješno zauzimanje memorije");
        return NULL;
    }

    fread(polje, sizeof(FILM), brojFilmova, fp);
    fclose(fp);

    return polje;

}

void urediPodatke(FILM* polje) {

    int id;
    printf("Unesite ID filma koji želite urediti: ");
    scanf("%d", &id);

    if (id < 1 || id > brojFilmova) {
        printf("Neispravan ID filma.\n");
        return;
    }

    FILM* film = &polje[id - 1];

    printf("Film koji želite urediti:\n");
    ispisiFilm(film);

    printf("Unesite nove podatke za film:\n");
    printf("Naslov: ");
    scanf(" %[^\n]s", film->naslov);
    printf("Godina: ");
    scanf("%d", &film->godina);
    printf("Zanr: ");
    scanf(" %[^\n]s", film->zanr);
    printf("Jeste li pogledali (da/ne): ");
    scanf(" %[^\n]s", &film->gledano);

    printf("Podaci o filmu su ažurirani.\n");
}

void ispisiFilm(FILM* polje) {

    if (polje == NULL) {
        printf("Nema unesenih filmova.\n");
        return;
    }

    printf("ID   Naslov                        Godina   Žanr               Gledano\n");
    printf("------------------------------------------------------------------------------\n");

    for (i = 0; i < brojFilmova; i++) {
        printf("%-4d %-30s %-8d %-20s %s", i + 1, (polje + 1)->naslov, (polje + 1)->godina, (polje + 1)->zanr, (polje + 1)->gledano);
    }

}

void* searchNaslov(FILM* polje) {

    char trazeniNaslov[100];
    int br = 0;

    printf("Unesite ime trazenog filma:\n");
    getchar();
    scanf(" %[^\n]", trazeniNaslov);

    if (br != 0) {
        printf("ID   Naslov                        Godina   Žanr               Gledano\n");
        printf("------------------------------------------------------------------------------\n");
    }

    for (i = 0; i < brojFilmova; i++) {
        if (!strcmp(trazeniNaslov, (polje + i)->naslov)) {
            printf("%-4d %-30s %-8d %-20s %s", i + 1, (polje + 1)->naslov, (polje + 1)->godina, (polje + 1)->zanr, (polje + 1)->gledano);
            br++;
        }
    }
    if (br == 0) {
        printf("\nFilm pod unesenim naslovom nije pronaden.\n");
    }
    return NULL;

}

void* searchGodina(FILM* polje) {

    int trazenaGodina;
    int br = 0;

    printf("Unesite godinu koju trazite:\n");
    scanf("%d", &trazenaGodina);

    if (br != 0) {
        printf("ID   Naslov                        Godina   Žanr               Gledano\n");
        printf("------------------------------------------------------------------------------\n");
    }

    for (i = 0; i < brojFilmova; i++) {
        if (trazenaGodina == (polje + i)->godina) {
            printf("%-4d %-30s %-8d %-20s %s", i + 1, (polje + 1)->naslov, (polje + 1)->godina, (polje + 1)->zanr, (polje + 1)->gledano);
            br++;
        }
    }
    if (br == 0) {
        printf("\nTrazena godina nije pronadena.\n");
    }
    return NULL;

}

void* searchZanr(FILM* polje) {
    char trazeniZanr[50];
    int br = 0;

    printf("Unesite zanr koji trazite:\n");
    getchar();
    scanf(" %[^\n]", trazeniZanr);

    if (br != 0) {
        printf("ID   Naslov                        Godina   Žanr               Gledano\n");
        printf("------------------------------------------------------------------------------\n");
    }

    for (i = 0; i < brojFilmova; i++) {
        if (!strcmp(trazeniZanr, (polje + i)->zanr)) {
            printf("%-4d %-30s %-8d %-20s %s", i + 1, (polje + 1)->naslov, (polje + 1)->godina, (polje + 1)->zanr, (polje + 1)->gledano);
            br++;
        }
    }
    if (br == 0) {
        printf("\nFilm sa ovim zanrom nije pronaden.\n");
    }
    return NULL;
}

void* searchGledano(FILM* polje) {

    char trazeniPogIliNepogFilm[3];
    int br = 0;

    printf("Unesite (da) za pogledane ili (ne) za nepogledane filmove:\n");
    getchar();
    scanf(" %[^\n]", trazeniPogIliNepogFilm);

    if (br != 0) {
        printf("ID   Naslov                        Godina   Žanr               Gledano\n");
        printf("------------------------------------------------------------------------------\n");
    }

    for (i = 0; i < brojFilmova; i++) {
        if (!strcmp(trazeniPogIliNepogFilm, (polje + i)->gledano)) {
            printf("%-4d %-30s %-8d %-20s %s", i + 1, (polje + 1)->naslov, (polje + 1)->godina, (polje + 1)->zanr, (polje + 1)->gledano);
            br++;
        }
    }
    if (br == 0) {
        printf("\nNema unesenih %s filmova.\n", strcmp(trazeniPogIliNepogFilm, "pogledani") ? "nepogledanih" : "pogledanih");
    }
    return NULL;

}

void selectionSortGodinaUzl(FILM* polje) {

    for (int j = 0; j < brojFilmova; j++) {
        for (int i = 0; i < brojFilmova - 1; i++) {
            if (polje[i].godina > polje[i + 1].godina) {
                subZaSortUzl((polje + i), (polje + i + 1));
            }
        }
    }

    printf("ID   Naslov                        Godina   Žanr               Gledano\n");
    printf("------------------------------------------------------------------------------\n");

    for (i = 0; i < brojFilmova; i++) {
        printf("%-4d %-30s %-8d %-20s %s", i + 1, (polje + 1)->naslov, (polje + 1)->godina, (polje + 1)->zanr, (polje + 1)->gledano);
    }

    printf("\n");

}

void selectionSortGodinaSil(FILM* polje) {
    
    for (int j = 0; j < brojFilmova; j++) {
        for (int i = 0; i < brojFilmova - 1; i++) {
            if (polje[i].godina < polje[i + 1].godina) {
                subZaSortSil((polje + i), (polje + i + 1));
            }
        }
    }

    printf("ID   Naslov                        Godina   Žanr               Gledano\n");
    printf("------------------------------------------------------------------------------\n");

    for (i = 0; i < brojFilmova; i++) {
        printf("%-4d %-30s %-8d %-20s %s", i + 1, (polje + 1)->naslov, (polje + 1)->godina, (polje + 1)->zanr, (polje + 1)->gledano);
    }

    printf("\n");

}

void subZaSortUzl(FILM* manji, FILM* veci) {

    FILM temp = { 0 };
    temp = *manji;
    *manji = *veci;
    *veci = temp;

}

void subZaSortSil(FILM* veci, FILM* manji) {

    FILM temp = { 0 };
    temp = *veci;
    *veci = *manji;
    *manji = temp;

}

void brisanjeFilma(FILM* polje) {
    
    FILE* fp = NULL;
    fp = fopen("filmovi.bin", "wb");
    if (fp == NULL) {
        perror("Pogreska pri brisanju filma.");
    }
    rewind(fp);
    fseek(fp, sizeof(int), SEEK_CUR);

    int id;
    printf("Unesite ID filma koji želite izbrisati: ");
    scanf("%d", &id);

    if (id < 1 || id > brojFilmova) {
        printf("Neispravan ID filma.\n");
        return;
    }

    for (int i = id - 1; i < brojFilmova - 1; i++) {
        polje[i] = polje[i + 1];
    }
    brojFilmova--;

    printf("Film je uspješno obrisan.\n");

}

void izlaz() {
    char izbor[3];                                                
    printf("Zelite li izaci iz programa? (da/ne)\n");
    while (1) {
        scanf(" %2s", izbor);
        if (strcmp(izbor, "da") == 0) {
            printf("\nIzlazak iz programa...");
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(izbor, "ne") == 0) {
            system("cls");
            return;
        }
        else {
            printf("\nUnesite 'da' ili 'ne':\n");
        }
    }
}
