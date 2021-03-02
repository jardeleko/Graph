#include <stdio.h>
#include <stdlib.h> 

typedef struct {
	int value;
}Vertice;

struct tp_list_vet{
	Vertice *v;
	struct tp_list_vet *left;//anterior
	struct tp_list_vet *right;//proximo
};
typedef struct tp_list_vet Vertices;

typedef struct{
	Vertice *origin; 
	Vertice *destine;
	// int peso;
}Edge;

struct tp_list_edges{
	Edge *e;
	struct tp_list_edges *left;//anterior
	struct tp_list_edges *right;//proximo
};
typedef struct tp_list_edges Edges;

typedef struct {
	Vertices *first_v;
	Vertices *last_v;

	Edges *first_e;
	Edges *last_e;
}Graph;

Graph *init_graph(){
	Graph *G = malloc(sizeof(Graph));
	G->first_v = NULL;
	G->last_v = NULL;
	G->first_e = NULL;
	G->last_e = NULL; 
	return G;
}

void free_graph(Graph *G){
	Vertices *aux_v = G->first_v;
	Edges *aux_e = G->first_e;

	while(aux_v != NULL){
		aux_v = G->first_v->right;
		free(G->first_v);
		G->first_v = aux_v;
	}

	while(aux_e != NULL){
		aux_e = G->first_e->right;
		free(G->first_e);
		G->first_e = aux_e;
	}
		free(G);
		printf("Memoria esta liberada\n");
}

void show_vertices(Graph *G){
	Vertices *aux = G->first_v;

	printf("\n\n\n------------Lista de Vertices-----------\n\t{");
	while(aux != NULL){
		printf("%d", aux->v->value);
		if(aux != G->last_v) printf(", ");
		aux = aux->right; //iteração até encontrar ultimo vertice

	}
	printf("}\n");

}

 void show_edges(Graph * G){
 	Edges *aux = G->first_e;

 	printf("\n************* Lista de Arestas********\n\t{");
 	while(aux != NULL){
 		printf("(%d, %d)", aux->e->origin->value, aux->e->destine->value);
 		if(aux != G->last_e) printf(",");
 		aux = aux->right;
 	}
 	printf("}\n\n\n\n");
 }

void *get_vertice(Graph *G, int value){
	Vertices *aux = G->first_v;

	while(aux != NULL){
		if(aux->v->value == value) return aux->v;
		aux = aux-> right;
	}
	return NULL;
}

void insert_vertice(Graph *G, int value){
	Vertice *new_v;
	Vertices *aux_v;

	new_v = malloc(sizeof(Vertice));
	new_v->value = value;

	aux_v = malloc(sizeof(Vertices));
	aux_v->left = NULL;
	aux_v->right = NULL;
	aux_v->v = new_v;

	if(G->first_v == NULL){
		G->first_v = aux_v;
		G->last_v = aux_v;
	}
	else{ // se existem vertices faz o encadeamento
		G->last_v->right = aux_v; //encadeia ultimo nodo no prox do ultimo vertice
		aux_v->left = G->last_v; // em meu novo grafo, encadeio ultimo anterior vertice existente antes
		G->last_v = aux_v; //o novo elemento agora passou a ser o ultimo
	}
}

void insert_edge(Graph *G, int origin, int destine){
	Edge *new_e;
	Edges *aux_e;
	Vertice *o, *d;
	new_e = malloc(sizeof(Edge));//vertice
	
	o = malloc(sizeof(Vertice));
	o->value = origin;
	new_e->origin = o;

	d = malloc(sizeof(Vertice));
	d->value = destine;
	new_e->destine = d;

	aux_e = malloc(sizeof(Edges));
	aux_e->left = NULL;
	aux_e->right = NULL;
	aux_e->e = new_e;

	if(G->first_e == NULL){//lista vazia
		//printf("entrou aqui\n");
		G->first_e = aux_e;
		G->last_e = aux_e;
	}else{ //se não estiver vazia a lista temos que encadear
		//printf("não é o primeiro\n");
		G->last_e->right = aux_e;
		aux_e->left = G->last_e;
		G->last_e = aux_e;
		//printf("feito\n");
	}

}

int grauVertice(Graph *G, int value){
	Edges *aux = G->first_e;
	int in = 0, out = 0, tmp;
	tmp = value;

 	while(aux != NULL){
 		if(aux->e->origin->value == tmp) out++;
 		else if(aux->e->destine->value == tmp) in++;
 		aux = aux->right;
 	}
 	printf("(Grau de entrada:[%d], Grau de saída[%d])\n\n",in, out);

 	return -1;
}

int grauEntradaVertice(Graph *G, int value){ //todas as vezes que ele é destino
	
	Edges *aux = G->first_e;
	int in = 0, tmp;
	tmp = value;

 	while(aux != NULL){
 		if(aux->e->destine->value == tmp) in++;
 		aux = aux->right;
 	}
 	printf("(Grau de entrada:[%d])\n\n",in);

 	return -1;
}


int grauSaidaVertice(Graph *G, int value){ //todas as vezes que ele origem
	
	Edges *aux = G->first_e;
	int out = 0, tmp;
	tmp = value;

 	while(aux != NULL){
 		if(aux->e->origin->value == tmp) out++;
 		aux = aux->right;
 	}
 	printf("(Grau de saída[%d])\n\n",out);

 	return -1;
}


int main(){
	
	Graph *G; //Armazena os dados no grafo (conjunto G(v,e))
	int i, n, value, origin, destine, tmp;
	char op;
	G = init_graph();

	while(scanf(" %c", &op) != EOF){ 
		switch(op){ 
			case 'i': 
				printf("Digite o numero de Vertices: ");
				scanf("%d", &n); //numero de vertices

				for (i = 0; i < n; i++)	{
					scanf("%d", &value);
					insert_vertice(G, value);
				}

				printf("\nDigite o numero de arestas: ");
				scanf("%d", &n);

				printf("\n Digite as arestas no formato origem/destino\n");
				for (int i = 0; i < n; i++){
					scanf("%d,%d", &origin, &destine);
					insert_edge(G, origin, destine);
				}
				break;
		
			case 's':
				show_vertices(G);
				show_edges(G);
				break;

			case 'a':
				printf("Entre com o vertice a ser analisado:\n");
				scanf("%d", &tmp);
				grauVertice(G, tmp);
				break;

			case 'e':	
				printf("Entre com o vertice a ser analisado(INPUT):\n");
				scanf("%d", &tmp);
				grauEntradaVertice(G, tmp);
				break;
			case 'o':	
				printf("Entre com o vertice a ser analisado(OUTPUT):\n");
				scanf("%d", &tmp);
				grauSaidaVertice(G, tmp);
				break;
			default:
			printf("opção invalida\n");	
		}
	}
	free_graph(G);
	return 0;
}

/*Observaçções do switch
i insert; 
s show list;
a analisa o vertice inteiro;
e analisa o vertice entrada;
o analisa o vertice saida;ls
*/
