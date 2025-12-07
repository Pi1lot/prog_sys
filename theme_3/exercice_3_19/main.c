#include <stdio.h>
#include <stdlib.h>

/* Node representing non-zero element of sparse matrix */
struct element {
    int i;        // row index
    int j;        // column index
    double v;     // value
    struct element *suivant;
};

typedef struct element * matrice;

/* create a new element */
matrice creer_element(int i, int j, double v) {
    matrice e = malloc(sizeof(struct element));
    if (!e) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    e->i = i;
    e->j = j;
    e->v = v;
    e->suivant = NULL;
    return e;
}

/* add two sparse matrices */
matrice ajouter_matrice(matrice M1, matrice M2, int n) {
    matrice resultat = NULL, queue = NULL;
    matrice p1 = M1, p2 = M2;

    // copy all elements from M1
    while (p1) {
        matrice e = creer_element(p1->i, p1->j, p1->v);
        if (!resultat) resultat = e;
        else queue->suivant = e;
        queue = e;
        p1 = p1->suivant;
    }

    // add elements from M2, summing values if same (i,j)
    while (p2) {
        matrice p = resultat;
        int found = 0;
        while (p) {
            if (p->i == p2->i && p->j == p2->j) {
                p->v += p2->v;
                found = 1;
                break;
            }
            p = p->suivant;
        }
        if (!found) {
            matrice e = creer_element(p2->i, p2->j, p2->v);
            if (!resultat) resultat = e;
            else queue->suivant = e;
            queue = e;
        }
        p2 = p2->suivant;
    }

    return resultat;
}

/* multiply two sparse matrices (naive method) */
matrice multiplier_matrice(matrice M1, matrice M2, int n) {
    matrice resultat = NULL, queue = NULL;
    for (matrice e1 = M1; e1; e1 = e1->suivant) {
        for (matrice e2 = M2; e2; e2 = e2->suivant) {
            if (e1->j == e2->i) {
                // position in result
                int i = e1->i;
                int j = e2->j;
                double v = e1->v * e2->v;

                // check if already exists
                matrice p = resultat;
                int found = 0;
                while (p) {
                    if (p->i == i && p->j == j) {
                        p->v += v;
                        found = 1;
                        break;
                    }
                    p = p->suivant;
                }
                if (!found) {
                    matrice e = creer_element(i, j, v);
                    if (!resultat) resultat = e;
                    else queue->suivant = e;
                    queue = e;
                }
            }
        }
    }
    return resultat;
}

/* print sparse matrix */
void afficher_matrice(matrice M) {
    while (M) {
        printf("(%d,%d) = %f\n", M->i, M->j, M->v);
        M = M->suivant;
    }
}

/* free sparse matrix */
void liberer_matrice(matrice M) {
    while (M) {
        matrice tmp = M;
        M = M->suivant;
        free(tmp);
    }
}

int main(void) {
    // Example: 3x3 matrices
    matrice A = NULL;
    matrice B = NULL;

    // A: non-zero elements
    A = creer_element(0, 0, 1.0);
    A->suivant = creer_element(1, 2, 2.0);

    // B: non-zero elements
    B = creer_element(0, 0, 3.0);
    B->suivant = creer_element(1, 2, 4.0);
    B->suivant->suivant = creer_element(2, 1, 5.0);

    printf("Matrix A:\n");
    afficher_matrice(A);
    printf("Matrix B:\n");
    afficher_matrice(B);

    matrice C = ajouter_matrice(A, B, 3);
    printf("A + B:\n");
    afficher_matrice(C);

    matrice D = multiplier_matrice(A, B, 3);
    printf("A * B:\n");
    afficher_matrice(D);

    // free memory
    liberer_matrice(A);
    liberer_matrice(B);
    liberer_matrice(C);
    liberer_matrice(D);

    return 0;
}
