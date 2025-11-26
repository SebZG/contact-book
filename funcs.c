#include <stdio.h>
#include <string.h>

#include "funcs.h"

void trimNewline(char *str)
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

int isValidPhone(const char *phone)
{
    int len = strlen(phone);

    if (len == 0)
        return 0;

    // Remove newline if present (for fgets)
    if (phone[len - 1] == '\n')
        len--;

    // Lengh must be between 7 and 14
    if (len < 7 || len > 14)
        return 0;

    // Must contain only digits
    for (int i = 0; i < len; i++)
        if (phone[i] < '0' || phone[i] > '9')
            return 0;

    return 1;
}

void addContact(void)
{
    if (count >= MAX)
    {
        printf("\nContact book is full!\n");
        return;
    }

    printf("\nEnter name: ");
    if (fgets(names[count], sizeof(names[count]), stdin) == NULL)
    {
        printf("\nFailed to read name.\n");
        return;
    }
    trimNewline(names[count]);

    while (1)
    {
        printf("\nEnter phone number: ");
        if (fgets(phones[count], sizeof(phones[count]), stdin) == NULL)
        {
            printf("\nFailed to read phone number.\n");
            return;
        }
        trimNewline(phones[count]);

        if (isValidPhone(phones[count]))
            break; // Valid number;
        else
            printf("\nInvalid phone number! It must be between 7-14 digits and contain "
                   "only numbers.\n");
    }

    printf("\nContact added successfully.\n");
    count++;
}

int byName(int index, char *query)
{
    if (index == count)
        return -1;

    if (strcmp(names[index], query) == 0)
        return index;

    return byName(index + 1, query);
}

int byPhone(int index, char *query)
{
    if (index == count)
        return -1;

    if (strcmp(phones[index], query) == 0)
        return index;

    return byPhone(index + 1, query);
}

void search(int (*op)(int, char *), char *query, int q_size)
{
    if (fgets(query, q_size, stdin) == NULL)
    {
        printf("\nFailed to read input.\n");
        return;
    }
    trimNewline(query);

    int index = op(0, query);
    if (index == -1)
        printf("\nContact not found.\n");
    else
        printf("\nFound...\n\nName: %s, Phone: %s\n", names[index], phones[index]);
}

void displayContacts(void)
{
    if (count == 0)
    {
        printf("\nNo contacts to display.\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    for (int i = 0; i < count; i++)
        printf("%d) Name: %s, Phone: %s\n\n", i + 1, names[i], phones[i]);
}

void updateContact(int (*op)(int, char *), char *query, int q_size)
{
    if (count == 0)
    {
        printf("\nNo contacts to update.\n");
        return;
    }

    if (fgets(query, q_size, stdin) == NULL)
    {
        printf("\nFailed to read input.\n");
        return;
    }
    trimNewline(query);

    int index = op(0, query);
    if (index == -1)
    {
        printf("\nContact not found.\n");
        return;
    }

    printf("\nCurrent Contact Info:\n\nName: %s, Phone: %s\n", names[index], phones[index]);

    int choice;
    printf("\nWhat would you like to update?\n");
    printf("1) Name\n");
    printf("2) Phone\n");
    printf("3) Both\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("\nInvalid input.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        return;
    }
    getchar(); // Clear newline

    if (choice == 1 || choice == 3)
    {
        printf("\nEnter new name: ");
        if (fgets(names[index], NAME_LEN, stdin) == NULL)
        {
            printf("\nFailed to read name.\n");
            return;
        }
        trimNewline(names[index]);
    }

    if (choice == 2 || choice == 3)
    {
        while (1)
        {
            printf("\nEnter new phone number: ");
            if (fgets(phones[index], PHONE_LEN, stdin) == NULL)
            {
                printf("\nFailed to read phone.\n");
                return;
            }
            trimNewline(phones[index]);

            if (isValidPhone(phones[index]))
                break;
            else
                printf("\nInvalid phone number! It must be between 7-14 digits and contain only numbers.\n");
        }
    }

    printf("\nContact updated successfuly.\n");
}

void deleteContact(int (*op)(int, char *), char *query, int q_size)
{
    if (count == 0)
    {
        printf("\nNo contacts to delete.\n");
        return;
    }

    if (fgets(query, q_size, stdin) == NULL)
    {
        printf("\nFailed to read input.\n");
        return;
    }
    trimNewline(query);

    int index = op(0, query);
    if (index == -1)
    {
        printf("\nContact not found.\n");
        return;
    }

    // If it's the last contact, just reduce count
    if (index == count - 1)
        count--;
    else // Copy last to correct index and reduce count
    {
        strcpy(names[index], names[count - 1]);
        strcpy(phones[index], phones[count - 1]);
        count--;
    }

    printf("\nContact deleted successfully.\n");
}
