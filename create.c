#include "header.h"

/* To Create the Database for the given File List
 * Input: File List and Hash Table
 * Output: Filled Hash Table
 * Return Value: SUCCESS
 */

int create_DB (file_node_t* file_head, main_node_t** head)
{
	printline();
	printf("\n");
	while (file_head != NULL)
	{
		read_datafile (head, file_head->f_name);

		printf ("✅ Database creation for the  %s Successful.\n", file_head->f_name);
		file_head = file_head->link;
	}
	printline();
	printf("\n");

	return SUCCESS;
}

/* To Insert all the Words in a given File into the Hash Table
 * Input: Hash Table and File Name
 * Output: Filled Hash Table
 * Return Value: NIL
 */

int read_datafile (main_node_t** head, char* f_name)
{
	FILE* fptr = fopen (f_name, "r");
	if (fptr == NULL)
		return 0;

	fseek (fptr, 0L, SEEK_SET);

	char buffer [BUFF_SIZE];
	int val;
	int key;
	int ret;
	
	do
	{
		memset (buffer, '\0', BUFF_SIZE);
		val = fscanf (fptr, "%s", buffer);
		if (val != 0)
		{
			if ((strlen (buffer)) != 0)
			{
				key = get_key (buffer [0]);
				
				ret = check_word (buffer, head [key]);
				if (ret == FAILURE)
				{
					ret = insert_at_last_main (&head [key], buffer, f_name);
					if (ret == FAILURE)
					{
						printf ("❌ Unable to add the Word \"%s\" in the Database.\n", buffer);
						return 0;
					}
				}
				else
				{
					ret = check_file (f_name, buffer, head [key]);
					if (ret == FAILURE)
					{
						ret = update_link_table (&head [key], buffer, f_name);
						if (ret == FAILURE)
						{
							printf ("❌ Unable to add the File \"%s\" details for the Word \"%s\" in the Database.\n", f_name, buffer);
							return 0;
						}
						
					}
					else
					{
						ret = update_word_count (&head [key], buffer, f_name);
						if (ret == FAILURE)
						{
							printf ("❌ Unable to Update the Word Count for the Word \"%s\" in the File \"%s\".\n", buffer, f_name);
							return 0;
						}
					}
				}
			}
		}
	} while (val != EOF);

	fclose (fptr);
	return SUCCESS;
}

/* To Insert the File Details in the Sub-List of the particular Word details in the Hash Table
 * Input: Hash Table, Given Word and Given File Name
 * Output: File Details added in the Sub-List
 * Return Value: SUCCESS or FAILURE
 */

int update_link_table (main_node_t** head, char* word, char* f_name)
{
	main_node_t* temp1 = *head;
	while (temp1 != NULL)
	{
		if (strncmp (temp1->word, word, BUFF_SIZE) == 0)
		{
			sub_node_t* temp2 = temp1->sub_link;
			while (temp2->link != NULL)
			{
				temp2 = temp2->link;
			}
			
			temp2->link = create_sub_node (f_name);
			if (temp2->link == NULL)
				return FAILURE;
			else
				temp1->f_count += 1;
		}

		temp1 = temp1->link;
	}
	
	return SUCCESS;
}

/* To Update the Word Count in the File details in the Sub-List
 * Input: Hash Table, Given Word and Given File Name
 * Output: Word Count updated in the File Sub-List
 * Return Value: SUCCESS or FAILURE
 */

int update_word_count (main_node_t **head, char* word, char* f_name)
{
	main_node_t* temp1 = *head;
	while (temp1 != NULL)
	{
		if (strncmp (temp1->word, word, BUFF_SIZE) == 0)
		{
			sub_node_t* temp2 = temp1->sub_link;
			while (temp2 != NULL)
			{
				if (strncmp (temp2->f_name, f_name, NAMELENGTH) == 0)
				{
					temp2->w_count += 1;
					return SUCCESS;
				}

				temp2 = temp2->link;
			}
		}

		temp1 = temp1->link;
	}
	
	return FAILURE;
}
