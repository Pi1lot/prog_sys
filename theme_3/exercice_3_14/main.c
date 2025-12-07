#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* define node type */
enum code { noeud, feuille };

struct noeud {
    enum code code;
    union {
        int valeur;
        struct {
            char operation;
            struct noeud *fils_gauche;
            struct noeud *fils_droit;
        } s;
    } u;
};

typedef struct noeud Noeud;

/* create a leaf node with an integer value */
Noeud *create_leaf(int value)
{
    Noeud *n = malloc(sizeof(Noeud));
    n->code = feuille;
    n->u.valeur = value;
    return n;
}

/* create an internal node with operation and two children */
Noeud *create_node(char op, Noeud *left, Noeud *right)
{
    Noeud *n = malloc(sizeof(Noeud));
    n->code = noeud;
    n->u.s.operation = op;
    n->u.s.fils_gauche = left;
    n->u.s.fils_droit = right;
    return n;
}

/* read a prefix expression from stdin and build the tree */
Noeud *lire_prefixe(void)
{
    char c;
    while (scanf(" %c", &c) == 1) {
        if (isdigit(c)) {
            ungetc(c, stdin);
            int value;
            scanf("%d", &value);
            return create_leaf(value);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            Noeud *left = lire_prefixe();
            Noeud *right = lire_prefixe();
            return create_node(c, left, right);
        }
    }
    return NULL;
}

/* write the tree in prefix notation */
void ecrire_prefixe(Noeud *arbre)
{
    if (!arbre) return;
    if (arbre->code == feuille) {
        printf("%d ", arbre->u.valeur);
    } else {
        printf("%c ", arbre->u.s.operation);
        ecrire_prefixe(arbre->u.s.fils_gauche);
        ecrire_prefixe(arbre->u.s.fils_droit);
    }
}

/* compute the depth of the tree */
int profondeur_arbre(Noeud *arbre)
{
    if (!arbre) return 0;
    if (arbre->code == feuille) return 1;
    int left_depth = profondeur_arbre(arbre->u.s.fils_gauche);
    int right_depth = profondeur_arbre(arbre->u.s.fils_droit);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

/* operation functions */
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

/* evaluate the expression using a function pointer table */
int evaluer_arbre(Noeud *arbre)
{
    if (!arbre) return 0;
    if (arbre->code == feuille) return arbre->u.valeur;

    int left = evaluer_arbre(arbre->u.s.fils_gauche);
    int right = evaluer_arbre(arbre->u.s.fils_droit);

    /* define a table of function pointers corresponding to operations */
    struct { char op; int (*func)(int,int); } table[] = {
        {'+', add},
        {'-', sub},
        {'*', mul},
        {'/', divide},
        {0, NULL} // sentinel
    };

    for (int i = 0; table[i].op != 0; i++) {
        if (arbre->u.s.operation == table[i].op)
            return table[i].func(left, right);
    }

    return 0; // should not happen
}

/* write the expression in infix notation */
void ecrire_algebrique(Noeud *arbre)
{
    if (!arbre) return;
    if (arbre->code == feuille) {
        printf("%d", arbre->u.valeur);
    } else {
        printf("(");
        ecrire_algebrique(arbre->u.s.fils_gauche);
        printf(" %c ", arbre->u.s.operation);
        ecrire_algebrique(arbre->u.s.fils_droit);
        printf(")");
    }
}

/* free the memory of the tree */
void free_tree(Noeud *arbre)
{
    if (!arbre) return;
    if (arbre->code == noeud) {
        free_tree(arbre->u.s.fils_gauche);
        free_tree(arbre->u.s.fils_droit);
    }
    free(arbre);
}

int main(void)
{
    printf("Enter a prefix expression (e.g. * * 3 + 1 2 + 4 5):\n");
    Noeud *arbre = lire_prefixe();

    printf("Prefix notation: ");
    ecrire_prefixe(arbre);
    printf("\n");

    printf("Infix notation: ");
    ecrire_algebrique(arbre);
    printf("\n");

    int depth = profondeur_arbre(arbre);
    printf("Tree depth: %d\n", depth);

    int result = evaluer_arbre(arbre);
    printf("Evaluation result: %d\n", result);

    free_tree(arbre);

    return 0;
}
