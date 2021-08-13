#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trab2.h"

int main()
{

    int option, isCand, qntdCand = 0, voteCard;
    Info *temp, aux;

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
            printf("Voce e um eleitor ou um candidato?\n1 - Eleitor ou 2 - Candidato: ");
            do
            {
                scanf("%d", &isCand);
                if (isCand < 1 || isCand > 2)
                    printf("Opcao invalida, digite novamente: ");
            } while (isCand < 1 || isCand > 2);

            if (isCand == 1)
            {
                temp = addNewPerson();
                insertOnTree(&titleTree, temp);
                printf("\nO eleitor '%s' foi adicionado...\n", temp->name);
            }
            else
            {
                qntdCand = addCand(qntdCand);
            }

            pauseExecution();
            cleanScreen();
            break;

        case 2:
            cleanScreen();
            printf("-------------------------------------------------------\n\n");
            inOrder(titleTree);
            printf("\n-------------------------------------------------------\n\n");

            printf("Digite o numero do titulo a ser removido: ");
            scanf("%d", &aux.voterCard);

            if (search(titleTree, aux.voterCard))
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
            break;

        case 3:
            printf("Uma nova votacao foi iniciada\nOs dados da antiga votacao foram perdidos\n\n");
            freeTree(titleTree);
            makeEmptyTree(&titleTree);
            qntdCand = 0;
            pauseExecution();
            break;

        case 4:
            if (qntdCand) // verifica se tem algum candidato cadastrado
            {
                cleanScreen();
                printf("Por favor, digite o numero do seu titulo: ");
                scanf("%d", &voteCard);

                if (search(titleTree, voteCard)) // verifica se o titulo digitado esta na arvore de titulos
                {
                    temp = (Info*)malloc(sizeof (Info));
                    temp->voterCard = voteCard;

                    pauseExecution();
                    if (!search(voteTree, temp->voterCard)) // se estiver, verifica se a pessoa ainda n votou
                    {
                        cleanScreen();
                        printf("---------------------- CANDIDATOS ----------------------\n\n");
                        printCands(qntdCand);
                        printf("\n-------------------------------------------------------\n\n");
                        printf("Digite o ID do candidato desejado: ");
                        do
                        {
                            scanf("%d", &temp->vote);
                            if (temp->vote < 1 || temp->vote > qntdCand)
                                printf("ID invalido, tente novamente: ");
                        } while (temp->vote < 1 || temp->vote > qntdCand);

                        candidatos[temp->vote - 1].qntdVotos++;

                        insertOnTree(&voteTree, temp);
                        printf("\nVoce votou no(a) candidato(a) %s\n\n", candidatos[temp->vote - 1].nomeCandidato);
                        pauseExecution();
                    }
                    else
                    {
                        printf("Voce ja votou uma vez, impossivel realizar outro voto...\n");
                        pauseExecution();
                    }
                }
                else
                {
                    printf("Titulo %d nao foi encontrado...\n", voteCard);
                }
            }
            else
            {
                printf("\nNENHUM CANDIDATO CADASTRADO\n\n");
                pauseExecution();
            }
            break;

        case 5:
            cleanScreen();
            printf("Por favor, digite o numero do seu titulo: ");
            scanf("%d", &aux.voterCard);

            // aux = *(search(titleTree, &aux));

            if (!search(titleTree, aux.voterCard))
            {
                printf("O titulo %d nao foi cadastrado...\n");
            }
            else
            {
                if (!search(voteTree, aux.voterCard))
                {
                    printf("Voce ainda nao votou, nao e possivel retirar o voto...\n");
                }
                else
                {
                    candidatos[aux.vote - 1].qntdVotos--;
                    removeFromTree(&voteTree, &aux);
                    printf("%s acabou de retirar seu voto.\n\n", aux.name);
                }
            }

            pauseExecution();

            break;

        case 6:
            if (qntdCand)
            {
                cleanScreen();
                printf("---------------------- RESULTADO PARCIAL ----------------------\n\n");
                printParcial(qntdCand);
                printf("\n-------------------------------------------------------\n\n");
                pauseExecution();
            }
            break;

        case 7:
            cleanScreen();
            printf("---------------------- ELEITORES ----------------------\n\n");
            if (!treeIsEmpty(titleTree))
                inOrder(titleTree);
            else
                printf("NENHUM ELEITOR CADASTRADO\n");
            printf("\n-------------------------------------------------------\n\n");
            pauseExecution();
            break;

        case 8:
            cleanScreen();
            printf("---------------------- CANDIDATOS ----------------------\n\n");
            if (qntdCand)
                printCands(qntdCand);
            else
                printf("NENHUM CANDIDATO CADASTRADO\n");
            printf("\n-------------------------------------------------------\n\n");
            pauseExecution();
            break;
        default:
            system(CLEAR);
            break;
        }
    } while (option != 9);

    return 0;
}