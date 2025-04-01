#ifndef LIB_H
#define LIB_H

 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>

//  Define constants for files names
#define QUESTIONS_FILE "questions.txt"
#define PLAYERS_FILE "players.txt"
#define PARTIES_FILE "parties.txt"
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

 //  Define constants for files names
#define QUESTIONS_FILE "questions.txt"
#define PLAYERS_FILE "players.txt"

// define constants 
#define MAX_QUESTION_LEGNTH 200      // Max question text length
#define MAX_ANSWER_LEGNTH 100      // Max questions limit
#define DOMAINS_NUMBER 3      // Number of domains
#define DIFFICULTY_LEVELS_NUMBER 3      // Number of difficulty levels
extern const char *DOMAINS[DOMAINS_NUMBER]; // Define the domains
extern const char *DIFFICULTY_LEVELS[DIFFICULTY_LEVELS_NUMBER]; // Define the difficulty levels

// define enumertion for the difficulty of the question and domains
typedef enum {
	EASY,
	MEDIUM,
	HARD
} Difficulty_level;
typedef enum {
	SPORT,
	VIDEOGAMES,
	INFORATION_TECHNOLOGY
} Question_domain;
// Define the Player structure

typedef struct {
    int playerId;                // Unique identifier for the player
    char nichname[50];           // Player's nickname
    bool Domainspref[DOMAINS_NUMBER]; 
	// Preferred domains for playing , each index represent a domain according to the enum true if the player prefer this domain
    int gamesPlayed;             // Number of games played
    int totalScore;              // Total score across all games
} Player;
// Define players linked list 
typedef struct p_node {
	Player val;
	struct p_node *next;
} PList;

// Define the Question structure
typedef struct {
	int qNum;               // Question ID
	Question_domain domain;        // Question domain
	Difficulty_level diff;          // Difficulty: "easy", "medium", "hard"
	char text[MAX_QUESTION_LEGNTH];     // Question text
	char *answers;
	// pointer do a dynamic array of answers (2 answers for eazy questions, 4 for medium ,1 for hard)
	// the first answer is the correct one
} Question; // this is qst struct
// Define questions linked list
typedef struct q_node {
	Question val;
	struct q_node *next;
} QList;

// Define the structure of the questions list for partie 
// contains the question and the score of the player and if the question is in the preferred domain
typedef struct partieQlist {
	Question *question;
	bool isPreferredDomain;
	int score;
	struct partieQlist *next;
} PartieQlist;
typedef struct {
	int playerId;
	int level;
	PartieQlist *questions;
	int totalScore;
}Partie;
typedef struct partie_node {
	Partie val;
	struct partie_node *next;
} PartieList;
// util functions
void readInt(int *i); // safely read an integer from the user

// functions for the questions

void AllocateQuestion(QList **q); // allocate memory for the answers of the question
void StringToQuestion(Question *q, char *str); // convert a string to a question
void QuestionToString(Question *q, char *str); // convert a question to a string
void FreeQuestion(QList **q); // free the memory allocated for the question
void DeleteQuestion(QList **head, int id); // delete a question by its ID
void InsertQuestion(QList **head, QList *q); // insert a question to the questions list
void ShowQuestion(Question *q); // display a question
bool FindQuestion(QList *head, int id, Question *q); // find a question by its ID
// functions for the players
void AllocatePlayer(PList **p); // allocate memory for a player
void StringToPlayer(Player *p, char *str); // convert a string to a player
void PlayerToString(Player *p, char *str); // convert a player to a string
void FreePlayer(PList **p); // free the memory allocated for a player
void DeletePlayer(PList **head, int id); // delete a player by its ID
void InsertPlayer(PList **head, PList *p); // insert a player to the players list
void ShowPlayer(Player *p); // display a player
bool FindPlayer(PList *head, int id, Player *p); // find a player by its ID
Question* ChooseRandomQuestion(QList *head, int domain, int difficulty);
int CalculateScore(int difficulty, int isPreferredDomain);
bool AskQuestion(Question *q, Player *player);
// Admin functions
void AdminMenu(QList **Qhead, PList **Phead, PartieList **partieHead, int *nbrQst, int *nbrPl, int *nbrParties);
void AddQuestionMenu(QList **Qhead, int *nbrQst); // display the add question menu
void AddPlayerMenu(PList **Phead, int *nbrPl); // display the add player menu
void PlayerMenu(QList *Qhead, PList **Phead, PartieList **partieHead);
void PlayerEditProfile(Player *player);
void ShowLeaderboard(PList *Phead);
int CalculateTotalScore(PartieList *partieHead, int playerId);
void StartGame(QList *Qhead, Player *player, PartieList **partieHead, int level);
int AskQuestions(QList *head, Player player, int count, int difficulty, PartieQlist **currentPartieQ);
bool AskQuestion(Question *q, Player *player);
void DisplayPartiesList(PartieList *partieHead);
void AddPlayerMenu(PList **Phead, int *nbrPl);
void PlayerEditProfile(Player *player);
void ShowLeaderboard(PList *Phead);
void StartGame(QList *Qhead, Player *player, PartieList **partieHead, int level);
int AskQuestions(QList *head, Player player, int count, int difficulty, PartieQlist **currentPartieQ);
void SaveQuestions(QList *head);
void SavePlayers(PList *head);
int LoadQuestions(QList **head);
int LoadPlayers(PList **head);
void SaveParties(PartieList *head);
int LoadParties(PartieList **head, QList *Qhead);
void PartieToString(Partie *partie, char *str);
void StringToPartie(Partie *partie, char *str, QList *Qhead);
#endif
