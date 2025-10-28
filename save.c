#include "header.h"

/* To Save the Database into a given File
 * Input: Hash Table and File Name
 * Output: Saved File
 * Return Value: SUCCESS/FAILURE
 */

int save_DB(main_node_t **head, char *fname)
{
    char name[NAMELENGTH];
    strncpy(name, fname, NAMELENGTH);

    int ret = check_name(fname);
    if (ret == FAILURE)
    {
        strncat(name,".txt",5);
    }
        
    FILE* fptr = fopen(name, "w");
    if (fptr == NULL)
    {
        printf("ERROR: Unable to open the File %s.\n", name);
        return FAILURE;
    }

    int i = 0;

    while (i < SIZE)
    {
        if (head[i] != NULL)
        {
            main_node_t* temp1 = head[i];
            fprintf(fptr, "#%d;\n", i);

            while (temp1 != NULL)
            {
                fprintf(fptr, "%s;", temp1->word);
                fprintf(fptr, "%d;", temp1->f_count);
                
                sub_node_t* temp2 = temp1->sub_link;
                
                while (temp2 != NULL)
                {
                    fprintf(fptr, "%s;", temp2->f_name);
                    fprintf(fptr, "%d;", temp2->w_count);
                    temp2 = temp2->link;
                }

                fprintf(fptr, "#\n");
                temp1 = temp1->link;
            }
        }

        i += 1;
    }

    fclose(fptr);
    return SUCCESS;
}

/* To Check whether the given File Name has an Extension or not
 * Input: Given File Name
 * Output: NIL
 * Return Value: SUCCESS/FAILURE
 */

int check_name(char* fname)
{
    char* str = strstr(fname, ".");
    if (str == NULL)
        return FAILURE;
    else
        return SUCCESS;
}
