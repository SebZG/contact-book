#pragma once

#include <stdio.h>

// Configuration
#define MAX 100
#define NAME_LEN 100
#define PHONE_LEN 15

// Globals (defined in main.c)
extern char names[MAX][NAME_LEN];
extern char phones[MAX][PHONE_LEN];
extern int count;

// Utilities
void trimNewline(char *str);
int isValidPhone(const char *phone);

// Operations
void addContact(void);
void displayContacts(void);
int byName(int index, const char *query);
int byPhone(int index, const char *query);
int search(int (*op)(int, const char *), const char *query);
void deleteContact(void);
