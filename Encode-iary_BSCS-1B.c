/*
    Members:            Babila, Angeline P.
                        Espiritu, Johnry E.
                        Girado, John Omar
                        San Jose, Carl Edward
    Course and Bloc:    BS Computer Science 1-B
    Title:              Encode-iary: A Personal Enciphered Journal Application
    Description:        A digital journal capable of enciphering and deciphering its entries providing an extra
                        layer of security for those who need to retain sensitive information or safeguard
                        confidentialsources
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ENTRY_SIZE 1000
#define MAX_USERINFO_LENGTH 25
#define MAX_DATE_SIZE 25
#define SYMBOLS_SIZE 124
#define CIPHER "symbols.txt"     // stores the array of characters responsible for character conversion
#define USER "user.txt"          // stores user's username and password
#define ENTRIES "entryfiles.txt" // stores the filenames of the entries already made

struct user
{
    char name[MAX_USERINFO_LENGTH];
    char pass[MAX_USERINFO_LENGTH];
};

void banner(char *text); // displays the name of the program and the section currently displayed in the screen
void title();
void logsave();                // a function that will save the user's username and password into a simple database
void logrtr(int);              // a function that will retrieve the user's login information when called
void clearscreen();            // looks at what operating system the program is ran on and executes the corresponding system call to clear the screen
void setup();                  // checks if the files necessary for the program already exists. If not, functions that would set up these files will be called
void setup_message();          // gives preliminary introduction to the user
int check_file(char *file);    // checks whether file containing character conversions already exists
void reps_pref();              // asks user if they are to use the program's pre-defined system of character conversion or to have it customized
void customized_conversions(); // warns the user that having customized conversions would take some time
void customized_file();        // function to be called if they want to customize the conversions through file
void customized_screen();      // function to be called if they want to customize the conversions through the program
void loadsymbols(int x);       // loads the character conversions in a file
void menu(int flag);           // displays the menu available in the program
char *encipher(char *entry);   // takes a string as an input and converts it into a random set of characters that is unreadable
char *decipher(char *entry);   // takes a string of random characters as an input and deciphers back into its readable form
void add_entry();              // gets an entry from the user
void view_entries();           // views an entry among the existing entries
void delete_entry();           // deletes an entry among the existing entries
void edit_password();          // allows user to edit their stored password
void reset_diary();            // allows user to erase all files and information created using the program
void exit_message();

int main()
{
    setup();
    title();
    logrtr(0);
    return 0;
}

void banner(char *message)
{
    printf("\n\n");
    printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\t\t\t*                                                                           *\n");
    printf("\t\t\t*          ENCODE-IARY: A Personal Enciphered Journal Application           *\n");
    printf("\t\t\t*                                                                           *\n");
    printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\t\t\t");
    int length = (78 - strlen(message)) / 2, j;
    for (j = 0; j < length; j++)
        printf(" "); // print space
    printf("%s\n", message);
    printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
}

void title()
{
    clearscreen();
    printf("\n\n");
    int length = (114 - strlen("Hi there! Welcome back to")) / 2, j;
    for (j = 0; j < length; j++)
        printf(" "); // print space
    printf("Hi there! Welcome back to");
    printf("\n\n\n");
    printf("\t-------  ---    ---   -------   -------  -------   -------        ----      ----      ----------  ---     ---\n");
    printf("\t|  ---|  |  \\   |  | |  ----|  |  ---  | |  --  \\  |  ---|        |  |     /    \\     |  ---   |   \\  \\  /  /\n");
    printf("\t| |---   |   \\  |  | |  |      |  | |  | |  | |  | | |---   ---   |  |    /  /\\  \\    |  |  |  |    \\  \\/  /\n");
    printf("\t|  ---|  |  \\ \\ |  | |  |      |  | |  | |  | |  | |  ---| |   |  |  |   /  /--\\  \\   |   --   /     \\    /\n");
    printf("\t| |---   |  |\\ \\|  | |  |      |  | |  | |  | |  | | |---   ---   |  |  /  /----\\  \\  |  | \\  \\       |  |\n");
    printf("\t|     |  |  | \\    | |  ----|  |  ---  | |  --  /  |     |        |  | /  /      \\  \\ |  |  \\  \\      |  |\n");
    printf("\t-------  ---   ----   -------   -------  -------   -------        ---- ---        --- ----   ----     ----\n");
    printf("\n");
    length = (114 - strlen("A Personal Enciphered Journal Application")) / 2;
    for (j = 0; j < length; j++)
        printf(" "); // print space
    printf("A Personal Enciphered Journal Application\n\n\n\n\n\n");
    printf("\tPress enter to continue...");
    getchar();
}

void logsave() // a function that will save the user's username and password into a simple database
{
    clearscreen();
    banner("WELCOME TO THE REGISTRATION PAGE");
    FILE *ofp;

    struct user person;
    struct user *personPtr = &person;

    printf("\n\t\t\tCreate a username (max of 20 characters): ");
    scanf("%s", personPtr->name);
    printf("\t\t\tCreate a password (max of 20 characters): ");
    scanf("%s", personPtr->pass);
    printf("\n\t\t\tYou have been registered. Press enter to continue... ");
    // output on the ofp database
    ofp = fopen(USER, "w+");
    fprintf(ofp, "%s\n", personPtr->name);
    fprintf(ofp, "%s\n", personPtr->pass);
    fclose(ofp);
    getchar();
    getchar();
}

void logrtr(int flag)
{
    clearscreen();
    banner("LOGIN");

    if (flag == 1)
    {
        getchar();
        printf("\n\t\t\tAs a security measure, please enter your user credentials to proceed.\n");
    }
    FILE *ifp;
    ifp = fopen(USER, "r+");
    if (ifp == NULL)
    {
        printf("\t\t\tError opening file.\n");
    }

    struct user person;
    struct user user1;
    struct user *personPtr = &person;

    int errorcount = 0, i;
    char ch;
    fgets(user1.name, MAX_USERINFO_LENGTH, ifp);
    fgets(user1.pass, MAX_USERINFO_LENGTH, ifp);
    while (errorcount < 3) // loop that would stop the program when the max of three attempts is already reached
    {
        printf("\n\t\t\tEnter your username: ");
        fgets(personPtr->name, MAX_USERINFO_LENGTH, stdin);
        printf("\t\t\tEnter your password: ");
        fgets(personPtr->pass, MAX_USERINFO_LENGTH, stdin);

        if ((strcmp(user1.name, personPtr->name) == 0) && (strcmp(user1.pass, personPtr->pass) == 0)) // if inputted username and password matches those stored on file
        {
            printf("\n\t\t\tLogin Succesful! \n");
            if (flag == 0)
                menu(0);
            else
                return;
            break;
        }
        else
        {
            errorcount++;
            printf("\t\t\tWrong Credentials. Please login again.\n");
        }
    }
    if (errorcount == 3)
    {
        printf("\n\t\t\tYou have reached max number of attempts. Goodbye.\n");
        exit(1);
    }
}

void setup()
{
    FILE *fp;
    int x = 0, i;
    char symbols[SYMBOLS_SIZE];
    x = check_file(USER) + check_file(ENTRIES) + check_file(CIPHER);
    if (x < 3)
        setup_message();

    if (check_file(USER) == 0) // checks if file "user.txt" does not yet exist
        logsave();
    if (check_file(ENTRIES) == 0) // checks if file "entryfiles.txt" does not yet exist
    {
        fp = fopen(ENTRIES, "w+");
        fclose(fp);
    }
    if (check_file(CIPHER) == 1) // if file for conversions exists but characters are incomplete
    {
        fp = fopen(CIPHER, "r+");
        for (i = 0; i < SYMBOLS_SIZE; i++) // reading the characters and conversions from the file and storing it in the array
            fscanf(fp, "%c", &symbols[i]);
        fclose(fp);
        if (strlen(symbols) < SYMBOLS_SIZE) // if file containing conversions exists but does not contain the right number of elements
        {
            clearscreen();
            banner("ERROR RETRIEVING SOURCE FILES");
            printf("\n\t\t\tIt seems that the file containing your character conversions were altered or \n\t\t\twasn't saved properly during setup. We would require you to setup your \n\t\t\tencryption system once again...");
            getchar();
            reps_pref();
        }
    }
    else if (check_file(CIPHER) == 0) // checks if file "symbols.txt" does not yet exist
        reps_pref();
    else
        return;
}

void setup_message()
{
    clearscreen();
    banner("WELCOME");
    printf("\n\t\t\tWelcome to ENCODE-IARY, your own personal diary, encrypted for your security\n");
    printf("\t\t\tand comfort. ");
    getchar();
    printf("\n\t\t\tCreate a secure, private journal to record your thoughts, feelings, and experiences.");
    getchar();
    printf("\n\t\t\tWith ENCODE-IARY, your entries are kept safe and secure with a personalized ");
    printf("\n\t\t\tencryption system. ");
    getchar();
    clearscreen();
    banner("WELCOME");
    printf("\n\t\t\tCreating an account with ENCODE-IARY is easy. ");
    getchar();
    printf("\n\t\t\tJust follow the instructions in the setup steps to get started. Once you've ");
    printf("\n\t\t\tcreated your account, you can start writing in your journal. Write as much or as ");
    printf("\n\t\t\tlittle as you like - ENCODE-IARY is here to keep your entries safe and secure. ");
    getchar();
    printf("\n\t\t\tSo go ahead, express yourself. With ENCODE-IARY, your entries are yours and yours ");
    printf("\n\t\t\talone. Record your thoughts, feelings, and experiences in a secure, private journal  ");
    printf("\n\t\t\twith ENCODE-IARY. ");
    getchar();
}

void clearscreen()
{
#ifdef _WIN32 // if program is ran on Windows
    system("cls");

#elif __linux__ // if program is ran on Linux
    system("clear");

#endif
}

int check_file(char *file)
{
    if (fopen(file, "r+") == NULL) // if file still does not exist...
        return 0;
    else // if file already exists
        return 1;
}

void reps_pref()
{
    clearscreen();
    banner("SETUP CONVERSIONS");
    int choice, errcount = 0; // choice stores user input; errcount determines if user has made an invalid input
    printf("\n\n\t\t\tYou have the choice of having your encryption system customized\n");
    printf("\t\t\tor making use of our own codes. Please enter your choice below:\n\n");
    printf("\t\t\t\t1. Customized encryption system\n");
    printf("\t\t\t\t2. Pre-defined encryption system\n");

    do
    {
        if (errcount != 0)
            printf("\t\t\tInvalid choice. Try again.");
        printf("\n\t\t\tEnter number of choice: ");
        scanf("%d", &choice);
        errcount++;
    } while (choice != 1 && choice != 2); // loop iterates until user has entered a valid input
    switch (choice)
    {
    case 1: // if user wants to have customized conversions
        customized_conversions();
        break;
    case 2:             // if user chose to use the pre-defined conversions
        loadsymbols(0); // parameter 0 means user wanted pre-defined conversions
        break;
    }
}

void customized_conversions()
{
    clearscreen();
    int choice, errcount = 0; // choice stores user input; errcount determines if user has made an invalid input
    banner("SETUP CONVERSIONS");
    printf("\n\t\t\tHow would you like to setup your customized encryption system?\n");
    printf("\n\t\t\t\t1. Through file");
    printf("\n\t\t\t\t\t- You will be asked to open a file where you will assign a \n\t\t\t\t\trepresentation for each character\n");
    printf("\n\t\t\t\t2. Through this program");
    printf("\n\t\t\t\t\t- You will be asked to choose from a set of available characters \n\t\t\t\t\tdisplayed on the screen for the representation you want for \n\t\t\t\t\teach character\n");
    printf("\n\t\t\t\t0. Go back to previous\n");
    do
    {
        if (errcount != 0)
            printf("\t\t\t\tInvalid choice. Try again.");
        printf("\n\t\t\tEnter number of choice: ");
        scanf("%d", &choice);
        errcount++;
    } while (choice != 1 && choice != 2 && choice != 0); // loop iterates until user has entered a valid input

    switch (choice)
    {
    case 1:
        customized_file();
        break;
    case 2:
        customized_screen();
        break;
    case 0:
        reps_pref();
    }
}

void customized_file()
{

    FILE *fp;
    int i, j, x = 0, flag = 0;
    char symbols[65], cipher[65];
    fp = fopen("instructions.txt", "w+"); // creating file named instructions.txt
    // Writing instructions on the file
    fprintf(fp, "/* To set up your customized encryption system using file, follow these steps: */\n\n");
    fprintf(fp, "\t1. Open file 'conversions.txt'.\n");
    fprintf(fp, "\t2. Upon opening you would see an array of characters containing the capital and\n\tsmall letters of the alphabet and the digits 0-9. If not, copy the one shown below\n\tand paste it on the file:\n\n");
    fprintf(fp, "\t\tABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\n\n");
    fprintf(fp, "\t3. Press enter once to create a new line\n");
    fprintf(fp, "\t4. Right below each character on the first line, type the character that you \n\twould want to represent it. Continue doing this step until you reach the end and have \n\tthe content of the file somehow looking like this:\n\n");
    fprintf(fp, "\t\tABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\n");
    fprintf(fp, "\t\tBCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789A\n\n");
    fprintf(fp, "*Note that the characters on the second line is just an example. You can have any \n\tother character that you want provided that it does not fall on any of the following conditions:\n");
    fprintf(fp, "\ta.) the same character with the one to be represented\n");
    fprintf(fp, "\tb.) Not among the characters: '.', '?', '!', ',', '\'', ':', ';'\n");
    fprintf(fp, "\tc.) Not a white space\n");
    fprintf(fp, "\n\t5. Save changes to file 'conversions.txt'.\n");
    fprintf(fp, "\t6. Go back to the program and press enter. Check if there are instructions to \n\treplace certain characters. If there is, replace the specified character with a valid one\n\t(see note). Repeat steps 4 to 6 until no replacements needed.\n");
    fprintf(fp, "\t7. If the program has proceed to the menu and the phrase 'Symbols setup completed' \n\tappears on the topmost of the screen, that means your inputs are all valid and that\n\ttthe setup for for your customized encryption syste, is done.\n");
    fclose(fp);
    fp = fopen("conversions.txt", "w+");  // creating file named conversions.txt
    for (i = 0, j = 65; i < 26; i++, j++) // loop that stores the capital letters 'A' to 'Z' on the first 26 elements of the array symbol and outputs it in a file
    {
        symbols[i] = j;
        fprintf(fp, "%c", symbols[i]);
    }
    for (j = 97; i < 52; i++, j++) // loop that stores the small letters 'a' to 'z' on the next 26 elements of the array symbol and outputs it in a file
    {
        symbols[i] = j;
        fprintf(fp, "%c", symbols[i]);
    }
    for (j = 48; i < 62; i++, j++) // loop that stores the digits 0 to 9 on the next 10 elements of the array symbols and outputs it in a file.
    {
        symbols[i] = j;
        fprintf(fp, "%c", symbols[i]);
    }
    fclose(fp);
    getchar();
    while (flag == 0) // flag determines whether file input is accurate. 0 for inaccurate, 1 for accurate
    {
        x = 0;
        clearscreen();
        banner("SETUP CUSTOMIZED CONVERSIONS THROUGH FILE");
        printf("\n\t\t\tINSTRUCTIONS: Go to the folder where this program is stored and look for the \n\t\t\tfile 'conversions.txt'. Open it and follow the steps found on your user \n\t\t\tmanual or on the file 'instructions.txt'\n\n\t\t\tGo back here once done and press enter to check if your inputs are valid...");
        getchar();
        fp = fopen("conversions.txt", "r+");
        fgets(symbols, 65, fp);
        printf("\n\n\t\t\t");
        int length = (78 - strlen("FILE ASSESSMENT")) / 4, j;
        for (j = 0; j < length; j++)
            printf("* ");
        printf("%s", "FILE ASSESSMENT");
        for (j = 0; j < length; j++)
            printf(" *");
        printf("\n");
        if (strlen(symbols) < 62) // determining whether the first line on file converesions.txt was altered
        {
            printf("\n\n\t\t\tERROR: The first line on file was altered and became invalid. You are not \n\t\t\tsupposed to make changes on the first line. Go to file 'instructions.txt' \n\t\t\tand copy the string of characters given in step number 2 and paste it on \n\t\t\tthe first line of 'conversions.txt'");
            x++;
        }
        else
        {
            for (i = 0; i < 62; i++)
            {
                fscanf(fp, "%c", &cipher[i]);
                // checks whether the inputted characters are valid
                for (j = 0; j < i; j++)
                {
                    if (cipher[i] == cipher[j])
                    {
                        printf("\n\t\t\tReplace representation for %c (character already used)", symbols[i]);
                        x++;
                        break;
                    }
                }
                if (cipher[i] == '.' || cipher[i] == '?' || cipher[i] == '!' || cipher[i] == ',' || cipher[i] == '\'' || cipher[i] == ':' || cipher[i] == ';' || cipher[i] == symbols[i] || cipher[i] == 32 || cipher[i] == 0 || cipher[i] <= 34 || cipher[i] >= 127)
                {
                    printf("\n\t\t\tReplace representation for %c (character can't be used as a representation)", symbols[i]);
                    x++;
                }
            }
        }
        if (x == 0)
        {
            flag = 1;
            break;
        }
        else
        {
            printf("\n\n\t\t\tPress enter to try again...");
        }
        fclose(fp);
        getchar();
    }
    fp = fopen(CIPHER, "w+");
    // printing valid conversion characters on symbols.txt
    for (i = 0; i < 62; i++)
        fprintf(fp, "%c", symbols[i]);
    for (i = 0; i < 62; i++)
        fprintf(fp, "%c", cipher[i]);
    fclose(fp);
    remove("instructions.txt"); // deleting instructions.txt
    remove("conversions.txt");  // deleting conversions.txt
    menu(1);
}

