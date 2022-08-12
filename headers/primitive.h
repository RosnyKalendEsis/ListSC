//
// Created by Rosny Kalend on 06/08/2022.
//

#ifndef LISTSC_PRIMITIVE_H
#define LISTSC_PRIMITIVE_H
typedef struct etudiant{
    char matricule[8];
    char nom[25];
    char postnom[25];
    char filiere[25];
}Etudiant;

typedef struct element {
    Etudiant etudiant ;
    struct element *suivant;
} element;

typedef struct {
    element *debut;
} liste;

element* cree_element(Etudiant etudiant);
void affiche_liste(liste l);
element* accede_element(liste l, int p);
int insere_element(liste *l, element *e, int p);
int supprime_element(liste *l, int position);
void afficherEtudiant(Etudiant etudiant);
void trierListe(liste l);
int comparer(char *chaine, char *chaine2);
int trouverPosition(liste *l, char *nom);
void menuPrincipal(liste l);
Etudiant ajouterEtudiant();
void menu(int choix, liste l);
void subMenu(liste l);

#endif //LISTSC_PRIMITIVE_H
