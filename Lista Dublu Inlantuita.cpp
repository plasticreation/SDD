#include<iostream>

struct Student {
	char* nume;
	int an;
};

struct nodDublu{
	Student info;
	nodDublu* next;
	nodDublu* prev;
};

struct LDI {
	nodDublu* prim;
	nodDublu* ult;
};

struct nodSimplu {
	Student info;
	nodSimplu* nextSimplu;
};

Student creareStudent(char* nume, int an) {
	Student s;
	s.nume = (char*)malloc(sizeof(char)*strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.an = an;

	return s;
}

nodDublu* creareNodDubllu(Student info, nodDublu* next, nodDublu* prev) {
	nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
	nou->info = creareStudent(info.nume, info.an);
	nou->next = next;
	nou->prev = prev;

	return nou;
}


LDI inserareInceput(LDI lista, Student student) {
	//cream nodul pe care il inseram chiar daca lista exista sau nu
	nodDublu* nou = creareNodDubllu(student, lista.prim, NULL);
	if (lista.prim) {
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	else {
		lista.prim = nou;
		lista.ult = nou;
	}
	return lista;
	
}

LDI inserareSfarsit(LDI lista, Student student) {
	nodDublu* nou = creareNodDubllu(student, NULL, lista.ult);
	if (lista.ult) {
		lista.ult->next = nou;
		lista.ult = nou;
	}
	else {
		lista.prim = nou;
		lista.ult = nou;
	}

	return lista;
}

LDI inserarePePozitie(LDI lista, Student s, int pozitie) {
	if (lista.prim) {
		int k = 1; 
		nodDublu* p = lista.prim;
		
		while (p && k < pozitie) {
			p = p->next;
			k++;
		}
		if (p) {
			nodDublu* nou = creareNodDubllu(s, p, p->prev);
			p->prev = nou;
			if (nou->prev) {
				nou->prev->next = nou;
			}
			else {
				lista.prim = nou;
			}	
		}
		else {
			lista = inserareSfarsit(lista, s);
		}
	}
	else {
		lista = inserareSfarsit(lista, s);
	}

	return lista;
}

void afisareStudent(Student s) {
	printf("Student: %s // anul: %d\n", s.nume, s.an);
}

void afisareCapCoada(LDI lista) {
	nodDublu* p= lista.prim;
	while (p) {
		afisareStudent(p->info);
		p = p->next;
	}
}

void afisareCoadaCap(LDI lista) {
	nodDublu* p = lista.ult;
	while (p) {
		afisareStudent(p->info);
		p = p->prev;
	}
}

void stergereLista(LDI lista) {
	while (lista.prim) {
		nodDublu* aux = lista.prim;
		lista.prim = lista.prim->next;
		free(aux->info.nume);
		free(aux);
	}
	lista.ult = NULL;
}


void main() {
	LDI lista;
	lista.prim = lista.ult = NULL;

	Student s1 = creareStudent("Gigel", 1);
	Student s2 = creareStudent("Ionel", 3);
	Student s3 = creareStudent("Sandel", 2);
	

	lista = inserareInceput(lista, s3);
	lista = inserareInceput(lista, s2);
	lista = inserarePePozitie(lista, s1,2);

	afisareCapCoada(lista);
	printf("\n");
	afisareCoadaCap(lista);
	printf("\n");

	Student s4 = creareStudent("bagat la mijloc", 4);
	lista = inserarePePozitie(lista, s4, 1);

	afisareCapCoada(lista);
	printf("\n");

	stergereLista(lista);

	


}