void customized_screen()
{
    clearscreen();
    banner("SETUP CONVERSIONS");
    printf("\t\t\tWARNING: This process would take some time and effort. If it would be too much\n");
    printf("\t\t\tof an inconvenience with you, we suggest you to just make use of our pre-defined\n");
    printf("\t\t\tencryption system. It is also important to note that once you proceed, you \n");
    printf("\t\t\thave to finish setting up the conversions up until the end to ensure seamless use\n");
    printf("\t\t\tof the program.");
    printf("\n\n\t\t\t\t1. Continue?");
    printf("\n\t\t\t\t2. Go back");
    int choice, errcount = 0;
    do
    {
        if (errcount != 0)
            printf("\t\t\t\tInvalid choice. Try again.");
        printf("\n\t\t\tEnter number of choice: ");
        scanf("%d", &choice);
        errcount++;
    } while (choice != 1 && choice != 2); // loop iterates until user has entered a valid input
    switch (choice)
    {
    case 1:
        loadsymbols(1); // parameter 1 means user wanted customized conversions
        break;
    case 2:
        reps_pref(); // goes back to choosing whether using customized or pre-defined conversions
        break;
    }
}

void loadsymbols(int x) // x indicates whether user has chosen to use customized or pre-defined conversions. 0 for pre-defined, 1 for customized
{

    FILE *fp;
    fp = fopen(CIPHER, "w+"); // creates a file to store character conversions
    clearscreen();
    banner("SETUP CONVERSIONS");
    char symbols[SYMBOLS_SIZE], allchars[88]; // symbols is the array to store the character conversions and is to be printed in the file; the first 52 elements are the uppercase and lowercase alphabet; the next 52 elements are their equivalent characters that will be used to encipher texts
                                              // allchars stores the available characters where the user can choose to represent the uppercase and lowercase letters
    int i, j, k, l, flag = 0;                 // i,j,k, and l are for loop counters; flag determines whether a character chosen by the user to represent another character was already used
    for (i = 0, j = 65; i < 26; i++, j++)     // loop that stores the capital letters 'A' to 'Z' on the first 26 elements of the array symbol and outputs it in a file
    {
        symbols[i] = j;
        fprintf(fp, "%c", symbols[i]);
    }
    for (j = 97; i < 52; i++, j++) // loop that stores the small letters 'a' to 'z' on the next 26 elements of the array symbol and outputs it in a file
    {
        symbols[i] = j;
        fprintf(fp, "%c", symbols[i]);
    }
    for (j = 48; i < 62; i++, j++) // loop that stores the digits 0 to 9 on the next 10 elements of the array symbols and outputs it in a file.
    {
        symbols[i] = j;
        fprintf(fp, "%c", symbols[i]);
    }
    if (x == 1) // checks the parameter passed when this function was called. 1 means user wanted customized codes
    {
        for (i = 0, j = 34; i < 88; i++, j++) // loop that stores the available characters the user can choose to represent characters in the array allchars
        {
            if (j == 39 || j == 44 || j == 46 || j == 45 || j == 63) // these characters are made not available because they are punctuation marks.
                i--;                                                 // decrements i to revert the count by 1 to fill in the place supposedly taken by the excluded characters
            else
                allchars[i] = j;
        }
        for (i = 62, j = 0; i < SYMBOLS_SIZE; i++, j++) // loop that will ask the user to input the character they want to represent another character; the input, if vaild, will be stored in the 53rd to the 104th element of the array symbols and will be printed in a file
        {
            flag = 0; // will determine if user has entered an invalid input
            while (flag == 0)
            {
                printf("\n\t\t\tAvailable characters: \n");
                printf("\t\t\t");
                for (k = 0; k < 88; k++) // displays the list of characters where the user can choose at most one at a time
                {
                    printf("%c ", allchars[k]);
                    if ((k + 1) % 38 == 0)
                        printf("\n\t\t\t");
                }
                printf("\n\n\t\t\tEnter character to represent '%c': ", symbols[j]);
                getchar();
                symbols[i] = getchar();  // gets a character as an input from the user
                for (l = 0; l < 88; l++) // scans the elements of allchars if the inputted character is still available
                {
                    if (allchars[l] == symbols[i]) // if match found...
                    {
                        allchars[l] = 32; // the position where the character inputted by the user is placed in the array allchars becomes blank
                        flag = 1;         // flag becomes 1; means that user has chosen a valild character
                        break;
                    }
                }
                if (flag == 0) // if flag did not become 1, user has made an invalid character input, program would ask the user to input a new character
                {
                    printf("\n\t\t\tCharacter unavailable. Please select among available characters.");
                }
            }
            fprintf(fp, "%c", symbols[i]); // valid character inputs would be stored on the 53rd to 104th element of array allchars consecutively
        }
        fclose(fp);
        menu(1); // proceeds to menu; parameter 1 means setup has just finished
    }
    else // user chose pre-defined codes
    {
        // assigns the character next to  the character in the ASCII table as the character's conversion
        // conversions will be stored on the 63rd to 124th element of array symbols and will be printed on a file
        for (i = 62, j = 66; i < 88; i++, j++)
        {
            symbols[i] = j;
            fprintf(fp, "%c", symbols[i]);
        }
        for (i = 88, j = 98; i < 114; i++, j++)
        {
            symbols[i] = j;
            fprintf(fp, "%c", symbols[i]);
        }
        for (i = 114, j = 49; i < SYMBOLS_SIZE; i++, j++)
        {
            if (j == ':')
                j += 2;
            symbols[i] = j;
            fprintf(fp, "%c", symbols[i]);
        }
        fclose(fp);
        menu(1);
    }
}

