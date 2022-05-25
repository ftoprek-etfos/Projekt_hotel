#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "funkcije.h"

void postoji();

int main(void) {
	int uvijet = 1;
	char imeDatoteke[9] = "data.bin";
	postoji();
	while (uvijet) {
		uvijet = izbornik(imeDatoteke);
	}
	printf("Zavrsetak programa!\n");
	return 0;
}

void postoji()
{
	FILE* file;

	if (!(file = fopen("data.bin", "rb")))
	{
		file = fopen("data.bin", "wb");
		int temp = 0;
		fwrite(&temp, sizeof(int), 1, file);
	}
	fclose(file);
}