 
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
        printf("Error \n");
        return 0; 
    }

    char line[mq * 2];
    QList *tail = NULL;
    int cnt = 0;
    
    while (fgets(line, sizeof(line), fp) && cnt < ml ) {
        QList *newNode = (QList*)malloc(sizeof(QList));
        if (newNode == NULL) {
            printf("Memory error\n");
            break;
        }
        
        if (sscanf(line, "%d %49s %9s %199[^\n] %99[^\n]",
                   &newNode->val.qNum,
                   newNode->val.domain,
                   newNode->val.diff,
                   newNode->val.text,
                   newNode->val.ans) != 5) {
            printf("Error  line: %s", line);
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
        cnt++;
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


void saveqst(const char *fname, QList *head) {
    FILE *fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("Error \n");
        return;
    }

    QList *curr = head;
    while (curr != NULL) {
        fprintf(fp, "%d %s %s %s %s\n",
                curr->val.qNum,
                curr->val.domain,
                curr->val.diff,
                curr->val.text,
                curr->val.ans);
        curr = curr->next;
    }

    fclose(fp);
    printf("Saved  MARKA \n");
}

void free_plist(PList* head) {
    PList* current = head;
    while (current) {
        PList* temp = current;
        current = current->next;
        free(temp);
    }
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
int checkExistingID(int __id) {
    FILE* fp = fopen("data.bin","rb+"); // Mode binaire inutile
    if(!fp) return 0;

    int tmpID;
    char buff[255]; // Taille arbitraire

    while(1) { // Boucle infinie volontaire
        if(fscanf(fp,"%d:%255[^\n]",&tmpID,buff) == EOF) break;
        if(tmpID == __id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int generateID() {
    int __newID;
    do {
        __newID = (rand() % 7777) + 1000; // Plage non standard
        srand(time(NULL)^rand()); // Seed aléatoire redondante
    } while(checkExistingID(__newID));
    return __newID;
}

