#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Container {
    int id;
    char nome[50];
    int status;
    struct Container *proximo;
} Container;

typedef struct {
    Container *head;
    Container *tail;
    int tam;
    int proximo_id;
} ListaContainers;

typedef struct Imagem {
    int id;
    char nome[50];
    ListaContainers *lista_cont;
    struct Imagem *proximo;
} Imagem;

typedef struct {
    Imagem *head;
    Imagem *tail;
    int tam;
    int proximo_id;
} ListaImagens;

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

ListaContainers* criar_lista_containers() {
    ListaContainers *l = malloc(sizeof(ListaContainers));
    if (l) {
        l->head = NULL;
        l->tail = NULL;
        l->tam = 0;
        l->proximo_id = 1;
    }
    return l;
}

void inicializar_sistema(ListaImagens *l) {
    l->head = NULL;
    l->tail = NULL;
    l->tam = 0;
    l->proximo_id = 1;
}

void liberar_sistema(ListaImagens *l) {
    Imagem *img = l->head;
    while (img != NULL) {
        Container *c = img->lista_cont->head;
        while (c != NULL) {
            Container *prox_c = c->proximo;
            free(c);
            c = prox_c;
        }
        free(img->lista_cont);
        Imagem *prox_img = img->proximo;
        free(img);
        img = prox_img;
    }
    inicializar_sistema(l);
}

void baixar_imagem(ListaImagens *l) {
    Imagem *nova = malloc(sizeof(Imagem));
    if (nova) {
        nova->id = l->proximo_id++;
        printf("Digite o nome da Imagem: ");
        scanf("%49[^\n]", nova->nome);
        limpar_buffer();
        nova->lista_cont = criar_lista_containers();
        nova->proximo = NULL;
        if (l->head == NULL) {
            l->head = nova;
            l->tail = nova;
        } else {
            l->tail->proximo = nova;
            l->tail = nova;
        }
        l->tam++;
        printf("-> Imagem '%s' (ID: %d) baixada com sucesso!\n", nova->nome, nova->id);
    } else {
        printf("Erro de memoria.\n");
    }
}

void excluir_imagem(ListaImagens *l) {
    if (l->head == NULL) {
        printf("Nenhuma imagem no sistema.\n");
        return;
    }
    int id_busca;
    printf("Digite o ID da imagem a excluir: ");
    scanf("%d", &id_busca);
    limpar_buffer();
    Imagem *aux = l->head;
    Imagem *anterior = NULL;
    while (aux != NULL && aux->id != id_busca) {
        anterior = aux;
        aux = aux->proximo;
    }
    if (aux == NULL) {
        printf("-> Erro: Imagem nao encontrada.\n");
        return;
    }
    if (aux->lista_cont->tam > 0) {
        printf("-> Erro: Imagem possui %d container(s) vinculado(s). Exclua-os primeiro.\n", aux->lista_cont->tam);
        return;
    }
    if (anterior == NULL) {
        l->head = aux->proximo;
        if (l->head == NULL) l->tail = NULL;
    } else {
        anterior->proximo = aux->proximo;
        if (aux->proximo == NULL) l->tail = anterior;
    }
    free(aux->lista_cont);
    free(aux);
    l->tam--;
    printf("-> Imagem excluida com sucesso!\n");
}

void criar_container(ListaImagens *l) {
    int id_img;
    printf("Digite o ID da Imagem base: ");
    scanf("%d", &id_img);
    limpar_buffer();
    Imagem *img = l->head;
    while (img != NULL && img->id != id_img) {
        img = img->proximo;
    }
    if (img == NULL) {
        printf("-> Erro: Imagem nao encontrada.\n");
        return;
    }
    Container *novo = malloc(sizeof(Container));
    if (novo) {
        ListaContainers *lc = img->lista_cont;
        novo->id = lc->proximo_id++;
        printf("Digite o nome do Container: ");
        scanf("%49[^\n]", novo->nome);
        limpar_buffer();
        novo->status = 1;
        novo->proximo = NULL;
        if (lc->head == NULL) {
            lc->head = novo;
            lc->tail = novo;
        } else {
            lc->tail->proximo = novo;
            lc->tail = novo;
        }
        lc->tam++;
        printf("-> Container '%s' (ID: %d) criado e EM EXECUCAO na base '%s'.\n", novo->nome, novo->id, img->nome);
    }
}

