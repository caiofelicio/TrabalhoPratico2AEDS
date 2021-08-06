#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trab2.h"

int main()
{

    int option;
    char byNameOrTitle;
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
            temp = addNewPerson();
            insertOnTree(&titleTree, temp);
            printf("\n%s foi adicionado...\n", temp->name);
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

            temp = search(titleTree, &aux);
            if (temp)
            {
                removeFromTree(&titleTree, *temp);
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
            printf("Uma nova votação foi iniciada\nOs dados da antiga votação foram perdidos\n\n");
            freeTree(titleTree);
            break;

        case 4:
            /* code */
            break;

        case 5:
            /* code */
            break;

        case 6:
            /* code */
            break;

        case 7:
            cleanScreen();
            printf("---------------------- ELEITORES ----------------------\n\n");
            if(!treeIsEmpty(titleTree))
                inOrder(titleTree);
            else
                printf("\tNENHUM ELEITOR CADASTRADO");
            printf("\n-------------------------------------------------------\n\n");
            pauseExecution();
            break;

        case 8:
            /* code */
            break;

        default:
            system(CLEAR);
            break;
        }
    } while (option != 8);

    return 0;
}