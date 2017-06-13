// FALTOU O IMPRIME

//definição da estrutura de co-árvore
typedef struct coarv{
    struct coarv *pai, *filho, *irmao;
    int marcado; // 0 desmarcado, 1 marcado, 2 marcado e desmarcado
    int tipo; // -1 vertice, tipo 0 ou tipo 1
    int id; // nome do vertice caso seja vertice do grafo senao -1
    int f = 0;
    int mf = 0;
    int f_marcados = 0;
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
    if(apai)
        apai->f++;
    if(afilho->marcado == 2)
        apai->mf++;
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

//mover nó a para ser filho de nó b
void mover(TCA *a, TCA*b){
    a->pai->f--;
    if(a->marcado == 2)
        a->pai->mf--;
    if(a == a->pai->filho){
        a->pai->filho = a->irmao;
    } else {
        TCA *p = a->pai->filho;
        while(p->irmao != a) p = p->irmao;
        p->irmao = a->irmao;
    }
    a->pai = b;
    b->f++;
    if(a->marcado == 2)
        b->mf++;
    a->irmao = b->filho;
    b->filho = a;
}

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
/*
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
*/
TCA *marca_aux(TG *g, TCA *a, int x){
    if(!a) return NULL;
    if(a->id != -1){
        if(buscaAresta(g,a->id,x)){
            a->marcado = 1;
            if(a->pai)
                a->pai->f_marcados++;
        }
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
        if((u->marcado == 1) && (u->f==u->mf)){
            u->marcado = 2;
            u->mf = 0;
            if(u->pai){
                u->pai->marcado = 1;
                u->pai->mf++;
                if(u->pai->pai)
                    u->pai->pai->f_marcados++;
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
    if(T){
        T->marcado = 0;
        T->mf = 0;
        T->f_marcados = 0;
        TCA *v;
        for(v = T->filho;v;v->irmao){
            reset(v);
        }
    }
    else if(!T->pai){
        printf("Co-arvore nao possui nos\n");
        exit(1);
}

void marcar(TCA *T, TG *x){
    reset(T);
    marca_aux(x,T,x->id);
    marca_desmarca(T);
    if(T->f == 1 && vertice_marcado(T))
        T->marcado == 1;
}

void adicionar_vertice(TCA *t, int id){
    TCA *no = cria(-1,id);
    inserir(no,t);
}

void remover_marca_filhos(TCA* a){
    if(!a) return;
    a->mf = 0;
    for(a = a->filho;a;a = a->irmao){
        if(a->marca == 2) a->marcado = 0;
    }
}

TCA *prox_marcado(TCA *inicial, TCA *i){
    if(!i)
        return NULL;
    if((i->marcado == 1) && (i != inicial))
        return i;
    TCA *prox, *aux;
    for(aux = i->filho;aux;aux = aux->irmao){
        prox = prox_marcado(inicial,aux);
        if(prox)
            return prox;
    }
    return NULL;
}
    
TCA * encontrar_no(TCA *r, TCA *w, TCA *y){
    TCA *u = prox_marcado(r,r);
    while(u){
        TCA* t;
        if(!y)
            return NULL;
        if(u->tipo == 1){
            if(u->mf != (u->f-1))
                y = u;
            if(u->pai->marcado == 1)
                return NULL;
            else t = u->pai->pai;
        }
        else{
            y = u;
            t = u->pai;
        }
        u->marcado = 2;
        if(u->pai)
            u->pai->mf++;
        remover_marca_filhos(u);
        while(t!=w){
            if(t == r)
                return NULL;
            if(t->marcado == 0)
                return NULL;
            if(t->mf != (t->f-1))
                return NULL;
            if(t->pai->marcado == 0)
                return NULL;
            t->marcado = 2;
            if(t->pai)
                t->pai->mf++;
            remover_marca_filhos(t);
            t = t->pai->pai;
        }
        w = u;
        u = prox_marcado(w,w);
    }
    return u;
}
    
int ver_marca(TCA *a, int marca){
    if(!a) return marca;
    if(a->marcado != marca) return a->marcado;
    TCA *p;
    for(p=a->filho;p;p=p->irmao){
        int r = busca(p,marca);
        if(r != marca) return r;
    }
    return marca;
}
    
int reconhece_cografos(TG *g){
    TCA *r = cria(1,-1);
    TG *v1 = g, *v2 = g->prox;
    if(buscaAresta(v1,v2){
        adicionar_vertice(r,v1->id);
        adicionar_vertice(r,v2->id);
    }
    else{
        TCA *n = cria(0,-1);
        inserir(n,r);
        TCA *v = cria(-1,v1->id);
        inserir(v,n);
        v = cria(-1,v2->id);
        inserir(v,n);
    }
    TCA *x;
    for(x = v2->prox;x;x = x->prox){
        marcar(r,x);
        if(ver_marca(r,2) == 2){
            TCA *ins = cria(-1,x->id);
            inserir(ins,r);
            continue;
        }
        if(ver_marca(r,0) == 0){
            if(r->f == 1){
                TCA *ins = cria(-1, x->id);
                inserir(ins,r->filho);
            }
            else{
                TCA *novor = cria(1,-1);
                TCA *filhor = cria(0, -1);
                inserir(filhor, novor);
                TCA *ins = cria(-1, x->id);
                inserir(ins, filhor);
                inserir(r, filhor);
                r = &novor;
            }
            continue;
        }
        TCA* u, *y = NULL;
        if (r->marcado == 0){
            return NULL;
        }
        else if (r->mf != r->f -1){
            y = r;
        }
        r->marcado =0;
        remover_marca_filhos(r);
        u = r;
        u = encontrar_no(r,u,y);
        if(!u){
            return 0;
        }       
        if(u->tipo == 0){
            y = cria(u->tipo,-1);
            int usadoy = 0;
            if(u->mf == 1){
                // setar valor de w antes
                if((w->pai == u) && (w->marcado == 2) && (w->tipo == -1)){
                    TCA *ins = cria(1,-1);
                    inserir(ins, w->pai);
                    u->f--;
                    if(w->marcado == 2)
                        u->mf--;
                    inserir(w, ins);
                    inserir(x, ins);
                }
                else {
                    inserir(x,w);
                }
            }
            else {
                usadoy = 1;
                for(TCA *i = u->filho;i;i=i->irmão){
                    if(i->marcado == 2){
                        mover(i, y);
                    }
                }
            }
            TCA *ins = cria (1,-1);
            mover(x,ins);
            y->tipo  = 0;
            usadoy = 1;
            inserir(y,ins);
            inserir(ins, u);
            if(!usadoy)
                destruir(y);
        }
        // rotulo(u) = 1
        else{
            TCA *y = cria(u->tipo,-1);
            int usadoy = 0;
            int cardinalidade == 0;
            TCA *aux;
            for(aux = u->filho;aux;aux = aux->irmao){
                if(aux->marcado == 0)
                    cardinalidade++;
            }
            if(cardinalidade == 1){
                if((w->pai == u) && (w->marcado == 0) && (w->tipo == -1)){
                    TCA *ins = cria(0,-1);
                    inserir(ins, w->pai);
                    u->f--;
                    if(w->marcado == 2)
                        u->mf--;
                    inserir(w, ins);
                    inserir(x, ins);
                }
                else {
                    inserir(x,w);
                }
            }
            else {
                usadoy = 1;
                for(TCA *i = u->filho;i;i=i->irmão){
                    if(i->marcado == 0){
                        mover(i, y);
                    }
                }
            }
            TCA *upai = u->pai;
            y->tipo = 1;
            usadoy = 1;
            inserir(y,upai);
            upai->f--;
            if(u->marcado == 2)
                upai->mf--;
            TCA *nozero = criar(0,-1);
            inserir(nozero,y);
            inserir(x,nozero);
            inserir(u,nozero);
            if(!usadoy)
                destruir(y);
           }
        }
    }
    return 1;
}
