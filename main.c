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
    int index;

    while (1)
    {
        printf("\n--- Contact Book Menu ---\n");
        printf("1. Add Contact\n");
        printf("2. Search by Name\n");
        printf("3. Search by Phone\n");
        printf("4. Display All Contacts\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");
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
            addContact();
            break;

        case 2:
            printf("\nEnter name to search: ");
            if (fgets(query, sizeof(query), stdin) == NULL)
                break;
            trimNewline(query);
            index = search(byName, query);
            if (index == -1)
                printf("\nContact not found.\n");
            else
                printf("\nFound...\n\nName: %s, Phone: %s\n", names[index], phones[index]);
            break;

        case 3:
            printf("\nEnter phone number to search: ");
            if (fgets(query, sizeof(query), stdin) == NULL)
                break;
            trimNewline(query);
            index = search(byPhone, query);
            if (index == -1)
                printf("\nContact not found.\n");
            else
                printf("\nFound...\n\nName: %s, Phone: %s\n", names[index], phones[index]);
            break;

        case 4:
            displayContacts();
            break;

        case 5:
            deleteContact();
            break;

        case 6:
            printf("\nExiting Contact Book. Goodbye!\n");
            return 0;

        default:
            printf("\nInvalid choice. Try again.\n");
            break;
        }
    }

    return 0;
}