void menu(int flag) // flag determines if system setup was done prior to displaying menu or not
{
    int choice; // stores user input
    char username[MAX_USERINFO_LENGTH];
    do
    {
        clearscreen();
        if (flag == 1)
            printf("\t\t\tSymbols setup completed...");
        banner("MENU");
        FILE *fp;
        fp = fopen(USER, "r+");
        fgets(username, MAX_USERINFO_LENGTH, fp);
        printf("\n\t\t\tHello, %s", username);
        fclose(fp);
        printf("\t\t\tWhat would you like to do?\n");
        printf("\n\n");
        printf("\t\t\t\t1. Add an entry\n");
        printf("\t\t\t\t2. View an entry\n");
        printf("\t\t\t\t3. Delete an entry\n");
        printf("\t\t\t\t4. Edit password\n");
        printf("\t\t\t\t5. Reset Diary\n");
        printf("\t\t\t\t0. Exit\n");
        printf("\n\t\t\tEnter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_entry();
            break;
        case 2:
            view_entries();
            break;
        case 3:
            delete_entry();
            break;
        case 4:
            edit_password();
            break;
        case 5:
            reset_diary();
            break;
        case 0:
            exit_message();
            break;
        default:
            printf("\t\t\t\tInvalid input. Press any key to try again...");
            getchar();
            getchar();
        }
        flag = 0;
    } while (choice != 0);
}

