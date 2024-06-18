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

	printf("%s", pocetniTekst);

	while (1) {
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
				polje = NULL;
			}
			break;

		case '3':
			polje = ucitajFilm();
			if (polje != NULL) {
				ispisiFilm(polje);
				free(polje);
				polje = NULL;
			}
			break;

		case '4':
			polje = ucitajFilm();
			if (polje != NULL) {
				izbornikPret(polje);
				free(polje);
				polje = NULL;
			}
			break;

		case '5':
			polje = ucitajFilm();
			if (polje != NULL) {
				izbornikSort(polje);
				free(polje);
				polje = NULL;
			}
			break;

		case '6':
			polje = ucitajFilm();
			if (polje != NULL) {
				brisanjeFilma(polje);
				free(polje);				
				polje = NULL;
			}
			break;

		case '7':
			izlaz();
			break;

		default:
			printf("Nepoznata opcija, molimo odaberite ponovno.\n");
		}
	}

}

void izbornikPret(FILM* polje) {

	if (polje == NULL) {
		printf("Nema unesenih filmova.\n");
		return;
	}

	char izbor[4];

	while (1) {
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

}

void izbornikSort(FILM* polje) {

	if (polje == NULL) {
		printf("Nema unesenih filmova.\n");
		return;
	}
	char izbor[4];

	while (1) {
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
		case '1':
			selectionSortGodinaUzl(polje);
			break;

		case '2':
			selectionSortGodinaSil(polje);
			break;

		case '3':
			return;

		default:
			printf("Nepoznata opcija, molimo odaberite ponovno.\n");
		}
	}

}

void kreiranjeDat() {

	FILE* fp = fopen("filmovi.txt", "w");

	if (fp == NULL) {
		perror("Greska pri otvaranju datoteke");
		exit(1);
	}

	if (fclose(fp) != 0) {
		perror("Greška pri zatvaranju datoteke");
	}

}

void unesiFilm() {

	FILE* fp = fopen("filmovi.txt", "a");
	if (fp == NULL) {
		perror("Neuspjesni unos");
		exit(1);
	}

	FILM noviFilm;
	int validUnos;

	printf("Unesite naslov filma (max 49 znakova): ");
	if (scanf(" %49[^\n]", noviFilm.naslov) != 1) {
		printf("Greska pri unosu naslova.\n");
		return;
	}
	ocistiBuffer();

	do {
		printf("Unesite godinu izdanja filma: ");
		validUnos = scanf("%d", &noviFilm.godina);
		ocistiBuffer();

		if (validUnos != 1 || validUnos > 9999) {
			printf("\nNeispravan unos godine izdanja.\n");
		}
		else if (noviFilm.godina > 9999) {
			printf("\nNeispravan unos godine izdanja.\n");
		}
	} while (validUnos != 1 || noviFilm.godina > 9999);

	printf("Unesite zanr filma (max 29 znakova): ");
	if (scanf(" %29[^\n]", noviFilm.zanr) != 1) {
		printf("Greska pri unosu zanra.\n");
		return;
	}
	ocistiBuffer();

	do {
		printf("Unesite je li film pogledan (da/ne): ");
		validUnos = scanf(" %3s", noviFilm.gledano);
		ocistiBuffer();
		
		if (validUnos != 1 || (strcmp(noviFilm.gledano, "da") != 0 && strcmp(noviFilm.gledano, "ne") != 0)) {
			printf("\nNeispravan unos statusa pogledanosti filma.\n");
		}
	} while (validUnos != 1 || (strcmp(noviFilm.gledano, "da") != 0 && strcmp(noviFilm.gledano, "ne") != 0));

	fprintf(fp, "%s,%d,%s,%s\n", noviFilm.naslov, noviFilm.godina, noviFilm.zanr, noviFilm.gledano);

	if (fclose(fp) != 0) {
		perror("Greska pri zatvaranju datoteke");
	}

	printf("\nFilm uspjesno dodan.\n");
	return;
	ocistiBuffer();

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

	while (i < brojFilmova && fscanf(fp, " %49[^,],%d,%29[^,],%3s\n", polje[i].naslov, &polje[i].godina, polje[i].zanr, polje[i].gledano) == 4) {
		i++;
	}

	if (fclose(fp) != 0) {
		perror("Greska pri zatvaranju datoteke");
	}

	return polje;

}

