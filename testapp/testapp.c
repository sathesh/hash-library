#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

typedef struct data_box
{
  unsigned int data;
}data_box_t;

int uint_key_cmp(void*, void*);
data_box_t* create_data_box();

void main()
{
  unsigned int user_input;
  hash_handle_t hash_handle; 

   hash_handle = hash_init(10,    /* Bkt size */
                           NULL,
                           uint_key_cmp); /* Hash function */

              
  do
  {
    user_input = 777;
    printf("\n\n\n0. quit\n1. Insert \n2. Delete \n" \
                  "3. Lookup \n4. Print Distribution\n");
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
          if (TRUE == hash_insert(hash_handle, &data_box->data, data_box))
          {
            printf("Insert done\n");
          }
          else
          {
            printf("Insert failed\n");
          }
        }
        break;

      case 2:
        {
          data_box_t *data_box;
          unsigned int key;
          printf("\nDelete key: ");
          scanf("%u", &key);
          data_box = hash_delete(hash_handle, &key);

          if (data_box)
          {
            printf ("data: %u", data_box->data);
            free (data_box);
          }
          else
          {
            printf ("key not found\n");
          }
          
        }
        break;

      case 3:
        {
          data_box_t *data_box;
          unsigned int key;
          printf("\nLook up key: ");
          scanf("%u", &key);
          data_box = hash_lookup(hash_handle, &key);

          if (data_box)
            printf ("data: %u", data_box->data);
          else
            printf ("key not found\n");
          
        }
        break;
      case 4:
        {
          int bkt_size= 0;
          int *result;
          int i,j;
          hash_distribution(hash_handle, &result, &bkt_size);

          for (i=0; i< bkt_size; i++)
          {
              printf("[%u]:", i);
              for (j=0; j<result[i]; j++)
                printf(".");
              printf("\n");
          }


        }
    }


  }while(1);

  hash_deinit(hash_handle);
}


data_box_t* create_data_box()
{
  data_box_t *data_box = malloc (sizeof(data_box_t));
  data_box->data = random();
#if 0
  printf("enter key: \n");
  scanf("%d", &data_box->data);
#endif

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


int uint_key_cmp(void *v1, void *v2)
{
  unsigned int *p1 = (unsigned int *)v1;
  unsigned int *p2 = (unsigned int *)v2;

  if (*p1 == *p2)
    return 0;
  else
    return -1;
}