void add_entry()
{
    FILE *fp, *entryfp;
    logrtr(1);
    clearscreen();
    char entry[MAX_ENTRY_SIZE], enciphered[MAX_ENTRY_SIZE]; // will store user's text input
    char date[MAX_DATE_SIZE];
    banner("ADD ENTRY");
    printf("\n\t\t\tEnter date (mm-dd-yyyy): ");
    scanf("%s", date);         // getting input for date
    strcat(date, ".txt");      // adding '.txt' to the date stored as a string as it will serve as the filename of the file where entry will be stored
    if (check_file(date) == 1) // checking if a file with the same same date already exists
    {
        printf("\n\t\t\tEntry for date already exists. The entry you will enter here will\n");
        printf("\t\t\tbe appended on the existing file of the same name.\n");
    }

    printf("\n\t\t\tEnter entry (Press enter once done): \n\n\t\t\t\t");
    getchar();
    fgets(entry, MAX_ENTRY_SIZE, stdin); // getting the entry
    strcpy(enciphered, encipher(entry)); // passing the string to function encipher and storing the returned value to enciphered

    entryfp = fopen(ENTRIES, "a+");
    if (check_file(date) == 1) // checking if a file with the same same date already exists
    {
        fp = fopen(date, "a+");
    }
    else
    {
        fp = fopen(date, "w+");
        fprintf(entryfp, "%s\n", date); // adding the filename of the newly created file to "entryfiles.txt" which stores the list of existing files
    }
    fprintf(fp, " %s (newline) ", enciphered); // printing the enciphered version of the entry on the file with date as the filename
    printf("\t\t\tEntry added successfully. Press enter to go back to menu... ");
    getchar();
    fclose(fp);
    fclose(entryfp);
}

