#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include "../lib/bib1.h"

const char *DOMAINS[DOMAINS_NUMBER] = {"SPORT", "VIDEOGAMES", "INFORATION_TECHNOLOGY"}; // Define the domains
const char* DIFFICULTY_LEVELS[3] = {"EASY", "MEDIUM", "HARD"}; // Define the difficulty levels
void readInt(int *i){
    char c;
	printf(": ");
    while(scanf("%u",i)!=1){
        while((c=fgetc(stdin))!=EOF && (c!='\n'));
        printf("%sEnter a valid number: %s",RED,RESET);
    }
	getchar();
} 

void AllocateQuestion(QList **q){
	*q = (QList*)malloc(sizeof(QList));
	if (*q == NULL) {
		printf("Memory error\n");
		return;
	}
	(*q)->next = NULL; // initialize the next pointer to NULL
	(*q)->val.answers = NULL; // initialize the answers pointer to NULL
}
void StringToQuestion(Question *q, char *str){
	Difficulty_level level;
	sscanf(str,"\"%d\"",&level); // read the difficulty level
		// Allocate dynamc array for the answers of the question and fill it
		switch (level)
		{
			case EASY:
				
				(q)->answers = (char*)malloc(2 * MAX_ANSWER_LEGNTH * sizeof(char)); // 2 answers for easy questions
				sscanf(str, "\"%d\" \"%d\" \"%d\" \"%199[^\"]\" \"%99[^\"]\" \"%99[^\"]\"",
					&q->diff,
					&q->qNum,
					&q->domain,
					q->text,
					q->answers,
					q->answers + MAX_ANSWER_LEGNTH);
				break;
	
			case MEDIUM:
				(q)->answers = (char*)malloc(4 * MAX_ANSWER_LEGNTH * sizeof(char)); // 4 answers for medium questions
				sscanf(str, "\"%d\" \"%d\" \"%d\" \"%199[^\"]\" \"%99[^\"]\" \"%99[^\"]\" \"%99[^\"]\" \"%99[^\"]\"",
					&q->diff,
					&q->qNum,
					&q->domain,
					q->text,
					q->answers,
					q->answers + MAX_ANSWER_LEGNTH,
					q->answers + 2 * MAX_ANSWER_LEGNTH,
					q->answers + 3 * MAX_ANSWER_LEGNTH);
				break;
	
			case HARD:
				(q)->answers = (char*)malloc(MAX_ANSWER_LEGNTH * sizeof(char)); // only one answer for hard questions
				sscanf(str, "\"%d\" \"%d\" \"%d\" \"%199[^\"]\" \"%99[^\"]\"",
					&q->diff,
					&q->qNum,
					&q->domain,
					q->text,
					q->answers);
				break;
	
			default:
				printf("Invalid difficulty level.\n");
				break;
		}

	}
void DeleteQuestion(QList **head, int qNum){
	QList *current = *head;
	QList *prev = NULL;
	while (current != NULL && current->val.qNum != qNum) {
		prev = current;
		current = current->next;
	}
	if (current == NULL) {
		printf("Question with ID %d not found!\n", qNum);
		return;
	}
	if (prev == NULL) {
		*head = current->next;
	} else {
		prev->next = current->next;
	}
	FreeQuestion(&current);
	printf("Question with ID %d deleted successfully!\n", qNum);
}
void FreeQuestion(QList **q){
	if (*q == NULL) return; // if the question is already freed
	if ((*q)->val.answers != NULL) free((*q)->val.answers);
	free(*q);
	*q = NULL;
}

