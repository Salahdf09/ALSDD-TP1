 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/bib.h"
 
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
int loadqst(const char *fname, QList **head) {
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Error opening questions file\n");
        return 0;
    }

    char line[512];  // Increased buffer size for long questions
    QList *tail = NULL;
    
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';
        
        QList *newNode = (QList*)malloc(sizeof(QList));
        if (newNode == NULL) {
            printf("Memory error\n");
            break;
        }
        
        // Parse the exact format: "69" "Informatique" "Difficile" "question" "answer"
        if (sscanf(line, "\"%d\" \"%49[^\"]\" \"%49[^\"]\" \"%199[^\"]\" \"%99[^\"]\"",
                  &newNode->val.qNum,
                  newNode->val.domain,
                  newNode->val.diff,
                  newNode->val.text,
                  newNode->val.ans) != 5) {
            printf("Error parsing line: %s\n", line);
            free(newNode);
            continue;
        }
        
        newNode->next = NULL;
        
        if (*head == NULL) {
            *head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);
    return 1;
}
void showqst(QList *head) {
    printf("Questions:\n");
    QList *curr = head;
    while (curr != NULL) {
        printf("Q%d:\n", curr->val.qNum);
        printf("  Domain: %s\n", curr->val.domain);
        printf("  Level: %s\n", curr->val.diff);
        printf("  Text: %s\n", curr->val.text);
        printf("  Answer: %s\n", curr->val.ans);
        printf("\n");
        curr = curr->next;
    }
}
void editqst(QList *head, int id, const char *newTxt) {
    QList *curr = head;
    while (curr != NULL) {
        if (curr->val.qNum == id) {
            strncpy(curr->val.text, newTxt, mq - 1);
            curr->val.text[mq - 1] = '\0';
            printf("Q%d updated\n", id);
            return;
        }
        curr = curr->next;
    }
    printf("Q%d not found!\n", id);
}
void free_plist(PList* head) {
    PList* current = head;
    while (current) {
        PList* temp = current;
        current = current->next;
        free(temp);
    }
}
void handleInputError() {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("%sInvalid input! Please enter a number.%s\n", RED, RESET);
}
void free_qlist(QList* head) {
    QList* current = head;
    while (current) {
        QList* temp = current;
        current = current->next;
        free(temp);
    }
}
void viewplayers(PList* head) {
    printf("\n%sAll Players:%s\n", BLUE, RESET);
    printf("%s%-5s %-20s %-15s %-5s %s\n", 
           GREEN, "ID", "Nickname", "Domains", "Games", "Score", RESET);
    
    PList* current = head;
    while (current != NULL) {
        printf("%-5d %-20s %-15s %-5d %d\n",
               current->val.playerId,
               current->val.nichname,
               current->val.Domainspref,
               current->val.gamesPlayed,
               current->val.totalScore);
        current = current->next;
    }
}
int loadPl(const char *p, PList **head) {
    FILE *fp = fopen(p, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    char line[256];
    PList *tail = NULL;
    
    while (fgets(line, sizeof(line), fp)) {
        PList *newNode = (PList*)malloc(sizeof(PList));
        if (newNode == NULL) {
            printf("Memory error\n");
            break;
        }
        
        if (sscanf(line, "%d|%49[^|]|%49[^|]|%d|%d",
                  &newNode->val.playerId,
                  newNode->val.nichname,
                  newNode->val.Domainspref,
                  &newNode->val.gamesPlayed,
                  &newNode->val.totalScore) != 5) {
            printf("Error reading line: %s", line);
            free(newNode);
            continue;
        }
        
        newNode->next = NULL;
        
        if (*head == NULL) {
            *head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);
    return 1;
}
Player* newpl() {

    Player *s = (Player*)malloc(sizeof(Player));
    if (!s) {
        printf("failed\n");
        return NULL; 
    }

    printf("Enter nickname: ");
    fgets(s->nichname, sizeof(s->nichname), stdin);
    s->nichname[strcspn(s->nichname, "\n")] = '\0';  // Remove newline

    s->playerId = generateNewID();  // Assume this is implemented elsewhere
    s->gamesPlayed = 0;
    s->totalScore = 0;

    printf("Account created successfully!\n");
    printf("Your new ID: %d\n", s->playerId);
    return s;  // Return the pointer to the new Player
}
findpl(players, name) {
    PList* current = players;
    while (current != NULL) {
        if (strcmp(current->val.nichname, name) == 0) {
            return &current->val;
        }
        current = current->next;
    }
    return NULL;
}
int generateNewID() {
    static int id = 1000; // Starting ID
    return id++;
}
void listDomains(QList* questions) {
    char domains[100][50] = {0};
    int count = 0;
    
    QList* current = questions;
    while (current) {
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(domains[i], current->val.domain) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(domains[count++], current->val.domain);
            printf("- %s\n", current->val.domain);
        }
        current = current->next;
    }
}
void play(QList* questions, Player* player, const char* domain) {
    int score = 0;
    int questionsAsked = 0;
    int totalEligible = 0;
    QList* current = questions;

    // Count eligible questions first
    while (current != NULL) {
        if (strcmp(domain, "random") == 0 || strcmp(current->val.domain, domain) == 0) {
            totalEligible++;
        }
        current = current->next;
    }

    if (totalEligible == 0) {
        printf("No questions available in this domain!\n");
        return;
    }

    printf("\n=== QUIZ (%s) ===\n", (strcmp(domain, "random") == 0) ? "Random" : domain);
    printf("Answer 5 questions from %s\n\n", 
          (strcmp(domain, "random") == 0) ? "all domains" : domain);
    current = questions;
    while (current != NULL && questionsAsked < 5) {
        if (strcmp(domain, "random") == 0 || strcmp(current->val.domain, domain) == 0) {
            printf("\nQuestion %d/%d (ID: %d)\n", questionsAsked+1, 5, current->val.qNum);
            printf("Domain: %s\n", current->val.domain);
            printf("Difficulty: %s\n", current->val.diff);
            printf("Question: %s\n", current->val.text);
            char answer[100];
            printf("Your answer: ");
            fgets(answer, sizeof(answer), stdin);
            answer[strcspn(answer, "\n")] = '\0';

            if (strcasecmp(answer, current->val.ans) == 0) {
                printf("god, +10 points\n");
                score += 10;
            } else {
                printf("no . The correct answer was: %s\n", current->val.ans);
            }
            questionsAsked++;
        }
        current = current->next;
    }
    player->totalScore += score;
    player->gamesPlayed++;
}
void board(PList* players) {
    printf("\nID\tScore\n");
    printf("--------\n");
    
    PList* current = players;
    while (current != NULL) {
        printf("%d\t%d\n", current->val.playerId, current->val.totalScore);
        current = current->next;
    }
}
int savepl(const char* filename, PList* players) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return 0;
    
    PList* current = players;
    while (current) {
        fprintf(fp, "%d|%s|%s|%d|%d\n",
                current->val.playerId,
                current->val.nichname,
                current->val.Domainspref,
                current->val.gamesPlayed,
                current->val.totalScore);
        current = current->next;
    }
    fclose(fp);
    return 1;
}
int deletepl(PList** head, int playerId, const char* filename) {
    if (*head == NULL) {
        printf("list is empty!\n");
        return 0;
    }

    PList *current = *head;
    PList *prev = NULL;

    while (current != NULL && current->val.playerId != playerId) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Player with ID %d not found!\n", playerId);
        return 0;
    }

    if (prev == NULL) {
        *head = current->next;  
    } else {
        prev->next = current->next;
    }
    free(current);
    savepl(filename, *head); 
    printf("Player with ID %d deleted successfully!\n", playerId);
    return 1;
}
void upStats(Player* player, int score, int games){
    player->totalScore += score;
    player->gamesPlayed += games;
    float averageScore = (player->gamesPlayed > 0) ? (float)player->totalScore / player->gamesPlayed : 0.0f;
   
}
void saveqst(const char *fname, QList *head) {
    FILE *fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("Error saving questions\n");
        return;
    }

    QList *curr = head;
    while (curr != NULL) {
        fprintf(fp, "\"%d\" \"%s\" \"%s\" \"%s\" \"%s\"\n",
                curr->val.qNum,
                curr->val.domain,
                curr->val.diff,
                curr->val.text,
                curr->val.ans);
        curr = curr->next;
    }

    fclose(fp);
    printf("Questions saved successfully\n");
}