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

int byName(int index, const char *query)
{
    if (index == count)
        return -1;

    if (strcmp(names[index], query) == 0)
        return index;

    return byName(index + 1, query);
}

int byPhone(int index, const char *query)
{
    if (index == count)
        return -1;

    if (strcmp(phones[index], query) == 0)
        return index;

    return byPhone(index + 1, query);
}

int search(int (*op)(int, const char *), const char *query)
{
    int index = 0;
    return op(index, query);
}

void deleteContact(void)
{
    char query[NAME_LEN];
    int index;

    printf("\nEnter the name to delete: ");
    if (fgets(query, sizeof(query), stdin) == NULL)
    {
        printf("\nFailed to read input.\n");
        return;
    }
    trimNewline(query);

    index = search(byName, query);
    if (index == -1)
    {
        printf("\nContact not found.\n");
        return;
    }

    // If it's the last contact, just reduce count
    if (index == count - 1)
        count--;
    else
    { // Copy last to correct index and reduce count
        strcpy(names[index], names[count - 1]);
        strcpy(phones[index], phones[count - 1]);
        count--;
    }

    printf("\nContact deleted successfully.\n");
}
