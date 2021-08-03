#include <stdio.h>
#include <stdlib.h>
#include "Trab2.h"

void makeEmptyTree(Node **root)
{
    *root = NULL;
}

void addNewVoterCard()
{
    Info *newVoter = (Info *)malloc(sizeof(Info));

    printf("Digite seu nome: ");
    fgets(newVoter->name, 50, stdin);

    fflush(stdin);

    do
    {
        printf("Digite o numero do titulo");
        scanf("%d", &newVoter->voterCard);
    } while (newVoter->vote < 1);
}

void freeTree(Node *root)
{
    if (root)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