void InsertQuestion(QList **head, QList *q){
	if ((*head) == NULL) {
		q->next = *head;
		*head = q;
		return;
	}
	QList *current = *head;
	// find the position to insert the question to keep order by difficulty	of sub lists
	while (current->next != NULL && current->next->val.diff <= q->val.diff) {
		current = current->next;
	}
	q->next = current->next;
	current->next = q;
	
}
void ShowQuestion(Question *q){
	printf("Q%d:\n", q->qNum);
	printf("  Domain: %s\n", DOMAINS[q->domain]);
	printf("  Level: %s\n", DIFFICULTY_LEVELS[q->diff]);
	printf("  Text: %s\n", q->text);
	switch (q->diff) {
		case EASY:
			printf("  Correct Answer: %s\n", q->answers);
			printf("  Other Option:\n");
			printf("    %s\n", q->answers + MAX_ANSWER_LEGNTH);
			break;
		case MEDIUM:
			printf("  Correct Answer: %s\n", q->answers);
			printf("  Other Options:\n");
			printf("    %s\n", q->answers + MAX_ANSWER_LEGNTH);
			printf("    %s\n", q->answers + 2 * MAX_ANSWER_LEGNTH);
			printf("    %s\n", q->answers + 3 * MAX_ANSWER_LEGNTH);
			break;
		case HARD:
			printf("  Correct Answer: %s\n", q->answers);
			break;
		default:
			printf("  Invalid difficulty level.\n");
			break;
	}
	printf("\n");
}
bool FindQuestion(QList *head, int id, Question *q){
	QList *current = head;
	while (current != NULL) {
		if (current->val.qNum == id) {
			*q = current->val;
			return true;
		}
		current = current->next;
	}
	return false;
}
void AddQuestionMenu(QList **Qhead, int *nbrQst){
	QList *newQst;
	AllocateQuestion(&newQst);
	printf("Choose the question Domain: \n");
	for (int i = 0; i < DOMAINS_NUMBER; i++) {
		printf("%d. %s\n", i + 1, DOMAINS[i]);
	}
	readInt((int *)&newQst->val.domain);
	newQst->val.domain--;
	printf("Choose the question difficulty: \n");
	for (int i = 0; i < DIFFICULTY_LEVELS_NUMBER; i++) {
		printf("%d. %s\n", i + 1, DIFFICULTY_LEVELS[i]);
	}
	readInt((int *)&newQst->val.diff);
	newQst->val.diff--;
	printf("Enter the question text: ");
	fgets(newQst->val.text, MAX_QUESTION_LEGNTH, stdin);
	newQst->val.text[strcspn(newQst->val.text, "\n")] = '\0';
	printf("Enter the correct answer: ");
	char correctAnswer[MAX_ANSWER_LEGNTH];
	fgets(correctAnswer, MAX_ANSWER_LEGNTH, stdin);
	correctAnswer[strcspn(correctAnswer, "\n")] = '\0';
	switch (newQst->val.diff)
	{
	case EASY:
		newQst->val.answers = (char*)malloc(2 * MAX_ANSWER_LEGNTH * sizeof(char));
		strcpy(newQst->val.answers, correctAnswer);
		printf("Enter the second answer: ");
		fgets(newQst->val.answers + MAX_ANSWER_LEGNTH, MAX_ANSWER_LEGNTH, stdin);
		newQst->val.answers[MAX_ANSWER_LEGNTH - 1] = '\0';
		break;
	case MEDIUM:
		newQst->val.answers = (char*)malloc(4 * MAX_ANSWER_LEGNTH * sizeof(char));
		strcpy(newQst->val.answers, correctAnswer);
		printf("Enter the second answer: ");
		fgets(newQst->val.answers + MAX_ANSWER_LEGNTH, MAX_ANSWER_LEGNTH, stdin);
		newQst->val.answers[MAX_ANSWER_LEGNTH - 1] = '\0';
		printf("Enter the third answer: ");
		fgets(newQst->val.answers + 2 * MAX_ANSWER_LEGNTH, MAX_ANSWER_LEGNTH, stdin);
		newQst->val.answers[2 * MAX_ANSWER_LEGNTH - 1] = '\0';
		printf("Enter the fourth answer: ");
		fgets(newQst->val.answers + 3 * MAX_ANSWER_LEGNTH, MAX_ANSWER_LEGNTH, stdin);
		newQst->val.answers[3 * MAX_ANSWER_LEGNTH - 1] = '\0';
		break;
	case HARD:
		newQst->val.answers = (char*)malloc(MAX_ANSWER_LEGNTH * sizeof(char));
		strcpy(newQst->val.answers, correctAnswer);
		break;
	default:
		printf("Invalid difficulty level.\n");
		break;
	}
	(*nbrQst)+=1;
	newQst->val.qNum = (*nbrQst);
	InsertQuestion(Qhead, newQst);

}
// Admin functions
void AdminMenu(QList **Qhead, PList **Phead, PartieList **partieHead, int *nbrQst, int *nbrPl, int *nbrParties) {
	int choice, id;

	while (1) {
		printf("%s\nAdmin Menu:\n", BLUE, RESET);
		printf("%sPlayer number: %d%s\n", YELLOW, *nbrPl, RESET);
		printf("%sQuestion number: %d%s\n", YELLOW, *nbrQst, RESET);
		printf("%sParties number: %d%s\n", YELLOW, *nbrParties, RESET);
		printf("%s1. Add a Question\n%s", GREEN, RESET);
		printf("%s2. Delete a Question\n%s", GREEN, RESET);
		printf("%s3. View Questions\n%s", GREEN, RESET);
		printf("%s4. Add a Player\n%s", GREEN, RESET);
		printf("%s5. Delete a Player\n%s", GREEN, RESET);
		printf("%s6. View Players\n%s", GREEN, RESET);
		printf("%s7. Display Parties List\n%s", GREEN, RESET);
		printf("%s0. Exit\n%s", GREEN, RESET);
		printf("%sEnter your choice: %s", RED, RESET);
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				AddQuestionMenu(Qhead, nbrQst);
				break;
			case 2:
				printf("Question ID to delete: ");
				scanf("%d", &id);
				DeleteQuestion(Qhead, id);
				break;
			case 3:
				int qid;
				printf("Question ID to view: ");
				scanf("%d", &qid);
				Question q;
				if (FindQuestion(*Qhead, qid, &q)) {
					ShowQuestion(&q);
				} else {
					printf("Question not found!\n");
				}
				break;
			case 4:
				AddPlayerMenu(Phead, nbrPl);
				break;
			case 5:
				printf("Player ID to delete: ");
				scanf("%d", &id);
				DeletePlayer(Phead, id);
				break;
			case 6:
				printf("Player ID to view: ");
				scanf("%d", &id);
				Player p;
				if (FindPlayer(*Phead, id, &p)) {
					ShowPlayer(&p);
				} else {
					printf("Player not found!\n");
				}
				break;
			case 7:
				DisplayPartiesList(*partieHead);
				break;
			case 0:
				return;
			default:
				printf("%sInvalid choice!%s\n", RED, RESET);
		}
	}
}

