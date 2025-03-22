 
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
    int questionNumber;          // Unique identifier for the question
    char domain[50];             // Domain of the question
    char difficultyLevel[10];    // Difficulty level: "facile", "moyen", "difficile"
    char content[MAX_LENGTH];    // The actual question text
    char correctAnswer[100];     // The correct answer to the question
} Question;

int loadQuestions(const char *filename, Question questions[], int *numQuestions) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0; // Return 0 to indicate failure
    }

    *numQuestions = 0; // Initialize the number of questions
    char line[MAX_LENGTH * 2]; // Buffer to hold each line from the file

    while (fgets(line, sizeof(line), file)) {
        if (*numQuestions >= MAX_QUESTIONS) {
            printf("Too many questions! Increase MAX_QUESTIONS.\n");
            break; // Stop reading if the limit is reached
        }

        // Parse the line into the Question struct
        if (sscanf(line, "%d %49s %9s %199[^\n] %99[^\n]",
                   &questions[*numQuestions].questionNumber,
                   questions[*numQuestions].domain,
                   questions[*numQuestions].difficultyLevel,
                   questions[*numQuestions].content,
                   questions[*numQuestions].correctAnswer) != 5) {
            printf("Error parsing line: %s", line);
            continue; // Skip this line if parsing fails
        }

        (*numQuestions)++; // Increment the number of questions
    }

    fclose(file); // Close the file
    return 1; // Return 1 to indicate success
}


void displayQuestions(Question questions[], int numQuestions) {
    printf("Loaded Questions:\n");
    for (int i = 0; i < numQuestions; i++) {
        printf("Question %d:\n", questions[i].questionNumber);
        printf("  Domain: %s\n", questions[i].domain);
        printf("  Difficulty: %s\n", questions[i].difficultyLevel);
        printf("  Content: %s\n", questions[i].content);
        printf("  Correct Answer: %s\n", questions[i].correctAnswer);
        printf("\n");
    }
}
void modifyQuestion(Question questions[], int count, int id, const char *newText) {
    for (int i = 0; i < count; i++) {
        if (questions[i].questionNumber == id) {
            // Modify the question text
            strncpy(questions[i].content, newText, MAX_LENGTH - 1);
            questions[i].content[MAX_LENGTH - 1] = '\0'; // Ensure null-termination
            printf("Question with ID %d modified successfully!\n", id);
            return;
        }
    }

    printf("Question with ID %d not found!\n", id);
}
void saveQuestions(const char *filename, Question questions[], int count) {
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
    printf("Questions saved to file successfully!\n");
}