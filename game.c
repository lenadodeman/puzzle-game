#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pos{ int x; int y;}pos;

/*ici la fonction sert à vérifier si le tableau de taquin est résolu(0) ou pas(1)*/
int verifTab(int **tab, int taille){ 
    int i,j;
    int tmp=0;
    int incoherence=0;
    for(i=0;i<taille;i++){
        for(j=0;j<taille ;j++){
            tmp++;
            if((tab[i][j]!=tmp)){
                    incoherence++; /*on sait que pour qu'il soit résolu un tableau doit avoir chaque case = à son numéro de case ( tab[0](la case numéro 1)=1)
                                     sauf la dernière case qui sera égale à zéro. Et donc à chaque fois que ce n'est pas le cas on augmente la variable incohérence*/
            }
        }
    } 
    if(tab[taille-1][taille-1]==0){
        incoherence--;                  /*Comme on l'a dit plus haut la dernière case doit être un 0 donc ici on enlève une incoérence si c'est le cas*/
    }  
    if(incoherence!=0){       /*Si le nombre d'incohérence est différent de 0 alors il y a forcèment une erreur et la fonction retourne 1 sinon 0*/
        return 1;
    }
    return 0;
}

void afficheTab(int **tab,int taille){
    int i,j;
    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){
            printf("%d    ",tab[i][j]);
        }
    printf("\n");
    }
}

/*Cette fonction va rechercher la position du zéro sur le tableau et placer son x et son y dans une structure posiZero que l'on retournera*/
pos search(int **tab,int taille){
    int i,j;
    pos posiZero;
    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){
            if(tab[i][j]==0){
                posiZero.x=i;
                posiZero.y=j;
            }
        }
    }
    return posiZero;
}

/*Cette fonction va créer un tableau de taquin réussi que l'on utilisera pour la fonction randomize */
int **creeTabId (int taille){
    int **tab = malloc(taille*sizeof(int*));
    int i;
    for (i = 0; i < taille; i++){
        tab[i] = malloc(taille*sizeof(int));
        if(tab[i]==NULL){
            exit(-1);
        }
    }
    int g,j,tmp=0;
    for(g=0;g<taille;g++){
        for(j=0;j<taille;j++){
            tmp++;
            tab[g][j]=tmp;
        }
    }
    tab[taille-1][taille-1]=0;
    return tab; 
}

/*Dans cette fonction on va prendre un tableau réussi de taquin et on va le "randomizer" en faisant plein de déplacement aléatoire et pour cela on utilisera à répétition la fonction rand et switch*/
int **randomize (int **tab, int taille){
    srand(time(NULL));
    int nbmouvement=0;
    int choix;
    pos posZero ={taille-1,taille-1};
    while(nbmouvement < 15){
        nbmouvement= rand () % 601;
    }
    while(nbmouvement>0){
        choix = rand () % 4;
        switch(choix){
            case 0: /*changer case du haut et la case vide (du zero) tout en verifiant que l'on ne soit pas sur la première ligne et en ce cas on break*/
                if(posZero.y-1<0){
                    break;
                }
                tab[posZero.x][posZero.y]=tab[posZero.x][posZero.y-1];
                tab[posZero.x][posZero.y-1]=0;
                posZero.y--;
                break;
            case 1: /*changer case de gauche et la case vide (du zero) tout en verifiant que l'on ne soit pas sur la première colonne et en ce cas on break*/
                if(posZero.x-1<0){
                    break;
                }
                tab[posZero.x][posZero.y]=tab[posZero.x-1][posZero.y];
                tab[posZero.x-1][posZero.y]=0;
                posZero.x--;
                break;
            case 2: /*changer case de droite et la case vide (du zero) tout en verifiant que l'on ne soit pas sur la dernière colonne et en ce cas on break*/
                if(posZero.x+1>=taille){
                    break;
                }
                tab[posZero.x][posZero.y]=tab[posZero.x+1][posZero.y];
                tab[posZero.x+1][posZero.y]=0;
                posZero.x++;
                break;
            case 3: /*changer case du bas et la case vide (du zero) tout en verifiant que l'on ne soit pas sur la dernière ligne et en ce cas on break*/
                if(posZero.y+1>=taille){
                    break;
                }
                tab[posZero.x][posZero.y]=tab[posZero.x][posZero.y+1];
                tab[posZero.x][posZero.y+1]=0;
                posZero.y++;
                break;
        }
        nbmouvement--;
    }
    return tab;
}

