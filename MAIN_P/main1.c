#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/bib1.h"

int main(){
	QList *head = NULL;
    PList *p_head = NULL;
	PartieList *partie_head = NULL;
	int partiesNbr = 0;
	int Qnbr = 0, Pnbr = 0;
	int choice, id;
	
	// load data from files
	Pnbr= LoadPlayers(&p_head);
	Qnbr = LoadQuestions(&head);
	partiesNbr = LoadParties(&partie_head, head);
	
    do {
        //printf("\033[2J"); 
        printf("%s%s=========== Welcome back ===========%s\n", BOLD, CYAN, RESET);
        printf("%s%sAre you: \n\t%s1. PLAYER \n\t2. Admin\n\t0. Exit...\n", BOLD, YELLOW, BLUE);
        printf("%sEnter your choice: %s", GREEN, RESET);
        readInt(&choice);
        printf("%d",choice);
        switch (choice) {
            case 1:
                PlayerMenu(head, &p_head,&partie_head);
                break;
            case 2:
                AdminMenu(&head, &p_head,&partie_head, &Qnbr,&Pnbr, &partiesNbr);
                break;
            case 0:
                printf("Exiting , tchaw \n");
				SavePlayers(p_head);
				SaveQuestions(head);
				SaveParties(partie_head);
                /*
                    save players and questions lists to files
                */
                break;
            default:
                printf(" Please try again.\n");
                break;
        }
    } while (choice != 0);
	return 0;

}