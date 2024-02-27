#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME 20
#define MAX_PASSCODE 5

void addUser(char name[], int passcode[]);

// Function to add user to the database
void addUser(char name[], int passcode[]) {
    FILE *userDB = fopen("userDB.txt", "a+");
    if (userDB == NULL) {
        perror("Error Creating File");
        return;
    }
    fprintf(userDB, "Name: %s - Passcode: %d\n", name, passcode);
    fclose(userDB);
}

int main() {
    int availableAttempts = 3;
    char name[MAX_NAME];
    int passcode;
    int loginPrompt;
    
    FILE *userDB = fopen("userDB.txt", "ra+");

    printf("\n***\nPress:\n 1 to login\n 2 to set up a new user\n***");
    scanf("%d", &loginPrompt);
    getchar(); // Consume newline character

    if (loginPrompt == 1) {
        // Code for login
        printf(" ***Welcome Back Home!***\nHope you had a lovely day\nInput your name to proceed: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; 
        
    } else if(loginPrompt == 2) {
    	printf("Input your name to register new user: ");
    	fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; 
        
        printf("Input your your 5-digit passcode: ");
        scanf("%d", &passcode);
        
        addUser(name, &passcode);
        printf("User successfully created");
    } else{
    	printf("%d is not an option\n", loginPrompt);
    	main();
	}

	fclose(userDB);
    return 0;
}

