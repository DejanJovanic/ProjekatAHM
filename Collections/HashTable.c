#include "HashTable.h"


/* This function calculates (ab)%c */
int modulo(int a, int b, int c) {
	long long x = 1, y = a; // long long is taken to avoid overflow of intermediate results
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x * y) % c;
		}
		y = (y * y) % c; // squaring the base
		b /= 2;
	}
	return x % c;
}

/* this function calculates (a*b)%c taking into account that a*b might overflow */
long long mulmod(long long a, long long b, long long c) {
	long long x = 0, y = a % c;
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x + y) % c;
		}
		y = (y * 2) % c;
		b /= 2;
	}
	return x % c;
}

/* Miller-Rabin primality test, iteration signifies the accuracy of the test */
BOOL Miller(long long p, int iteration) {
	if (p < 2) {
		return FALSE;
	}
	if (p != 2 && p % 2 == 0) {
		return FALSE;
	}
	long long s = p - 1;
	while (s % 2 == 0) {
		s /= 2;
	}
	for (int i = 0; i < iteration; i++) {
		long long a = rand() % (p - 1) + 1, temp = s;
		long long mod = modulo(a, temp, p);
		while (temp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mulmod(mod, mod, p);
			temp *= 2;
		}
		if (mod != p - 1 && temp % 2 == 0) {
			return FALSE;
		}
	}
	return TRUE;
}

inline uint32_t _HashTable_get_hash(void* key) {
	uintptr_t a = (uintptr_t)key;
	a -= (a << 6);
	a ^= (a >> 17);
	a -= (a << 9);
	a ^= (a << 4);
	a -= (a << 3);
	a ^= (a << 10);
	a ^= (a >> 15);
	return a >> ((sizeof(uintptr_t) - sizeof(uint32_t)) * 8);
}
void* SieveOfEratosthenes(int n)
{
	// Create a boolean array "prime[0..n]" and initialize 
	// all entries it as true. A value in prime[i] will 
	// finally be false if i is Not a prime, else true. 
	BOOL* primes = (BOOL*)malloc(sizeof(BOOL) * (n + 1));
	memset(primes, TRUE, sizeof(BOOL) * (n + 1));

	for (int p = 2; p * p <= n; p++)
	{
		// If prime[p] is not changed, then it is a prime 
		if (primes[p] == TRUE)
		{
			// Update all multiples of p greater than or  
			// equal to the square of it 
			// numbers which are multiple of p and are 
			// less than p^2 are already been marked.  
			for (int i = p * p; i <= n; i += p)
				primes[i] = FALSE;
		}
	}
	return primes;
}
BOOL HashTable_initialize_table(HashTable* table, unsigned int buckets, BOOL(*key_comparer)(void*, void*), void* (*bucket_list_allocating_function)(int), void(*bucket_list_free_function)(HashNode**), void* (*node_allocate_function)(), void(*node_free_function)(HashNode*)) {
	BOOL ret = TRUE;
	table->entries = 0;
	table->key_comparer_function = key_comparer;
	table->bucket_list_allocating_function = bucket_list_allocating_function;
	table->bucket_list_free_function = bucket_list_free_function;
	table->node_allocate_function = node_allocate_function;
	table->node_free_function = node_free_function;
	if(buckets > 0 && key_comparer != NULL)
		table->_table = table->bucket_list_allocating_function(buckets);
	if (table->_table != NULL) {
		table->size = buckets;
		for (int i = 0; i < buckets; i++)
			table->_table[i] = NULL;
		table->primes = SieveOfEratosthenes(1000000);
	}
	else
		ret = FALSE;

	return ret;
}

HashNode* HashTable_get(HashTable* table, void* key) {
	uint32_t hash = _HashTable_get_hash(key);
	uint32_t index = hash % table->size;
	HashNode* node;
	uintptr_t pointer_value = (uintptr_t)key;
	for (node = table->_table[index]; node != NULL; node = node->next) {
		if (table->key_comparer_function(key,node->key))
			break;
	}

	return node;
}

void HashTable_rebuild_table(HashTable* table) {
	HashNode** old_table, * next, * current;
	unsigned int old_size, index, i;

	old_table = table->_table;
	old_size = table->size;
	int new_size = old_size << 1;
	if (new_size % 2 == 0)
		new_size++;
	for (; new_size < 4 * old_size; new_size += 2)
		if (Miller(new_size, 20))
			break;
	//if (new_size <= 1000000){
	//	while (TRUE) {
	//		if (table->primes[new_size])
	//			break;
	//			new_size++;
	//	}
	//}

	table->size = new_size;
	table->_table = table->bucket_list_allocating_function(table->size);
	for (int i = 0; i < table->size; i++) {
		table->_table[i] = NULL;
	}
	
	for (i = 0; i < old_size; i++) {
		next = old_table[i];
		while (next) {
			current = next;
			next = next->next;
			index = _HashTable_get_hash(current->key) % table->size;
			current->next = table->_table[index];
			table->_table[index] = current;
		}
	}
	table->bucket_list_free_function(old_table);
}

BOOL HashTable_insert(HashTable* table, void* key, void* value) {
	if (HashTable_get(table, key) == NULL) {
		while (table->entries >= table->size * 0.75)
			HashTable_rebuild_table(table);
		uint32_t index = _HashTable_get_hash(key) % table->size;
		HashNode* node = (HashNode*)table->node_allocate_function();
		node->key = key;
		node->value = value;
		node->next = table->_table[index];
		table->_table[index] = node;
		table->entries++;
		return TRUE;
	}
	else
		return FALSE;
}


BOOL HashTable_delete(HashTable* table, void* key,void** out_value) {
	HashNode* node;
	HashNode* last;

	node = HashTable_get(table, key);
	uint32_t index = _HashTable_get_hash(key) % table->size;
	if (node != NULL) {
		if (node == table->_table[index]) {
			table->_table[index] = node->next;
		}
		else {
			for (last = table->_table[index]; last != NULL && last->next != NULL; last = last->next) {
				if (last->next == node)
					break;
			}

			last->next = node->next;
		}
		table->entries--;
		*out_value = node->value;
		table->node_free_function(node);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL HashTable_deinitialize_table(HashTable* table) {
	HashNode* current = NULL;
	HashNode* next = NULL;
	for (int i = 0; i < table->size; i++) {
		current = table->_table[i];
		while (current != NULL) {
			next = current->next;
			table->node_free_function(current);
			current = next;
		}
	}
	table->bucket_list_free_function(table->_table);
	table->size = 0;
	table->entries = 0;
	free(table->primes);
	return TRUE;
}