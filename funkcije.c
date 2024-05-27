#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

static int brojFilmova = 0;
static int i;

void izbornik() {

	char izbor[4];
	FILM* polje = NULL;

	printf("\n######## IZBORNIK ########\n");
	printf("1. Unos novog filma\n");
	printf("2. Uredi podatke o filmu\n");
	printf("3. Ispis filmova\n");
	printf("4. Pretrazivanje filmova\n");
	printf("5. Sortiranje filmova\n");
	printf("6. Brisanje filma\n");
	printf("7. Izlaz\n");
	printf("##########################\n");
	printf("\nIzbor: ");

	do {
		if (fgets(izbor, sizeof(izbor), stdin) == NULL) {
			continue;
		}

		if (strchr(izbor, '\n') == NULL) {
			ocistiBuffer();
		}

		if (strlen(izbor) != 2 || (izbor[0] < '1' || izbor[0] > '7')) {
			printf("\nNepoznata opcija, molimo odaberite ponovno: ");
			continue;
		}

		if ((izbor[0] == '1' || izbor[0] == '2' || izbor[0] == '3' || izbor[0] == '4' || izbor[0] == '5' || izbor[0] == '6' || izbor[0] == '7')) {
			break;
		}

	} while (1);
	
	system("cls");

	switch (izbor[0]) {
	case '1':
		if (brojFilmova == 0) {
			kreiranjeDat();
		}
		unesiFilm();
		break;

	case '2':
		polje = ucitajFilm();
		if (polje != NULL) {
			urediPodatke(polje);
			free(polje);
		}
		break;

	case '3':
		polje = ucitajFilm();
		if (polje != NULL) {
			ispisiFilm(polje);
			free(polje);
		}
		break;

	case '4':
		polje = ucitajFilm();
		if (polje != NULL) {
			izbornikPret(polje);
		}
		free(polje);
		break;

	case '5':
		polje = ucitajFilm();
		if (polje != NULL) {
			izbornikSort(polje);
			free(polje);
		}
		break;

	case '6':
		polje = ucitajFilm();
		if (polje != NULL) {
			brisanjeFilma(polje);
			free(polje);
		}
		break;

	case '7':
		izlaz();
		break;

	default:
		printf("Nepoznata opcija, molimo odaberite ponovno.\n");
	}


}

void izbornikPret(FILM* polje) {

	char izbor[4];

	printf("\n### Pretrazivanje ###\n");
	printf("1. Naslov\n");
	printf("2. Godina\n");
	printf("3. Zanr\n");
	printf("4. Pogledani filmovi\n");
	printf("5. Natrag\n");
	printf("#####################\n");
	printf("\nIzbor: ");

	do {
		if (fgets(izbor, sizeof(izbor), stdin) == NULL) {
			continue;
		}

		if (strchr(izbor, '\n') == NULL) {
			ocistiBuffer();
		}

		if (strlen(izbor) != 2 || (izbor[0] < '1' || izbor[0] > '5')) {
			printf("\nNepoznata opcija, molimo odaberite ponovno: ");
			continue;
		}

		if ((izbor[0] == '1' || izbor[0] == '2' || izbor[0] == '3' || izbor[0] == '4' || izbor[0] == '5')) {
			break;
		}

	} while (1);

	system("cls");

	switch (izbor[0]) {
	case '1':
		searchNaslov(polje);
		break;

	case '2':
		searchGodina(polje);
		break;

	case '3':
		searchZanr(polje);
		break;

	case '4':
		searchGledano(polje);
		break;

	case '5':
		return;

	default:
		printf("Nepoznata opcija, molimo odaberite ponovno.\n");
	}

}

