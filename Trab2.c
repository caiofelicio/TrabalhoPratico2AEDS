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
    printf("-------------------------------------------------\n");
    printf("|           1) Cadastrar eleitor/candidato      |\n");
    printf("|           2) Descadastrar um titulo           |\n");
    printf("|           3) Iniciar votacao                  |\n");
    printf("|           4) Votar                            |\n");
    printf("|           5) Retirar voto                     |\n");
    printf("|           6) Resultado parcial                |\n");
    printf("|           7) Listar Eleitores                 |\n");
    printf("|           8) Listar Candidatos                |\n");
    printf("|           9) Encerrar programa                |\n");
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
        return NULL;

    if (info->voterCard < root->info->voterCard)
        return search(root->left, info);

    if (info->voterCard > root->info->voterCard)
        return search(root->right, info);

    aux = root->info;
    return aux;
}

int removeFromTree(Node **root, Info *info)
{
    Node *aux;

    if (*root == NULL)
        return 0;

    if (info->voterCard < (*root)->info->voterCard)
        return removeFromTree(&(*root)->left, info);

    if (info->voterCard > (*root)->info->voterCard)
        return removeFromTree(&(*root)->right, info);

    if ((*root)->right == NULL)
    {
        aux = *root;
        aux->info->vote = -1;
        *root = (*root)->left;
        *info = *aux->info;
        free(aux);
        return 1;
    }

    if ((*root)->left == NULL)
    {
        aux = *root;
        aux->info->vote = -1;
        *root = (*root)->right;
        *info = *aux->info;
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

        if (newPerson->voterCard < 1 || search(titleTree, newPerson))
        {
            printf("\nNumero de titulo invalido ou ja esta cadastrado. Tente novamente...\n\n");
        }

    } while (newPerson->voterCard < 1 || search(titleTree, newPerson));

    newPerson->vote = -1;

    return newPerson;
}

int addCand(int qntdCand)
{
    if (qntdCand >= MAX_CAND)
    {
        printf("Numero maximo de candidatos ja cadastrados...\n");
        return qntdCand;
    }
    else
    {
        fflush(stdin);
        printf("\nQual e o seu nome: ");
        fgets(candidatos[qntdCand].nomeCandidato, 50, stdin);
        candidatos[qntdCand].nomeCandidato[strcspn(candidatos[qntdCand].nomeCandidato, "\n")] = 0;

        fflush(stdin);
        printf("Qual e o seu partido: ");
        fgets(candidatos[qntdCand].partido, 7, stdin);
        candidatos[qntdCand].partido[strcspn(candidatos[qntdCand].partido, "\n")] = 0;

        candidatos[qntdCand].qntdVotos = 0;
        candidatos[qntdCand].ID = qntdCand + 1;

        printf("\nCandidato '%s' do partido '%s' foi cadastrado...\n\n", candidatos[qntdCand].nomeCandidato, candidatos[qntdCand].partido);

        return 1 + qntdCand;
    }
}

void inOrder(Node *root)
{
    if (root)
    {
        inOrder(root->left);
        if (search(voteTree, root->info))
            printf("Nome: %s\nNumero do titulo: %d\nJa votou: Sim\n\n", root->info->name, root->info->voterCard);
        else
            printf("Nome: %s\nNumero do titulo: %d\nJa votou: Nao\n\n", root->info->name, root->info->voterCard);
        inOrder(root->right);
    }
}

void printCands(int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Canditado %d:\n   Nome: %s\n   Partido: %s\n   ID: %d\n\n", i + 1, candidatos[i].nomeCandidato, candidatos[i].partido, candidatos[i].ID);
    }
}

void printParcial(int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Canditado %d:\n   Nome: %s\n   Partido: %s\n   Votos: %d\n\n", i + 1, candidatos[i].nomeCandidato, candidatos[i].partido, candidatos[i].qntdVotos);
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
        // free(root->info);
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