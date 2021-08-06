#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trab2.h"

void showMenu()
{
    printf("-------------------------------------------------\n");
    printf("|                                               |\n");
    printf("|              SISTEMA DE VOTACAO               |\n");
    printf("|                                               |\n");
    printf("|           1) Cadastrar um titulo              |\n");
    printf("|           2) Descadastrar um titulo           |\n");
    printf("|           3) Iniciar votacao                  |\n");
    printf("|           4) Votar                            |\n");
    printf("|           5) Retirar voto                     |\n");
    printf("|           6) Resultado parcial                |\n");
    printf("|           7) Listar numeros e titulos         |\n");
    printf("|           8) Encerrar programa                |\n");
    printf("|                                               |\n");
    printf("-------------------------------------------------\n");
}

void makeEmptyTree(Node **root)
{
    *root = NULL;
}

int insertOnTree(Node **root, Info *info)
{

    if (*root == NULL)
    {
        *root = (Node *)malloc(sizeof(Node));
        (*root)->info = info;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return 1;
    }
    else
    {
        if (strcmp(info->name, (*root)->info->name) < 0)
            return insertOnTree(&((*root)->left), info);

        else if (strcmp(info->name, (*root)->info->name) > 0)
            return insertOnTree(&((*root)->right), info);
    }
    return 0;
}

Info *search(Node *root, Info *info)
{
    Info *aux = NULL;

    if (root == NULL)
        return aux;

    if (info->voterCard < root->info->voterCard)
        return search(root->left, info);

    if (info->voterCard > root->info->voterCard)
        return search(root->right, info);

    aux = root->info;
    return aux;
}

int removeFromTree(Node **root, Info info)
{
    Node *aux;

    if (*root == NULL)
        return 0;

    if (info.voterCard < (*root)->info->voterCard)
        return removeFromTree(&(*root)->left, info);

    if (info.voterCard > (*root)->info->voterCard)
        return removeFromTree(&(*root)->right, info);

    if ((*root)->right == NULL)
    {
        aux = *root;
        *root = (*root)->left;
        free(aux);
        return 1;
    }

    if ((*root)->left == NULL)
    {
        aux = *root;
        *root = (*root)->right;
        free(aux);
        return 1;
    }

    next(&(*root)->right, *root);
    return 1;
}

void next(Node **root, Node *no)
{
    Node *aux;

    if ((*root)->left != NULL)
    {
        next(&(*root)->left, no);
        return;
    }

    no->info = (*root)->info;
    aux = *root;
    *root = (*root)->right;
    free(aux);
}

Info *addNewPerson()
{
    Info *newPerson = (Info *)malloc(sizeof(Info));

    fflush(stdin);
    printf("\nDigite seu nome: ");
    fgets(newPerson->name, 50, stdin);
    newPerson->name[strcspn(newPerson->name, "\n")] = 0;

    do
    {
        printf("Digite o numero do titulo: ");
        scanf("%d", &newPerson->voterCard);
    } while (newPerson->voterCard < 1);

    return newPerson;
}

void inOrder(Node *root)
{
    if (root)
    {
        inOrder(root->left);
        printf("Nome: %s - Numero do titulo: %d\n", root->info->name, root->info->voterCard);
        inOrder(root->right);
    }
}

int treeIsEmpty(Node *tree)
{
    return tree == NULL;
}

void freeTree(Node *root)
{
    if (root)
    {
        freeTree(root->left);
        freeTree(root->right);
        //free(root->info);
        free(root);
    }
}

// extra functions
void cleanScreen()
{
    system(CLEAR);
}

void pauseExecution()
{
    if (IS_WIN)
        system("pause");
    else
    {
        printf("Pressione ENTER para voltar ao menu...");
        getchar();
    }
}