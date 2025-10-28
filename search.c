#include "header.h"

/* To Search for a given Word in the Hash Table
 * Input: Hash Table and Word to be searched
 * Output: Search Result
 * Return Value: SUCCESS/FAILURE
 */

int search_word (main_node_t** head, char* word){
    int key = get_key (word [0]);
    main_node_t* temp1 = head [key];
    printline();
    printf("\n");
    while (temp1 != NULL)
    {
        if (strncmp (temp1->word, word, BUFF_SIZE) == 0)
        {

            printf ("The Word '%s' is found in the following files:\n", word);
            sub_node_t* temp2 = temp1->sub_link;
            while (temp2 != NULL)
            {
                printf ("File Name: %s | Word Count: %d\n", temp2->f_name, temp2->w_count);
                temp2 = temp2->link;
            }
            return SUCCESS;
        }
        temp1 = temp1->link;
    }
    
    printf ("❌ The Word '%s' is not found in the Database.\n", word);
    printline();
    printf("\n");
    return FAILURE;
}