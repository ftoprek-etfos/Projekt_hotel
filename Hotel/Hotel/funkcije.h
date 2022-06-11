#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "strukture.h"

int izbornik(const char* const);
void unosRezervacija(const char* const);
void* ucitavanjeRezervacija(const char* const);
void brisanjeRezervacija(REZERVACIJA** const, REZERVACIJA* const, const char* const);
void azuriranjeRezervacija(REZERVACIJA* const, REZERVACIJA* const, const char* const);
void ispisivanjeRezervacija(const REZERVACIJA*);
void* pretrazivanjeRezervacija(REZERVACIJA* const);
void brisanjeDatoteke(const char* const);
int izlazIzPrograma(REZERVACIJA*);
#endif