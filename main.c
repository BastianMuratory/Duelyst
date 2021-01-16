#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(void) {
	system("ls ./unit > temp");
	system("wc -l temp > temp2");
	system("clear");
	
	int total = 0; 
	
	FILE* fichier = fopen("temp2","r");
	fscanf(fichier,"%d",&total);
	fclose(fichier);
  printf("[%d] : ",total);
	char c;
	c = getchar();
	if(c!='\n'){
		return EXIT_SUCCESS;
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


	char name_of_unit[50] = "";

	/////////////// Recup nom 

	strncat(name_of_unit,nom[0],strlen(nom[0])-7);

	//////////////////

	char chemin[100] = "result/";
	strcat(chemin,name_of_unit);




	// creation du dossier teminal
	char commande1[100] = "mkdir ";
	strcat(commande1,chemin);
	system(commande1);
	//mkdir result/name

	// creation du fichier data
	char commande2[100] = "touch ";
	strcat(commande2,chemin);
	strcat(commande2,"/data.txt");
	system(commande2);
	//touch result/name/data.txt

	// ouverture du fichier data
	char file[100] = "";
	strcat(file,chemin);
	strcat(file,"/data.txt");
	fichier = fopen(file,"w");
	for(int i=0;i<differentes;i++){
		fprintf(fichier,"%d\n",occurence[i]);
	}
	// affichage des degats
	for(int i =0;i<5;i++){
		fprintf(fichier,"0\n");
	}
	fclose(fichier);
	

	
	// copie des sprites pour vider unit
	char cp[50] = "cp -r unit ";
	strcat(cp,chemin);
	strcat(cp,"/sprite");
	system(cp);

	// vidage de unit
	system("rm -rf unit");
	system("rm temp*");
	system("mkdir unit");
	
  return 0;
}