 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_QUESTIONS 100
#define MAX_LENGTH 200
 
//colors // to be used to change color text when printing
#define RESET   "\e[m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define CLEAR "\033[2J"
#define BOLD "\e[1m"

void readUINT(unsigned int *i){
    char c;
    while(scanf("%u",i)!=1){
        while((c=fgetc(stdin))!=EOF && (c!='\n'));
        printf("%sEnter a valid number: %s",RED,RESET);
    }
} 

// Define the Question structure
typedef struct {
    int questionNumber;          //   id for the question
    char domain[50];             // Domain of the question
    char difficultyLevel[10];    // Difficulty level: "facile", "moyen", "difficile"
    char content[MAX_LENGTH];    // The actual question text
    char correctAnswer[100];     // The correct answer 
} Question; 




int loadqst(const char *filename, Question questions[], int *numQuestions) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error \n");
        return 0; 
    }

    *numQuestions = 0; 
    char line[MAX_LENGTH * 2]; 
    while (fgets(line, sizeof(line), file)) {
        if (*numQuestions >= MAX_QUESTIONS) {
            printf("Too many questions! Increase MAX_QUESTIONS.\n");
            break; 
        };
        if (sscanf(line, "%d %49s %9s %199[^\n] %99[^\n]",
                   &questions[*numQuestions].questionNumber,
                   questions[*numQuestions].domain,
                   questions[*numQuestions].difficultyLevel,
                   questions[*numQuestions].content,
                   questions[*numQuestions].correctAnswer) != 5) {
            printf("Error line: %s", line);
            continue; 
        }

        (*numQuestions)++; 

    fclose(file); 
    return 1; 
    } 
}





void displayqst(Question questions[], int numQuestions) {           
        printf("Loaded Questions:\n");
    for (int i = 0; i < numQuestions; i++) {
        printf("question %d:\n", questions[i].questionNumber);
        printf("  Domain: %s\n", questions[i].domain);
        printf("  Difficulty: %s\n", questions[i].difficultyLevel);
        printf("  Contente: %s\n", questions[i].content);
        printf("  Coorection: %s\n", questions[i].correctAnswer);
        printf("\n");
    }
} 






void modifyqst(Question questions[], int count, int id, const char *newText) {
    for (int i = 0; i < count; i++) {
        if (questions[i].questionNumber == id) {
            // Modify the question text
            strncpy(questions[i].content, newText, MAX_LENGTH - 1);
            questions[i].content[MAX_LENGTH - 1] = '\0'; 
            printf("Question with di: %d  modified \n", id);
            return;
        }
    }

    printf("Question with ID %d not found!\n", id);
}





void saveqst(const char *filename, Question questions[], int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %s %s\n",
                questions[i].questionNumber,
                questions[i].domain,
                questions[i].difficultyLevel,
                questions[i].content,
                questions[i].correctAnswer);
    }

    fclose(file);
    printf("Question saved, cbn \n");
}




// Define the Player structure
typedef struct {
    int playerId;                // Unique identifier for the player
    char nichname[50];           // Player's nickname
    char Domainspref[100];       // Preferred domains for playing
    int gamesPlayed;             // Number of games played
    int totalScore;              // Total score across all games
} Player;