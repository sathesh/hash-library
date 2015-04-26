#include <string.h>
#include "hash.h"

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
  key_cmp_fn_ptr key_cmp_fn;
  hash_bkt_t   **hash_bkt;
  unsigned int total_elements;
}hash_root_t;

/* Function declaration */
static int INSERT_NODE(hash_bkt_t *bkt, void *key, void *data);
static list_node_t* GET_NODE(hash_bkt_t *bkt, void *key, key_cmp_fn_ptr key_cmp_fn);
static void hash_bkt_deinit(hash_bkt_t *bkt);


/* Fn Definitions */
int hashpjw_string(unsigned int bkt_size, const void *key)
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


hash_handle_t hash_init(unsigned int bkt_size, 
                       hash_fn_ptr hash_fn,
                       key_cmp_fn_ptr key_cmp_fn)
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

  root->key_cmp_fn = key_cmp_fn;

  root->total_elements = 0;

  return (hash_handle_t)root;
}

int hash_deinit(hash_handle_t handle)
{
  hash_root_t *root = (hash_root_t*)handle;
  int i;

  for (i=0; i<root->bkt_size; i++)
  {
    if (root->hash_bkt[i])
    {
      hash_bkt_deinit(root->hash_bkt[i]);
      HASH_FREE(root->hash_bkt[i]);
    }
  }
  HASH_FREE(root->hash_bkt);
  HASH_FREE(root);
}

void hash_distribution(hash_handle_t handle, int **result_pp, int *bkt_size)
{
  hash_root_t *root = (hash_root_t*)handle;
  int i;
  int *result = HASH_MALLOC(sizeof(unsigned int) * root->bkt_size);

  memset(result, 0, sizeof(unsigned int) * root->bkt_size);

  for (i=0; i<root->bkt_size; i++)
  {
    if (root->hash_bkt[i])
    {
      result[i] = root->hash_bkt[i]->length;
    }
  }
  *bkt_size = root->bkt_size;
  *result_pp = result;

}

int hash_insert(hash_handle_t handle, void *key, void* data)
{
  hash_root_t *root = (hash_root_t*)handle;
  unsigned int hash_index = root->hash_fn(root->bkt_size, key);
  int result;

  if (!root->hash_bkt[hash_index])
  {
     root->hash_bkt[hash_index] = HASH_MALLOC(sizeof(hash_bkt_t));
     if (!root->hash_bkt[hash_index])
       return FALSE;
     root->hash_bkt[hash_index]->length = 0;
     root->hash_bkt[hash_index]->head = NULL;
  }
  result = INSERT_NODE(root->hash_bkt[hash_index], key, data);
  if (result == TRUE)
    root->total_elements++;

  return result;
}

void* hash_lookup(hash_handle_t handle, void *key)
{
  hash_root_t *root = (hash_root_t*)handle;
  unsigned int hash_index = root->hash_fn(root->bkt_size, key);
  list_node_t *node;

  if (root->hash_bkt[hash_index] == NULL)
    return NULL;

  node = GET_NODE(root->hash_bkt[hash_index], key, root->key_cmp_fn);
  if (node)
    return node->data;

  return NULL;
}

void* hash_delete(hash_handle_t handle, void *key)
{
  hash_root_t *root = (hash_root_t*)handle;
  unsigned int hash_index = root->hash_fn(root->bkt_size, key);
  list_node_t *node_to_be_del = NULL;
  hash_bkt_t *bkt = root->hash_bkt[hash_index];

  if (bkt == NULL || bkt->head == NULL)
    return NULL;

  if (root->key_cmp_fn(key, bkt->head->key) ==0)
  {
    node_to_be_del = bkt->head;
    bkt->head = bkt->head->next;
  }
  else
  {
    list_node_t *node = bkt->head;

    while (node->next)
    {
      if (root->key_cmp_fn(key, node->next->key) ==0)
      {
        list_node_t *tmp = node->next;
        node->next = tmp->next;
        node_to_be_del = tmp; /* node to be removed */
        break;
      }
      node = node->next;
    }

  }
  if (node_to_be_del)
  {
    void *data = node_to_be_del->data;
    HASH_FREE(node_to_be_del);
    bkt->length--;
    return data;
  }
  return NULL;
}


static int INSERT_NODE(hash_bkt_t *bkt, void *key, void *data)
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
  return TRUE;
}

static list_node_t* GET_NODE(hash_bkt_t *bkt, void *key, key_cmp_fn_ptr key_cmp_fn)
{
  list_node_t *tmp;

  ASSERT(bkt);

  tmp = bkt->head;

  while (tmp)
  {
    if (key_cmp_fn(key, tmp->key) == 0)
      return tmp;
    tmp = tmp->next;
  }
  return NULL;
}

static void hash_bkt_deinit(hash_bkt_t *bkt)
{
  list_node_t *tmp;
  list_node_t *tmp2;

  ASSERT(bkt);

  tmp = bkt->head;

  while (tmp)
  {
    tmp2 = tmp->next;
    HASH_FREE(tmp);
    tmp = tmp2;
  }
}
