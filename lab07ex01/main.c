#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

typedef struct products
{
    char *id;
    char *proName;
    int price;
    struct products *next;
} Product;
typedef struct producers
{
    char *manName;
    char *id;
    struct producers *next;
    Product *product;
} Producer;

FILE *openFile(char *,char *);
Producer *load(FILE *,FILE *);
Producer *createInsert(char [MAX],char [MAX]);
Product *createNew(char [MAX],char [MAX],int);
void addToList(Producer *,Product *);
void display(Producer *);

int main(int argc,char *argv[])
{
    FILE *f1,*f2;
    Producer *head;

    if(argc!=3)
    {
        printf("error in receiving command line parameters!\n");
        exit(0);
    }
    f1=openFile(argv[1],"r");
    f2=openFile(argv[2],"r");

    head=load(f1,f2);
    display(head);

    fclose(f1);
    fclose(f2);
    return 0;
}

FILE *openFile(char *fn,char *mode)
{
    FILE *fp;
    fp=fopen(fn,mode);
    if(fp==NULL)
    {
        printf("error in opening files!\n");
        exit(0);
    }
    return fp;
}

Producer *load(FILE *f1,FILE *f2)
{
    Producer *head,*newP;
    Product *newProduct;
    char manName[MAX],id[MAX],name[MAX];
    int price;

    head=NULL;
    while(fscanf(f1,"%s %s",manName,id)!=EOF)
    {
        newP=createInsert(manName,id);
        if(head==NULL)
        {
            newP->next=NULL;
            head=newP;
        }
        else
        {
            newP->next=head;
            head=newP;
        }
    }

    while(fscanf(f2,"%s %s %d",id,name,&price)!=EOF)
    {
        newProduct=createNew(id,name,price);
        addToList(head,newProduct);
    }

    return head;
}

Producer *createInsert(char manName[MAX],char id[MAX])
{
    Producer *newP;
    newP=(Producer *)malloc(sizeof(Producer));
    if(newP==NULL)
    {
        printf("There is not enough memory to allocate for new producer!\n");
        exit(0);
    }
    newP->manName=strdup(manName);
    newP->id=strdup(id);
    newP->product=NULL;
    newP->next=NULL;
    return newP;
}
Product *createNew(char id[MAX],char name[MAX],int price)
{
    Product *newProduct;
    newProduct=(Product *)malloc(sizeof(Product));
    if(newProduct==NULL)
    {
        printf("There is not enough memory to allocate for new product!\n");
        exit(0);
    }
    newProduct->id=strdup(id);
    newProduct->proName=strdup(name);
    newProduct->price=price;
    newProduct->next=NULL;
    return newProduct;
}
void addToList(Producer *head,Product *newProduct)
{
    Producer *tmp;
    tmp=head;
    while(tmp!=NULL)
    {
        if(strcmp(tmp->id,newProduct->id)==0)
        {
            if(tmp->product==NULL)
            {
                newProduct->next=NULL;
                tmp->product=newProduct;
                return;

            }
            else
            {
                newProduct->next=tmp->product;
                tmp->product=newProduct;
                return;
            }
        }

        tmp=tmp->next;

    }
    return;
}

void display(Producer *head)
{
    Producer *tmp;
    char wanted[MAX];

    do
    {
        printf("insert name of manufacturer:\n");
        scanf("%s",wanted);
        tmp=head;
        while(tmp!=NULL)
        {
            if(strcmp(tmp->manName,wanted)==0)
            {
                while(tmp->product!=NULL)
                {
                    printf("%s %d\n",tmp->product->proName,tmp->product->price);
                    tmp->product=tmp->product->next;
                }
            }
            tmp=tmp->next;
        }
    }
    while(strcmp(wanted,"stop")!=0);

    return;
}