char *encipher(char entry[]) // takes a string as an input and converts it into a random set of characters that is unreadable
{
    FILE *fp, *ofp;             // fp will read the file containing the character coversions; ofp creates a file
    char symbols[SYMBOLS_SIZE]; // will store the array for conversions read from the file
    int i, j;                   // for loop counters
    fp = fopen(CIPHER, "r+");   // reads file containing conversions

    for (i = 0; i < SYMBOLS_SIZE; i++) // stores the characters read from the file of conversions in the array symbols
    {
        fscanf(fp, "%c", &symbols[i]);
    }

    for (i = 0; i < MAX_ENTRY_SIZE; i++) // converts characters to their corresponding representations
    {
        for (j = 0; j < (SYMBOLS_SIZE / 2); j++)
            if (entry[i] == symbols[j])
            {
                entry[i] = symbols[j + (SYMBOLS_SIZE / 2)];
                break;
            }
    }
    fclose(fp);
    return entry;
}

void view_entries()
{
    logrtr(1);
    clearscreen();
    char entry[MAX_ENTRY_SIZE];   // array to store entry to be read from file
    char filename[MAX_DATE_SIZE]; // array to store the filename to be entered by the user
    int x = 1, i, choice;
    FILE *fp, *entryfp;
    entryfp = fopen(ENTRIES, "r+");

    banner("VIEW ENTRY");

    printf("\n\n\t\t\tExisting files: \n\n");
    while (fscanf(entryfp, "%s", filename) != EOF) // prints the list of existing files read from "entryfiles.txt"
    {
        printf("\t\t\t\t%d. %s\n", x, filename);
        x++;
    }
    if (x == 1) // if "entryfiles.txt is empty"
    {
        printf("\t\t\t\tNo files exist as of the moment. Please first add an entry.\n");
        printf("\t\t\tPress enter to go back to menu... ");
        getchar();
        menu(0);
    }
    else
    {
        printf("\n\t\t\t0. Go back to menu\n");
        i = 0;
        int check;
        do
        {
            if (i != 0)
                printf("\t\t\t\tInvalid input. Please try again...\n");
            printf("\n\t\t\tEnter the number of the file you want to view (example: 1): ");
            check = scanf("%d", &choice); // gets input for filename
            if (check != 1)
            {
                printf("\t\t\t\tInvalid input. Input must be an integer. Please try again later...");
                getchar();
                getchar();
                menu(0);
            }
            i++;
        } while (choice < 0 || choice > x - 1);
        if (choice == 0)
            menu(0);
        else
        {
            rewind(entryfp);
            for (x = 1; x <= choice; x++)
            {
                fscanf(entryfp, "%s", filename);
            }
        }
        if (check_file(filename) == 0) // if file does not exist
        {
            printf("\t\t\tEntry does not exist. Please try again later...");
            getchar();
            getchar();
            menu(0);
        }
        else
        {
            fp = fopen(filename, "r+"); // reads entry file where enciphered entry is stored
            printf("\n\n\t\t\tViewing content of %s: \n", filename);
            printf("\n\t\t\t\t");
            while (fscanf(fp, "%s", entry) != EOF) // reading enciphered text from file
            {
                if (strcmp("(newline)", entry) == 0)
                    printf("\n\n\t\t\t\t");
                else
                    printf("%s ", entry); // printing enciphered text
            }
            printf("\n\n\t\t\t\t1. Unveil message\n\t\t\t\t2. Go back to menu ");
            printf("\n\t\t\tEnter choice: ");
            scanf("%d", &x);
            while (1)
            {
                switch (x)
                {
                case 1:        // if user wishes to view text in deciphered form
                    logrtr(1); // login is required
                    break;
                case 2:
                    menu(0);
                    break;
                default:
                    printf("\t\t\tInvalid input.\n\n");
                }
                if (!((x == 1) || (x == 2)))
                {
                    printf("\t\t\t\t1. Unveil message\n\t\t\t\t2. Go back to menu ");
                    printf("\n\t\t\tEnter choice: ");
                    scanf("%d", &x);
                }
                else
                    break;
            }
            clearscreen();
            banner("VIEW ENTRY");
            printf("\n\t\t\tMessage stored in %s: \n", filename);
            printf("\n\t\t\t\t");
            rewind(fp);
            while (fscanf(fp, "%s", entry) != EOF)
            {
                if (strcmp(entry, "(newline)") == 0)
                    printf("\n\n\t\t\t\t");
                else
                {
                    strcpy(entry, decipher(entry)); // function call to decipher() which returns the readable form of the text
                    printf("%s ", entry);           // printing deciphered text
                }
            }
            fclose(fp);
            printf("\n\t\t\tPress any key to go back to menu...");
            getchar();
            menu(0);
        }
    }
}

