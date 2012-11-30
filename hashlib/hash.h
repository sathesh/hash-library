#include <stdlib.h>
#include <assert.h>

#ifndef PRIME_BKT_SIZE
#define PRIME_BKT_SIZE 157  /* A fair prime number between 2^7 and 2^8 */
#endif

#define TRUE        1
#define FALSE       0
#define HASH_MALLOC malloc
#define HASH_FREE   free
#define ASSERT      assert

#define hash_function_char  hashpjw

typedef int (*hash_fn_ptr)(unsigned int bkt_size, void*);

typedef struct list_node
{
    struct list_node *next;
    void *key;
    void *data;
}list_node_t;

typedef struct hash_bkt_struct
{
  unsigned int length;
  list_node_t *head;
}hash_bkt_t;


typedef struct hash_root
{
  unsigned int bkt_size;
  hash_fn_ptr  hash_fn;
  hash_bkt_t   **hash_bkt;
  unsigned int total_elements;
}hash_root_t;

hash_root_t* hash_init(unsigned int bkt_size, int (*hash_fn)(unsigned int bkt_size,void *));
int hash_function_int(unsigned int bkt_size, void *key_p);
int hash_insert(hash_root_t* root, void *key, void* data);