Container* buscar_container_global(ListaImagens *l, int id_cont, Imagem **img_pai, Container **cont_anterior) {
    Imagem *img = l->head;
    while (img != NULL) {
        Container *aux = img->lista_cont->head;
        Container *ant = NULL;
        while (aux != NULL) {
            if (aux->id == id_cont) {
                if (img_pai) *img_pai = img;
                if (cont_anterior) *cont_anterior = ant;
                return aux;
            }
            ant = aux;
            aux = aux->proximo;
        }
        img = img->proximo;
    }
    return NULL;
}

void interromper_container(ListaImagens *l) {
    int id_cont;
    printf("Digite o ID do Container: ");
    scanf("%d", &id_cont);
    limpar_buffer();
    Container *c = buscar_container_global(l, id_cont, NULL, NULL);
    if (c) {
        if (c->status == 0) {
            printf("-> O container ja esta interrompido.\n");
        } else {
            c->status = 0;
            printf("-> Container '%s' INTERROMPIDO.\n", c->nome);
        }
    } else {
        printf("-> Erro: Container nao encontrado.\n");
    }
}

void iniciar_container(ListaImagens *l) {
    int id_cont;
    printf("Digite o ID do Container: ");
    scanf("%d", &id_cont);
    limpar_buffer();
    Container *c = buscar_container_global(l, id_cont, NULL, NULL);
    if (c) {
        if (c->status == 1) {
            printf("-> O container ja esta em execucao.\n");
        } else {
            c->status = 1;
            printf("-> Container '%s' INICIADO.\n", c->nome);
        }
    } else {
        printf("-> Erro: Container nao encontrado.\n");
    }
}

void excluir_container(ListaImagens *l) {
    int id_cont;
    printf("Digite o ID do Container a excluir: ");
    scanf("%d", &id_cont);
    limpar_buffer();
    Imagem *img_pai = NULL;
    Container *anterior = NULL;
    Container *c = buscar_container_global(l, id_cont, &img_pai, &anterior);
    if (c == NULL) {
        printf("-> Erro: Container nao encontrado.\n");
        return;
    }
    if (c->status == 1) {
        printf("-> Erro: Container em execucao. Interrompa-o primeiro.\n");
        return;
    }
    ListaContainers *lc = img_pai->lista_cont;
    if (anterior == NULL) {
        lc->head = c->proximo;
        if (lc->head == NULL) lc->tail = NULL;
    } else {
        anterior->proximo = c->proximo;
        if (c->proximo == NULL) lc->tail = anterior;
    }
    free(c);
    lc->tam--;
    printf("-> Container excluido com sucesso!\n");
}

void listar_imagens(ListaImagens *l) {
    printf("\n--- IMAGENS DISPONIVEIS (%d) ---\n", l->tam);
    Imagem *aux = l->head;
    while (aux != NULL) {
        printf("[ID: %d] Nome: %s | Containers vinculados: %d\n", aux->id, aux->nome, aux->lista_cont->tam);
        aux = aux->proximo;
    }
}

void listar_containers(ListaImagens *l) {
    printf("\n--- TODOS OS CONTAINERS ---\n");
    Imagem *img = l->head;
    int total = 0;
    while (img != NULL) {
        Container *c = img->lista_cont->head;
        while (c != NULL) {
            printf("[ID: %d] Nome: %s | Status: %s | Base: %s\n",
                c->id, c->nome, c->status == 1 ? "EM EXECUCAO" : "INTERROMPIDO", img->nome);
            total++;
            c = c->proximo;
        }
        img = img->proximo;
    }
    if (total == 0) printf("Nenhum container no sistema.\n");
}

int main() {
    ListaImagens docker;
    inicializar_sistema(&docker);
    int op;

    do {
        printf("\n========== GESTAO DE CONTAINERS ==========\n");
        printf("1. Baixar Imagem (Criar)\n");
        printf("2. Excluir Imagem\n");
        printf("3. Criar Container\n");
        printf("4. Interromper Container\n");
        printf("5. Iniciar Container\n");
        printf("6. Excluir Container\n");
        printf("7. Listar Imagens\n");
        printf("8. Listar Containers\n");
        printf("0. Sair\n");
        printf("==========================================\n");
        printf("Opcao: ");
        scanf("%d", &op);
        limpar_buffer();

        switch (op) {
            case 1: baixar_imagem(&docker); break;
            case 2: excluir_imagem(&docker); break;
            case 3: criar_container(&docker); break;
            case 4: interromper_container(&docker); break;
            case 5: iniciar_container(&docker); break;
            case 6: excluir_container(&docker); break;
            case 7: listar_imagens(&docker); break;
            case 8: listar_containers(&docker); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (op != 0);

    liberar_sistema(&docker);

    return 0;
}