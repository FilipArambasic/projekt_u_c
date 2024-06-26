#define _CRT_SECURE_NO_WARNINGS

#ifndef FUNKCIJE_H
#define FUNKCIJE_H

typedef struct film {
	char naslov[50];
	int godina;
	char zanr[30];
	char gledano[4];
} FILM;

extern char pocetniTekst[];

void izbornik();
void izbornikPret(FILM* polje);
void izbornikSort(FILM* polje);
void kreiranjeDat();
void unesiFilm();
void* ucitajFilm();
void urediPodatke(FILM* polje);
void ispisiFilm(FILM* polje);
void* searchNaslov(FILM* polje);
void* searchGodina(FILM* polje);
void* searchZanr(FILM* polje);
void* searchGledano(FILM* polje);
void bubbleSortGodinaUzl(FILM* polje);
void bubbleSortGodinaSil(FILM* polje);
inline void subZaSortUzl(FILM* manji, FILM* veci);
inline void subZaSortSil(FILM* veci, FILM* manji);
void brisanjeFilma(FILM* polje);
void izlaz();
void brisanjeDat();
void ocistiBuffer();

#endif /* FUNKCIJE_H */
