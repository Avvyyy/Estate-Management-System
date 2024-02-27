#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME 20
#define MAX_PASSCODE 5

// Structure to represent a user
typedef struct {
    char name[MAX_NAME];
    int passCode[MAX_PASSCODE];
} User;

// Function to add user to the database
void addUser(char name[], int passcode[]) {
    FILE *userDB = fopen("../Desktop/userDB.txt", "a");
    if (userDB == NULL) {
        printf("Error Creating File");
        return;
    }
    fprintf(userDB, "Name: %s - Passcode: %d", name, passcode);
    fclose(userDB);
}

int main() {
    int availableAttempts = 3;
    char name[MAX_NAME];
    int passcode[MAX_PASSCODE];
    int loginPrompt;
    
    FILE *userDB = fopen("../Desktop/userDB.txt", "re");

    while (loginPrompt != 1 || loginPrompt != 2) {
        printf("\n***Press:\n 1 to login\n 2 to set up a new user\n");
        scanf("%d", &loginPrompt);
    }

    if (loginPrompt == 1) {
        // Code for login
        printf(" ***Welcome Back Home!***\nHope you had a lovely day\nInput your name to proceed: ");
        fgets(name, sizeof(name), STDIN);
        name[strcspn(name, "\n")] = 0; 
        
    } else {
        // Code for setting up a new user
    }

	fclose(userDB);
    return 0;
}


	
	if (name == storedName){
		while(availableAttempts != 0) 
		{
			printf("Input the passcode to proceed");
			scanf("%d", &passCode);
			
			sprintf(passCodeString, "%d", passCode);
			if (strlen(passCodeString) != 5)
			{
				printf("Wrong Password!");
				availableAttempts --;
			}
			else if ()
			{
				
			}
		}
	}
}