void DisplayPartiesList(PartieList *partieHead) {
	if (partieHead == NULL) {
		printf("No parties available.\n");
		return;
	}

	printf("%sParties List:%s\n", BLUE, RESET);
	PartieList *current = partieHead;
	while (current != NULL) {
		printf("Player ID: %d\n", current->val.playerId);
		printf("  Level: %d\n", current->val.level);
		printf("  Total Score: %d\n", current->val.totalScore);
		printf("  Questions:\n");
		PartieQlist *qCurrent = current->val.questions;
		while (qCurrent != NULL) {
			printf("    Question ID: %d, Score: %d, Preferred Domain: %s\n",
				   qCurrent->question->qNum,
				   qCurrent->score,
				   qCurrent->isPreferredDomain ? "Yes" : "No");
			qCurrent = qCurrent->next;
		}
		current = current->next;
	}
}


void AllocatePlayer(PList **p) {
    *p = (PList*)malloc(sizeof(PList));
    if (*p == NULL) {
        printf("Memory error\n");
        return;
    }
    (*p)->next = NULL; // Initialize the next pointer to NULL
}

void StringToPlayer(Player *p, char *str) {
	char Domainspref[DOMAINS_NUMBER];
	sscanf(str, "\"%d\"|\"%49[^\"]\"|\"%d\"|\"%d\"|\"%49[^\"]\"",
           &p->playerId,
           p->nichname,
           &p->gamesPlayed,
           &p->totalScore
		   ,Domainspref);
	for (int i = 0; i < DOMAINS_NUMBER; i++) {
		p->Domainspref[i] = (Domainspref[i] == '1');
	}
	
}

void PlayerToString(Player *p, char *str) {
	char Domainspref[DOMAINS_NUMBER + 1] = {0};
	for (int i = 0; i < DOMAINS_NUMBER; i++) {
		Domainspref[i] = p->Domainspref[i] ? '1' : '0';
	}
	sprintf(str, "\"%d\"|\"%s\"|\"%d\"|\"%d\"|\"%s\"",
			p->playerId,
			p->nichname,
			p->gamesPlayed,
			p->totalScore,
			Domainspref);
}

