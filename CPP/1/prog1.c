#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int utworz_tablice_f(float* array, int sizeofarray)
{
	int i=0;
	//if(sizeof(array)!=sizeofarray) return -1;
	/*else*/ if(array==NULL) return -1;
	else
	{
		srand(time(NULL));
		for(i=0;i<sizeofarray;i++) array[i]=(rand());
		return 1;
	}	
}
int wyswietl_tablice_f(float* array, int sizeofarray)
{
	int i=0;
	//if(sizeof(array)!=sizeofarray) return -1;
	/*else*/ if(array==NULL) return -1;
	else
	{
		for(i=0;i<sizeofarray;i++) printf("%f\n",array[i]);
		return 1;
	}
}
int utworz_tablice_d(double* array, int sizeofarray)
{
	int i=0;
	//if(sizeof(array)!=sizeofarray) return -1;
	/*else*/ if(array==NULL) return -1;
	else
	{
		srand(time(NULL));
		for(i=0;i<sizeofarray;i++) array[i]=(rand());
		return 1;
	}	
}
int wyswietl_tablice_d(double* array, int sizeofarray)
{
	int i=0;
	//if(sizeof(array)!=sizeofarray) return -1;
	/*else*/ if(array==NULL) return -1;
	else
	{
		for(i=0;i<sizeofarray;i++) printf("%f\n",array[i]);
		return 1;
	}
}
int main(void)
{
	int rozmiar=0,choice=0;
	char string[64];
	double* tablica_d=NULL;
	float* tablica_f=NULL;
	printf("1 for  Float, 2 for Double\n");
	while(!choice)
	{
		fgets(string,sizeof(string),stdin);
		sscanf(string,"%d",&choice);
		if(!choice)
			puts("Try again");
	}
	switch(choice)
	{
		case 1:
			puts("What size?");
			while(!rozmiar)
			{
				fgets(string,sizeof(string),stdin);
				sscanf(string,"%d",&rozmiar);
				if(!rozmiar)
					puts("Try again");
			}
			tablica_d=(double*)malloc(rozmiar*(sizeof(double)));
			if(utworz_tablice_d(tablica_d,rozmiar)==-1) printf("Wykonane z bledami!!!\n");
			else if(wyswietl_tablice_d(tablica_d,rozmiar)==-1) printf("Wykonane z bledami!!!\n");
			else puts("Wykonano bez bledow!!!");
			free(tablica_d);
			break;
		case 2:
			puts("What size?");
			while(!rozmiar)
			{
			fgets(string,sizeof(string),stdin);
			sscanf(string,"%d",&rozmiar);
			if(!rozmiar)
				puts("Try again");
			}
			tablica_f=(float*)malloc(rozmiar*(sizeof(float)));
			if(utworz_tablice_f(tablica_f,rozmiar)==-1) printf("Wykonane z bledami!!!\n");
			else if(wyswietl_tablice_f(tablica_f,rozmiar)==-1) printf("Wykonane z bledami!!!\n");
			else puts("Wykonano bez bledow!!!");
			free(tablica_f);
			break;
		default:
			puts("Niepoprawny wybór");
			break;
	}
	exit(0);
}