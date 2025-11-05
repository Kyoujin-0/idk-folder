#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{	

	char username[50][50];
	char password[50][50];

	char storedUsername[50][50];
	char storedPassword[50][50];
	char loggedUser[50];
	bool passedLogin = false;
	int completedSection = 0;
	int numberOfUser = 0;
	int loginOption = 0;

	FILE *file = fopen("User login.txt", "r");
	if (file != NULL)
	{
		while (fscanf(file, " %49[^,],%49[^\n]\n", storedUsername[numberOfUser], storedPassword[numberOfUser]) == 2)
		{
			numberOfUser++;
		}
		fclose(file);
		printf("Loaded %d accounts from User login.txt\n", numberOfUser);
	}
	else
	{
		printf("No existing accounts, Create a new one\n");
	}
	printf("Welcome to the User Login System\n");
	printf("[1] Sign up\n");
	printf("[2] Log in\n");
	printf("Choose an option: ");
	scanf(" %d", &loginOption);
	getchar();

		switch (loginOption)
		{
		case 1: //sign up

				printf("Enter username: ");
				fgets(storedUsername[numberOfUser], 50, stdin);
				storedUsername[numberOfUser][strcspn(storedUsername[numberOfUser], "\n")] = 0;

				printf("Enter password: ");
				fgets(storedPassword[numberOfUser], 50, stdin);
				storedPassword[numberOfUser][strcspn(storedPassword[numberOfUser], "\n")] = 0;

				numberOfUser++;
			break;


		case 2: //log in

		do {
			printf("Enter username: ");
			fgets(username[0], 50, stdin);
			username[0][strcspn(username[0], "\n")] = 0;

			printf("Enter password: ");
			fgets(password[0], 50, stdin);
			password[0][strcspn(password[0], "\n")] = 0;

			passedLogin = false;
			for (int i = 0; i < numberOfUser; i++)
			{
				if (strcmp(username[0], storedUsername[i]) == 0 && strcmp(password[0], storedPassword[i]) == 0)
			{	
				printf("Login successful! Welcome, %s\n", storedUsername[i]);
				strcpy(loggedUser, storedUsername[i]);
				passedLogin = true;
				break;

				
			} 
			}
			if (!passedLogin)
            {
                printf("Invalid username or password. Please try again.\n");
            }
		
		} while (!passedLogin);
			break;

		default:
			printf("Invalid option. Exiting program.\n");
			return 1;
	}

	file = fopen("User login.txt", "w");
	if (file == NULL)
	{
		printf("Error saving file!\n");
		return 1;
	}

	for (int i = 0; i < numberOfUser; i++)
	{
		fprintf(file, "%s,%s\n", storedUsername[i], storedPassword[i]);
	}

	fclose(file);

if (loginOption == 1)
{
	printf("You can now log in with your new account.\n");
	getchar();
	return 0;
}

char command[200];
// put username in quotes in case it has spaces, and use snprintf to avoid overflow
snprintf(command, sizeof(command), "Advance_version.exe \"%s\"", loggedUser);

// run once — this launches the other program with the username argument
int status = system(command);
if (status != 0) {
	printf("Failed to launch Advance_version.exe or it exited with an error (exit code: %d)\n", status);
}

//system("pause");
return 0;
}