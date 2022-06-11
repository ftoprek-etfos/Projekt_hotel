#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "strukture.h"
#include "funkcije.h"

int izbornik(const char* const imeDatoteke) {
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	printf("\t\t\tOpcija 1: Unos rezervacija!\n");
	printf("\t\t\tOpcija 2: Ucitavanje rezervacija!\n");
	printf("\t\t\tOpcija 3: Brisanje rezervacija!\n");
	printf("\t\t\tOpcija 4: Pretrazivanje rezervacija!\n");
	printf("\t\t\tOpcija 5: Azuriranje rezervacija!\n");
	printf("\t\t\tOpcija 6: Ispisivanje rezervacija!\n");
	printf("\t\t\tOpcija 7: brisanje datoteke!\n");
	printf("\t\t\tOpcija 8: izlaz iz programa!\n");
	printf("======================================\
======================================\n");
	int uvijet = 0;
	static REZERVACIJA* poljeRezervacija = NULL;
	static REZERVACIJA* pronadjenaRezervacija = NULL;
	scanf("%d", &uvijet);
	switch (uvijet) {
	case 1:
		unosRezervacija(imeDatoteke);
		break;
	case 2:
		if (poljeRezervacija != NULL) {
			free(poljeRezervacija);
			poljeRezervacija = NULL;
		}
		poljeRezervacija = (REZERVACIJA*)ucitavanjeRezervacija(imeDatoteke);
		if (poljeRezervacija == NULL) {
			exit(EXIT_FAILURE);
		}
		break;
	case 3:
		brisanjeRezervacija(&pronadjenaRezervacija, poljeRezervacija, imeDatoteke);
		break;
	case 4:
		pronadjenaRezervacija = (REZERVACIJA*)pretrazivanjeRezervacija(poljeRezervacija);
		break;
	case 5:
		azuriranjeRezervacija(pronadjenaRezervacija, poljeRezervacija, imeDatoteke);
		break;
	case 6:
		ispisivanjeRezervacija(poljeRezervacija);
		break;
	case 7:
		brisanjeDatoteke(imeDatoteke);
		break;
	case 8:
		uvijet = izlazIzPrograma(poljeRezervacija);
		break;
	default:
		uvijet = 0;
	}
	return uvijet;
}