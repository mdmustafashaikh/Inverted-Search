#include "header.h"

/******************************************************************************
 *                                                                            *
 *                               INVERTED SEARCH                              *
 *                                                                            *
 *  Project Title  : Inverted Search                                          *
 *  Description    : Implementation of an Inverted Index-based Search         *
 *                   for efficient word searching across multiple files.      *
 *                                                                            *
 *  Name           : Md Mustafa                                               *
 *  Batch ID       : [25008_052]                                              *
 *  Language Used  : C Language                                               *
 *  Date           : [06/09/2025]                                             *
 *                                                                            *
 ******************************************************************************/

/* Main Function to start the Program
 * Input: Command Line Arguments
 * Output: Handled Commands
 * Return Value: SUCCESS/FAILURE
 */ 

int main (int argc, char* argv [])
{
    if (argc < 2){
        printf ("❌ Invalid number of Arguments.\n");
        printf ("📢 Usage ./a.out <file.txt> <file1.txt> ...\n");
    }else{
        command_handler (argv);
    }
    return 0;
}

/* To Handle all the Commands from the User
 * Input: Command Line Arguments
 * Output: Handled Commands
 * Return Value: SUCCESS
 */

int command_handler (char* argv [])
{
    file_node_t* files_H = NULL;
    main_node_t* HT [SIZE] = {NULL};
    int ret, option, flag = 0;
    char choice;

    validate_n_store_filenames (&files_H, argv);

    do
    {
        printline();
        printf("\n");
        printf("\t\tWelcome to Inverted Search Project 🚀\n");
        printline();
        printf("\n");
        printf ("1. Create Database\n2. Display Database\n3. Search Database\n4. Update Database\n5. Save Database\n");
        printf("👉 Please enter your choice (1-5): ");

        if (scanf ("%d", &option) != 1)   
        {
            while (getchar() != '\n'); 
            printf("\n❌ Invalid Choice. Please enter a number between 1 to 5.\n");
        }
        else
        {
            switch (option)
            {
                case 1:        
                        if (flag == 0)
                        {
                            ret = create_DB (files_H, HT);
                            if (ret == SUCCESS)
                            {
                                printf ("✅ Database Creation Successful.\n");
                                printline();
                            }
                            flag = 1;
                        }
                        else
                        {
                            printf ("❌ Create Database can only be called once at program start.\n");
                        }
                    break;
                case 2:        
                    {
                        ret = display_DB (HT);
                        if (ret == FAILURE)
                        {
                            printf ("📢 The Database is Empty.\n");
                        }else{
                            printline();
                            printf("\n✅ Database Displayed Successfully!\n");
                            printline();
                        }
                    }
                    break;
                case 3:        
                    {
                        char word [BUFF_SIZE];
                        printf ("🔍 Enter the word to be searched: ");
                        scanf ("%s", word);

                        ret = search_word(HT,word);
                        if (ret == SUCCESS)
                        {
                            printline();
                            printf("\n");
                            printf ("✅ Word Search Successful.\n");
                            printline();
                            printf("\n");
                        }
                        else
                        {
                            printf ("❌ Word not found in Database.\n");
                        }
                    }
                    break;
                case 4:        
                    {
                        if (flag == 1)
                        {
                            char f_name [NAMELENGTH];
                            printf ("✏️  Enter the File Name to update Database: ");
                            scanf ("%s", f_name);
                            
                            ret = update_DB (&files_H, HT, f_name);
                            if (ret == SUCCESS)
                            {
                                printline();
                                printf("\n");
                                printf ("✅ Database Update Successful.\n");
                                printline();
                                printf("\n");
                            }
                            else
                            {
                                printf ("❌ Update Failed. File not found.\n");
                            }
                        }
                        else
                        {
                            printf ("⚠️  Please Create Database before updating.\n");
                        }
                    }
                    break;
                case 5:
                    {
                        char f_name [NAMELENGTH];
                        printf ("💾 Enter the File Name to save Database: ");
                        scanf ("%s", f_name);
                        
                        ret = save_DB (HT, f_name);
                        if (ret == SUCCESS)
                        {
                            printline();
                            printf("\n");
                            printf ("✅ Database Saved Successfully.\n");
                            printline();
                            printf("\n");
                        }
                        else
                        {
                            printf ("❌ Failed to Save Database.\n");
                        }
                    }
                    break;
                default: 
                    printf ("❌ Invalid Choice. Please enter a number between 1 to 5.\n");
            }
        }

        printf ("\nDo you want to Continue? [y / n]: ");
        scanf (" %c", &choice);

    } while ((choice == 'y'));

    printf("Thank you for using the Inverted Search Project. Goodbye! 👋\n");
    return SUCCESS;
}

/* To Validate and Store the given File Names into the File List
 * Input: File List and Command Line Arguments
 * Output: Filled File List
 * Return Value: NIL
 */

int insert_at_last_file (file_node_t** head, char* f_name)
{
    file_node_t* new = (file_node_t*) malloc (sizeof (file_node_t));
    if (new == NULL)
        return FAILURE;

    strncpy (new->f_name, f_name, (strlen (f_name) + 1));
    new->link = NULL;

    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    file_node_t* temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new;

    return SUCCESS;
}

/* To Insert the given Word at the end of the Main List
 * Input: Given Word, Given File Name and Main List
 * Output: Filled Main List
 * Return Value: SUCCESS/FAILURE
 */

int insert_at_last_main (main_node_t** head, char* word, char* f_name)
{
    main_node_t* new = (main_node_t*) malloc (sizeof (main_node_t));
    if (new == NULL)
        return FAILURE;

    strncpy (new->word, word, (strlen (word) + 1));
    new->link = NULL;
    new->sub_link = create_sub_node (f_name);
    new->f_count = 1;

    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    main_node_t* temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new;

    return SUCCESS;
}

/* To Create a new Sub-Node with given File Name
 * Input: Given File Name
 * Output: New Sub-Node created
 * Return Value: Pointer to the new Sub-Node
 */

sub_node_t* create_sub_node (char* f_name)
{
    sub_node_t* new = (sub_node_t*) malloc (sizeof (sub_node_t));
    strncpy (new->f_name, f_name, (strlen (f_name) + 1));
    new->w_count = 1;
    new->link = NULL;
    return new;
}

/* To Print a line of '=' characters for better readability
 * Input: NIL
 * Output: Printed line
 * Return Value: NIL
 */

void printline(){
    for(int i=0; i<80; i++){
        printf("=");
    }
}
