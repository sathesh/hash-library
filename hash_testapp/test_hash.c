#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

typedef struct data_box
{
  unsigned int data;
}data_box_t;

data_box_t* create_data_box();
void main()
{
  unsigned int user_input;

  hash_root_t *hash_root = hash_init(-1,    /* Bkt size */
                           NULL); /* Hash function */

              
  do
  {
    user_input = 777;
    printf("\n\n\n0. quit\n1. Insert \n2. Delete \n3. Search\n" \
                  "4. Lookup \n5. Print Distribution\n");
    printf("\tEnter ur option: ");
    scanf("%u", &user_input);
    getchar();

    if (user_input == 0)
      break;

    switch(user_input)
    {
      case 1:
        {
          data_box_t *data_box = create_data_box();
          hash_insert(hash_root, &data_box->data, data_box);
          
        }
        break;
#if 0
      case 2:
        {
          data_box_t *data_box = create_data_box();
          LIST_INSERT_AT_TAIL(&data_list, &data_box->list_entry);
        }
        break;
       case 3:
        {
          data_box_t *tmp = LIST_GET_MEMBER_HEAD(&data_list, data_box_t, list_entry);
          if (tmp)
            printf("\nHead member data: %c\n\n", tmp->data);
          else
            printf("\nlist empty\n\n");

        }
        break;
        case 4:
        {
          data_box_t *tmp = LIST_GET_MEMBER_TAIL(&data_list, data_box_t, list_entry);
          if (tmp)
            printf("\ntail member data: %c\n\n", tmp->data);
          else
            printf("\nlist empty\n\n");
        }
        break;
        case 5:
        {
          data_box_t *tmp = LIST_GET_MEMBER_HEAD(&data_list, data_box_t, list_entry);
          
          while(tmp)
          {
            printf("\n %c ", tmp->data);
            tmp = LIST_GET_MEMBER_NEXT(&data_list, &tmp->list_entry, data_box_t, list_entry);
          }
        }
        break;
        case 6:
         {
          data_box_t *tmp = LIST_GET_MEMBER_TAIL(&data_list, data_box_t, list_entry);
          
          while(tmp)
          {
            printf("\n %c ", tmp->data);
            tmp = LIST_GET_MEMBER_PREVIOUS(&data_list, &tmp->list_entry, data_box_t, list_entry);
          }
        }
          break;
        case 7:
          printf("List length : %u\n", LIST_GET_LENGTH(&data_list));
          break;
        case 8:
        {
          data_box_t *tmp = LIST_GET_MEMBER_HEAD(&data_list, data_box_t, list_entry);
          
          while(tmp)
          {
            data_box_t *next;
            next = LIST_GET_MEMBER_NEXT(&data_list, &tmp->list_entry, data_box_t, list_entry);
            LIST_REMOVE_MEMBER(&data_list, tmp, list_entry);
            free(tmp);
            tmp = next;
          }
          printf("List is empty now!!\n\n");
        }
        case 9:
        {
          data_box_t *tmp = NULL;
          char key1;

          printf("Enter Key to lookup: ");
          key1 = getchar();
          LIST_LOOKUP_MEMBER(&data_list, &key1, data, data_box_t, list_entry, cmp_char, tmp);

          /*
          {
            list_node_t* node = ((&data_list)->listhead.next);
            while (node)
            {
              if (0 == cmp_char(&key1, &(((data_box_t*) ((unsigned long)node - (unsigned long) & (((data_box_t*)0)->list_entry))) ->data)))
              {
                (tmp) = (((data_box_t*) ((unsigned long)node - (unsigned long) & (((data_box_t*)0)->list_entry))));
                break;
              }
              node = LIST_GET_NEXT(&data_list, node);
            }
            (tmp) = ((void *)0);
          };
          */


          if (tmp)
          {
            printf("Look up success!!\n");
          }
          else
          {
            printf("Look up Fail!!\n");
          }
        }
        break;
       default:
          break;
#endif
    }


  }while(1);
}


data_box_t* create_data_box()
{
  data_box_t *data_box = malloc (sizeof(data_box_t));
  data_box->data = random();
  printf("\nKey = %u\n", data_box->data);
  return data_box;
}

int cmp_char(char* a, char* b)
{
  if (*a == *b)
    return 0;
  else
    return 1;
}


