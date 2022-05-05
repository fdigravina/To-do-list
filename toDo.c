/*
  
  Author: Filippo di Gravina
  Title: To-Do application
  
  Description:
  
  Every task has a description, a category, flag (completed) and a user associated
  Every user has a name and some tasks associated
  
*/


// libraries

#include <stdio.h>      // input/output
#include <string.h>     // string manipulation
#include <ctype.h>      // isdigit, isalpha

// macros

#define string_dim 21  // username and password max length
#define max_num_of_tasks 100  // maximum number of tasks per user
#define description_dim 100  // maximum description length
#define category_dim 100  // maximum category string length
#define max_user_capacity 100  // max number of users in the program

// user defined types

struct task {
    
    char description [description_dim];
    char category [category_dim];
    int completed;
    
};

struct user {

    char username [string_dim];
    char password [string_dim];
    struct task myTasks [max_num_of_tasks];
    
};


// global variables

char name [string_dim];  // user logged in the system
struct user registeredUser [max_user_capacity];  // list of users registered in the program
int hasAccess;  // false if the user isn't logged in the system
int myUserIndex;    // it stores the index of this user in the registredUser array


// functions

// let the user choice between login and registration

char getAccess () {

    int validValue = 0;  // false if not accessed in the system yet
    char accessOption;  // character that gets the option selected

    do {

        printf ("Print R to register, L to login: ");
        scanf (" %c", &accessOption);

        if (accessOption == 'R' || accessOption == 'r') {
            validValue = 1;
            puts ("You choose to register!\n");
        } else if (accessOption == 'L' || accessOption == 'l') {
            validValue = 1;
            puts ("You choose to login!\n");
        } else {
            puts ("The input is not correct!\n");
        }

    } while (!validValue);
    
    return accessOption;

}


/*
  
  the username is correct if:
    - the username contains only alphanumeric characters
    - the username length is between six and twenty characters
  
*/

int isCorrectUsername () {

    int length = strlen (name);

    if (length < 6) {
        puts ("This username is too short!");
        return 0;
    }

    for (int i=0; i<length; ++i)
        if (!isdigit(name[i]) && !isalpha(name[i])) {
            puts ("This name does not respect all the conditions!");
            return 0;
    }

    return 1;

}


/*
  
  the password is correct if:
    - it contains an uppercase letter
    - it contains a lowercase letter
    - it contains a digit
    - it contains a symbol
    - its length is between eight and twenty characters
  
*/

int isCorrectPassword (char* password) {
    
    int length = strlen (password);
    
    int hasDigit = 0;       // true if the password contains at least a digit
    int hasUppercase = 0;   // true if the password contains at least an uppercase letter
    int hasLowercase = 0;   // true if the password contains at least a lowercase letter
    int hasSymbol = 0;      // true if the password contains at least a symbol

    if (length < 8) {
        puts ("This password is too short!");
        return 0;
    }

    for (int i=0; i<length; ++i) {
        
        if (password[i] >= 48 && password[i] <= 57) hasDigit = 1;
        else if (password[i] >= 65 && password[i] <= 90) hasUppercase = 1;
        else if (password[i] >= 97 && password[i] <= 122) hasLowercase = 1;
        else hasSymbol = 1;
        
    }
    
    if (hasDigit & hasUppercase & hasLowercase & hasSymbol == 0) {
        puts ("This name does not respect all the conditions!");
        return 0;
    }

    return 1;

}


// true if the name is already present in the database

int alreadyRegistered () {

    for (int i=0; i<max_user_capacity; ++i)
        if (strcmp (registeredUser[i].username, name) == 0) {
            puts ("This name is already registered in the database!");
            return 1;
        }

    return 0;

}

/*
    Finds the first empty spot in the registeredUser array
    
    Return value:
        - Index of the first empty position if there's a empty position
        - -1 elsewhere
    
*/

int firstFreeUserPosition () {
    
     for (int i=0; i<max_user_capacity; ++i)
        if (strcmp (registeredUser[i].username, "") == 0)
            return i;
    
    return -1;
    
}

int firstFreeTaskPosition () {
    
     for (int i=0; i<max_num_of_tasks; ++i)
        if (strcmp (registeredUser[myUserIndex].myTasks[i].description, "") == 0)
            return i;
    
    return -1;
    
}

