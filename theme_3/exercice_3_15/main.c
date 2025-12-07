#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define the doubly linked list element structure 
struct element {
    int clef;              // key 
    char *valeur;          // associated value 
    struct element *suivant;    // next element 
    struct element *precedent;  // previous element 
};

// head of the list 
struct element tete;

// initialize the list 
void initialiser_liste(void)
{
    tete.suivant = &tete;
    tete.precedent = &tete;
    tete.clef = 0;
    tete.valeur = NULL;
}

// add an element in sorted order by key 
void ajouter_element(int clef, char *valeur)
{
    struct element *new_elem = malloc(sizeof(struct element));
    if (!new_elem) return;

    new_elem->clef = clef;
    new_elem->valeur = strdup(valeur); // copy the string 
    if (!new_elem->valeur) {
        free(new_elem);
        return;
    }

    // find insertion point 
    struct element *current = tete.suivant;
    while (current != &tete && current->clef < clef) {
        current = current->suivant;
    }

    // insert before current 
    new_elem->suivant = current;
    new_elem->precedent = current->precedent;
    current->precedent->suivant = new_elem;
    current->precedent = new_elem;
}

// read value by key, return pointer to value or NULL 
char *lire_valeur(int clef)
{
    struct element *current = tete.suivant;
    while (current != &tete) {
        if (current->clef == clef) return current->valeur;
        current = current->suivant;
    }
    return NULL;
}

// remove element by key 
void retirer_element(int clef)
{
    struct element *current = tete.suivant;
    while (current != &tete) {
        if (current->clef == clef) {
            current->precedent->suivant = current->suivant;
            current->suivant->precedent = current->precedent;
            free(current->valeur);
            free(current);
            return;
        }
        current = current->suivant;
    }
}

// print list for debugging 
void afficher_liste(void)
{
    struct element *current = tete.suivant;
    while (current != &tete) {
        printf("Key: %d, Value: %s\n", current->clef, current->valeur);
        current = current->suivant;
    }
}

int main(void)
{
    initialiser_liste();

    ajouter_element(5, "five");
    ajouter_element(2, "two");
    ajouter_element(8, "eight");

    printf("List after insertion:\n");
    afficher_liste();

    char *val = lire_valeur(2);
    if (val) printf("Value for key 2: %s\n", val);

    retirer_element(5);
    printf("List after removing key 5:\n");
    afficher_liste();

    // free remaining elements 
    while (tete.suivant != &tete) {
        retirer_element(tete.suivant->clef);
    }

    return 0;
}
