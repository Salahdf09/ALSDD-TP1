#ifndef LIB_H
#define LIB_H

 #include <stdlib.h>
 #include <string.h>
 // Define color codes for terminal text formatting
#define RESET   "\e[m"      // Reset text formatting to default
#define RED     "\033[31m"  // Set text color to red
#define GREEN   "\033[32m"  // Set text color to green
#define YELLOW  "\033[33m"  // Set text color to yellow
#define BLUE    "\033[34m"  // Set text color to blue
#define MAGENTA "\033[35m"  // Set text color to magenta
#define CYAN    "\033[36m"  // Set text color to cyan
#define WHITE   "\033[37m"  // Set text color to white
#define CLEAR   "\033[2J"   // Clear the terminal screen
#define BOLD    "\e[1m"     // Set text to bold

 
#define MAX_QUESTIONS 100
#define MAX_LENGTH 200
typedef struct {
    int questionNumber;          //   id for the question
    char domain[50];             // Domain of the question
    char difficultyLevel[10];    // Difficulty level: "facile", "moyen", "difficile"
    char content[MAX_LENGTH];    // The actual question text
    char correctAnswer[100];     // The correct answer 
} Question; 
typedef struct qst_node{
    Question value;
    struct qst_list *next;
} qst_list;
// this is qst struct

void readUINT(unsigned int *i); // Function prototype for reading an unsigned integer
int loadqst(const char *filename, Question questions[], int *numQuestions); // Function prototype for loading questions from a file
void displayqst(Question questions[], int numQuestions); // Function  for displaying questions
void modifyqst(Question questions[], int count, int id, const char *newText); // Function  for modifying a question
void saveqst(const char *filename, Question questions[], int count); // Function  for saving questions to a file
// void deleteqst(Question questions[], int *count, int id); // // Function  for deleting questions to a file

#endif