/*
  
  - gets username and password
  - registers the user if the credentials are correct
  
  the credentials are correct if:
    - the username is not previously registered
    - the username contains only alphanumeric characters
    - the username length is between six and twenty characters
    - the password contains an uppercase letter
    - the password contains a lowercase letter
    - the password contains a digit
    - the password contains a symbol
    - the password length is between eight and twenty characters
  
*/

void signUp () {

    int validUsername;  // // true if the password has a valid pattern and is not already used
    int validPassword;  // true if the password has a valid pattern
    char password [string_dim];  // takes the password from the user

    do {

        puts ("What username do you want to register?");
        puts ("The name must contain only alphanumeric characters and its length must be between six and twenty characters.");
        
        printf ("Your username: ");
        scanf (" %20s", name);
        
        validUsername = 1;
        validUsername &= isCorrectUsername ();
        validUsername &= !alreadyRegistered ();

    } while (!validUsername);
    
    do {

        puts ("\nThe password must contain an uppercase letter, a lowercase letter, a digit and a symbol and its length must be between six and twenty characters.\n");
        
        printf ("Your password: ");
        scanf (" %20s", password);
        
        validPassword = isCorrectPassword (password);

    } while (!validPassword);
    
    int pos = firstFreeUserPosition ();
    
    if (pos !=- 1) {
        
        myUserIndex = pos;
        
        strcpy (registeredUser[pos].username, name);
        strcpy (registeredUser[pos].password, password);
        
    }
    
    hasAccess = 1;

}

int isRegistered (char* name, char* password) {
    
    for (int i=0; i<max_user_capacity; ++i)
        if (strcmp (registeredUser[i].username, name) == 0 && strcmp (registeredUser[i].password, password) == 0) {
            myUserIndex = i;
            return 1;
        }
    
    return 0;
    
}

/*
    It requests a username and a password and let the registered user access the program
*/

void signIn () {

    int validUsername;  // true if the username has a valid pattern and is not already used
    int validPassword;  // true if the password has a valid pattern
    char password [string_dim];
    
    do {

        puts ("Welcome to the login form!\n");
        printf ("Your username: ");

        scanf (" %20s", name);

        validUsername &= isCorrectUsername ();
        
    } while (!validUsername);
    
    do {

        puts ("\nThe password must contain an uppercase letter, a lowercase letter, a digit and a symbol and its length must be between six and twenty characters.\n");
        
        printf ("Your password: ");
        scanf (" %20s", password);
        
        validPassword = isCorrectPassword (password);

    } while (!validPassword);
    
    if (isRegistered (name, password)) {
        puts ("Welcome to the program!");
        hasAccess = 1;
    } else {
        puts ("Username or password not correct!\n");
    }

}

// creates a new task for this user

void createTask () {
    
    char description [description_dim];
    char category [category_dim];
    
    printf ("Enter the description of the task: ");
    scanf (" %[^\n]100s", &description);
    
    printf ("Enter the category of the task: ");
    scanf (" %[^\n]100s", &category);
    
    int pos = firstFreeTaskPosition ();
    
    strcpy (registeredUser[myUserIndex].myTasks[pos].description, description);
    strcpy (registeredUser[myUserIndex].myTasks[pos].category, category);
    registeredUser[myUserIndex].myTasks[pos].completed = 0;
    
}


/*
    Displays all the tasks of a user
*/

void viewMyTasks () {
    
    char completedSign;
    
    for (int i=0; i<max_num_of_tasks; ++i) {
        
        if (strcmp (registeredUser[myUserIndex].myTasks[i].description, "") == 0) continue;
        
        if (registeredUser[myUserIndex].myTasks[i].completed) completedSign = 'X';
        else completedSign = ' ';
        
        printf ("[%c] %do task:\n", completedSign, i+1);
        printf ("Description: %s\n", registeredUser[myUserIndex].myTasks[i].description);
        printf ("Category: %s\n\n", registeredUser[myUserIndex].myTasks[i].category);
        
    }
    
    putchar ('\n');
    
}

// swaps two integers

void swap (int* x, int* y) {
    
    int z = *x;
    *x = *y;
    *y = z;
    
}

void swapStr (char* x, char* y) {
    
    char z [description_dim];
    
    strcpy (z, x);
    strcpy (x, y);
    strcpy (y, z);
    
}


