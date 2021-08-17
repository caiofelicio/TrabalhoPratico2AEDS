#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trab2.h"

void showMenu() {
    printf("-------------------------------------------------\n");
    printf("|                                               |\n");
    printf("|              SISTEMA DE VOTACAO               |\n");
    printf("|                                               |\n");
    printf("-------------------------------------------------\n");
    printf("|           1) Cadastrar titulo                 |\n");
    printf("|           2) Descadastrar um titulo           |\n");
    printf("|           3) Iniciar votacao                  |\n");
    printf("|           4) Votar                            |\n");
    printf("|           5) Retirar voto                     |\n");
    printf("|           6) Resultado parcial                |\n");
    printf("|           7) Listar Eleitores                 |\n");
    printf("|           8) Encerrar programa                |\n");
    printf("-------------------------------------------------\n");
}

void makeEmptyTree(Node **root) {
    *root = NULL;
}

int insertOnTree(Node **root, Info *info) {

    if (*root == NULL) {
        *root = (Node *) malloc(sizeof(Node));
        (*root)->info = info;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return 1;
    } else {
        if (info->voterCard < (*root)->info->voterCard)
            return insertOnTree(&((*root)->left), info);

        else if (info->voterCard > (*root)->info->voterCard)
            return insertOnTree(&((*root)->right), info);
    }
    return 0;
}

Info *search(Node *root, int info) {
    Info *aux = NULL;

    if (root == NULL)
        return NULL;

    if (info < root->info->voterCard)
        return search(root->left, info);

    if (info > root->info->voterCard)
        return search(root->right, info);

    aux = root->info;
    return aux;
}

int removeFromTree(Node **root, Info *info) {
    Node *aux;

    if (*root == NULL)
        return 0;

    if (info->voterCard < (*root)->info->voterCard)
        return removeFromTree(&(*root)->left, info);

    if (info->voterCard > (*root)->info->voterCard)
        return removeFromTree(&(*root)->right, info);

    if ((*root)->right == NULL) {
        aux = *root;
        aux->info->hasVoted = 0;
        *root = (*root)->left;
        *info = *aux->info;
        free(aux);
        return 1;
    }

    if ((*root)->left == NULL) {
        aux = *root;
        aux->info->hasVoted = 0;
        *root = (*root)->right;
        *info = *aux->info;
        free(aux);
        return 1;
    }

    next(&(*root)->right, *root);
    return 1;
}

void next(Node **root, Node *no) {
    Node *aux;

    if ((*root)->left != NULL) {
        next(&(*root)->left, no);
        return;
    }

    no->info = (*root)->info;
    aux = *root;
    *root = (*root)->right;
    free(aux);
}

Info *addNewPerson() {
    Info *newPerson = (Info *) malloc(sizeof(Info));

    fflush(stdin);
    printf("\nDigite seu nome: ");
    fgets(newPerson->name, 50, stdin);
    newPerson->name[strcspn(newPerson->name, "\n")] = 0; // removendo o caractere \n

    do {
        printf("Digite o numero do titulo: ");
        scanf("%d", &newPerson->voterCard);

        if (newPerson->voterCard < 1 || search(titleTree, newPerson->voterCard)) {
            printf("\nNumero de titulo invalido ou ja esta cadastrado. Tente novamente...\n\n");
        }

    } while (newPerson->voterCard < 1 || search(titleTree, newPerson->voterCard));

    newPerson->hasVoted = 0;
    newPerson->vote = 0;
    newPerson->qntdVotes = 0;
    return newPerson;
}

Info checkWinner(Node *root) {
    static int winnerTitleNumber = 0;
    static Info winner;

    winner.qntdVotes = -1;

    if (root) {
        checkWinner(root->left);
        checkWinner(root->right);
        if (root->info->qntdVotes > winner.qntdVotes)
            winner = *(root->info);
    }

    return winner;
}

void inOrder(Node *root) {
    if (root) {
        inOrder(root->left);
        if(root->info->hasVoted)
            printf("\nNome: %s\nNumero do titulo: %d\nJa votou: Sim\n", root->info->name, root->info->voterCard);
        else
            printf("\nNome: %s\nNumero do titulo: %d\nJa votou: Nao\n", root->info->name, root->info->voterCard);
        inOrder(root->right);
    }
}

void printParcial(Node *root) {
    if (root) {
        printParcial(root->left);
        printParcial(root->right);
        printf("\nNome: %s\nNumero de votos: %d\n", root->info->name, root->info->qntdVotes);
    }
}

int treeIsEmpty(Node *tree) {
    return tree == NULL;
}

void freeTree(Node *root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->info);
        free(root);
    }
}

// extra functions
void cleanScreen() {
    system(CLEAR);
}

void pauseExecution() {
    if (IS_WINDOWS)
        system("pause");
    else {
        printf("Pressione ENTER para voltar ao menu...");
        getchar();
    }
}