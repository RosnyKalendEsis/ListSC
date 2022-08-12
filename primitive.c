#include <malloc.h>
#include <stdio.h>
#include "headers/primitive.h"
#include <string.h>

//
// Created by Rosny Kalend on 06/08/2022.
//
int comparer(char *chaine, char *chaine2){
    int i=0;
    while(chaine[i]!="\0" || chaine2[i]!="\0"){
        if(chaine[i]!=chaine2[i]){
            if(chaine[i]>chaine2[i]){
                //si le caractère de la chaine est superieur à celle de la chaine 2
                return 1;
            }else{
                //si le caractère de la chaine est superieur à celle de la chaine 2
                return 0;
            }
        }
        i++;
    }
}
void afficherEtudiant(Etudiant etudiant){
    char *nom= strupr(etudiant.nom);
    char *pst= strupr(etudiant.postnom);
    char *flr= strupr(etudiant.filiere);
    char *mat= strupr(etudiant.matricule);
    printf("Nom: ");
    for(int i=0;nom[i] !='\0';i++){
        printf("%c",nom[i]);
    }
    printf("  ");
    printf("Postnom: ");
    for(int i=0;pst[i] !='\0';i++){
        printf("%c",pst[i]);
    }
    printf("  ");
    printf("Matricule: ");
    for(int i=0;mat[i] !='\0';i++){
        printf("%c",mat[i]);
    }
    printf("  ");
    printf("Filiere:");
    for(int i=0;flr[i] !='\0';i++){
        printf("%c",flr[i]);
    }
    printf("\n");
}
element* cree_element(Etudiant etudiant) {
    element *e;
    if((e = (element *) malloc(sizeof(element))) != NULL) {
        e->etudiant = etudiant;
        e->suivant = NULL;
    }
    return e;
}

void affiche_liste(liste l) {
    element *temp = l.debut;
    printf("{");
    while(temp != NULL) {
        afficherEtudiant(temp->etudiant);
        temp = temp->suivant;
    }
    printf(" }\n");
}

element* accede_element(liste l, int p) {
    element *resultat = l.debut;
    int i;
    i=0;
    while(i<p && resultat!=NULL) {
        resultat = resultat->suivant;
        i++;
    }
    return resultat;
}

int insere_element(liste *l, element *e, int p) {
    element *temp = l->debut, *avant, *apres;
    int erreur = 0;
     if(p==0) {
         e->suivant = temp;
         l->debut = e;
     }else {
         temp = accede_element(*l, p - 1);
         if (temp == NULL) {
             erreur = -1;
         }else {
             avant = temp;
             apres = temp->suivant;
             e->suivant = apres;
             avant->suivant = e;
         } }
     return erreur;
}
int trouverPosition(liste *l, char *matricule){
    int position=0;
    element *temp = l->debut;
    int i=0;
    while(temp != NULL) {
        if(strcmp(strlwr(temp->etudiant.matricule), strlwr(matricule))==0){
            return position;
        }
        position++;
        temp=temp->suivant;
    }
    return position;
}

int supprime_element(liste *l, int p) {
    element *temp = l->debut, *e, *avant, *apres;
    int erreur = 0;
    if(p==0) {
        e = temp;
        if(e == NULL) {
            erreur = -1;
        }else{
            l->debut = e->suivant;
        }
    }else {
        temp = accede_element(*l,p-1);
        if(temp==NULL){
            erreur = -1;
        }else{
            avant = temp;
            e = temp->suivant;
            if(e == NULL){
                erreur = -1;
            }else {
                apres = e->suivant;
                avant->suivant = apres;
            } } }
    // on désalloue l'élément
    if(erreur != -1){
        free(e);
    }
    // on termine la fonction
    return erreur;
}
void trierListe(liste l){
    liste temp,temp1,temp2;
    Etudiant etudiant;
    for(temp=l; temp.debut!=NULL;temp.debut=temp.debut->suivant){
        temp2=temp;
        etudiant=temp.debut->etudiant;
        for(temp1.debut=temp.debut->suivant;temp1.debut!=NULL;temp1.debut=temp1.debut->suivant){
            if(comparer(etudiant.nom,temp1.debut->etudiant.nom)==1 ){
                temp2=temp1;
                etudiant=temp2.debut->etudiant;
            }
        }
        temp2.debut->etudiant=temp.debut->etudiant;
        temp.debut->etudiant=etudiant;
    }
}
void menuPrincipal(liste l){
    printf("-------------------------ACCEUIL-------------------------\n");
    printf("1.Ajouter un Etudiant\n");
    printf("2.Supprimer un Etudiant\n");
    printf("3.Afficher les etudiants\n");
    printf("4.Trier par Nom\n");
    printf("5.Quitter L'application\n");
    printf("--------------------------------------------------------\n");
    printf("Quel est votre choix:");
    int choix;
    scanf("%d",&choix);
    menu(choix,l);

}
Etudiant ajouterEtudiant(){
    Etudiant etudiant;
    scanf("%c",&etudiant.nom);
    printf("Entrer le nom de l'etudiant: ");
    gets(etudiant.nom);
    printf("Entrer le postnom de l'etudiant: ");
    gets(etudiant.postnom);
    printf("Entrer le matricule de l'etudiant: ");
    gets(etudiant.matricule);
    printf("Entrer la filiere de l'etudiant: ");
    gets(etudiant.filiere);
    return etudiant;
}
void menu(int choix, liste l){
    if(choix==1){
        printf("----------Ajouter un Etudiant----------\n");
        Etudiant etudiant=ajouterEtudiant();
        insere_element(&l,cree_element(etudiant),0);
        printf("Enregistrement Effectuer\n");
        subMenu(l);
        //printf("---------------------------------------\n");
    }else if(choix==2){
        printf("-----------------Supprimer un Etudiant-----------------\n");
        char matricule[8];
        scanf("%c",&matricule);
        printf("Matricul de l'etudiant: ");
        gets(matricule);
        int num= trouverPosition(&l,matricule);
        int erreur=supprime_element(&l,num);
        if(erreur==0){
            printf("suppression effectuer avec success\n");
            subMenu(l);
        }else{
            printf("suppression echecs, le matricule n'existe pas!\n");
            subMenu(l);
        }
    }else if(choix==3){
        printf("----------Afficher la liste des Etudiants----------\n");
        affiche_liste(l);
        subMenu(l);
    }else if(choix==4){
        printf("-------------------Liste des Etudiants Trier par Nom-------------------\n");
        trierListe(l);
        affiche_liste(l);
        subMenu(l);
    } else if(choix==5){
        printf("Vous avez quitter l'application");
    }else{
        printf("choix incorrect veilliez recommencer: ");
        scanf("%d",&choix);
        menu(choix,l);
    }

}
void subMenu(liste l){
    int choix;
    printf("---------------subMenu------------------\n");
    printf("1.Continuer...\n");
    printf("2.Quitter\n");
    printf("---------------subMenu------------------\n");
    printf("Que voulez vous faire? : ");
    scanf("%d",&choix);
    if(choix==1){
        menuPrincipal(l);
    }else if(choix==2){
        printf("Vous avez quitter l'application");
    }else{
        printf("choix incorrect, recommencer: ");
        scanf("%d",&choix);
        subMenu(l);
    }
}

