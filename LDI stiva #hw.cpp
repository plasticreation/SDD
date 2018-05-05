#include<iostream>

//voi folosi stiva deoarece o persoana cand isi cumpara un ceas nou, il va pune langa celelalte insa il va purta pe cel mai nou, aplicand principiul FI-LO

struct Ceas {
	char* forma;
	int pret;
	float greutate;
};

struct nodDublu {
	Ceas info;
	nodDublu* next;
	nodDublu* prev;
};

struct LDI {
	nodDublu* prim;
	nodDublu* ult;
};

nodDublu* creareNodDublu(Ceas info, nodDublu* next, nodDublu* prev) {
	nodDublu* nodNou = (nodDublu*)malloc(sizeof(nodDublu));
	nodNou->info = creareCeas(info.forma, info.pret, info.greutate);
	nodNou->next = next;
	nodNou->prev = prev;
	return nodNou;
}

Ceas creareCeas(char* forma, int pret, float greutate) {
	Ceas ceas;
	ceas.forma = (char*)malloc(sizeof(char)*strlen(forma) + 1);
	strcpy(ceas.forma, forma);
		ceas.pret = pret;
	ceas.greutate = greutate;
	return ceas;
}

void afisareCeas(Ceas ceas) {
	printf("Ceasul %s costa %d lei si are greutatea %5.2f grame.\n", ceas.forma, ceas.pret, ceas.greutate);
}



LDI inserareInceput(LDI lista, Ceas info) {
	nodDublu* nodNou = creareNodDublu(info, lista.prim, NULL);
	if (lista.prim) {
		lista.prim->prev = nodNou;
		lista.prim = nodNou;
	}
	else {
		lista.prim = nodNou;
		lista.ult = nodNou;

	}
	return lista;
}


void afisareListaDublaCapCoada(LDI lista) {
	nodDublu* p = lista.prim;
	printf("\n");
	while (p) {
		afisareCeas(p->info);
		p = p->next;
	}
}

void stergereLista(LDI* lista) {
	while (lista->prim) {
		nodDublu* p = lista->prim;
		lista->prim = lista->prim->next;
		free(p->info.forma);
		free(p);
	}
	lista->ult = NULL;
}



LDI pushStack(LDI stiva, Ceas info) {
	stiva = inserareInceput(stiva, info);
	return stiva;
}

Ceas popStack(nodDublu* *stiva) {
	Ceas ceas;
	if (*stiva) {
		ceas = creareCeas((*stiva)->info.forma, (*stiva)->info.pret, (*stiva)->info.greutate);
		nodDublu* aux = *stiva;
		*stiva = (*stiva)->next;
		free(aux->info.forma);
		free(aux);
		return ceas;
	}
	else {
		ceas.forma = NULL;
		ceas.pret = 0;
		ceas.greutate = -1;
		return ceas;
	}

}


void main() {
	/*
	LDI lista;
	lista.prim = lista.ult = NULL;

	lista = inserareInceput(lista, creareCeas("Rotund", 120, 120.3));
	lista = inserareInceput(lista, creareCeas("Patrat", 530, 157.6));
	lista = inserareInceput(lista, creareCeas("Oval", 985, 210.7));

	printf("\nAfisare lista dubla inlantuita:\n");
	afisareListaDublaCapCoada(lista);
	stergereLista(&lista);
	*/
	
	LDI stiva;
	stiva.prim = stiva.ult = NULL;

	stiva = pushStack(stiva, creareCeas("ROTUND", 120, 120.3));
	stiva = pushStack(stiva, creareCeas("PATRAT", 530, 157.6));
	stiva = pushStack(stiva, creareCeas("OVAL", 985, 210.7));

	printf("\nAfisare stiva:\n");
	while (stiva.prim) {
		Ceas c = popStack(&(stiva.prim));
		afisareCeas(c);
		free(c.forma);
	}


	stergereLista(&stiva);




}