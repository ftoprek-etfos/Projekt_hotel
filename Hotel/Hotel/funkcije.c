#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strukture.h"
#include "funkcije.h"
#include <ctype.h>
static int brojRezervacija = 0;
static int sobe[10] = {0,0,0,0,0,0,0,0,0,0};

char* toLower(char* str)
{
	for (int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}

	return str;
}
void unosRezervacija(const char* const imeDatoteke) {
	FILE* pF = fopen(imeDatoteke, "rb+");
	if (pF == NULL) {
		perror("Dodavanje rezervacije u datoteku data.bin");
		exit(EXIT_FAILURE);
	}
	fread(&brojRezervacija, sizeof(int), 1, pF);
	printf("Broj rezervacije : %d\n", brojRezervacija);
	REZERVACIJA temp = { 0 };
	temp.id = brojRezervacija;
	getchar();
	printf("Unesite ime gosta!\n");
	scanf("%19[^\n]", temp.ime_gosta);
	strcpy(temp.ime_gosta, toLower(temp.ime_gosta));
	printf("Unesite prezime gosta!\n");
	getchar();
	scanf("%19[^\n]", temp.prezime_gosta);
	strcpy(temp.prezime_gosta, toLower(temp.prezime_gosta));
	printf("Unesite broj sobe!\n");
	getchar();
	scanf("%d", &temp.brojSobe);
	for (int i = brojRezervacija; i >= 0; i--)
	{
		while (sobe[i] == temp.brojSobe)
		{
			printf("Soba broj %d je zauzeta, unesite drugi broj sobe!\n",temp.brojSobe);
			scanf("%d", &temp.brojSobe);
		} 
	}
	sobe[brojRezervacija] = temp.brojSobe;
	fseek(pF, sizeof(REZERVACIJA) * brojRezervacija, SEEK_CUR);
	fwrite(&temp, sizeof(REZERVACIJA), 1, pF);
	rewind(pF);
	brojRezervacija++;
	fwrite(&brojRezervacija, sizeof(int), 1, pF);
	fseek(pF, sizeof(int)* brojRezervacija, SEEK_END);
	fwrite(&sobe, sizeof(int) * brojRezervacija, 1, pF);
	fclose(pF);
}
void* ucitavanjeRezervacija(const char* const imeDatoteke) {
	FILE* pF = fopen(imeDatoteke, "rb");
	if (pF == NULL) {
		perror("Ucitavanje rezervacija iz datoteke data.bin");
		return NULL;
		//exit(EXIT_FAILURE);
	}
	fread(&brojRezervacija, sizeof(int), 1, pF);
	printf("Broj Rezervacije: %d\n", brojRezervacija);
	REZERVACIJA* poljeRezervacija = (REZERVACIJA*)calloc(brojRezervacija, sizeof(REZERVACIJA));
	if (poljeRezervacija == NULL) {
		perror("Zauzimanje memorije za rezervacije");
		return NULL;
	}
	fseek(pF, sizeof(int), SEEK_SET);
	fread(poljeRezervacija, sizeof(REZERVACIJA), brojRezervacija, pF);
	fseek(pF, sizeof(int), SEEK_END);
	fread(&sobe, sizeof(int)*brojRezervacija, 1, pF);
	fclose(pF);
	return poljeRezervacija;
}
void ispisivanjeRezervacija(const REZERVACIJA* const poljeRezervacija) {
	if (poljeRezervacija == NULL) {
		printf("Polje rezervacija je prazno!\n");
		return;
	}
	int i;
	for (i = 0; i < brojRezervacija; i++)
	{
		printf("Gost broj %d\tID gosta: %d\time gosta: %s\tprezime gosta: %s\tbroj sobe: %d\t\n",
			i + 1,
			poljeRezervacija[i].id,
			poljeRezervacija[i].ime_gosta,
			poljeRezervacija[i].prezime_gosta,
			poljeRezervacija[i].brojSobe);
	}
}
void* pretrazivanjeRezervacija(REZERVACIJA* const poljeRezervacija) {
	if (poljeRezervacija == NULL) {
		printf("Polje rezervacija je prazno!\n");
		return NULL;
	}
	int i;
	int trazenaSoba;
	printf("Unesite broj sobe.\n");
	getchar();
	scanf("%d", &trazenaSoba);
	if (isalpha(trazenaSoba))
	{
		printf("Unjeli ste znak umjesto broja sobe!");
		return NULL;
	}
	for (i = 0; i < brojRezervacija; i++)
	{
		if (trazenaSoba == poljeRezervacija[i].brojSobe) {
			printf("Rezervacija je pronadena!\n");
			return &poljeRezervacija[i];
		}
	}
	return NULL;
}
int izlazIzPrograma(REZERVACIJA* poljeRezervacija) {
	free(poljeRezervacija);
	return 0;
}
void brisanjeRezervacija(REZERVACIJA** const rezervacijaZaBrisanje, REZERVACIJA* const poljeRezervacija, const char* imeDatoteke){
	if (poljeRezervacija == NULL) {
		printf("Polje rezervacija je prazno!\n");
		return;
	}
	if (rezervacijaZaBrisanje == NULL)
	{
		printf("Molimo pretrazite rezervaciju koju zelite obrisati.\n");
		return NULL;
	}
	FILE* pF = fopen(imeDatoteke, "wb");
	if (pF == NULL) {
		perror("Brisanje studenta iz datoteke studenti.bin");
		exit(EXIT_FAILURE);
	}
	fseek(pF, sizeof(int), SEEK_SET);
	int i;
	int noviBrojac = 0;
	for (i = 0; i < brojRezervacija; i++)
	{
		if (*rezervacijaZaBrisanje !=	(poljeRezervacija + i)) {
			fwrite((poljeRezervacija + i), sizeof(REZERVACIJA), 1, pF);
			noviBrojac++;
		}
	}
	rewind(pF);
	fwrite(&noviBrojac, sizeof(int), 1, pF);
	fclose(pF);
	printf("Rezervacija obrisana.\n");
	*rezervacijaZaBrisanje = NULL;
}
void azuriranjeRezervacija(REZERVACIJA* const rezervacijaZaAzuriranje, REZERVACIJA* const poljeRezervacija, const char* imeDatoteke) {
	if (poljeRezervacija == NULL) {
		printf("Polje rezervacija je prazno!\n");
		return;
	}
	if (rezervacijaZaAzuriranje == NULL)
	{
		printf("Molimo pretrazite rezervaciju koju zelite azurirati.\n");
		return NULL;
	}
	FILE* pF = fopen(imeDatoteke, "rb+");
	if (pF == NULL) {
		perror("Azuriranje rezervacije nije moguce\n");
		exit(EXIT_FAILURE);
	}
	fseek(pF, sizeof(REZERVACIJA) * rezervacijaZaAzuriranje->id, SEEK_CUR);
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	printf("\t\t\tOpcija 1: Azuriranje imena gosta!\n");
	printf("\t\t\tOpcija 2: Azuriranje prezimena gosta!\n");
	printf("\t\t\tOpcija 3: Azuriranje broja sobe!\n");
	printf("======================================\
======================================\n");
	int uvijet = 0;
	scanf("%d", &uvijet);
	switch (uvijet) {
	case 1:
		getchar();
		scanf("%19[^\n]", rezervacijaZaAzuriranje->ime_gosta);
		break;
	case 2:
		getchar();
		scanf("%19[^\n]", rezervacijaZaAzuriranje->prezime_gosta);
		break;
	case 3:
		getchar();
		scanf("%d", &rezervacijaZaAzuriranje->brojSobe);
		break;
	default:
		uvijet = 0;
	}
	fwrite(rezervacijaZaAzuriranje, sizeof(REZERVACIJA), 1, pF);
	fclose(pF);
}
void brisanjeDatoteke(const char* imeDatoteke)
{
	if (remove("data.bin") == 0) {
		printf("Datoteka obrisana.\n");
	}
	else {
		printf("Datoteka nije obrisana ili ne postoji.\n");
	}
}