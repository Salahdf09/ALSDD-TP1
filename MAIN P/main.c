
#include "../lib/bib.h"
#include <stdio.h>
#include <string.h>
#define MAX_QUESTIONS 100
#define MAX_LENGTH 200
// Define the Player structure
typedef struct {
    int playerId;                // Unique identifier for the player
    char nichname[50];           // Player's nickname
    char Domainspref[100];       // Preferred domains for playing
    int gamesPlayed;             // Number of games played
    int totalScore;              // Total score across all games
} Player;
// Define the Question structure
typedef struct {
    int questionNumber;          // Unique identifier for the question
    char domain[50];             // Domain of the question
    char difficultyLevel[10];    // Difficulty level: "facile", "moyen", "difficile"
    char content[MAX_LENGTH];    // The actual question text
    char correctAnswer[100];     // The correct answer to the question
} Question;
void adminMenu() {
    Question questions[MAX_QUESTIONS];
    int numQuestions = 0;
    char filename[] = "questions.txt";
    int choice, id;
    char newText[MAX_LENGTH];

    // Load questions from file
    if (!loadQuestions(filename, questions, &numQuestions)) {
        return 1; 
    }

    while (1) {
        printf("\nAdmin Menu:\n");
        printf("1. Delete a Question\n");
        printf("2. Modify a Question\n");
        printf("3. Delete a Player\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the question ID to delete: ");
                scanf("%d", &id);
                deleteQuestion(questions, &numQuestions, id);
                saveQuestions(filename, questions, numQuestions);
                break;
            case 2:
                printf("Enter the question ID to modify: ");
                scanf("%d", &id);
                printf("Enter the new question text: ");
                getchar(); // Consume newline left by scanf
                fgets(newText, MAX_LENGTH, stdin);
                newText[strcspn(newText, "\n")] = '\0'; 
                modifyQuestion(questions, numQuestions, id, newText);
                saveQuestions(filename, questions, numQuestions);
                break;
            case 3:
                printf("Delete Player functionality not implemented yet.\n");
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }

        // Display questions after each operation
        displayQuestions(questions, numQuestions);
    }
}

// Player menu function (to be implemented)
void playerMenu() {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:::
    ::::::::::::::::::::::::::::::::::::::::::::
    ////////////////////////////////////////////
// Main function}
}
int main() {
    int choice;
    do {
        printf("\033[2J"); // Clear screen
        printf("%s%s=========== Welcome back ===========%s\n", BOLD, CYAN, RESET);
        printf("%s%sAre you: \n\t%s1) PLAYER \n\t2) Admin\n\t0) Exit...\n", BOLD, YELLOW, BLUE);
        printf("%sEnter your choice: %s", GREEN, RESET);
        readUINT(&choice);

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