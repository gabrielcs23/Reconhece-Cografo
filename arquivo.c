#include <stdio.h>
void grafo_arquivo(TG *grafo)
{
    FILE *fp = fopen("grafo.dat", "w");
    fwrite(fp, "graph [\n");
    TG *i;
    for(i = grafo; i; i = i-> prox)
    {
        fwrite(fp,"node [\n");
        fwrite(fp,"id %d\n", i->id);
        fwrite(fp,"label %d\n]\n", i->id);
    }
    for(i = grafo; i; i = i-> prox)
    {
        TViz *j;
        for(j = i->viz; j;j->prox)
        {
            fwrite(fp,"edge [\n");
            fwrite(fp,"source %d\n", i->id);
            fwrite(fp,"target %d\n]\n", j->id);
        }
    }
    fwrite(fp, "]");
    fclose(fp);
}

void coarvore_arquivo(TCA *arvore);
