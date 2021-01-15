#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(void) {

	system("ls ./unit > temp");
	system("wc -l temp > temp2");
	system("clear");
	
	int total = 0; // nombre total d'image
	

	FILE* fichier = fopen("temp2","r");
	fscanf(fichier,"%d",&total);
	fclose(fichier);
	//printf("Il y a %d images\n",total);
  printf("[%d]\n",total);
	char c;
	c = getchar();
	if(c!='\n'){
		return EXIT_FAILURE;
	}else{
		printf("%c",c);
	}


	char** liste = (char**)malloc(total*sizeof(char*));
	char** liste2 = (char**)malloc(total*sizeof(char*));

	fichier = fopen("temp","r");
	for(int i =0;i<total;i++){
		liste[i] = (char*)malloc(MAX*sizeof(char));
		liste2[i] = (char*)malloc(MAX*sizeof(char));
		fscanf(fichier,"%s",liste[i]);
	}
	
	char current[50] = ""; // verif si nouvelle image
	int differentes = 0; // nombre d'image déjà traitée
	for(int i =0;i<total;i++){
		strncpy(liste2[i],liste[i],strlen(liste[i])-8);
		if(strcmp(current,liste2[i])!=0){
			differentes++;
			strcpy(current,liste2[i]);
		}
		//printf("[%d] %s\n",i,liste2[i]);
	}
	


	char** nom = (char**)malloc(differentes*sizeof(char*));
	int* occurence = (int*)malloc(differentes*sizeof(int));
	for(int i =0;i<differentes;i++){
		nom[i] = (char*)malloc(50*sizeof(char));
	}

	int indice = 0;
	for(int i =0;i<total;i++){
		if(strcmp(current,liste2[i])!=0){
			strcpy(current,liste2[i]);
			strcpy(nom[indice],liste2[i]);
			indice++;
		}
		occurence[indice-1] ++;
	}

	for(int i=0;i<differentes;i++){
		//printf("[%d] %s = %d\n",i,nom[i],occurence[i]);
		printf("%d\n",occurence[i]);
	}

	// ouverture du fichier sprite
	fichier = fopen("f","w");
	for(int i=0;i<differentes;i++){
		fprintf(fichier,"%d\n",occurence[i]);
	}

	system("rm -rf unit");puts("");
	system("mkdir unit");
	fclose(fichier);
	





	





  return 0;
}