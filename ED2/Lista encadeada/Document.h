typedef struct TypeDocument{
	char* nome;
	int id;
	int paginas;
	int bytes;
	struct TypeDocument* prox;
	struct TypeDocument* ant;
}TypeDocument;

typedef TypeDocument* Document;

typedef struct TypeList{
	Document head;
	Document tail;
	int size;
}TypeList;

typedef TypeList* List;

List new_List(){
	List nova = malloc(sizeof(TypeList));
	nova->head = NULL;
	nova->tail = NULL;
	nova->size = 0;
	return nova;
}

Document new_Document(List lst, int id, char nome[],int pgs, int size){
	Document novo = malloc(sizeof(TypeDocument));
	novo->prox = NULL;
	
	novo->ant = lst->tail;
	if(lst->tail)
		lst->tail->prox = novo;
		
	novo->id = id;
	novo->paginas = pgs;
	novo->bytes = size;
	novo->nome = malloc(strlen(nome)+1);
	strcpy(novo->nome,nome);
	
	lst->tail = novo;
	if(!lst->head)
		lst->head = novo;
	
	lst->size++;
	return novo;
}

void print_Document(Document d){
	printf("%d\t%s\t%d\t%d\n",d->id,d->nome,d->paginas,d->bytes);
}

void print_List(List l){
	Document i = l->head;
	while(i){
		print_Document(i);
		i = i->prox;
	}
}