void FreePlayer(PList **p) {
    if (*p == NULL) return; // If the player is already freed
    free(*p);
    *p = NULL;
}

void DeletePlayer(PList **head, int id) {
    PList *current = *head;
    PList *prev = NULL;
    while (current != NULL && current->val.playerId != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Player with ID %d not found!\n", id);
        return;
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    FreePlayer(&current);
    printf("Player with ID %d deleted successfully!\n", id);
}

void InsertPlayer(PList **head, PList *p) {
    if (*head == NULL) {
        p->next = *head;
        *head = p;
        return;
    }
    PList *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = p;
    p->next = NULL;
}

void ShowPlayer(Player *p) {
    printf("Player ID: %d\n", p->playerId);
    printf("  Nickname: %s\n", p->nichname);
	printf("  Preferred Domains: ");
	for (int i = 0; i < DOMAINS_NUMBER; i++) {
		if (p->Domainspref[i]) {
			printf("%s , ", DOMAINS[i]);
		}
	}
	printf("\n");
	printf("  Games Played: %d\n", p->gamesPlayed);
    printf("  Total Score: %d\n", p->totalScore);
    printf("\n");
}

bool FindPlayer(PList *head, int id, Player *p) {
    PList *current = head;
    while (current != NULL) {
        if (current->val.playerId == id) {
            *p = current->val;
            return true;
        }
        current = current->next;
    }
    return false;
}
void AddPlayerMenu(PList **Phead, int *nbrPl) {
	PList *newPlayerNode;
	AllocatePlayer(&newPlayerNode);
	if (!newPlayerNode) {
		printf("%sMemory allocation failed for new player.%s\n", RED, RESET);
		return;
	}

	Player *newPlayer = &newPlayerNode->val;
	newPlayerNode->next = NULL;

	printf("%sEnter player nickname: %s", YELLOW, RESET);
	scanf("%49s", newPlayer->nichname);

	printf("%sSet domain preferences (1 for yes, 0 for no):%s\n", YELLOW, RESET);
	for (int i = 0; i < DOMAINS_NUMBER; i++) {
		printf("%s  %s: %s", YELLOW, DOMAINS[i], RESET);
		int pref;
		readInt(&pref);
		newPlayer->Domainspref[i] = (pref != 0);
	}

	newPlayer->gamesPlayed = 0;
	newPlayer->totalScore = 0;

	InsertPlayer(Phead, newPlayerNode);
	(*nbrPl)++;
	newPlayer->playerId = *nbrPl;

	printf("%sPlayer added successfully!%s\n", GREEN, RESET);
}

Question* ChooseRandomQuestion(QList *head, int domain, int difficulty) {
    QList *current = head;
    QList *matchingQuestions[100]; // Array to store matching questions
    int count = 0;

    // Traverse the list and collect matching questions
    while (current != NULL) {
        if (current->val.domain == domain && current->val.diff == difficulty) {
            matchingQuestions[count++] = current;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("%sNo questions found for the given domain and difficulty.%s\n", RED, RESET);
        return NULL;
    }

    srand(time(NULL));

    // Select a random question from the matching ones
    int randomIndex = rand() % count;
    return &matchingQuestions[randomIndex]->val;
}
int CalculateScore(int difficulty, int isPreferredDomain) {
    switch (difficulty) {
        case EASY:
            return isPreferredDomain ? 1 : 2;
        case MEDIUM:
            return isPreferredDomain ? 2 : 3;
        case HARD:
            return isPreferredDomain ? 4 : 5;
        default:
            printf("%sInvalid difficulty level.%s\n", RED, RESET);
            return 0;
    }
}

void StartGame(QList *Qhead, Player *player,PartieList **partieHead, int level) {
    int easyQuestions, mediumQuestions, hardQuestions;
	PartieList *newPartie = (PartieList*)malloc(sizeof(PartieList));
	newPartie->next = *partieHead;
	*partieHead = newPartie;
	newPartie->val.playerId = player->playerId;
	newPartie->val.level = level;
	newPartie->val.questions = NULL;
	PartieQlist **currentPartieQ = &newPartie->val.questions;
    // Determine the number of questions for each difficulty based on the level
    switch (level) {
        case 1:
            easyQuestions = 6;
            mediumQuestions = 6;
            hardQuestions = 3;
            break;
        case 2:
            easyQuestions = 5;
            mediumQuestions = 5;
            hardQuestions = 5;
            break;
        case 3:
            easyQuestions = 2;
            mediumQuestions = 5;
            hardQuestions = 8;
            break;
        default:
            printf("%sInvalid level selected.%s\n", RED, RESET);
            return;
    }

    int totalScore = 0;



    // Ask questions for each difficulty
		printf("%sStarting the game at level %d ...%s\n", BLUE, level, RESET);
		totalScore+= AskQuestions(Qhead, *player, easyQuestions, EASY ,currentPartieQ);
		totalScore+= AskQuestions(Qhead, *player, mediumQuestions, MEDIUM ,currentPartieQ);
		totalScore+= AskQuestions(Qhead, *player, hardQuestions, HARD ,currentPartieQ);


    // Display the total score
    printf("%sGame over! Your total score is: %d%s\n", GREEN, totalScore, RESET);

    // Update the player's total score
    player->totalScore += totalScore;
	player->gamesPlayed++;
	newPartie->val.totalScore = totalScore;
	printf("%sGame saved successfully!%s\n", GREEN, RESET);
}
int AskQuestions(QList *head, Player player , int count, int difficulty , PartieQlist **currentPartieQ) {
	if (count <= 0) {
		printf("%sInvalid number of questions.%s\n", RED, RESET);
		return 0;
	}
	int totalScore = 0;
	int preferredDomainsCoutn;
	int nonPreferredDomainsCount;
	int preferredDomains[DOMAINS_NUMBER];
	int nonPreferredDomains[DOMAINS_NUMBER];
	for (int i = 0; i < DOMAINS_NUMBER; i++) {
		if (player.Domainspref[i]) {
			preferredDomains[preferredDomainsCoutn++] = i;
		} else {
			nonPreferredDomains[nonPreferredDomainsCount++] = i;
		}
	}
	switch (difficulty) {
		case EASY:
			printf("%sDifficulty Level: EASY%s\n", GREEN, RESET);
			break;
		case MEDIUM:
			printf("%sDifficulty Level: MEDIUM%s\n", YELLOW, RESET);
			break;
		case HARD:
			printf("%sDifficulty Level: HARD%s\n", RED, RESET);
			break;
		default:
			printf("Invalid difficulty level.\n");
			break;
	}
	srand(time(NULL));
	for (int i = 0; i < count; i++) {
		printf("%sDo you want the next question to be from your preferred domains? (1 for Yes, 0 for No): %s", YELLOW, RESET);
		int preferPreferredDomain;
		readInt(&preferPreferredDomain);

		int *domainsToAsk;
		int numberOfDomains;

		if (preferPreferredDomain) {
			domainsToAsk = preferredDomains;
			numberOfDomains = preferredDomainsCoutn;
		} else {
			domainsToAsk = nonPreferredDomains;
			numberOfDomains = nonPreferredDomainsCount;
		}
		int domainIndex = rand() % numberOfDomains;
		int domain = domainsToAsk[domainIndex];
		Question *q = ChooseRandomQuestion(head, domain, difficulty);
		if (q == NULL) {
			printf("%sNot enough questions available for difficulty %d in domain %s.%s\n", RED, difficulty, DOMAINS[domain], RESET);
			printf("%sSearching for another question.%s\n", RED, RESET);
			i--;
			continue;
		}
		printf("%sQuestion Domain: %s%s\n", YELLOW, DOMAINS[q->domain], RESET);
		int score;
		if (AskQuestion(q, &player)){
			score = CalculateScore(difficulty, player.Domainspref[q->domain]);
			totalScore += score;
			printf("%sCorrect! You earned %d points.%s\n", GREEN, score, RESET);
		} else {
			printf("%sIncorrect! The correct answer was: %s%s\n", RED, q->answers, RESET);
		}

		if (currentPartieQ !=NULL){
			(*currentPartieQ) = (PartieQlist*)malloc(sizeof(PartieQlist));
			(*currentPartieQ)->next = NULL;
			(*currentPartieQ)->question = q;
			(*currentPartieQ)->isPreferredDomain = player.Domainspref[q->domain];
			(*currentPartieQ)->score = score;
			(*currentPartieQ) = (*currentPartieQ)->next;
		}
	}
	return totalScore;
	
}
bool AskQuestion(Question *q, Player *player) {
	printf("Question: %s\n", q->text);
	switch (q->diff) {
	case EASY: {
		int randomStart = rand() % 2;
		printf("Choose the correct answer:\n");
		for (int i = 0; i < 2; i++) {
			int index = (randomStart + i) % 2;
			printf("%d. %s\n", i + 1, q->answers + index * MAX_ANSWER_LEGNTH);
		}
		int playerChoice;
		readInt(&playerChoice);
		return (playerChoice - 1 == randomStart);
	}
	case MEDIUM: {
		int randomStart = rand() % 4;
		printf("Choose the correct answer:\n");
		for (int i = 0; i < 4; i++) {
			int index = (randomStart + i) % 4;
			printf("%d. %s\n", i + 1, q->answers + index * MAX_ANSWER_LEGNTH);
		}
		int playerChoice;
		readInt(&playerChoice);
		return (playerChoice - 1 == randomStart);
	}
	case HARD: {
		printf("Enter your answer: ");
		char playerAnswer[MAX_ANSWER_LEGNTH];
		fgets(playerAnswer, MAX_ANSWER_LEGNTH, stdin);
		playerAnswer[strcspn(playerAnswer, "\n")] = '\0';
		return strcmp(playerAnswer, q->answers) == 0;
	}
	default:
		printf("Invalid question difficulty.\n");
		return false;
	}
}
int CalculateTotalScore(PartieList *partieHead, int playerId) {
    int totalScore = 0;
    PartieList *current = partieHead;

    
    while (current != NULL) {
        if (current->val.playerId == playerId) {
            totalScore += current->val.totalScore;
        }
        current = current->next;
    }

    return totalScore;
}

void PlayerMenu(QList *Qhead, PList **Phead, PartieList **partieHead) {
	int choice, level;
	Player *player;
	printf("Enter your player ID: ");
	int playerId;
	readInt(&playerId);
	if (!FindPlayer(*Phead, playerId, player)) {
		printf("%sPlayer not found!%s\n", RED, RESET);
		return;
	}

	while (1) {
		printf("%s\nPlayer Menu:\n", BLUE, RESET);
		printf("%s1. Start Game\n%s", GREEN, RESET);
		printf("%s2. Edit Profile\n%s", GREEN, RESET);
		printf("%s3. Show Leaderboard\n%s", GREEN, RESET);
		printf("%s0. Exit\n%s", GREEN, RESET);
		printf("%sEnter your choice: %s", RED, RESET);
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Choose game level (1: Easy, 2: Medium, 3: Hard): ");
				readInt(&level);
				StartGame(Qhead, player, partieHead, level);
				break;
			case 2:
				PlayerEditProfile(player);
				break;
			case 3:
				ShowLeaderboard(*Phead);
				break;
			case 0:
				return;
			default:
				printf("%sInvalid choice!%s\n", RED, RESET);
		}
	}
}

void PlayerEditProfile(Player *player) {
	int choice;

	while (1) {
		printf("%s\nEdit Profile:\n", BLUE, RESET);
		printf("%s1. Edit Nickname\n%s", GREEN, RESET);
		printf("%s2. Edit Preferred Domains\n%s", GREEN, RESET);
		printf("%s0. Back\n%s", GREEN, RESET);
		printf("%sEnter your choice: %s", RED, RESET);
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Enter new nickname: ");
				scanf("%49s", player->nichname);
				printf("%sNickname updated successfully!%s\n", GREEN, RESET);
				break;
			case 2:
				printf("Set domain preferences (1 for yes, 0 for no):\n");
				for (int i = 0; i < DOMAINS_NUMBER; i++) {
					printf("  %s: ", DOMAINS[i]);
					int pref;
					readInt(&pref);
					player->Domainspref[i] = (pref == 1);
				}
				printf("%sPreferred domains updated successfully!%s\n", GREEN, RESET);
				break;
			case 0:
				return;
			default:
				printf("%sInvalid choice!%s\n", RED, RESET);
		}
	}
}

