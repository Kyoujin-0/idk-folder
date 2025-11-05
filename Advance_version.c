#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void displayProducts(char products[][100], int productQuantity[], int productCount)
{
    printf("\n==========================================\n");
    printf("| %-3s | %-20s | %-8s |\n", "No", "Product Name", "Quantity");
    printf("------------------------------------------\n");

    for (int i = 0; i < productCount; i++)
    {
        printf("| %-3d | %-20s | %-8d |\n", i + 1, products[i], productQuantity[i]);
    }

    printf("==========================================\n");
}

int main(int argc, char *argv[])
{

    int actionChoice = 0;
    int additionalQuantity = 0;
    int productChoice = 0;

    char products[100][100];
    int productQuantity[50];
    int totalProducts = 0;
    int productCount = 0;
    char loggedUser[50];

    printf("\n=======================================\n \033[1;32mProduct Inventory Management System\033[0m \n=======================================\n");
    printf("               \033[1;31mUPDATED\033[0m\n\n");

    // get the username
    if (argc > 1)
    {
        printf("Logged in as: %s\n", argv[1]);
        strncpy(loggedUser, argv[1], sizeof(loggedUser) - 1);
        loggedUser[sizeof(loggedUser) - 1] = '\0';
    }
    else
    {
        printf("No username argument received.\n");
    }

    // Load saved inventory or create new file
    char filename[100];
    snprintf(filename, sizeof(filename), "%s.txt", loggedUser);

    FILE *pF = fopen(filename, "a+");
    if (pF != NULL)
    {
        rewind(pF);
        while (fscanf(pF, "%99[^,],%d\n", products[productCount], &productQuantity[productCount]) == 2)
        {
            productCount++;
            totalProducts++;
        }
        fclose(pF);
    }
    else
    {
        printf("Failed to open or create '%s'.\n", filename);
    }

    do
    {
        actionChoice = 0;

        printf("\n");
        printf("1. Add Product\n");
        printf("2. View all product\n");
        printf("3. Update quantity\n");
        printf("4. Delete product\n");
        printf("5. Save & Exit\n");
        printf("Choose an action: ");
        scanf("%d", &actionChoice);
        printf("---------------------------------------\n");

        switch (actionChoice)
        {
        case 1: // Add Product

            if (productCount >= 50)
            {
                printf("Inventory full! Cannot add more products.\n");
                break;
            }

            getchar();

            printf("Enter product name: ");
            fgets(products[productCount], sizeof(products[productCount]), stdin);
            products[productCount][strcspn(products[productCount], "\n")] = 0;
            printf("Enter product quantity: ");
            scanf("%d", &productQuantity[productCount]);
            productCount++;
            printf("Product added successfully!\n\n");
            printf("Updated Product List:\n");
            displayProducts(products, productQuantity, productCount);

            break;
        case 2: // View all product

            displayProducts(products, productQuantity, productCount);

            break;

        case 3: // Update quantity

            printf("\nItem List\n");
            displayProducts(products, productQuantity, productCount);

            printf("Choose product to update quantity: ");
            scanf("%d", &productChoice);
            printf("Enter additional quantity to add: ");
            scanf("%d", &additionalQuantity);

            productQuantity[productChoice - 1] += additionalQuantity;
            printf("Updated %s quantity to %d\n", products[productChoice - 1], productQuantity[productChoice - 1]);

            printf("---------------------------------------\n");

            break;

        case 4: // Delete product

            printf("\nItem List\n");

            if (productCount == 0)
            {
                printf("No products to delete.\n");
                break;
            }
            for (int i = 0; i < productCount; i++)
            {
                printf("%d. %s - Quantity: %d\n", i + 1, products[i], productQuantity[i]);
            }
            int productDeleteChoice = 0;
            printf("Choose product to delete: ");
            scanf("%d", &productDeleteChoice);

            if (productDeleteChoice < 1 || productDeleteChoice > productCount)
            {
                printf("Invalid choice!\n");
                break;
            }

            for (int i = productDeleteChoice - 1; i < productCount - 1; i++)
            {
                strcpy(products[i], products[i + 1]);
                productQuantity[i] = productQuantity[i + 1];
            }
            productCount--;
            printf("Product deleted successfully!\n");

            printf("---------------------------------------\n");

            break;

        case 5: // Save & Exit
        {

            FILE *pF = fopen(filename, "w");
            if (pF == NULL)
            {
                printf("Error saving file!\n");
                break;
            }

            for (int i = 0; i < productCount; i++)
            {
                fprintf(pF, "%s,%d\n", products[i], productQuantity[i]);
            }

            fclose(pF);
            printf("Inventory saved successfully to '%s'!\n", filename);
            break;
        }

        default:
            printf("Invalid action! Please choose again.\n");
            break;
        }
    } while (actionChoice != 5);

    system("pause");
    return 0;
}