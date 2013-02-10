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
typedef int (*key_cmp_fn_ptr)(void*, void*);
typedef void* hash_handle_t;


hash_handle_t hash_init(unsigned int bkt_size, 
                       hash_fn_ptr hash_fn,
                       key_cmp_fn_ptr key_cmp_fn);
int hash_function_int(unsigned int bkt_size, void *key_p);
int hash_insert(hash_handle_t root, void *key, void* data);
void* hash_lookup(hash_handle_t root, void *key);
void* hash_delete(hash_handle_t handle, void *key);
void hash_distribution(hash_handle_t handle, int **result_pp, int *bkt_size);