char *decipher(char *entry)
{
    FILE *fp, *ofp;
    char symbols[SYMBOLS_SIZE]; // array to contain characters and their conversions
    int i, j;                   // for loop counters
    fp = fopen(CIPHER, "r+");
    for (i = 0; i < SYMBOLS_SIZE; i++) // reading the characters and conversions from the file and storing it in the array
        fscanf(fp, "%c", &symbols[i]);
    for (i = 0; i < MAX_ENTRY_SIZE; i++) // converting the conversions back to its original character
        for (j = 62; j < SYMBOLS_SIZE; j++)
            if (entry[i] == symbols[j])
            {
                entry[i] = symbols[j - (SYMBOLS_SIZE / 2)];
                break;
            }
    return entry;
}

void delete_entry()
{
    clearscreen();
    char filename[MAX_DATE_SIZE], compare[MAX_DATE_SIZE]; // filename and compare would store filenames
    int x = 1, i, choice;
    FILE *fp, *entryfp;
    entryfp = fopen(ENTRIES, "r+");
    fp = fopen("temp.txt", "w+"); // creating a temporary file that will store a copy of the list of existing entries
    banner("DELETE ENTRY");
    printf("\n\n\t\t\tExisting files: \n\n");
    while (fscanf(entryfp, "%s", filename) != EOF) // printing the list of existing entries read from "entryfiles.txt"
    {
        printf("\t\t\t\t%d. %s\n", x, filename);
        fprintf(fp, "%s\n", filename);
        x++;
    }
    if (x == 1) // if "entryfiles.txt" is empty
    {
        printf("\t\t\t\tNo files exist as of the moment. Please first add an entry.\n");
        printf("\t\t\tPress enter to go back to menu... ");
        getchar();
        getchar();
        menu(0);
    }
    else
    {
        printf("\n\t\t\t0. Go back to menu\n");
        i = 0;
        int check;
        do
        {
            if (i != 0)
                printf("\t\t\t\tInvalid input. Please try again...\n");
            printf("\n\t\t\tEnter the number of the file you want to delete (example: 1): ");
            check = scanf("%d", &choice); // gets input for filename
            if (check != 1)
            {
                printf("\t\t\t\tInvalid input. Input must be an integer. Please try again later...");
                getchar();
                getchar();
                menu(0);
            }
            i++;
        } while (choice < 0 || choice > x - 1);
        if (choice == 0)
            menu(0);
        else
        {
            rewind(entryfp);
            for (x = 1; x <= choice; x++)
            {
                fscanf(entryfp, "%s", filename);
            }
        }
        if (check_file(filename) == 0) // checking if file that the user wants to delete exists
        {
            printf("\t\t\tEntry does not exist. Please try again later...");
            getchar();
            getchar();
            menu(0);
        }
        else
        {
            i = 0;
            do
            {
                if (i != 0)
                    printf("\t\t\t\tInvalid input. Please try again...\n");
                printf("\n\t\t\tAre you sure you want to delete the entry stored in '%s'(1-YES / 2-NO)? ", filename);
                check = scanf("%d", &choice); // gets input for filename
                if (check != 1)
                {
                    printf("\t\t\t\tInvalid input. Input must be an integer. Please try again later...");
                    getchar();
                    getchar();
                    menu(0);
                }
                i++;
            } while (choice != 1 && choice != 2);
            if (choice == 2)
            {
                printf("\n\t\t\tWhew. Your memories are important. We're glad you chose to keep it.\n\t\t\tPress enter to go back to menu...");
                getchar();
                getchar();
                menu(0);
            }
            else
            {
                logrtr(1);                               // login is required
                remove(filename);                        // deleting the file from the disk
                rewind(fp);                              // resetting file pointer position
                entryfp = fopen(ENTRIES, "w+");          // creating a ne "entryfiles.txt" file
                while (fscanf(fp, "%s", compare) != EOF) // compare is used to store a filename read one by one from file
                {
                    if (strcmp(compare, filename) == 0)    // if the filename the user entered matches one of the filenames in temp.txt
                        strcpy(compare, " ");              // the filename is erased
                    if (strcmp(compare, " ") != 0)         // if filename stored in compared was not erased
                        fprintf(entryfp, "%s\n", compare); // write the filename in the new "entryfiles.txt"
                }
                clearscreen();
                banner("DELETE ENTRY");
                printf("\n\n\t\t\tEntry stored in file '%s' successfully deleted...", filename);
                getchar();
            }
        }
    }
    remove("temp.txt"); // deleting temp.txt
    fclose(entryfp);
    fclose(fp);
}

