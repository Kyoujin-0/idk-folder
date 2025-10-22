#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main()
{

    int actionChoice = 0;
    int additionalQuantity = 0;
    int productChoice = 0;

    // inventory (default items)
    char products[100][100] = {"Keyboard", "CPU", "Monitor"};
    int productQuantity[50] = {30, 20, 15};
    int totalProducts = 3;
    int productCount = 3;

    printf("=======================================\n Product Inventory Management System \n=======================================");

    do
    {
        actionChoice = 0;

        printf("\n");
        printf("1. Add Product\n");
        printf("2. View all product\n");
        printf("3. Update quantity\n");
        printf("4. Delete product\n");
        printf("9. Save & Exit\n");
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

            for (int i = 0; i < productCount; i++)
            {
                printf("%d. %s - Quantity: %d\n", i + 1, products[i], productQuantity[i]);
            }

            printf("---------------------------------------\n");

            break;
        case 2: // View all product

            printf("\nProduct List:\n");
            for (int i = 0; i < productCount; i++)
            {
                printf("%d. %s - Quantity: %d\n", i + 1, products[i], productQuantity[i]);
            }
            printf("---------------------------------------\n");

            break;

        case 3: // Update quantity

            printf("\nItem List\n");
            for (int i = 0; i < productCount; i++)
            {
                printf("%d. %s - Quantity: %d\n", i + 1, products[i], productQuantity[i]);
            }
            printf("Choose product to update quantity: ");
            scanf("%d", &productChoice);
            printf("Enter additional quantity to add: ");
            scanf("%d", &additionalQuantity);

            productQuantity[productChoice - 1] += additionalQuantity;
            printf("Updated %s quantity to %d\n", products[productChoice - 1], productQuantity[productChoice - 1]);

            printf("---------------------------------------\n");

            break;

        case 4: // Delete product

        case 9:
            break;
        }

    } while (actionChoice != 9);

    system("pause");
    return 0;
}