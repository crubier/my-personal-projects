#include <stdio.h>
#include <values.h>
#include <malloc.h>
#include <math.h>

#define V3 1.7320508075688772935

// Programme Obsolete mais toujours valable.

/*
Matrice
0       0       0       0       -V3/2   V3/2
0       0       0       1       -1/2    -1/2
1       1       1       0       0       0
0       -V3/2   V3/2    0       0       0
1       -1/2    -1/2    0       0       0
0       0       0       1       1       1

Son inverse
0       0       1/3     0       2/3     0 
0       0       1/3     -V3/3   -1/3    0   
0       0       1/3     V3/3    -1/3    0   
0       2/3     0       0       0       1/3 
-V3/3   -1/3    0       0       0       1/3 
V3/3    -1/3    0       0       0       1/3 

*/

void resolutionsysteme(double *entree, double *sortie);

int main()
{
	double entree[6]; /*Fx,Fy,Fz,Cx,Cy,Cz*/
	double sortie[6]; /*F1,F2,F3,Th1,Th2,Th3*/
	int i;
	
	FILE *a;
	a=fopen("d:/Parametres.txt","r");
	/*
	char b[8000];
	for(i=0;i<=500;i++)
	{	
		fgets(b,5000,a);
		printf(b);
	}
*/
	fscanf(a,"%lf %lf %lf %lf %lf %lf",entree,entree+1,entree+2,entree+3,entree+4,entree+5);
	fclose(a);
	
	/*scanf("%lf %lf %lf %lf %lf %lf",entree,entree+1,entree+2,entree+3,entree+4,entree+5);*/
	
	
	
	printf("\n\nEntree\n");
	for(i=0;i<=2;i++)
	{
	printf("%lf    %lf\n",entree[i], entree[i+3]);
	}
	
	resolutionsysteme(entree,sortie);
	
	printf("Sortie\n");
	for(i=0;i<=2;i++)
	{
	printf("%lf    %lf\n",sortie[i], sortie[i+3]);
	}
	
}

void resolutionsysteme(double *entree, double *sortie)
{
	double intermediaire[6]; /*Fz1,Fz2,Fz3,Fth1,Fth2,Fth3*/
	double matrice[6][6]={0,0,1,0,2,0,0,0,1,-V3,-1,0,0,0,1,V3,-1,0,0,2,0,0,0,1,-V3,-1,0,0,0,1,V3,-1,0,0,0,1};
	int i,j;
	for(i=0;i<=5;i++)
	{
		intermediaire[i]=0;
		for(j=0;j<=5;j++)
		{
			intermediaire[i]=intermediaire[i]+matrice[i][j]*entree[j];
		}
		intermediaire[i]=intermediaire[i]/3;
	}
		
	for(i=0;i<=2;i++)
	{
		sortie[i]=sqrt((intermediaire[i]*intermediaire[i])+(intermediaire[i+3]*intermediaire[i+3]));
		sortie[i+3]=atan2(intermediaire[i],intermediaire[i+3])/M_PI;
	}
}