void urediPodatke(FILM* polje) {

	if (polje == NULL) {
		printf("Greska: NULL pokazivac na polje filmova.\n");
		return;
	}

	int id;
	printf("Unesite ID filma koji zelite urediti: ");
	if (scanf("%d", &id) != 1) {
		printf("Greska pri unosu ID-a.\n");
		return;
	}

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
	int validUnos;

	printf("\tNaslov: ");
	if (scanf(" %49[^\n]", film->naslov) != 1) {
		printf("Greska pri unosu novog naslova.\n");
		return;
	}

	do {
		printf("\tGodina: ");
		validUnos = scanf("%d", &film->godina);
		ocistiBuffer();

		if (validUnos != 1 || validUnos > 9999) {
			printf("\nNeispravan unos godine izdanja.\n");
		}
		else if (film->godina > 9999) {
			printf("\nNeispravan unos godine izdanja.\n");
		}
	} while (validUnos != 1 || film->godina > 9999);

	printf("\tZanr: ");
	if (scanf(" %29[^\n]", film->zanr) != 1) {
		printf("Greska pri unosu novog zanra.\n");
		return;
	}

	do {
		printf("\tGledano (da/ne): ");
		validUnos = scanf(" %3s", film->gledano);
		ocistiBuffer();

		if (validUnos != 1 || (strcmp(film->gledano, "da") != 0 && strcmp(film->gledano, "ne") != 0)) {
			printf("\nNeispravan unos statusa pogledanosti filma.\n");
		}
	} while (validUnos != 1 || (strcmp(film->gledano, "da") != 0 && strcmp(film->gledano, "ne") != 0));

	FILE* fp = fopen("filmovi.txt", "w");
	if (fp == NULL) {
		perror("Neuspjesno otvaranje datoteke");
		return;
	}

	for (int i = 0; i < brojFilmova; i++) {
		fprintf(fp, "%s,%d,%s,%s\n", polje[i].naslov, polje[i].godina, polje[i].zanr, polje[i].gledano);
	}

	if (fclose(fp) != 0) {
		perror("Greska pri zatvaranju datoteke");
	}

	printf("\nPodaci o filmu su azurirani.\n");

}

void ispisiFilm(FILM* polje) {

	if (polje == NULL) {
		printf("Nema unesenih filmova.\n");
		return;
	}

	printf("ID   Naslov                                            Godina   Zanr                          Gledano\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		printf("%-4d %-50s %-7d %-30s  %-4s\n", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
	}

}

void* searchNaslov(FILM* polje) {
	
	if (polje == NULL) {
		printf("Greska: NULL pokazivac na polje filmova.\n");
		return NULL;
	}

	char trazeniNaslov[50];
	int br = 0;

	printf("Unesite naslov trazenog filma: ");
	fgets(trazeniNaslov, sizeof(trazeniNaslov), stdin);
	trazeniNaslov[strcspn(trazeniNaslov, "\n")] = '\0';

	printf("ID   Naslov                                            Godina   Zanr                          Gledano\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < brojFilmova; i++) {
		if (strstr(polje[i].naslov, trazeniNaslov) != NULL) {
			printf("%-4d %-50s %-7d %-30s  %s\n", i + 1, polje[i].naslov, polje[i].godina, polje[i].zanr, polje[i].gledano);
			br++;
		}
	}

	if (br == 0) {
		printf("\nFilm pod unesenim naslovom nije pronaden.\n");
	}

	return NULL;
}

void* searchGodina(FILM* polje) {

	if (polje == NULL) {
		printf("Greska: NULL pokazivac na polje filmova.\n");
		return NULL;
	}

	int trazenaGodina;
	int br = 0;

	printf("Unesite godinu koju trazite: ");
	if (scanf("%d", &trazenaGodina) != 1) {
		printf("Greska pri unosu godine.\n");
		ocistiBuffer();
		return NULL;
		ocistiBuffer();
	}

	printf("ID   Naslov                                            Godina   Zanr                          Gledano\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		if (trazenaGodina == (polje + i)->godina) {
			printf("%-4d %-50s %-7d %-30s  %s\n", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
			br++;
		}
	}

	if (br == 0) {
		printf("\nTrazena godina nije pronadena.\n");
	}

	ocistiBuffer();
	return NULL;

}

void* searchZanr(FILM* polje) {

	if (polje == NULL) {
		printf("Greska: NULL pokazivac na polje filmova.\n");
		return NULL;
	}

	char trazeniZanr[30];
	int br = 0;

	printf("Unesite zanr koji trazite: ");
	fgets(trazeniZanr, sizeof(trazeniZanr), stdin);
	trazeniZanr[strcspn(trazeniZanr, "\n")] = '\0';

	printf("ID   Naslov                                            Godina   Zanr                          Gledano\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < brojFilmova; i++) {
		if (strstr(polje[i].zanr, trazeniZanr) != NULL) {
			printf("%-4d %-50s %-7d %-30s  %s\n", i + 1, polje[i].naslov, polje[i].godina, polje[i].zanr, polje[i].gledano);
			br++;
		}
	}

	if (br == 0) {
		printf("\nFilm sa ovim zanrom nije pronaden.\n");
	}

	return NULL;

}

