 #include <stdlib.h>
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
void readUINT(unsigned int *i); //The readUINT function safely reads an unsigned integer from user input, validates it, clears any invalid input, and provides feedback until a valid number is entered.