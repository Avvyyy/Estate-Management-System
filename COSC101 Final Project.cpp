#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME 20
#define MAX_PASSCODE 6

void addUser(char name[], char passcode[]);
int loginUser(char name[], char passcode[]);

// Function to add user to the database
void addUser(char name[], char passcode[]) {
    FILE *userDB = fopen("userDB.txt", "a+");
    if (userDB == NULL) {
        perror("Error Creating File");
        return;
    }
    fprintf(userDB, "Name: %s - Passcode: %s\n", name, passcode);
    fclose(userDB);
}

int loginUser(char name[], char passcode[]) {
    // Variables to hold the name and passcode retrieved from the userDB
    char storedName[MAX_NAME];
    char storedPasscode[MAX_PASSCODE];
    
    // Open the file in read mode
    FILE *userDB = fopen("userDB.txt", "r");
    if (userDB == NULL){
        perror("Database could not be accessed!\n");
        return 1;
    }
    
    // Declare a buffer to store the line read from the userDB
    char buffer[MAX_NAME + MAX_PASSCODE + 20]; // 20 for "Name: " and " - Passcode: "
    
    // While there is content in the userDB
    while(fgets(buffer, sizeof(buffer), userDB) != NULL){
        // Extract the name and passcode from the buffer
        sscanf(buffer, "Name: %s - Passcode: %s\n", storedName, storedPasscode);
        
        // Compare the name and passcode inputted to the name and passcode stored in the userDB
        if(strcmp(storedName, name) == 0 && strcmp(storedPasscode, passcode) == 0){
            fclose(userDB);
            return 0; // Login successful
        }
    }
    fclose(userDB); // Close the file after use
    
    return 1; // No matching user found or incorrect passcode
}

int main() {
    int availableAttempts = 3;
    char name[MAX_NAME];
    char passcode[MAX_PASSCODE];
    int loginPrompt;
    int isSuccessful;
    
    FILE *userDB = fopen("userDB.txt", "a+");
    if (userDB == NULL) {
        perror("Error Creating/Opening File");
        return 1;
    }
    fclose(userDB);
    
    printf("\n***\nPress:\n 1 to login\n 2 to set up a new user\n***");
    scanf("%d", &loginPrompt);
    while(getchar() != '\n'); // Flush the input buffer

    if (loginPrompt == 1) {
        // Code for login
        while (availableAttempts > 0) {
            printf("***Welcome Back Home!***\nHope you had a lovely day\nInput your name to proceed: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            
            printf("Input your your 5-digit passcode: ");
            fgets(passcode, sizeof(passcode), stdin);
            passcode[strcspn(passcode, "\n")] = 0;
            
            isSuccessful = loginUser(name, passcode);
            
            if (isSuccessful != 0) {
                printf("Incorrect name or password\nLogin Failed\n");
                availableAttempts--;
                if (availableAttempts <= 0) {
                    printf("You have exceeded your login limits\n");
                    break;
                }
            } else {
                printf("Login Successful\n");
                break;
            }
        }
    } else if (loginPrompt == 2) {
        printf("Input your name to register new user: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        
        printf("Input your your 5-digit passcode: ");
        fgets(passcode, sizeof(passcode), stdin);
        passcode[strcspn(passcode, "\n")] = 0;
        
        addUser(name, passcode);
        printf("User successfully created\n");
    } else {
        printf("%d is not an option\n", loginPrompt);
    }

    return 0;
}

