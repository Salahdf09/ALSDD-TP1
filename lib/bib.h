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
void readUINT(unsigned int *i); // Function prototype for reading an unsigned integer
int loadQuestions(const char *filename, Question questions[], int *numQuestions); // Function prototype for loading questions from a file
void displayQuestions(Question questions[], int numQuestions); // Function  for displaying questions
void modifyQuestion(Question questions[], int count, int id, const char *newText); // Function  for modifying a question
void saveQuestions(const char *filename, Question questions[], int count); // Function  for saving questions to a file
void deleteQuestion(Question questions[], int *count, int id); // // Function  for deleting questions to a file