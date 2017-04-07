#ifndef ARVDIR_H_INCLUDED
#define ARVDIR_H_INCLUDED

// FALTOU O IMPRIME

//defini��o da estrutura de �rvore de diret�rio
typedef struct coarv{
    struct coarv *pai, *filho, *irmao;
    int marcado; // 0 marcado, 1 desmarcado, 2 marcado e desmarcado
    int tipo; // -1 vertice, tipo 0 ou tipo 1
    int id; // nome do vertice caso seja vertice senao -1
}TCA;

//defini��o dos m�todos b�sicos de �rvores
TCA *cria (int tipo,int id){
    TCA *a = (TCA*) malloc (sizeof(TCA));
    a->pai = NULL;
    a->filho = NULL;
    a->irmao = NULL;
    a->tipo = tipo;
    a->id = id;
    return a;
};

//inser��o de subarvore "filho" em uma arvore "pai"
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
//mover n� a para ser filho de n� b
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
//remove um n� e seus filhos
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

//busca e retorna o n� com o nome procurando-o na sub�rvore a
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

// FALTOU O IMPRIME, ANIMAL

#endif // ARVDIR_H_INCLUDED