void edit_password() // allows user to edit their stored password
{
    FILE *fp;
    int choice;
    char name[MAX_USERINFO_LENGTH], pass[MAX_USERINFO_LENGTH], compare[MAX_USERINFO_LENGTH];
    clearscreen();
    banner("EDIT PASSWORD");
    getchar();
    printf("\n\t\t\tEnter current password: ");
    fgets(pass, MAX_USERINFO_LENGTH, stdin); // getting input for current password
    fp = fopen(USER, "rt");                  // reading file storing password and username
    fgets(name, MAX_USERINFO_LENGTH, fp);    // reading username from file and storing it it name
    fgets(compare, MAX_USERINFO_LENGTH, fp); // reading password from file and storing it it pass
    fclose(fp);
    if (strcmp(compare, pass) == 0) // if entered password matches stored password
    {
        printf("\t\t\tEnter new password: ");
        fgets(pass, MAX_USERINFO_LENGTH, stdin); // getting input  for new password
        printf("\n\t\t\tAre you sure you want to replace your password? 1-YES / 2-NO: ");
        scanf("%d", &choice);              // getting choice
        while (choice != 1 && choice != 2) // while choice is not valid, get input for choice
        {
            printf("\t\t\t\tInvalid input. Try again. 1-YES / 2-NO: ");
            scanf("%d", &choice);
        }
        if (choice == 1)
        {
            fp = fopen(USER, "w+");  // create a new "user.txt" that would overwrite the existing one
            fprintf(fp, "%s", name); // print the username of new file
            fprintf(fp, "%s", pass); // print the password in new file
            fclose(fp);
            printf("\n\t\t\tPassword successfully updated. Since password has been\n");
            printf("\t\t\tchanged, we would require you to login again...");
            getchar();
            getchar();
            logrtr(0);
        }
        else
            menu(0);
    }
    else
    {
        printf("\n\t\t\tPassword does not match. Try again later...");
        getchar();
        menu(0);
    }
}