void izbornikSort(FILM* polje) {

	char izbor[4];

	printf("\n### Sortiraj po: ###\n");
	printf("1. Godini uzlazno\n");
	printf("2. Godini silazno\n");
	printf("3. Natrag\n");
	printf("####################\n");
	printf("\nIzbor: ");

	do {
		if (fgets(izbor, sizeof(izbor), stdin) == NULL) {
			continue;
		}

		if (strchr(izbor, '\n') == NULL) {
			ocistiBuffer();
		}

		if (strlen(izbor) != 2 || (izbor[0] < '1' || izbor[0] > '3')) {
			printf("\nNepoznata opcija, molimo odaberite ponovno: ");
			continue;
		}

		if ((izbor[0] == '1' || izbor[0] == '2' || izbor[0] == '3')) {
			break;
		}

	} while (1);

	system("cls");

	switch (izbor[0]) {
	case 1:
		selectionSortGodinaUzl(polje);
		break;

	case 2:
		selectionSortGodinaSil(polje);
		break;

	case 3:
		return;

	default:
		printf("Nepoznata opcija, molimo odaberite ponovno.\n");
	}
}

void kreiranjeDat() {

	FILE* fp = fopen("filmovi.txt", "w");

	if (fp == NULL) {
		perror("Greska pri otvaranju datoteke");
		exit(1);
	}

	fclose(fp);

}

void unesiFilm() {

	FILE* fp = fopen("filmovi.txt", "a");
	if (fp == NULL) {
		perror("Neuspjesni unos");
		exit(1);
	}

	FILM noviFilm;

	printf("Unesite naslov filma: ");
	scanf(" %[^\n]", noviFilm.naslov);

	printf("Unesite godinu izdanja filma: ");
	scanf("%d", &noviFilm.godina);

	printf("Unesite zanr filma: ");
	scanf(" %[^\n]", noviFilm.zanr);

	printf("Unesite je li film pogledan (da/ne): ");
	scanf(" %s", noviFilm.gledano);

	fprintf(fp, "%s,%d,%s,%s\n", noviFilm.naslov, noviFilm.godina, noviFilm.zanr, noviFilm.gledano);

	fclose(fp);

	printf("Film uspjesno dodan.\n");

}

void* ucitajFilm() {

	FILE* fp = fopen("filmovi.txt", "r");
	if (fp == NULL) {
		perror("Nema unesenih filmova\n");
		return NULL;
	}

	brojFilmova = 0;
	char ch;
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n') {
			brojFilmova++;
		}
	}
	rewind(fp);

	FILM* polje = (FILM*)malloc(brojFilmova * sizeof(FILM));
	if (polje == NULL) {
		perror("Neuspjesno zauzimanje memorije");
		fclose(fp);
		return NULL;
	}

	int i = 0;
	while (i < brojFilmova && fscanf(fp, " %99[^,],%d,%49[^,],%3s\n", polje[i].naslov, &polje[i].godina, polje[i].zanr, polje[i].gledano) == 4) {
		i++;
	}

	fclose(fp);
	return polje;

}

void urediPodatke(FILM* polje) {

	int id;
	printf("Unesite ID filma koji zelite urediti: ");
	scanf("%d", &id);

	if (id < 1 || id > brojFilmova) {
		printf("Neispravan ID filma.\n");
		return;
	}

	FILM* film = &polje[id - 1];

	printf("\nFilm koji zelite urediti:\n");
	printf("\tNaslov: %s\n", film->naslov);
	printf("\tGodina: %d\n", film->godina);
	printf("\tZanr: %s\n", film->zanr);
	printf("\tGledano: %s\n\n", film->gledano);

	printf("Unesite nove podatke za film:\n");
	printf("\tNaslov: ");
	scanf(" %[^\n]", film->naslov);
	printf("\tGodina: ");
	scanf("%d", &film->godina);
	printf("\tZanr: ");
	scanf(" %[^\n]", film->zanr);
	printf("\tGledano (da/ne): ");
	scanf(" %[^\n]", film->gledano);

	FILE* fp = fopen("filmovi.txt", "w");
	if (fp == NULL) {
		perror("Neuspjesno otvaranje datoteke");
		return;
	}

	for (int i = 0; i < brojFilmova; i++) {
		fprintf(fp, "%s,%d,%s,%s\n", polje[i].naslov, polje[i].godina, polje[i].zanr, polje[i].gledano);
	}

	fclose(fp);

	printf("\nPodaci o filmu su azurirani.\n");

}

