
#include "../lib/bib.h"
#include <stdio.h>

void main(){ 
    int choice;
    do
    {
        printf("\033[2J");// clear screen
        printf("%s%s=========== Welcome back ===========%s\n",BOLD,CYAN,RESET);
        printf("%s%sAre you: \n\t%s1)PLAYER \n\t2)Admin\n\t0) Exit...\n",BOLD,YELLOW,BLUE);
        printf("%sEnter your choice: %s",GREEN,RESET);
        readUINT(&choice);
        
        switch (choice)
        {
        case 1:
           
            break;
        case 2:
           
            break;
        case 0:
            break;
        
        default:
            printf("\nEnter a vlid choice: ");
            break;
        }

    } while (choice!=0);

   
    }

    
