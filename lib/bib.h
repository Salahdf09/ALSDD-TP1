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

 
#define mq 200      // Max question text length
#define ml 100      // Max questions limit

// Define the Player structure
typedef struct {
    int playerId;                // Unique identifier for the player
    char nichname[50];           // Player's nickname
    char Domainspref[100];       // Preferred domains for playing
    int gamesPlayed;             // Number of games played
    int totalScore;              // Total score across all games
} Player;
typedef struct {
    int qNum;               // Question ID
    char domain[50];        // Question domain
    char diff[10];          // Difficulty: "easy", "medium", "hard"
    char text[mq];     // Question text
    char ans[100];          // Correct answer
} Question; // this is qst struct
typedef struct q_node {
    Question val;
    struct q_node *next;
} QList;
typedef struct p_node {
    Player val;
    struct p_node *next;
} PList;
void readUINT(unsigned int *i); //Read an unsigned integer from the user
int loadqst(const char *fname, QList **head);//Load questions from file into linked list
void showqst(QList *head); //Display all questions in the linked list 
void editqst(QList *head, int id, const char *newTxt); //modify question text by question ID
void saveqst(const char *fname, QList *head);//Save all questions to file 
void free_qlist(QList *head);//Free memory allocated for question list 













#endif