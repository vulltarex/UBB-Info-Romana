#pragma once

typedef struct {
	int cod, cantitate;
	char tip[50], producator[50], model[50];
	float pret;
}Produs;

Produs creare(int cod, const char* tip, const char* producator, const char* model, float pret, int cantitate);
int egal(Produs p, Produs other);