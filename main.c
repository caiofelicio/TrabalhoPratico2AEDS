#include <stdio.h>
#include <stdlib.h>
#include "trab2.h"

int main()
{

    int option = 0, voteCard = 0, hasVotation = 0;

    Info *aux = (Info *)malloc(sizeof(Info)), *temp = (Info *)malloc(sizeof(Info)), copy;

    makeEmptyTree(&titleTree);
    makeEmptyTree(&voteTree);

    do
    {
        system(CLEAR);
        showMenu();

        printf("\nEscolha uma opcao: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            temp = addNewPerson();
            insertOnTree(&titleTree, temp);
            printf("\nO eleitor '%s' foi adicionado...\n", temp->name);
            pauseExecution();
            cleanScreen();
            temp = NULL;
            break;

        case 2:
            cleanScreen();
            printf("-------------------------------------------------------\n\n");
            inOrder(titleTree);
            printf("\n-------------------------------------------------------\n\n");

            printf("Digite o numero do titulo a ser removido: ");
            scanf("%d", &voteCard);

            temp = search(titleTree, voteCard);
            if (temp)
            {
                removeFromTree(&titleTree, temp);
                printf("\n\n%s foi removido(a)!\n", temp->name);
                pauseExecution();
            }
            else
            {
                printf("\n\nTitulo nao encontrado...\n");
                pauseExecution();
            }
            temp = NULL;
            break;

        case 3:

            if (hasVotation)
            {
                printf("Uma nova votacao foi iniciada\nOs dados da antiga votacao foram perdidos\n\n");
                printf("O vencendor da antiga votacao e '%s' com %d votos.\n", checkWinner(titleTree).name,
                       checkWinner(titleTree).qntdVotes);
                freeTree(titleTree);
                freeTree(voteTree);
                makeEmptyTree(&titleTree);
                makeEmptyTree(&voteTree);
            }
            else
            {
                hasVotation = 1;
                printf("Uma nova votacao foi iniciada...\n");
            }

            pauseExecution();

            break;

        case 4:
            if (!hasVotation)
            {
                printf("Inicie uma votacao antes de comecar a votar...\n");
            }
            else
            {
                cleanScreen();
                printf("Por favor, digite o numero do seu titulo: ");
                scanf("%d", &voteCard);

                if (search(titleTree, voteCard)) // verifica se o titulo digitado esta na arvore de titulos
                {

                    aux = search(titleTree, voteCard);

                    if (!search(voteTree, aux->voterCard)) // se estiver, verifica se a pessoa ainda n votou
                    {
                        cleanScreen();
                        printf("---------------------- CANDIDATOS ----------------------\n\n");
                        inOrder(titleTree);
                        printf("\n-------------------------------------------------------\n\n");
                        printf("Digite o numero do titulo do candidato desejado: ");
                        do
                        {
                            scanf("%d", &voteCard);
                            temp = search(titleTree, voteCard);
                            if (!temp)
                            {
                                printf("Numero invalido, tente novamente: ");
                            }
                        } while (!temp);
                        temp->qntdVotes++;
                        aux->vote = voteCard;
                        aux->hasVoted = 1;

                        copy = *aux;
                        insertOnTree(&voteTree, &copy);
                        printf("Voce votou em '%s'\n", temp->name);
                    }
                    else
                    {
                        printf("Voce ja votou uma vez, impossivel realizar outro voto...\n");
                    }
                }
                else
                {
                    printf("Titulo %d nao foi encontrado...\n", voteCard);
                }
            }
            pauseExecution();
            temp = NULL;
            break;

        case 5:
            cleanScreen();
            printf("Por favor, digite o numero do seu titulo: ");
            scanf("%d", &voteCard);

            temp = search(titleTree, voteCard);

            if (!temp)
            {
                printf("O titulo %d nao foi cadastrado...\n", voteCard);
            }
            else
            {
                if (!search(voteTree, voteCard))
                { // se a pessoa ainda nao votou
                    printf("Voce ainda nao votou, nao e possivel retirar o voto...\n");
                }
                else
                { // se tiver votado
                    temp->hasVoted = 0;
                    temp->vote = 0;
                    voteCard = temp->vote;
                    printf("\n%s acabou de retirar seu voto.\n\n", temp->name);
                    removeFromTree(&voteTree, temp);

                    aux = search(titleTree, voteCard);
                    if (aux)
                    {
                        removeFromTree(&titleTree, aux);
                        aux->qntdVotes--;
                        insertOnTree(&titleTree, aux);
                    }
                }
            }
            temp = NULL;
            pauseExecution();

            break;

        case 6:
            cleanScreen();
            printf("---------------------- RESULTADO PARCIAL ----------------------\n\n");
            if (!treeIsEmpty(titleTree))
                printParcial(titleTree);
            else
                printf("NAO EXISTE NENHUMA VOTACAO EM ANDAMENTO...\n");
            printf("\n-------------------------------------------------------\n\n");
            pauseExecution();
            break;

        case 7:
            cleanScreen();
            printf("---------------------- ELEITORES ----------------------\n");
            if (!treeIsEmpty(titleTree))
                inOrder(titleTree);
            else
                printf("\nNENHUM ELEITOR CADASTRADO\n");
            printf("\n-------------------------------------------------------\n\n");
            pauseExecution();
            break;

        default:
            system(CLEAR);
            break;
        }
    } while (option != 8);

    free(temp);
    free(aux);
    if (titleTree)
        freeTree(titleTree);
    if (voteTree)
        freeTree(voteTree);

    return 0;
}