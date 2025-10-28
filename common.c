#include "header.h"

/* To Validate and Store the Filenames from Command Line Arguments
 * Input: File List and Command Line Arguments
 * Output: Filled File List
 * Return Value: NIL
 */

void validate_n_store_filenames(file_node_t** files_h, char* filenames[])
{
    int i = 1, ret;    
    printline();
    printf("\n");
    while (filenames[i] != NULL)
    {
        ret = IsFileValid(filenames[i]);
        if (ret == SUCCESS)
        {
            ret = IsFileDuplicate(filenames[i], files_h);
            if (ret == FAILURE)
            {
                ret = store_filenames_to_list(filenames[i], files_h);
                if (ret == SUCCESS)
                {
                    printf("📢 The File %s is added to the List Successfully.\n", filenames[i]);
                }
            }
        }
        i += 1;
    }

    if (*files_h == NULL)
    {
        printf("❌ There is no Valid File passed as Input.\n"
               "📢 Please enter names of Valid Files only.\n");
        exit(0);
    }

    return;
}

/* To Check if the given File is Valid (Present and Non-Empty)
 * Input: File Name
 * Output: NIL
 * Return Value: SUCCESS/NOT_PRESENT/FILE_EMPTY
 */

int IsFileValid(char* filename)
{
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("❌ The File %s is not present.\n", filename);
        return NOT_PRESENT;
    }
    else
    {
        fseek(fptr, 0L, SEEK_END);
        int pos = ftell(fptr);

        if (pos == 0)
        {
            printf("❌ The File %s is an Empty File.\n", filename);
            return FILE_EMPTY;
        }
        else
        {
            fclose(fptr);
            return SUCCESS;
        }
    }
}

/* To Check if the given File is Duplicate in the File List
 * Input: File Name and File List
 * Output: NIL
 * Return Value: REPEATED/FAILURE
 */

int IsFileDuplicate(char* filename, file_node_t** head)
{
    file_node_t* temp = *head;

    while (temp != NULL)
    {
        if ((strncmp(filename, temp->f_name, NAMELENGTH)) == 0)
        {
            printf("❌ The File %s is repeated.\n", filename);
            return REPEATED;
        }
        
        temp = temp->link;
    }

    return FAILURE;
}

/* To Store the given File Name into the File List
 * Input: File Name and File List
 * Output: Filled File List
 * Return Value: SUCCESS/FAILURE
 */ 

int store_filenames_to_list(char* f_name, file_node_t** head)
{
    int ret = insert_at_last_file(head, f_name);
    if (ret == FAILURE)
    {
        printf("❌ Unable to add the File %s into the File List.\n", f_name);
        return FAILURE;
    }
    
    return SUCCESS;
}

int get_key(char f_char)
{
    if (isalpha(f_char))
    {
        f_char = (char) toupper(f_char);
        return (f_char % 65);
    }
    else if (isdigit(f_char))
    {
        return 26;
    }
    else
    {
        return 27;
    }
}

/* To Insert the given File Name at the end of the File List
 * Input: File Name and File List
 * Output: Filled File List
 * Return Value: SUCCESS/FAILURE
 */

int check_word(char* word, main_node_t* head)
{
    while (head != NULL)
    {
        if (strncmp(head->word, word, BUFF_SIZE) == 0)
            return REPEATED;

        head = head->link;
    }

    return FAILURE;
}

/* To Insert the given File Name at the end of the File List
 * Input: File Name and File List
 * Output: Filled File List
 * Return Value: SUCCESS/FAILURE
 */

int check_file(char* f_name, char* word, main_node_t* head)
{
    while (head != NULL)
    {
        if (strncmp(head->word, word, BUFF_SIZE) == 0)
        {
            sub_node_t* temp = head->sub_link;
            while (temp != NULL)
            {
                if (strncmp(temp->f_name, f_name, NAMELENGTH) == 0)
                    return REPEATED;
                
                temp = temp->link;
            }
        }

        head = head->link;
    }
    return FAILURE;
}
