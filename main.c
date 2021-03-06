#include <stdio.h>
#include <stdlib.h>
#include "trab2.h"

int main()
{
    /* definindo variáveis utilizadas */
    int option = 0, voteCard = 0, hasVotation = 0, count = 0, index = 0;

    Info *aux = (Info *)malloc(sizeof(Info));
    Info *temp = (Info *)malloc(sizeof(Info));
    Info *arrayAux = NULL;

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
        {
            temp = addNewPerson();
            insertOnTree(&titleTree, temp);
            printf("\nO eleitor '%s' foi adicionado...\n", temp->name);
            pauseExecution();
            cleanScreen();
            temp = NULL;
            break;
        }
        case 2:
        {
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
        }
        case 3:
        {
            if (hasVotation)
            {
                printf("\nUma nova votacao foi iniciada\nOs dados da antiga votacao foram perdidos\n\n");
                resetData(&titleTree);
                freeTree(voteTree);
                makeEmptyTree(&voteTree);
            }
            else
            {
                hasVotation = 1;
                printf("\nUma nova votacao foi iniciada...\n");
            }
            pauseExecution();
            break;
        }
        case 4:
        {
            if (!hasVotation)
            {
                printf("\nInicie uma votacao antes de comecar a votar...\n");
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
                                printf("Nenhuma pessoa encontrada com o titulo %d.\nTente novamente: ", voteCard);
                            }
                        } while (!temp);
                        temp->qntdVotes++;
                        aux->vote = voteCard;
                        aux->hasVoted = 1;
                        insertOnTree(&voteTree, aux);
                        printf("Voce votou em '%s'\n", temp->name);
                        aux = NULL;
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
        }
        case 5:
        {
            Info aux2;

            cleanScreen();
            setbuf(stdin, NULL);
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
                {
                    // se a pessoa ainda nao votou
                    printf("Voce ainda nao votou, nao e possivel retirar o voto...\n");
                }
                else
                {
                    // se tiver votacao
                    temp->hasVoted = 0;
                    voteCard = temp->vote;
                    aux = search(titleTree, voteCard);
                    temp->vote = 0;
                    aux2 = *aux;
                    aux2.qntdVotes--;
                    removeFromTree(&titleTree, aux);
                    insertOnTree(&titleTree, &aux2);

                    printf("\n%s acabou de retirar seu voto.\n\n", temp->name);
                    removeFromTree(&voteTree, temp);
                }
            }
            temp = NULL;
            pauseExecution();
            break;
        }
        case 6:
        {
            cleanScreen();
            printf("---------------------- RESULTADO PARCIAL ----------------------\n\n");
            if (!treeIsEmpty(titleTree))
            {
                count = getNumberOfNodes(titleTree);
                arrayAux = (Info *)malloc(count * sizeof(Info));
                copyTreeToArray(titleTree, arrayAux, &index);
                sortArrayByNumberOfVotes(arrayAux, count);
                for (int i = 0; i < count; i++)
                {
                    printf("\nNome: %s\nNumero de votos: %d\n", arrayAux[i].name, arrayAux[i].qntdVotes);
                }
                index = 0;
                free(arrayAux);
            }
            else
                printf("NAO EXISTE NENHUMA VOTACAO EM ANDAMENTO...\n");
            printf("\n-------------------------------------------------------\n\n");
            pauseExecution();
            break;
        }
        case 7:
        {
            cleanScreen();
            printf("---------------------- ELEITORES ----------------------\n");
            if (!treeIsEmpty(titleTree))
                inOrder(titleTree);
            else
                printf("\nNENHUM ELEITOR CADASTRADO\n");
            printf("\n-------------------------------------------------------\n\n");
            pauseExecution();
            break;
        }

        default:
            system(CLEAR);
            break;
        }
    } while (option != 8);

    free(temp);
    free(aux);
    if (!treeIsEmpty(titleTree))
        freeTree(titleTree);
    if (!treeIsEmpty(voteTree))
        freeTree(voteTree);

    return 0;
}