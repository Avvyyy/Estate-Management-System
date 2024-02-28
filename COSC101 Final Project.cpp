#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME 20
#define MAX_PASSCODE 5

void addUser(char name[], int passcode[]);
int loginUser(char name[], int passcode[]);

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

int loginUser(char name[], int passcode[]) {
	//Variables hold the names and passcode gotten from userDB
	char storedName[MAX_NAME];
	int storedPasscode[MAX_PASSCODE];
	//Open the file in readmode
	FILE *userDB = fopen("userDB.txt", "r");
	//What happens if the userDB cannot be found?
	if (userDB == NULL){
		perror("Database could not be accessed!\n");
		return 1;
	}
	//Declare a buffer to store the password and email from the db temporaily
	char buffer[MAX_NAME + MAX_PASSCODE];
	//While there is content in the userDB
	while(fgets(buffer, sizeof(buffer), userDB) != NULL){
		
		//Store the name and password in temporary variables
		sscanf(buffer, "Name: %s - Passcode: %d\n", storedName, storedPasscode);
		
		if(strcmp(storedName, name) == 0 && passcode == storedPasscode){
			fclose(userDB);
			return 0;
		}
		else{
			return 1;
		}
		//Compare the name and passcode inputted to the name and passcode 
	}
}

int main() {
    int availableAttempts = 3;
    char name[MAX_NAME];
    int passcode;
    int loginPrompt;
    int isSuccessful;
    
    FILE *userDB = fopen("userDB.txt", "ra+");
    
    printf("\n***\nPress:\n 1 to login\n 2 to set up a new user\n***");
    scanf("%d", &loginPrompt);
    getchar(); // Consume newline character

    if (loginPrompt == 1) {
        // Code for login
        while (availableAttempts != 0 && isSuccessful != 0){
	        printf(" ***Welcome Back Home!***\nHope you had a lovely day\nInput your name to proceed: ");
	        fgets(name, sizeof(name), stdin);
	        name[strcspn(name, "\n")] = 0;
			
			printf("Input your your 5-digit passcode: ");
	        scanf("%d", &passcode);
			
			isSuccessful = loginUser(name, &passcode);
			
			if (isSuccessful != 0){
				printf("Incorrect name or password\nLogin Failed\a\n");
				availableAttempts --;
				if (availableAttempts < 0){
					printf("You have exceeded your login limits");
					break;
				}
			}else{
				printf("Login Successful");
				break;
			}

		}
		
        
        
        
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

