#include "header.h"

/* To Update the Database with a new File
 * Input: File List, Hash Table and new File Name
 * Output: Updated File List and Hash Table
 * Return Value: SUCCESS/FAILURE
 */

int update_DB(file_node_t** files_h, main_node_t** head, char* f_name)
{
    int ret;
    printline();
    printf("\n");

    if ((IsFileValid(f_name)) == SUCCESS)
    {
        if ((IsFileDuplicate(f_name, files_h)) == FAILURE)
        {
            ret = store_filenames_to_list(f_name, files_h);
            if (ret == SUCCESS)
            {
                printf("✅ The File %s is added to the List successfully.\n", f_name);
                
                read_datafile(head, f_name);

                printf("✅ Database creation for the File %s Successful.\n", f_name);

                return SUCCESS;
            }
        }
    }

    return FAILURE;
}
