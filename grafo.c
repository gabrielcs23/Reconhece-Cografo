#include <stdio.h>
#include <stdlib.h>

typedef struct vizf{
    int id;
    struct viz *prox;
}TViz;

typedef struct grafo{
    int id;
    TViz *viz;
    struct grafo *prox;
}TG;

TG *inicializa(void){
    return NULL;
}

void imprime(TG *g){
    TG *p = g;
    while(p)\{\
        printf("%d\\n",p->id);\
        TViz *v = p->viz;\
        while(v)\{\
            printf("%d ",v->id);\
            v = v->prox;\
        \}\
        printf("\\n");\
        p = p->prox;\
    \}\
\}\
\
TG *buscaNo(TG *g,int no)\{\
    TG *p = g;\
    while((p)&&(p->id!=no))\
        p = p->prox;\
    return p;\
\}\
\
TG *insereNo(TG *g,int no)\{\
    TG *p = buscaNo(g,no);\
    if(p) return g;\
    p = (TG*)malloc(sizeof(TG));\
    p->id = no;\
    p->viz = NULL;\
    p->prox = g;\
    return p;\
\}\
\
TViz *buscaAresta(TG *g,int no1,int no2)\{\
    TG *p = buscaNo(g,no1);\
    if(!p) return NULL;\
    TViz *v = p->viz;\
    while((v)&&(v->id!=no2))\
        v = v->prox;\
    return v;\
\}\
\
void insereArestaUmSentido(TG *g, int no1, int no2)\{\
    TViz *v = buscaAresta(g,no1,no2);\
    if(v) return;\
    TG *p = buscaNo(g,no1);\
    if(!p) return;\
    v = (TViz *)malloc(sizeof(TViz));\
    v->id = no2;\
    v->prox = p->viz;\
    p->viz = v;\
\}\
\
void insereAresta(TG *g, int no1, int no2)\{\
    insereArestaUmSentido(g,no1,no2);\
    insereArestaUmSentido(g,no2,no1);\
\}\
\
void retiraArestaUmSentido(TG *g,int no1, int no2)\{\
    TG *p = buscaNo(g,no1);\
    if(!p) return;\
    TViz *q = p->viz, *ant = NULL;\
    while((q)&&(q->id!=no2))\{\
        ant = q;\
        q = q->prox;\
    \}\
    if(!q) return;\
    if(!ant) p->viz = q->prox;\
    else ant->prox = q->prox;\
    free(q);\
\}\
\
void retiraAresta(TG *g, int no1, int no2)\{\
    retiraArestaUmSentido(g,no1,no2);\
    retiraArestaUmSentido(g,no2,no1);\
\}\
\
TG *retiraNo(TG *g,int no)\{\
    TG *p = g, *ant = NULL;\
    while((p)&&(p->id!=no))\{\
        ant = p;\
        p=p->prox;\
    \}\
    if(!p) return g;\
    TViz *v = p->viz;\
    while(v)\{\
        retiraAresta(g,no,v->id);\
        v = p->viz;\
    \}\
    if(!ant) g = p->prox;\
    else ant->prox = p->prox;\
    free(p);\
    return g;\
\}\
\
void libera(TG *g)\{\
    while(g)\
        g = retiraNo(g,g->id);\
\}\
\
}
