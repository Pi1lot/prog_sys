#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define stack element 
struct element {
    void *data;              // pointer to stored value 
    struct element *suivant; // next element 
    struct element *precedent; // previous element 
};

// define stack type 
typedef struct {
    struct element tete; // dummy head element 
    int taille;          // size of each element in bytes 
} PILE;

// initialize stack for elements of size 'taille' 
PILE *initialiser_pile(int taille)
{
    PILE *pile = malloc(sizeof(PILE));
    if (!pile) return NULL;
    pile->taille = taille;
    pile->tete.suivant = &pile->tete;
    pile->tete.precedent = &pile->tete;
    pile->tete.data = NULL;
    return pile;
}

// push an element onto the stack 
void empiler(PILE *pile, void *valeur)
{
    struct element *elem = malloc(sizeof(struct element));
    if (!elem) return;
    elem->data = malloc(pile->taille);
    if (!elem->data) {
        free(elem);
        return;
    }
    memcpy(elem->data, valeur, pile->taille);

    // insert at the head (after dummy) 
    elem->suivant = pile->tete.suivant;
    elem->precedent = &pile->tete;
    pile->tete.suivant->precedent = elem;
    pile->tete.suivant = elem;
}

// check if stack is empty 
int pile_vide(PILE *pile)
{
    return pile->tete.suivant == &pile->tete;
}

// pop an element from the stack and copy to valeur 
void depiler(PILE *pile, void *valeur)
{
    if (pile_vide(pile)) return;

    struct element *elem = pile->tete.suivant;

    // remove from list 
    elem->suivant->precedent = &pile->tete;
    pile->tete.suivant = elem->suivant;

    memcpy(valeur, elem->data, pile->taille);
    free(elem->data);
    free(elem);
}

// free the entire stack 
void free_pile(PILE *pile)
{
    while (!pile_vide(pile)) {
        char buffer[pile->taille];
        depiler(pile, buffer);
    }
    free(pile);
}

// example usage 
int main(void)
{
    PILE *pile = initialiser_pile(sizeof(int));
    if (!pile) {
        fprintf(stderr, "Failed to initialize stack\n");
        return 1;
    }

    int a = 10, b = 20, c = 30;
    empiler(pile, &a);
    empiler(pile, &b);
    empiler(pile, &c);

    printf("Popping values:\n");
    while (!pile_vide(pile)) {
        int x;
        depiler(pile, &x);
        printf("%d\n", x);
    }

    free_pile(pile);
    return 0;
}