void reset_diary()
{
    int choice, errcount = 0;
    clearscreen();
    banner("RESET DIARY");
    // displaying warning
    printf("\n\t\t\tWARNING: Resetting the diary would erase all user information\n");
    printf("\t\t\tand all entries being stored by the program. All of these would be \n");
    printf("\t\t\tpermanently gone. Once the program is ran again, system setup would commence.\n\n");
    do
    {
        if (errcount != 0)
            printf("\t\t\tInvalid input. Try again\n");
        printf("\t\t\tWould you like to continue? 1-YES / 2-NO: ");
        scanf("%d", &choice);
        errcount++;
    } while (choice != 1 && choice != 2); // while choice is not valid, get choice
    if (choice == 1)
    {
        logrtr(1);
        FILE *fp;
        char filename[MAX_DATE_SIZE];
        fp = fopen(ENTRIES, "r+");                // reading "entryfiles.txt"
        while (fscanf(fp, "%s", filename) != EOF) // reading the filenames listed on the file one by one
        {
            remove(filename); // deleting the files one by one
        }
        fclose(fp);
        remove(ENTRIES); // deleting "entryfiles.txt"
        remove(USER);    // deleting "user.txt"
        remove(CIPHER);  // deleting "symbols.txt"
        clearscreen();
        banner("RESET DIARY");
        printf("\t\t\tReset done. Thank you for using ENCODE-IARY. Hope you had fun.\n");
        printf("\t\t\tIf you wish to create a new account. Just rerun the program...\n");
        exit(1);
    }
    else
    {
        printf("\n\t\t\tWhew. That was close. Thanks for staying. Press enter to go back to menu...");
        getchar();
        getchar();
    }
}

void exit_message()
{
    clearscreen();
    printf("\n\n");
    int length = (114 - strlen("Thank you for using")) / 2, j;
    for (j = 0; j < length; j++)
        printf(" "); // print space
    printf("Thank you for using");
    printf("\n\n\n");
    printf("\t-------  ---    ---   -------   -------  -------   -------        ----      ----      ----------  ---     ---\n");
    printf("\t|  ---|  |  \\   |  | |  ----|  |  ---  | |  --  \\  |  ---|        |  |     /    \\     |  ---   |   \\  \\  /  /\n");
    printf("\t| |---   |   \\  |  | |  |      |  | |  | |  | |  | | |---   ---   |  |    /  /\\  \\    |  |  |  |    \\  \\/  /\n");
    printf("\t|  ---|  |  \\ \\ |  | |  |      |  | |  | |  | |  | |  ---| |   |  |  |   /  /--\\  \\   |   --   /     \\    /\n");
    printf("\t| |---   |  |\\ \\|  | |  |      |  | |  | |  | |  | | |---   ---   |  |  /  /----\\  \\  |  | \\  \\       |  |\n");
    printf("\t|     |  |  | \\    | |  ----|  |  ---  | |  --  /  |     |        |  | /  /      \\  \\ |  |  \\  \\      |  |\n");
    printf("\t-------  ---   ----   -------   -------  -------   -------        ---- ---        --- ----   ----     ----\n");
    printf("\n");
    length = (114 - strlen("A Personal Enciphered Journal Application")) / 2;
    for (j = 0; j < length; j++)
        printf(" "); // print space
    printf("A Personal Enciphered Journal Application\n\n\n\n\n\n");
    printf("\tSee you again soon. Goodbye...\n\n");
    exit(1);
}