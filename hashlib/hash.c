#include "hash.h"

/* Function declaration */
int INSERT_NODE(hash_bkt_t *bkt, void *key, void *data);


/* Fn Definitions */
int hashpjw(unsigned int bkt_size, const void *key)
{
  const char *ptr;
  int val;
  /*****************************************************************************
    * *
    * Hash the key by performing a number of bit operations on it. *
    * *
    *****************************************************************************/
  val = 0;
  ptr = key;
  while (*ptr != '\0') {
    int tmp;
    val = (val << 4) + (*ptr);
    if (tmp = (val & 0xf0000000)) {
      val = val ^ (tmp >> 24);
      val = val ^ tmp;
    }
    ptr++;
  }

  return val % bkt_size;
}

int hash_function_int(unsigned int bkt_size, void *key_p)
{
  return (*(unsigned int *)key_p%bkt_size);
}


hash_root_t* hash_init(unsigned int bkt_size, int (*hash_fn)(unsigned int bkt_size,void *))
{
  hash_root_t *root = HASH_MALLOC(sizeof(hash_root_t));

  if (!root)
    return NULL;

  if (bkt_size == -1)
    bkt_size = PRIME_BKT_SIZE;

  root->hash_bkt = HASH_MALLOC(sizeof(hash_bkt_t*) * bkt_size);
  if (!root->hash_bkt)
  {
    HASH_FREE(root);
    return NULL;
  }

  root->bkt_size = bkt_size;
  if (hash_fn)
    root->hash_fn = hash_fn;
  else
    root->hash_fn = hash_function_int;

  root->total_elements = 0;

  return root;
}

int hash_insert(hash_root_t* root, void *key, void* data)
{
  unsigned int hash_index = root->hash_fn(root->bkt_size, key);

  if (!root->hash_bkt[hash_index])
  {
     root->hash_bkt[hash_index] = HASH_MALLOC(sizeof(hash_bkt_t*));
     if (!root->hash_bkt[hash_index])
       return FALSE;
     root->hash_bkt[hash_index]->length = 0;
     root->hash_bkt[hash_index]->head = NULL;
  }
  return INSERT_NODE(root->hash_bkt[hash_index], key, data);
}

int INSERT_NODE(hash_bkt_t *bkt, void *key, void *data)
{
  list_node_t *tmp;

  ASSERT ((bkt->length == 0 && bkt->head == NULL) || (bkt->length != 0 && bkt->head != NULL));

  tmp = HASH_MALLOC(sizeof(list_node_t));
  if (!tmp)
    return FALSE;

  tmp->next = NULL;
  tmp->key = key;
  tmp->data = data;

  if (!bkt->head)
  {
    tmp->next = NULL;
  }
  else
  {
    tmp->next = bkt->head;
  }
  bkt->head = tmp;
  bkt->length++;
}
