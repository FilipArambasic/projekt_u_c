#define _CRT_SECURE_NO_WARNINGS

#ifndef FUNKCIJE_H
#define FUNKCIJE_H

typedef struct film {
    char naslov[100];
    int godina;
    char zanr[50];
    char gledano[3];
} FILM;

int izbornik();
int izbornikPret();
int izbornikSort();
void kreiranjeDat();
void unesiFilm();
FILM* ucitajFilm();
void urediPodatke();
void ispisiFilm(FILM* polje);
void* searchNaslov(FILM* polje);
void* searchGodina(FILM* polje);
void* searchZanr(FILM* polje);
void* searchGledano(FILM* polje);
void selectionSortGodinaUzl(FILM* polje);
void selectionSortGodinaSil(FILM* polje);
void subZaSortUzl(FILM* manji, FILM* veci);
void subZaSortSil(FILM* veci, FILM* manji);
void brisanjeFilma(FILM* polje);
void izlaz();

#endif /* FUNKCIJE_H */
