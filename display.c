#include "header.h"

/* To Display the entire Database
 * Input: Hash Table
 * Output: Displayed Database
 * Return Value: SUCCESS/FAILURE
 */

int display_DB(main_node_t** head)
{
       printline();
       printf("\n");
    int i = 0, flag = 0;

    while (i < SIZE)
    {
        if (head[i] != NULL)
        {
            display_words(head[i], i);
            flag = 1;
        }
        i += 1;
    }

    if (flag == 0)
        return FAILURE;
    else
        return SUCCESS;
}

/* To Display the Words in a particular index of the Hash Table
 * Input: Main List at that index and index value
 * Output: Displayed Words with their File details
 * Return Value: NIL
 */

void display_words(main_node_t* temp1, int index)
{
 
    while (temp1 != NULL)
    {
        printf("[%-2d]  %-12s | Files: %-2d | ", index, temp1->word, temp1->f_count);
        display_files(temp1->sub_link);
        printf("-> NULL\n");

        temp1 = temp1->link;
    }
}

/* To Display the File details in the Sub-List of a particular Word
 * Input: Sub-List Head
 * Output: Displayed File details
 * Return Value: NIL
 */

void display_files(sub_node_t* temp2)
{
    while (temp2 != NULL)
    {
        printf("{%-10s : %-2d} ", temp2->f_name, temp2->w_count);
        temp2 = temp2->link;

        if (temp2 != NULL)
            printf("-> ");
    }
}
