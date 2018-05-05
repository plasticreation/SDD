#include<iostream>
using namespace std;

struct Persoana {
	char* nume;
	int varsta;

};

struct nod {
	Persoana info;
	nod* next; //adresa urmatorului nod
};

Persoana crearePersoana(char* nume, int varsta) {
	Persoana p;
	p.nume = (char*)malloc(sizeof(char)*strlen(nume) + 1);
	strcpy(p.nume, nume);
	p.varsta = varsta;

	return p;
}

nod* inserareInceput(nod* cap, Persoana persoana) { //in lista //s3
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearePersoana(persoana.nume, persoana.varsta);
	nou->next = cap;

	return nou;
}

nod* inserareSfarsit(nod* cap, Persoana persoana) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearePersoana(persoana.nume, persoana.varsta);
	nou->next = NULL;
	if (cap) {
		nod* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		
		return nou;
	}
}

nod* inserarePePozitie(nod* cap, Persoana persoana, int pozitie) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearePersoana(persoana.nume, persoana.varsta);
	
	if (cap) {
		if (pozitie == 1) {
			cap = inserareInceput(cap, persoana);
		}
		else {
			int contor = 1;
			nod* p = cap;

			while (p->next && contor < pozitie - 1) {
				p = p->next;
				contor++;
			}

			nou->next = p->next;
			p->next = nou;
			return cap;
		}
		
	}
	else {
		nou->next = NULL;
		return nou;
	}
}


nod* inserareSortata(nod* cap, Persoana persoana) {
	if (cap) {
		if (persoana.varsta < cap->info.varsta) {
			cap = inserareInceput(cap, persoana);
		}
		else {
			nod* p = cap;
			
			while (p->next && p->next->info.varsta < persoana.varsta) {
				p = p->next;
			}
			p->next = inserareInceput(p->next, persoana);
		}
	}
	else {
		cap = inserareInceput(NULL, persoana); //cap in loc de null
	}

	return cap;
}

void afisareLista(nod* cap) {
	nod* p = cap;

	while (p) {
		printf("%s are %d ani \n", p->info.nume, p->info.varsta);
		p = p->next;
	}
}

nod* stergereLista(nod* cap) {
	while (cap) {
		free(cap->info.nume);
		nod* p = cap;
		cap = cap->next;
		free(p);
	}
	return NULL;
}


//sau
void stergeListaDubluPointer(nod* *cap) {
	while (*cap) {
		free((*cap)->info.nume);
		nod* p = *cap;
		*cap = (*cap)->next;
		free(p);
	}
}


void main() {
	nod* lista = NULL;

	Persoana p = crearePersoana("Maria", 12);
	lista = inserareInceput(lista, p);

	Persoana p2 = crearePersoana("Ana", 11);
	lista = inserareSfarsit(lista,p2);


	afisareLista(lista);
	printf("\n\n");

	p2.varsta= 9;
	inserareSfarsit(lista, p2);
	afisareLista(lista);
	printf("\n\n");


	lista = stergereLista(lista);

	lista = inserareSfarsit(lista, p2);
	afisareLista(lista);
	printf("\n\n");

	stergeListaDubluPointer(&lista);

	Persoana p3 = crearePersoana("Marius",10 );
	lista = inserarePePozitie(lista, p, 2);
	lista = inserarePePozitie(lista, p2, 3);
	lista = inserarePePozitie(lista, p3, 1);

	afisareLista(lista);
	printf("\n\n");


	lista = stergereLista(lista);
	
	lista = inserareSortata(lista, p);
	lista = inserareSortata(lista, p2);
	lista = inserareSortata(lista, p3);

	afisareLista(lista);
	printf("\n\n");

	stergeListaDubluPointer(&lista);

}