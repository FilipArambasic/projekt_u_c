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
void* ucitajFilm();
void urediPodatke();
void ispisiFilm(FILM*);
void* searchNaslov(FILM*);
void* searchGodina(FILM*);
void* searchZanr(FILM*);
void* searchGledano(FILM*);
void selectionSortGodinaUzl(FILM*);
void selectionSortGodinaSil(FILM*);
void subZaSortUzl(FILM*, FILM*);
void subZaSortSil(FILM*, FILM*);
void brisanjeFilma(FILM*);
void izlaz();

#endif /* FUNKCIJE_H */