void ispisiFilm(FILM* polje) {

	if (polje == NULL) {
		printf("Nema unesenih filmova.\n");
		return;
	}

	printf("ID   Naslov                        Godina   Zanr               Gledano\n");
	printf("------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		printf("%-4d %-30s %-7d %-20s  %-4s\n", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
	}

}

void* searchNaslov(FILM* polje) {

	char trazeniNaslov[100];
	int br = 0;

	printf("Unesite naslov trazenog filma: ");
	getchar();
	scanf(" %[^\n]", trazeniNaslov);

	printf("\nID   Naslov                        Godina   Zanr               Gledano\n");
	printf("------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		if (strcmp(trazeniNaslov, (polje + i)->naslov) == 0) {
			printf("%-4d %-30s %-7d %-20s  %s\n", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
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

	printf("Unesite godinu koju trazite: ");
	scanf("%d", &trazenaGodina);

	printf("\nID   Naslov                        Godina   Zanr               Gledano\n");
	printf("------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		if (trazenaGodina == (polje + i)->godina) {
			printf("%-4d %-30s %-7d %-20s  %s\n", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
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

	printf("Unesite zanr koji trazite: ");
	getchar();
	scanf(" %[^\n]", trazeniZanr);

	printf("\nID   Naslov                        Godina   Zanr               Gledano\n");
	printf("------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		if (strcmp(trazeniZanr, (polje + i)->zanr) == 0) {
			printf("%-4d %-30s %-7d %-20s  %s\n", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
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

	printf("Unesite (da) za pogledane ili (ne) za nepogledane filmove: ");
	getchar();
	scanf(" %[^\n]", trazeniPogIliNepogFilm);

	printf("\nID   Naslov                        Godina   Zanr               Gledano\n");
	printf("------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		if (strcmp(trazeniPogIliNepogFilm, (polje + i)->gledano) == 0) {
			printf("%-4d %-30s %-7d %-20s  %s\n", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
			br++;
		}
	}

	if (br == 0) {
		printf("\nNema unesenih %s filmova.\n", strcmp(trazeniPogIliNepogFilm, "da") == 0 ? "pogledanih" : "nepogledanih");
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

	printf("ID   Naslov                        Godina   Zanr               Gledano\n");
	printf("------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		printf("%-4d %-30s %-7d %-20s  %s", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
		printf("\n");
	}

}

void selectionSortGodinaSil(FILM* polje) {

	for (int j = 0; j < brojFilmova; j++) {
		for (int i = 0; i < brojFilmova - 1; i++) {
			if (polje[i].godina < polje[i + 1].godina) {
				subZaSortSil((polje + i), (polje + i + 1));
			}
		}
	}

	printf("ID   Naslov                        Godina   Zanr               Gledano\n");
	printf("------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		printf("%-4d %-30s %-7d %-20s  %s", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
		printf("\n");
	}

}

inline void subZaSortUzl(FILM* manji, FILM* veci) {

	FILM temp = *manji;
	*manji = *veci;
	*veci = temp;

}

inline void subZaSortSil(FILM* veci, FILM* manji) {

	FILM temp = *veci;
	*veci = *manji;
	*manji = temp;

}

void brisanjeFilma(FILM* polje) {

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

	FILE* fp = fopen("filmovi.txt", "w");
	if (fp == NULL) {
		perror("Pogreska pri otvaranju datoteke.");
		return;
	}

	for (int i = 0; i < brojFilmova; i++) {
		fprintf(fp, "%s,%d,%s,%s\n", polje[i].naslov, polje[i].godina, polje[i].zanr, polje[i].gledano);
	}

	fclose(fp);

	printf("Film je uspješno obrisan.\n");

}

void izlaz() {

	char izbor[3];
	printf("Zelite li izaci iz programa? (da/ne)\n");

	while (1) {
		printf("Odgovor: ");
		scanf(" %s", izbor);
		if (strcmp(izbor, "da") == 0) {
			printf("\nIzlazak iz programa...");
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(izbor, "ne") == 0) {
			system("cls");
			return;
		}
		else {
			printf("\nUnesite 'da' ili 'ne'\n");
		}
	}

}

void ocistiBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);

}
