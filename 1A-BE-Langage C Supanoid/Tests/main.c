#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGCHAINE 100
#define NBPARAM 32
#define VIDE ""

typedef enum{FALSE,TRUE} BOOLEAN;

char* fichier2chaine(FILE* fichier);
int longueurfichier(FILE* fichier);
char* executercommande(char* parametres);
char* executerfichier(char* parametres);
char* creerchaine(char* chaine);

int main(int argc, char *argv[])
{
	char temp[200];

	sscanf("bobie[a1,a2,a3]","%[^[][%[^]",temp);
	printf("%s\n",temp);
	system("pause");
  	return 0;
}




char* creerchaine(char* chaine)
{
    char* res;
	if(chaine==NULL)return NULL;
    res=malloc((strlen(chaine)+2)*sizeof(char));
    strcpy(res,chaine);
    return res;
}

int longueurfichier(FILE* fichier)
{
	char pos;
	int res;

	//On verifie le fichier
	if(fichier==NULL)
	{
		return 0;
	}

	//On parcourt le fichier jusqu'à la fin en comptant
	res=0;
	do
	{
		pos=fgetc(fichier);
		if(res!=EOF)
		{
			res++;
		}

	}while(pos!=EOF);
	rewind(fichier);
	return(res);

}

char* fichier2chaine(FILE* fichier)
{
	int longfichier;
	char* res;
	int pos;
	int i;

	//On verifie le fichier
	if(fichier==NULL)
	{
		return NULL;
	}
	longfichier=longueurfichier(fichier);

	//On créé la chaine de caracteres
	res=malloc((longfichier+2)*sizeof(char));
	if(res==NULL)
	{
		return NULL;
	}
	for(i=0;i<=longfichier;i++)
	{
		*(res+i*sizeof(char))='\0';
	}
	
	//On lit le fichier caractere par caractere
	i=0;
	do
	{
		pos=fgetc(fichier);
		if(pos!=9 && pos!=10 && pos!=11 && pos!=12 && pos!=32 && pos!=EOF)
		{
			*(res+i*sizeof(char))=pos;
			i++;
		}

	}while(pos!=EOF);

	return res;
}

char* executerfichier(char* parametres)
{
	char* nomfichier;
	FILE* fichier;
	char* chaine;
	char* posa;
	char* posb;
	char* temp;
	
	nomfichier=creerchaine(parametres);
	fichier=fopen(nomfichier,"r");
	if(fichier==NULL)
	{
		return creerchaine("");
	}
	
	chaine=fichier2chaine(fichier);

	posa=chaine;
	while(strchr(posa,';')!=NULL)
	{
		posb=strchr(posa,';');
		executercommande(posa);
		posa=posb;
	}

	printf("%s\n",chaine);
	
	return NULL;
}

char* executercommande(char* parametres)
{
	printf("Commande : <%s>\n",parametres);
	system("pause");
}