/*
    Ordered the tasks of a user:
        - It displays all the non-completed tasks first
        - And then it displays all the completed tasks
*/

void orderMyTasks () {
    
    for (int i=0; i<max_num_of_tasks; ++i) for (int j=i+1; j<max_num_of_tasks; ++j)
        if (registeredUser[myUserIndex].myTasks[i].completed > registeredUser[myUserIndex].myTasks[j].completed) {
            
            if (strcmp (registeredUser[myUserIndex].myTasks[i].description, "") == 0 || strcmp (registeredUser[myUserIndex].myTasks[j].description, "") == 0)
                continue;
            
            swapStr (registeredUser[myUserIndex].myTasks[i].description, registeredUser[myUserIndex].myTasks[j].description);
            swapStr (registeredUser[myUserIndex].myTasks[i].category, registeredUser[myUserIndex].myTasks[j].category);
            swap (&registeredUser[myUserIndex].myTasks[i].completed, &registeredUser[myUserIndex].myTasks[j].completed);
            
        }
    
    puts ("Now your task are ordered!\n");
    
}


/*
    displays to the user the non-completed tasks
    and lets the user flag one of them as completed
    
*/

void setAsCompleted () {
    
    int pos;    // position of the task to set as completed
    
    for (int i=0; i<max_num_of_tasks; ++i)
        if (registeredUser[myUserIndex].myTasks[i].completed == 0 && strcmp (registeredUser[myUserIndex].myTasks[i].description, "") != 0) {
            
            printf ("[ ] %do task: ", i+1);
            printf ("Description: %s\n", registeredUser[myUserIndex].myTasks[i].description);
            printf ("Category: %s\n\n", registeredUser[myUserIndex].myTasks[i].category);
            
        }
    
    printf ("\nWhat task do you wanna set as completed: ");
    scanf (" %d", &pos);
    
    --pos;
    
    if (pos < 0 || pos > max_num_of_tasks) puts ("This value is not valid!\n");
    else if (registeredUser[myUserIndex].myTasks[pos].completed == 0) registeredUser[myUserIndex].myTasks[pos].completed = 1;
    else puts ("This value is not valid!\n");
    
}


// It displays all the tasks with that category

void viewCategory () {
    
    int found = 0;  // true if at least one task has a category
    char category [category_dim];   // the category to search
    
    printf ("Enter the category you want to see: ");
    scanf (" %[^\n]100s", &category);
    
    for (int i=0; i<max_num_of_tasks; ++i)
        if (strcmp (registeredUser[myUserIndex].myTasks[i].category, category) == 0) {
            
            found = 1;
            
            printf ("[ ] %do task: ", i+1);
            printf ("Description: %s\n", registeredUser[myUserIndex].myTasks[i].description);
            printf ("Category: %s\n\n", registeredUser[myUserIndex].myTasks[i].category);
            
        }
        
    if (!found) puts ("No task has this category!\n");
    
    
}


/*
    It displays the program functionalities and let the user choice one
    Returns 0 if the user wants to terminate the execution of the program, 1 elsewhere
*/

int menu () {
    
    puts ("\n\n");
    
    puts ("Print 1 to create a new task.");
    puts ("Print 2 to flag a task as completed.");
    puts ("Print 3 to order your tasks (not completed task first).");
    puts ("Print 4 to view your tasks.");
    puts ("Print 5 to view all the task of a particular category.");
    puts ("Print 6 to terminate the execution of the program.");
    
    int choice;
    
    printf ("Your choice: ");
    scanf (" %d", &choice);
    
    putchar ('\n');
    
    if (choice == 1) createTask ();
    else if (choice == 2) setAsCompleted ();
    else if (choice == 3) orderMyTasks ();
    else if (choice == 4) viewMyTasks ();
    else if (choice == 5) viewCategory ();
    else if (choice == 6) return 0;
    else puts ("Your choice is not valid!\n");
    
    return 1;
    
}

int main() {
    
    while (!hasAccess) {
        
        puts ("---- To-Do list application ----\n");
        
        puts ("Do you want to login or register?");
        char accessOption = getAccess ();

        if (accessOption == 'R' || accessOption == 'r')
            signUp ();
        else
            signIn ();
        
        getchar ();
        
    }
    
    int choice;
    
    while (menu()) getchar();

}