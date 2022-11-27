#include <stdio.h>
#include <stdlib.h>

typedef struct nodo_{

	int num;
	struct nodo_ *next;

} nodo_t;

void visualizza_lista(nodo_t*);
void visualizza_lista_ricorsiva(nodo_t*);

int lunghezza_lista(nodo_t*);
int lunghezza_lista_ricorsiva(nodo_t*);

nodo_t* cerca(nodo_t*, int);
nodo_t* cerca_ricorsivo(nodo_t*, int);

nodo_t* inserisci_in_testa(nodo_t*, int);
void inserisci_in_testa_no_return(nodo_t** , int);

nodo_t* inserisci_in_coda(nodo_t*, int);
void inserisci_in_coda_no_return(nodo_t**, int);
nodo_t* inserisci_in_coda_ricorsivo(nodo_t*, int);

nodo_t* inserisci_dopo_elemento(nodo_t*, int, int);

nodo_t* sostituisci_elemento_ricorsivo(nodo_t*, int, int);

nodo_t* cancella_in_testa(nodo_t*);
nodo_t* cancella_in_coda(nodo_t*);
nodo_t* cancella_in_coda_ricorsiva(nodo_t*);

nodo_t* cancella_dopo_elemento(nodo_t*, int);
nodo_t* cancella_elemento(nodo_t*, int);
nodo_t* cancella_elemento_ricorsivo(nodo_t*, int);

nodo_t* cancella_ultimo_elemento_uguale(nodo_t*, int);
nodo_t* cancella_in_testa(nodo_t*);

int main(){

	nodo_t *head = NULL;

	nodo_t *cercato;

	head = inserisci_in_coda(head, 1);
	head = inserisci_in_coda(head, 2);
	head = inserisci_in_coda(head, 3);
	head = inserisci_in_coda(head, 4);
	head = inserisci_in_coda(head, 5);
	head = inserisci_in_coda(head, 6);
	head = inserisci_in_coda(head, 7);

	visualizza_lista(head);
	

	return 0;
}

void visualizza_lista(nodo_t *l){ //passo l per valore non per indirizzo

	while(l != NULL){

		printf("\n%d\n", l->num); //l->num  = *p.num con p che punta alla struct l

		l = l->next; //si avanza l'elemento successivo della lista

	}

}

void visualizza_lista_ricorsiva(nodo_t* l){

	if(l==NULL){

		return;

	}else{

		printf("\n%d", l->num);

		visualizza_lista_ricorsiva(l->next);
	}
}

int lunghezza_lista(nodo_t* l){

	int len=0;

	while(l != NULL){

		len++;

		l = l->next;

	}

	return len;

}

int lunghezza_lista_ricorsiva(nodo_t* l){

	if(l==NULL){

		return 0;

	}else{

		return 1 + lunghezza_lista_ricorsiva(l->next);
	}

}

nodo_t* cerca(nodo_t* l, int num){

	while(l != NULL && l->num != num){

		l = l->next;

	}

	return l; //ritorna i puntatore all'elemento cercato, non più l'head della lista

} 

nodo_t* cerca_ricorsivo(nodo_t* l, int num){

	if(l==NULL || l->num == num){ //non invertire le due condizioni se no da segmentation fault perche l->num == num non viene eseguito se la prima è vera

		return l;
	}

	return cerca(l->next, num);

}

nodo_t* inserisci_in_testa(nodo_t* l, int num){

	nodo_t *tmp;							//puntatore al nuovo oggetto

	tmp = malloc(sizeof(nodo_t));			//alloco il nuovo oggetto

	if(tmp != NULL){						//controllo malloc

		tmp->num = num;						//assegno il valore al nuovo valore da mettere in testa

		tmp->next = l;						//tmp ora punta al nuovo valore della lista e diventa head della lista

		l = tmp;							//l assume indirizzo di tmp e quindi il valore di head
	
	}else{

		printf("\nErrore nel malloc\n");
	}

	return l;

}

//non viene passato più il puntatore ma l'indirizzo di memoria del puntatore
void inserisci_in_testa_no_return(nodo_t** l, int num){

	nodo_t *tmp;							

	tmp = malloc(sizeof(nodo_t));			

	if(tmp != NULL){						

		tmp->num = num;						

		tmp->next = *l;						

		*l = tmp;					
	
	}else{

		printf("\nerrore nel malloc\n");
	}

}

nodo_t* inserisci_in_coda(nodo_t* l, int num){

	nodo_t *tmp, *prec;
	int flag=1;

	tmp = malloc(sizeof(nodo_t));

	if(tmp != NULL){

		tmp->num = num; //creazione nuovo elemento

		tmp->next = NULL;


		if(l==NULL){		//se la lista è vuota inserisce in testa

			l = tmp;

		}else{

			for(prec=l; flag == 1; prec=prec->next){ //si scorre tutta la lista

				if(prec->next == NULL){

					prec->next = tmp; //si mette in coda all'ultimo

					flag--;

				}			

			}

	}
	}else{

			printf("\nerrore nel malloc\n");
		}

	return l;

}

