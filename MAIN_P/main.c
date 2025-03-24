
#include "../lib/bib.h"
#include <stdio.h>
#include <string.h>
#define MAX_QUESTIONS 100
#define MAX_LENGTH 200

// Define the Question structure


int adminMenu() {
    QList *head = NULL;
    char filename[] = "questions.text";
    int choice, id;
    char newText[mq];

    if (!loadqst(filename, &head)) {
        return 1;
    }  
    while (1) {
        printf(  "\nAdmin Menu:\n", BLUE , RESET );
        printf("1. Delete a Question\n",GREEN,RESET);
        printf("2. Modify a Question\n",GREEN,RESET);
        printf("3. Delete a Player\n",GREEN,RESET);
        printf("4. Exit\n",GREEN,RESET);
        printf("Enter your choice: ",RED,RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            printf("Question ID to delete: ");
            scanf("%d", &id);
            saveqst(filename, head);
            break;
            
        case 2:
            printf("Question ID to modify: ");
            scanf("%d", &id);
            printf("New question text: ");
            getchar(); 
            fgets(newText, mq, stdin);
            newText[strcspn(newText, "\n")] = '\0';
            editqst(head, id, newText);
            saveqst(filename, head);
            break;
            
        case 3:
            printf("Player deletion not available\n");
            break;
            
        case 4:
            free_qlist(head);
            return 0;
            
        default:
            printf("Invalid choice!\n");
    }

    showqst(head);
}
}
// Player menu function (to be implemented)
void playerMenu() {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:::
    ////////////////////////////////////////////
// Main function}
}
int main() {
    int choice;
    do {
        // printf("\033[2J"); 
        printf("%s%s=========== Welcome back ===========%s\n", BOLD, CYAN, RESET);
        printf("%s%sAre you: \n\t%s1) PLAYER \n\t2) Admin\n\t0) Exit...\n", BOLD, YELLOW, BLUE);
        printf("%sEnter your choice: %s", GREEN, RESET);
        readUINT(&choice);
        printf("%d",choice);
        switch (choice) {
            case 1:
                playerMenu();
                break;
            case 2:
                adminMenu();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
return 0;
} 