void* searchGledano(FILM* polje) {

	if (polje == NULL) {
		printf("Greska: NULL pokazivac na polje filmova.\n");
		return NULL;
	}

	char trazeniPogIliNepogFilm[4];
	int br = 0;

	printf("Unesite (da) za pogledane ili (ne) za nepogledane filmove: ");
	fgets(trazeniPogIliNepogFilm, sizeof(trazeniPogIliNepogFilm), stdin);
	trazeniPogIliNepogFilm[strcspn(trazeniPogIliNepogFilm, "\n")] = '\0';

	if (strlen(trazeniPogIliNepogFilm) != 2 || strcmp(trazeniPogIliNepogFilm, "da") != 0 && strcmp(trazeniPogIliNepogFilm, "ne") != 0) {
        printf("Greska pri unosu.\n");
        return NULL;
    }

	printf("ID   Naslov                                            Godina   Zanr                          Gledano\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		if (strcmp(trazeniPogIliNepogFilm, (polje + i)->gledano) == 0) {
			printf("%-4d %-50s %-7d %-30s  %s\n", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
			br++;
		}
	}

	if (br == 0) {
		printf("\nNema unesenih %s filmova.\n", strcmp(trazeniPogIliNepogFilm, "da") == 0 ? "pogledanih" : "nepogledanih");
	}
	
	return NULL;
	
}

void selectionSortGodinaUzl(FILM* polje) {

	if (polje == NULL) {
		printf("Greska: NULL pokazivac na polje filmova.\n");
		return;
	}

	for (int j = 0; j < brojFilmova; j++) {
		for (int i = 0; i < brojFilmova - 1; i++) {
			if (polje[i].godina > polje[i + 1].godina) {
				subZaSortUzl((polje + i), (polje + i + 1));
			}
		}
	}

	printf("ID   Naslov                                            Godina   Zanr                          Gledano\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		printf("%-4d %-50s %-7d %-30s  %s", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
		printf("\n");
	}

}

void selectionSortGodinaSil(FILM* polje) {

	if (polje == NULL) {
		printf("Greska: NULL pokazivac na polje filmova.\n");
		return;
	}

	for (int j = 0; j < brojFilmova; j++) {
		for (int i = 0; i < brojFilmova - 1; i++) {
			if (polje[i].godina < polje[i + 1].godina) {
				subZaSortSil((polje + i), (polje + i + 1));
			}
		}
	}

	printf("ID   Naslov                                            Godina   Zanr                          Gledano\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	for (i = 0; i < brojFilmova; i++) {
		printf("%-4d %-50s %-7d %-30s  %s", i + 1, (polje + i)->naslov, (polje + i)->godina, (polje + i)->zanr, (polje + i)->gledano);
		printf("\n");
	}

}

inline void subZaSortUzl(FILM* manji, FILM* veci) {

	if (manji == NULL || veci == NULL) {
		printf("Greska: NULL pokazivac na film.\n");
		return;
	}

	FILM temp = *manji;
	*manji = *veci;
	*veci = temp;

}

inline void subZaSortSil(FILM* veci, FILM* manji) {

	if (veci == NULL || manji == NULL) {
		printf("Greska: NULL pokazivac na film.\n");
		return;
	}

	FILM temp = *veci;
	*veci = *manji;
	*manji = temp;

}

void brisanjeFilma(FILM* polje) {

	if (polje == NULL) {
		printf("Greska: NULL pokazivac na polje filmova.\n");
		return;
	}

	int id;
	printf("Unesite ID filma koji zelite izbrisati: ");
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

	if (fclose(fp) != 0) {
		perror("Greska pri zatvaranju datoteke");
	}

	printf("Film je uspjesno obrisan.\n");
	ocistiBuffer();

}

void izlaz() {

	char izbor[50];
	printf("Zelite li izaci iz programa? (da/ne)\n");
	printf("Odgovor: ");

	if (scanf("%s", &izbor) != 1) {
		printf("Greska pri unosu izbora.\n");
		return NULL;
	}

	if (strcmp(izbor, "da") == 0) {
		system("cls");
		brisanjeDat();
		return;
	}
	else if (strcmp(izbor, "ne") == 0) {
		system("cls");
		ocistiBuffer();
		return;
	}
	else {
		printf("\nUnesite 'da' ili 'ne'\n");
		izlaz();
	}

}

void brisanjeDat() {

	char izbor[50];
	printf("Zelite li izbrisati datoteku filmovi.txt? (da/ne)\n");
	printf("Odgovor: ");

	if (scanf("%s", &izbor) != 1) {
		printf("Greska pri unosu izbora.\n");
		return NULL;
	}

	if (strcmp(izbor, "da") == 0) {
		if (remove("filmovi.txt") == 0) {
			printf("\nDatoteka je uspjesno obrisana.\n");
		}
		else {
			perror("Greska pri brisanju datoteke");
		}
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(izbor, "ne") == 0) {
		printf("\nDatoteka nije obrisana.\n");
		exit(EXIT_SUCCESS);
	}
	else {
		printf("\nUnesite 'da' ili 'ne'\n");
		brisanjeDat();
	}

}

void ocistiBuffer() {

	int c;
	while ((c = getchar()) != '\n' && c != EOF);

}