void inserisci_in_coda_no_return(nodo_t **l, int num){

	nodo_t *tmp, *prec;
	int flag=1;

	tmp = malloc(sizeof(nodo_t));

	if(tmp != NULL){

		tmp->num = num; //creazione nuovo elemento

		tmp->next = NULL;


		if(*l==NULL){		//se la lista è vuota inserisce in testa

			*l = tmp;

		}else{

			for(prec=*l; flag == 1; prec=prec->next){ //si scorre tutta la lista

				if(prec->next == NULL){

					prec->next = tmp; //si mette in coda all'ultimo

					flag--;

				}			

			}

	}
	}else{

			printf("\nerrore nel malloc\n");
		}

}

nodo_t* inserisci_in_coda_ricorsivo(nodo_t* l, int num){

	if(l==NULL){

		return inserisci_in_testa(l, num);
	}

	l->next = inserisci_in_coda_ricorsivo(l->next, num);

	return l;

}

nodo_t* inserisci_dopo_elemento(nodo_t* l, int cerc, int num){

	nodo_t *tmp, *prec;

	int flag=0;

	tmp = malloc(sizeof(nodo_t));

	if(tmp){

		tmp->num = num;

		tmp->next = NULL;

		if(l==NULL){ //se la lista è vuota

			l=tmp;

		}else{

			for(prec=l; prec->next != NULL; prec=prec->next){

				//si scorrono tutti gli elementi e ogni volta si controlla che prec->num non sia uguale a cerc

				if (prec->num == cerc && flag == 0){ //flag può non sembrare necessaria ma se si rientra nell'if perchè c'è un altro elemento uguale si rompe la connessione della lista
				
					tmp->next = prec->next;
					prec -> next = tmp;
					flag++;
				}

				
			}
		}


	}else{

		printf("\nerrore nel malloc\n");
	}

	return l;
}

nodo_t* sostituisci_elemento_ricorsivo(nodo_t* l, int cerc, int num){

	if(l == NULL || l->num == cerc){

		return inserisci_in_testa(l->next, num);

	}

	l->next = sostituisci_elemento_ricorsivo(l->next, cerc, num);

	return l;
}

nodo_t* cancella_in_testa(nodo_t* l){
    
    nodo_t *tmp;

	if(l != NULL){

		tmp = l;

		l= l->next;

		free(tmp);

		return l;
	}
}

nodo_t* cancella_in_coda(nodo_t* l){

	nodo_t *tmp, *prec;

	if(l->next == NULL){

		free(l);

		l=NULL;

	}else{

		prec = l;

		while(prec->next == NULL){

			if(prec->next->next == NULL){

				tmp = prec->next;

				prec->next = NULL;

				free(tmp);

			}


		}


	}

	return l;

}

nodo_t* cancella_in_coda_ricorsiva(nodo_t* l){

	if(l == NULL){

		return NULL;
	}

	if(l->next == NULL){

		return cancella_in_testa(l);

	}

	l->next = cancella_in_coda_ricorsiva(l->next);

	return l;

}

nodo_t* cancella_dopo_elemento(nodo_t* l, int cerc){

	nodo_t *prec, *tmp;

	if(l==NULL){

		return NULL;
	}

	if(l->next != NULL ){

		for(prec=l; prec->next != NULL; prec=prec->next){

			if(prec->num == cerc){

				tmp = prec->next;

				prec->next = prec->next->next;

				free(tmp);
			}

		}
	}
	return l;
}

nodo_t* cancella_elemento(nodo_t* l, int n){

	nodo_t *prec1, *prec2;

	if(l==NULL){ //se la lista è vuota

		return l;

	}
	if(l->num == n){ //se il primo elemento della lista è quello cercato

		cancella_in_testa(l);
	}
	
	else if(l->next != NULL){

			prec2 = l;

			prec1 = l->next;

			while(prec1 != NULL && prec1->num != n){

				prec1 = prec1->next;

				prec2 = prec2->next;
			}

			if(prec1 != NULL){

				prec2->next = prec1->next;

				free(prec1);

			

		}
	}

	return l;

}

nodo_t* cancella_elemento_ricorsivo(nodo_t* l, int n){

	if(l==NULL){

		return l;
	}

	if(l->num == n){

		return cancella_in_testa(l);

	}

	l->next = cancella_elemento_ricorsivo(l->next, n);

	return l;
}

nodo_t* cancella_ultimo_elemento_uguale(nodo_t* l, int n){

	nodo_t *tmp1, *tmp2, *prec1, *prec2;

	tmp2 = malloc(sizeof(nodo_t));
	tmp1 = malloc(sizeof(nodo_t));


	if(l==NULL){ //se la lista è vuota

		return l;
	}
	if (l->next == NULL){ //se la lista è composta da un solo elemento

		if(l->num == n){
		
			tmp2 = l;

			free(tmp2);
			l = NULL;

			return l;


		}
	}

	else if(l->next != NULL){
		printf("\nLa lista ha più di un elemento");

		prec1 = l;
		prec2 = l->next;


		while(prec2->next != NULL){

			printf("\nSto esaminando il %d", prec2->num);
			if(prec2->num == n){

				printf("\nHo trovato l'elemento da eliminare, sono nell'if");
				tmp2 = prec2; //tmp2 è l'elemento da eliminare
				tmp1 = prec1; //tmp1 è l'elemento PRECEDENTE a quello da eliminare
			}

			prec1 = prec1->next;
			prec2 = prec2->next;
		}


		printf("\nL'elemento da eliminare è: %d", tmp2->num);
		tmp1->next = tmp2->next;
		free(tmp2);
		
		tmp2 = NULL;

		return l;
	}

	
}