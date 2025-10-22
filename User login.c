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
	bool passedLogin = false;
	int completedSection = 0;
	int numberOfUser = 0;
	int numberOfUsername = 0;
	int numberOfPassword = 0;
	int loginOption = 0;

	FILE *file = fopen("User login.txt", "r");
	if (file != NULL)
	{
		while (fscanf(file, " %49[^,],%49[^\n]\n", storedUsername[numberOfUsername], &storedPassword[numberOfPassword]) == 2)
		{
			numberOfUser++;
			numberOfUsername++;
			numberOfPassword++;
		}
		fclose(file);
		printf("Loaded %d products from User login.txt\n", numberOfUser);
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

			for (int i = 0; i < 1; i++)

			{
				printf("Enter username: ");
				fgets(username[numberOfUsername], 50, stdin);
				username[numberOfUsername][strcspn(username[numberOfUsername], "\n")] = 0;

				printf("Enter password: ");
				fgets(password[numberOfPassword], 50, stdin);
				password[numberOfPassword][strcspn(password[numberOfPassword], "\n")] = 0;

				numberOfUser++;
				numberOfUsername++;
				numberOfPassword++;
			}
			break;

		case 2: //log in

		do {
			printf("Enter username: ");
			fgets(username[0], 50, stdin);
			username[0][strcspn(username[0], "\n")] = 0;
			printf("Enter password: ");
			fgets(password[0], 50, stdin);
			password[0][strcspn(password[0], "\n")] = 0;
			if (strcmp(username[0], storedUsername[0]) == 0 && strcmp(password[0], storedPassword[0]) == 0)
			{	
				printf("Login successful! Welcome, %s\n", username[0]);
				passedLogin = true;
				break;
			}

			else
			{
				printf("Invalid username or password. Please try again.\n");
			}
		} while (passedLogin == false);
			break;
	}

	file = fopen("User login.txt", "w");
	if (file == NULL)
	{
		printf("Error saving file!\n");
		return 1;
	}

	for (int i = 0; i < numberOfUser - 1; i++)
	{
		fprintf(file, "%s,%s\n", storedUsername[i], storedPassword[i]);
	}

	fprintf(file, "%s,%s\n", username[numberOfUsername - 1], password[numberOfPassword - 1]);

	fclose(file);
	printf("login saved successfully to 'User login.txt'!\n");


/*print sample output
for (int i = 0; i < numberOfUser - 1; i++)
{
	printf("Login successful! Welcome, %s   ", storedUsername[i]);
	printf("%s\n", storedPassword[i]);
}

printf("Login successful! Welcome, %s   ", username[numberOfUsername - 1]);
printf("%s\n", password[numberOfPassword - 1]);*/

printf("Username:%s\n", storedUsername[0]);
	printf("password:%s\n", storedPassword[0]);
	printf("answer:%s\n", username[0]);
	printf("answer:%s\n", password[0]);

system("pause");
// system("main.exe");
return 0;
}