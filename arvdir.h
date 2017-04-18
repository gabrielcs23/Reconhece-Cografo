#ifndef ARVDIR_H_INCLUDED
#define ARVDIR_H_INCLUDED

// FALTOU O IMPRIME

//definição da estrutura de árvore de diretório
typedef struct coarv{
    struct coarv *pai, *filho, *irmao;
    int marcado; // 0 desmarcado, 1 marcado, 2 marcado e desmarcado
    int tipo; // -1 vertice, tipo 0 ou tipo 1
    int id; // nome do vertice caso seja vertice senao -1
}TCA;

//definição dos métodos básicos de árvores
TCA *cria (int tipo,int id){
    TCA *a = (TCA*) malloc (sizeof(TCA));
    a->pai = NULL;
    a->filho = NULL;
    a->irmao = NULL;
    a->tipo = tipo;
    a->id = id;
    return a;
};

//inserção de subarvore "filho" em uma arvore "pai"
void inserir (TCA *afilho, TCA *apai){
    afilho->irmao = apai->filho;
    afilho->pai = apai;
    apai->filho = afilho;
}

//liberar arvore da memoria
void liberar (TCA *a){
    TCA *p = a->filho;
    while(p){
        TCA *t = p->irmao;
        liberar(p);
        p = t;
    }
    free(a);
}
/*
//mover nó a para ser filho de nó b
void mover(TCA *a, TCA*b){
    if(a == a->pai->filho){
        a->pai->filho = a->irmao;
    } else {
        TCA *p = a->pai->filho;
        while(p->irmao != a) p = p->irmao;
        p->irmao = a->irmao;
    }
    a->pai = b;
    a->irmao = b->filho;
    b->filho = a;
    if(!a->arquivo){
        TDir *aux = (TDir*)b->info;
        aux->num_dir++;
    }
    else{
        TDir *aux = (TDir*)b->info;
        aux->num_arq++;
    }
}
*/
//remove um nó e seus filhos
void destruir (TCA *a){
    TCA *i;
    i = a->pai->filho;
    if(i == a) a->pai->filho = a->irmao;
    else{
        while (i->irmao != a) i = i->irmao;
        i->irmao = a->irmao;
    }
    liberar(a);
}

//busca e retorna o nó com o nome procurando-o na subárvore a
TCA* busca (TCA* a, char *c){
    if(!a) return NULL;
    if(a->id == id) return a;
    TCA *r, *p;
    for(p=a->filho;p;p=p->irmao){
        r = busca(p,c);
        if(r) return r;
    }
    return NULL;
}

int f(TCA *a){
    TCA *f = a->filho;
    if(!f) return 0;
    int retorno = 1;
    while(f){
        f = f->irmao;
        retorno++;
    }
    return retorno;
}

int mf(TCA *a){
    TCA *f = a->filho;
    if(!f) return 0;
    int retorno = 0;
    while(f){
        if(f->marcado == 2)
            retorno++;
        f = f->irmao;
    }
    return retorno;
}

TCA *marca_aux(TG *g, TCA *a, int x){
    if(!a) return NULL;
    if(a->id != -1){
        if(buscaAresta(g,a->id,x))
            a->marcado = 1;
    }
    TCA *i;
    for(i=a->filho;i;i=i->irmao){
        i = marca_aux(g,i,x);
    }
    return NULL;
}

void marca_desmarca(TCA *T){
    TCA *u;
    for(u=T->filho;u;u->irmao){
        marca_desmarca(u);
        if((u->marcado == 1) && (f(u)==mf(u))){
            u->marcado = 2;
            if(u->pai){
                u->pai->marcado = 1;
            }
        }
    }
}

int vertice_marcado(TCA *T){
    if(T->marcado == 1)
        return 1;
    TCA *u;
    for(u=T->filho;u;u->irmao){
        if(vertice_marcado(u))
            return 1;
    }
    return 0;
}

void reset(TCA *T){
    if(T)
        T->marcado = 0;
    TCA *v;
    for(v = T->filho;v;v->irmao){
        reset(v);
    }
}

void marcar(TCA *T, TG *x){
    reset(T);
    marca_aux(x,T,x->id);
    marca_desmarca(T);
    if(f(T) == 1 && vertice_marcado(T))
        T->marcado == 1;
}
// FALTOU O IMPRIME, ANIMAL

#endif // ARVDIR_H_INCLUDED