void ShowLeaderboard(PList *Phead) {
	PList *players[100];
	int count = 0;

	// Collect players into an array
	while (Phead != NULL) {
		players[count++] = Phead;
		Phead = Phead->next;
	}

	// Sort players by total score in descending order
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (players[i]->val.totalScore < players[j]->val.totalScore) {
				PList *temp = players[i];
				players[i] = players[j];
				players[j] = temp;
			}
		}
	}

	// Display leaderboard
	printf("%s\nLeaderboard:\n", BLUE, RESET);
	for (int i = 0; i < count; i++) {
		printf("%d. %s - Total Score: %d\n", i + 1, players[i]->val.nichname, players[i]->val.totalScore);
	}
}
void QuestionToString(Question *q, char *str) {
	switch (q->diff) {
		case EASY:
			sprintf(str, "\"%d\" \"%d\" \"%d\" \"%s\" \"%s\" \"%s\"",
					q->diff,
					q->qNum,
					q->domain,
					q->text,
					q->answers,
					q->answers + MAX_ANSWER_LEGNTH);
			break;
		case MEDIUM:
			sprintf(str, "\"%d\" \"%d\" \"%d\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"",
					q->diff,
					q->qNum,
					q->domain,
					q->text,
					q->answers,
					q->answers + MAX_ANSWER_LEGNTH,
					q->answers + 2 * MAX_ANSWER_LEGNTH,
					q->answers + 3 * MAX_ANSWER_LEGNTH);
			break;
		case HARD:
			sprintf(str, "\"%d\" \"%d\" \"%d\" \"%s\" \"%s\"",
					q->diff,
					q->qNum,
					q->domain,
					q->text,
					q->answers);
			break;
		default:
			printf("Invalid difficulty level.\n");
			break;
	}
}
void SaveQuestions(QList *head) {
	FILE *file = fopen(QUESTIONS_FILE, "w");
	if (file == NULL) {
		printf("%sError opening file.%s\n", RED, RESET);
		return;
	}
	fprintf(file, "THIS FILE USED TO STORE QUESTIONS\n");
	fprintf(file,"QUESTION FORMAT: \"DIFFICULTY\" \"QUESTION NUMBER\" \"DOMAIN\" \"TEXT\" \"ANSWER1\" \"ANSWER2\" \"ANSWER3\" \"ANSWER4\"\n");
	QList *current = head;
	while (current != NULL) {
		char str[MAX_QUESTION_LEGNTH + 100];
		QuestionToString(&current->val, str);
		fprintf(file, "%s\n", str);
		current = current->next;
	}

	fclose(file);
	printf("%sQuestions saved successfully!%s\n", GREEN, RESET);
}
void SavePlayers(PList *head) {
	FILE *file = fopen(PLAYERS_FILE, "w");
	if (file == NULL) {
		printf("%sError opening file.%s\n", RED, RESET);
		return;
	}
	fprintf(file, "THIS FILE USED TO STORE PLAYERS\n");
	fprintf(file,"PLAYER FORMAT: \"PLAYER ID\"|\"NICKNAME\"|\"GAMES PLAYED\"|\"TOTAL SCORE\"|\"DOMAINS PREFERENCES\"\n");
	PList *current = head;
	while (current != NULL) {
		char str[200];
		PlayerToString(&current->val, str);
		fprintf(file, "%s\n", str);
		current = current->next;
	}

	fclose(file);
	printf("%sPlayers saved successfully!%s\n", GREEN, RESET);
}
int LoadQuestions(QList **head) {
	FILE *file = fopen(QUESTIONS_FILE, "r");
	if (file == NULL) {
		printf("%sError opening file.%s\n", RED, RESET);
		return -1;
	}
	int nbrQst = 0;
	char line[MAX_QUESTION_LEGNTH + 100];
	fgets(line, sizeof(line), file); // Skip the first line
	fgets(line, sizeof(line), file); // Skip the second line	
	while (fgets(line, sizeof(line), file)) {
		// Remove newline character
		line[strcspn(line, "\n")] = '\0';

		QList *newQst;
		AllocateQuestion(&newQst);
		StringToQuestion(&newQst->val, line);
		InsertQuestion(head, newQst);
		nbrQst++;
	}

	fclose(file);
	printf("%sQuestions loaded successfully!%s\n", GREEN, RESET);
	return nbrQst;
}
int LoadPlayers(PList **head) {
	FILE *file = fopen(PLAYERS_FILE, "r");
	if (file == NULL) {
		printf("%sError opening file.%s\n", RED, RESET);
		return -1;
	}
	int nbrPl = 0;
	char line[200];
	fgets(line, sizeof(line), file); // Skip the first line
	fgets(line, sizeof(line), file); // Skip the second line	
	while (fgets(line, sizeof(line), file)) {
		// Remove newline character
		line[strcspn(line, "\n")] = '\0';

		PList *newPlayer;
		AllocatePlayer(&newPlayer);
		StringToPlayer(&newPlayer->val, line);
		InsertPlayer(head, newPlayer);
		nbrPl++;
	}

	fclose(file);
	printf("%sPlayers loaded successfully!%s\n", GREEN, RESET);
	return nbrPl;
}
void PartieToString(Partie *partie, char *str) {
	char questionsStr[1000] = "";
	PartieQlist *currentQ = partie->questions;

	while (currentQ != NULL) {
		char questionStr[200];
		sprintf(questionStr, "%d,%d,%d|", currentQ->question->qNum, currentQ->score, currentQ->isPreferredDomain);
		strcat(questionsStr, questionStr);
		currentQ = currentQ->next;
	}

	sprintf(str, "%d|%d|%d|%s", 
			partie->playerId, 
			partie->level, 
			partie->totalScore, 
			questionsStr);
}

