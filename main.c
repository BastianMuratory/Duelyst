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
		printf("[%d] %s\n",i,liste2[i]);
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
		printf("[%d] %s = %d\n",i,nom[i],occurence[i]);
	}

	char name_of_unit[50];
	printf("Nom de l'unitée :");
	scanf("%s",name_of_unit);
	char chemin[100] = "result/";
	strcat(chemin,name_of_unit);

	// creation du dossier teminal
	char commande1[100] = "mkdir ";
	strcat(commande1,chemin);
	system(commande1);
	strcat(commande1,"/sprites");
	system(commande1);

	// creation du fichier sprite
	char commande2[100] = "touch ";
	strcat(commande2,chemin);
	strcat(commande2,"/sprite.txt");
	system(commande2);

	// ouverture du fichier sprite
	char file[100] = "";
	strcat(file,chemin);
	strcat(file,"/sprite.txt");
	fichier = fopen(file,"w");
	fprintf(fichier,"%d,%d\n",total,differentes);
	for(int i=0;i<differentes;i++){
		fprintf(fichier,"%d,%s\n",occurence[i],nom[i]);
	}
	fclose(fichier);
	
	char deplacement2[10] = "mv unit/";
	for(int i = 0;i<total;i++){
		char com[100] = "";
		strcat(com,deplacement2);
		strcat(com,liste[i]);
		strcat(com," result/");
		strcat(com,name_of_unit);
		strcat(com,"/sprites");
		system(com);
	}





	





  return 0;
}