/*Ici c'est la résolution du tableau par l'utilisateur */
void resoTaquin(int **tab,int taille){
    pos posZero=search(tab,taille); /*on récupère la position du zéro dans le tableau*/
    char touche;
    printf("\n");
    printf("\n");
    printf("BON COURAGE!!!!\n");
    printf("\n");
    printf("\n");
    printf("Pour jouer il suffit d'appuyer sur g,d,h,b puis d'appuyer sur entrée.\n");
    printf("\n");
    printf("Pour quitter veuillez tapper sur q puis entrée.\n"); 
    printf("\n");
    afficheTab(tab,taille);   
    while(verifTab(tab,taille)!=0){ /* on fait une boucle qui dure tant que le tbaleau n'est pas résolu*/
        scanf("%c",&touche);
        switch(touche){ 
            case 'h':
                if(posZero.x+1>=taille){
                    printf("Mouvement interdit : limites de la grille.\n");
                    afficheTab(tab,taille);
                    printf("\n");
                    break;
                }
                tab[posZero.x][posZero.y]=tab[posZero.x+1][posZero.y];
                tab[posZero.x+1][posZero.y]=0;
                posZero.x++;
                afficheTab(tab,taille); 
                printf("\n");
                break;
            case 'b':
                if(posZero.x-1<0){
                    printf("Mouvement interdit : limites de la grille.\n");
                    afficheTab(tab,taille);
                    printf("\n");
                    break;
                }
                tab[posZero.x][posZero.y]=tab[posZero.x-1][posZero.y];
                tab[posZero.x-1][posZero.y]=0;
                posZero.x--;  
                afficheTab(tab,taille);
                printf("\n");
                break;
            case 'g':
                if(posZero.y+1>=taille){
                    printf("Mouvement interdit : limites de la grille.\n");
                    afficheTab(tab,taille);
                    printf("\n");                   
                    break;
                }
                tab[posZero.x][posZero.y]=tab[posZero.x][posZero.y+1];
                tab[posZero.x][posZero.y+1]=0;
                posZero.y++;
                afficheTab(tab,taille);
                printf("\n");
                break;
            case 'd':
                 if(posZero.y-1<0){
                    printf("Mouvement interdit : limites de la grille.\n");
                    afficheTab(tab,taille);
                    printf("\n");
                    break;
                }
                tab[posZero.x][posZero.y]=tab[posZero.x][posZero.y-1];
                tab[posZero.x][posZero.y-1]=0;
                posZero.y--;
                afficheTab(tab,taille);
                printf("\n");
                break;
            case 'q' :
                printf("\n");
                printf("\n");
                printf("Vous allez quitter le jeu.\n");
                printf("\n");
                exit(-1);
        }
    }
    printf("\n");
    printf("\n");
    printf("Le taquin est résolu, BRAVO!!!!\n");
    printf("\n");
    afficheTab(tab,taille); 
    printf("\n");
}


/*On va récupérer un tableau de taquin grâce à un fichier(du nom :grilletaquin.txt et chaque ligne sera de la forme "case1 case2 case3 .........dernièrecase") et le retourner*/
int **recupTab(int dim){
    int ligne,i,l,j,tmp=0;
    char tmpc,tmpc2;
    char tmpstr[100];
    printf("Veuillez taper la ligne de la matrice voulue. (1 étant la première ligne) \n");
    scanf("%d",&ligne);
    int **tabTaquin = malloc(dim*sizeof(int*));/*On créer le tableau de taquin qu'il faudra retourner*/
    if(tabTaquin==NULL){
        printf("exit 1\n");
        exit(-1);
    }
    for (i = 0; i < dim; i++){
        tabTaquin[i] = malloc(dim*sizeof(int));
        if(tabTaquin[i]==NULL){
            printf("exit 2\n");
            exit(-2);
        }
    }
    FILE *fd = fopen("grilletaquin.txt","r"); /*On ouvre le fichier*/
    if(fd==NULL){
        printf("exit 3\n");
        exit(-3);
    }
    for(int h=1;h<ligne;h++){ /*On fait des fgets le nombre de fois qu'il faut pour arriver devant la bonne ligne*/
        fgets(tmpstr,100,fd);
    }
    /*On parcours le tableau de taquin et à chaque itération on va pouvoir récuperer deux caractères.Si les deux sont différents du char espace alors on sait que c'est un nombre supérieur à 10 et on multiplie le premier charactère-'0' par 10 puis on ajoute le deuxième-'0' on met le nombre récupérer dans la case de tabTaquin et on refait un fgetc pour arriver à la prochaine itération à un charactère, si 1 seul des deux est différent du char espace alors on récupère le char-'0' et on le met dans la case de tabTaquin*/
    for(l=0;l<dim;l++){
        for(j=0;j<dim;j++){
                tmpc=fgetc(fd);
                tmpc2=fgetc(fd);
                if(tmpc!=' ' && tmpc2!=' '){
                    tmp=(tmpc-'0')*10+(tmpc2-'0');
                    tabTaquin[l][j]=tmp;
                    fgetc(fd);
                }
                if(tmpc!=' ' && tmpc2==' '){
                    tmp=tmpc-'0';
                    tabTaquin[l][j]=tmp;
                }
        }
    }
    fclose(fd);   /*On ferme le fichier*/
    return tabTaquin;
}


int taquin(int dim){
    int **tab=creeTabId(dim);
    resoTaquin(randomize(tab,dim),dim);
    for(int i=0;i<dim;i++){
        free(tab[i]);
    }
    free(tab);
    return 1;
}

int main(){
    int choix,dim;
    printf("Voulez-vous utiliser votre fichier(1) OU une matrice aléatoire(2) ?\n");
    scanf("%d",&choix);
    if(choix==1){
        printf("Veuillez taper la dimension des matrices mises dans le fichier.\n");
        scanf("%d",&dim);
        resoTaquin(recupTab(dim),dim);
    }
    else if(choix==2){
        printf("Veuillez taper la dimension du tableau de taquin que vous voulez\n");
        scanf("%d",&dim);
        taquin(dim);
    }
    return 0;
}