void StringToPartie(Partie *partie, char *str, QList *Qhead) {
	char questionsStr[1000];
	sscanf(str, "%d|%d|%d|%999[^\n]", 
		   &partie->playerId, 
		   &partie->level, 
		   &partie->totalScore, 
		   questionsStr);

	char *token = strtok(questionsStr, "|");
	PartieQlist **currentQ = &partie->questions;

	while (token != NULL) {
		int qNum, score, isPreferredDomain;
		sscanf(token, "%d,%d,%d", &qNum, &score, &isPreferredDomain);

		Question *q = NULL;
		QList *current = Qhead;
		while (current != NULL) {
			if (current->val.qNum == qNum) {
				q = &current->val;
				break;
			}
			current = current->next;
		}

		if (q != NULL) {
			*currentQ = (PartieQlist *)malloc(sizeof(PartieQlist));
			(*currentQ)->question = q;
			(*currentQ)->score = score;
			(*currentQ)->isPreferredDomain = isPreferredDomain;
			(*currentQ)->next = NULL;
			currentQ = &(*currentQ)->next;
		}

		token = strtok(NULL, "|");
	}
}

void SaveParties(PartieList *head) {
	FILE *file = fopen(PARTIES_FILE, "w");
	if (file == NULL) {
		printf("%sError opening file.%s\n", RED, RESET);
		return;
	}
	fprintf(file, "THIS FILE USED TO STORE PARTIES\n");
	fprintf(file, "PARTIE FORMAT: \"PLAYER ID\"|\"LEVEL\"|\"TOTAL SCORE\"|\"QUESTION ID,SCORE,IS PREFERRED DOMAIN|...\"\n");
	PartieList *current = head;
	while (current != NULL) {
		char str[1200];
		PartieToString(&current->val, str);
		fprintf(file, "%s\n", str);
		current = current->next;
	}

	fclose(file);
	printf("%sParties saved successfully!%s\n", GREEN, RESET);
}

int LoadParties(PartieList **head, QList *Qhead) {
	FILE *file = fopen(PARTIES_FILE, "r");
	if (file == NULL) {
		printf("%sError opening file.%s\n", RED, RESET);
		return -1;
	}
	
	int nbrParties = 0;
	char line[1200];
	fgets(line, sizeof(line), file); // Skip the first line
	fgets(line, sizeof(line), file); // Skip the second line
	while (fgets(line, sizeof(line), file)) {
		line[strcspn(line, "\n")] = '\0';

		PartieList *newPartie = (PartieList *)malloc(sizeof(PartieList));
		StringToPartie(&newPartie->val, line, Qhead);
		newPartie->next = *head;
		*head = newPartie;
		nbrParties++;
	}

	fclose(file);
	printf("%sParties loaded successfully!%s\n", GREEN, RESET);
	return nbrParties;
}