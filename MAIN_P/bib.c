 
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
        printf("Error opening file\n");
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
            printf("Error in line: %s", line);
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
        printf("Error writing file\n");
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
    printf("Saved successfully\n");
}


void free_qlist(QList *head) {
    QList *curr = head;
    while (curr != NULL) {
        QList *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}