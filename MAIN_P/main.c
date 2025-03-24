
#include "../lib/bib.h"
#include <stdio.h>
#include <string.h>

int adminMenu() {
    QList *head = NULL;
    PList *p_head = NULL;
    char filename[] = "questions.txt";
    char p_file[] = "players.txt";
    int choice, id;
    char newText[mq];

    if (!loadqst(filename, &head)) {
        return 1;
    }  
    while (1) {
        printf(  "%s\nAdmin Menu:\n", BLUE , RESET );
        printf("%s1. Delete a Question\n%s",GREEN,RESET);
        printf("%s2. Modify a Question\n%s",GREEN,RESET);
        printf("%s3. View Players\n%s",GREEN,RESET);
        printf("%s4. Delete a Player\n%s",GREEN,RESET);
        printf("%s5. Exit\n%s",GREEN,RESET);
        printf("%sEnter your choice: %s",RED,RESET);
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
             
            case 3 :    
            //showPlayers(players);
                break;

           case 4:
            // printf("MZL\n");
            break;
            
        case 5:
            free_qlist(head);
            return 0;
            
        default:
            printf("Invalid choice!\n");
    }

    showqst(head);
}
}

    int playerMenu() {
        PList* players = NULL;
        QList* questions = NULL;
        char p_file[] = "players.txt";
        char q_file[] = "questions.txt";
        int choice;
        if (!loadPlayers(p_file, &players) || !loadqst(q_file, &questions)) {
            printf("Error loading data\n");
            return 1;
        }
    
        while (1) {
            printf("%s\nPlayer Menu:\n", BLUE);
            printf("%s1. start the game\n%s", GREEN, RESET);
            printf("%s2. View Scores\n%s", GREEN, RESET);
            printf("%s3. Exit\n%s", GREEN, RESET);
            printf("%sEnter your choice: %s", RED, RESET);
            scanf("%d", &choice);
    
            switch (choice) {
                case 1:
                    
                case 2:
                    
                case 3:
                
                    return 0;
                default:
                    printf("Invalid choice!\n");
            }
        }
}
int main() {
    int choice;
    do {
        printf("\033[2J"); 
        printf("%s%s=========== Welcome back ===========%s\n", BOLD, CYAN, RESET);
        printf("%s%sAre you: \n\t%s1. PLAYER \n\t2. Admin\n\t0. Exit...\n", BOLD, YELLOW, BLUE);
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