
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
            viewplayers(p_head);
                break;

           case 4:
            printf("Player ID to delete: ");
            scanf("%d", &id);   
            deletepl(&p_head, id, p_file);
            savepl(p_file, p_head);
            break;
            
        case 5:
            free_qlist(head);
            free_plist(p_head);
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
    char p_file[] = "players.txt";  // Changed from "players.text"
    char q_file[] = "questions.txt";  // Changed from "questions.text"
    Player* currentPlayer = NULL;
    char input[50];
    int choice;
    
    // Load data
    if (!loadPl(p_file, &players) || !loadqst(q_file, &questions)) {
        printf("%sError%s\n", RED, RESET);
        return 1;
    }
    printf("\n%sQUIZ GAME%s\n", BLUE, RESET);
    char answer[10];
    printf("%sDo you have an account?  answer :yes orno): %s", GREEN, RESET);
    scanf("%s", answer); 
   while (getchar() != '\n');
    if (strcmp(answer, "yes") == 0) {  
        char name[20];
        printf("%sEnter your nickname: %s", GREEN, RESET);
        scanf("%s", name);
        currentPlayer = findPlayer(players, name);   
        if (!currentPlayer) {
            printf("%sno acount %s\n", RED, RESET);
            free_plist(players);    
            free_qlist(questions);
            return 1;
        }
    } else {
       * currentPlayer = newpl();
        if (!currentPlayer) {
            free_plist(players);
            free_qlist(questions);
        }
        savepl(p_file, players);
        
    }
    return 0;
    while (1) {
        printf("\n%sMAIN MENU - %s%s\n", BLUE, currentPlayer->nichname, RESET);
        printf("%s1. Play Random Quiz%s\n", GREEN, RESET);
        printf("%s2. Play Domain Quiz%s\n", GREEN, RESET);
        printf("%s3.Leaderboard%s\n", GREEN, RESET);
        printf("%s4. Exit%s\n", GREEN, RESET);
        printf("%sChoice:%s ", RED, RESET);
        
        if (scanf("%d", &choice) != 1) {
            handleInputError();
            continue;
        }
        getchar();

        switch (choice) {
            case 1: play(questions, currentPlayer, "random");
                    break;
            case 2: play(questions, currentPlayer, currentPlayer->Domainspref);
                    break;
            case 3: board(players);
                    break;
            case 4: free_plist(players);
                    free_qlist(questions);
                    printf("%sGoodbye%s\n", BLUE, currentPlayer->nichname, RESET);
                    return 0;
            default: printf("%sInvalid choice!%s\n", RED, RESET);
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
                printf("Exiting , tchaw \n");
                break;
            default:
                printf(" Please try again.\n");
                break;
        }
    } while (choice != 0);
return 0;
} 