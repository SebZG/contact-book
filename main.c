#include <stdio.h>

#include "funcs.h"

/*
    names[0][{"Sebastian"}]
    names[1][{"John"}]
    names[2][{"Michael"}]

    phones[0][{"1234567"}]
    phones[1][{"1234567"}]
    phones[2][{"1234567"}]
*/

// Globals (storage for contacts)
char names[MAX][NAME_LEN];
char phones[MAX][PHONE_LEN];
int count = 0;

int main()
{
    int choice;
    char query[NAME_LEN];
    int index = 0;

    while (1)
    {
        printf("\n--- Contact Book Menu ---\n");
        printf("1. Add Contact\n");
        printf("2. Search by Name\n");
        printf("3. Search by Phone\n");
        printf("4. Display All Contacts\n");
        printf("5. Update Contact\n");
        printf("6. Delete Contact\n");
        printf("7. Exit\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            // Clear invalid input
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("\nInvalid input. Try agian.\n");
            continue;
        }
        getchar(); // Clear leftover newline from input buffer

        switch (choice)
        {
        case 1:
            if (count >= MAX)
            {
                printf("\nContact book is full!\n");
                break;
            }
            else
            {
                addContact();
                break;
            }

        case 2:
            if (count == 0)
            {
                printf("\nNo contacts to search.\n");
                break;
            }
            else
            {
                printf("\nEnter name to search: ");
                search(byName, query, NAME_LEN);
                break;
            }

        case 3:
            if (count == 0)
            {
                printf("\nNo contacts to search.\n");
                break;
            }
            else
            {
                printf("\nEnter phone number to search: ");
                search(byPhone, query, PHONE_LEN);
                break;
            }

        case 4:
            if (count == 0)
            {
                printf("\nNo contacts to display.\n");
                break;
            }
            else
            {
                displayContacts();
                break;
            }

        case 5:
            if (count == 0)
            {
                printf("\nNo contacts to update.\n");
                break;
            }
            else
            {
                printf("\nEnter name to update: ");
                updateContact(byName, query, NAME_LEN);
                break;
            }

        case 6:
            if (count == 0)
            {
                printf("\nNo contacts to delete.\n");
                break;
            }
            else
            {
                printf("\nEnter name to delete: ");
                deleteContact(byName, query, NAME_LEN);
                break;
            }

        case 7:
            printf("\nExiting Contact Book. Goodbye!\n");
            return 0;

        default:
            printf("\nInvalid choice. Try again.\n");
            break;
        }
    }

    return 0;
}
