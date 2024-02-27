#include<stdio.h>
#include<stdlib.h>

struct nodo {
    int id;
    char nombre[30];
    struct nodo *sig;
};

struct nodo *primero=NULL;

void agregarnodo()
{
        struct nodo *nuevo;
        nuevo=malloc(sizeof(struct nodo));
        printf("Ingrese su id: ");
        scanf("%d",&nuevo->id);
        fflush(stdin);
        printf("Ingrese su nombre: ");
        gets(nuevo->nombre);
        if (primero == NULL)
        {
            nuevo->sig = NULL;
            primero = nuevo;
        }
        else
        {
            struct nodo *temp = primero;
            while (temp->sig != NULL)
            {
                temp = temp->sig;
            }
            temp->sig = nuevo;
            nuevo->sig = NULL;
        }
}

void imprimir()
{
    struct nodo *temp = primero;
    printf("Contenido de la lista...\n");
    while (temp != NULL)
    {
        printf("Codigo: %i\n",temp->id);
        printf("Nombre: %s\n",temp->nombre);
 		printf("\n");      
        temp = temp->sig;
    }
    printf("\n");
}

int main()
{
    agregarnodo();
    agregarnodo();
    agregarnodo();
    agregarnodo();
    agregarnodo();
    imprimir();
    return 0;
}
