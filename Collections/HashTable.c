#include "HashTable.h"


///Funkcija racuna (a^b)%c
int _HashTable_modulo(int a, int b, int c) {
	long long x = 1, y = a; // long long jer moze doci do overflow-a int-a.
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x * y) % c;
		}
		y = (y * y) % c; // kvadriranje baze.
		b /= 2;
	}
	return x % c;
}

/* this function calculates (a*b)%c taking into account that a*b might overflow */
long long _HashTable_mulmod(long long a, long long b, long long c) {
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

/// Funkcija koja koristi miller-rabin-ovu metodu za racunanje sledeceg prostog broja.
BOOL _HashTable_miller_rabin(long long p, int iteration) {
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
		long long mod = _HashTable_modulo(a, temp, p);
		while (temp != p - 1 && mod != 1 && mod != p - 1) {
			mod = _HashTable_mulmod(mod, mod, p);
			temp *= 2;
		}
		if (mod != p - 1 && temp % 2 == 0) {
			return FALSE;
		}
	}
	return TRUE;
}

/// Hash algoritam koji odredjuje hash uz pomoc multiplikacije i siftovanja.
/// Algoritam preuzet sa: http://burtleburtle.net/bob/hash/integer.html
inline uint32_t _HashTable_get_hash(void* key) {
	uintptr_t a = (uintptr_t)key;
	a -= (a << 6);
	a ^= (a >> 17);
	a -= (a << 9);
	a ^= (a << 4);
	a -= (a << 3);
	a ^= (a << 10);
	a ^= (a >> 15);
	/// u slucaju 64-bitnih adresa, siftuju se najznacajniji biti (koji su najvazniji), kako bi se dobio 32-bitni broj.
	return a >> ((sizeof(uintptr_t) - sizeof(uint32_t)) * 8); 
}

BOOL HashTable_initialize_table(HashTable* table, unsigned int minimal_size, void* (*bucket_list_allocating_function)(int), void(*bucket_list_free_function)(HashNode**), void* (*node_allocate_function)(), void(*node_free_function)(HashNode*)) {
	BOOL ret = TRUE;

	table->entries = 0;

	/// Osiguraj da prosledjeni parametri nisu NULL
	if (table == NULL)
		return FALSE;

	if (bucket_list_allocating_function != NULL)
		table->bucket_list_allocating_function = bucket_list_allocating_function;
	else
		return FALSE;

	if (bucket_list_free_function != NULL)
		table->bucket_list_free_function = bucket_list_free_function;
	else
		return FALSE;

	if (node_allocate_function != NULL)
		table->node_allocate_function = node_allocate_function;
	else
		return FALSE;

	if (node_free_function != NULL)
		table->node_free_function = node_free_function;
	else
		return FALSE;

	/// Osiguraj da je minimalna velicina tabele prost broj
	if (minimal_size > 0) {
		int size = minimal_size;
		if (size % 2 == 0)
			size++;

		for (; size < 2 * size; size += 2)
			if (_HashTable_miller_rabin(size, 20))
				break;
		table->size = size;
	}
	else
		table->size = 1009;

	table->minimal_size = table->size;
	// alociraj tabelu i inicijalizuj je sa NULL pokazivacima
	table->_table = table->bucket_list_allocating_function(table->size);
	if (table->_table != NULL) 
		for (int i = 0; i < minimal_size; i++)
			table->_table[i] = NULL;
	else
		ret = FALSE;

	return ret;
}

HashNode* HashTable_get(HashTable* table, void* key) {
	if (table != NULL && key != NULL && table->_table != NULL) {
		uint32_t index = _HashTable_get_hash(key) % table->size;	

		/// iteriraj kroz bucket u kojem se nalazi element, i u slucaju pronalaska vrati pokazivac na element.
		for (HashNode* node = table->_table[index]; node != NULL; node = node->next) {
			if (node->key == key)
				return node;
		}
		return NULL;
	}
	else
		return NULL;

}

void _HashTable_rebuild_table(HashTable* table, BOOL is_table_increasing) {
	HashNode** old_table, * next, * current;
	unsigned int old_size, index, i;
	float table_direction = 0;
	old_table = table->_table;
	old_size = table->size;
	int new_size = 0;
	if (is_table_increasing) {
		new_size = old_size << 1;
		table_direction = 2;
	}
	else {
		new_size = old_size >> 1;
		if (new_size < table->minimal_size)
			new_size = table->minimal_size;

		table_direction = 0.5;
	}

	if (new_size % 2 == 0)
		new_size++;
	for (; new_size < 2 * table_direction * old_size; new_size += 2)
		if (_HashTable_miller_rabin(new_size, 20))
			break;

	table->size = new_size;
	table->_table = table->bucket_list_allocating_function(table->size);
	if (table->_table == NULL) {
		table->_table = old_table;
		table->size = old_size;
		return;
	}
		
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
	if (table != NULL && key != NULL) {
		/// u slucaju da tabela vec sadrzi element sa datim kljucem, operacija vraca FALSE
		if (HashTable_get(table, key) == NULL) {

			if (table->entries >= table->size * 0.75) ///< u slucaju da je tabela popunjena vise od 75%, zbog performansa joj je potrebno duplo povecati velicinu.
				_HashTable_rebuild_table(table,TRUE);

			if (table->_table == NULL)
				return FALSE;
			uint32_t index = _HashTable_get_hash(key) % table->size;

			HashNode* node = (HashNode*)table->node_allocate_function();
			/// alociranom elementu dodeli vrednosti
			node->key = key;
			node->value = value;
			node->next = table->_table[index];

			if (table->_table != NULL) {
				table->_table[index] = node; ///< alociran element ubaci u tabelu
				table->entries++;
			}

			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;

}


BOOL HashTable_delete(HashTable* table, void* key,void** out_value) {
	if (table != NULL && key != NULL) {
		HashNode* node = HashTable_get(table, key); ///< dobavi element sa datim kljucem

		if (node != NULL) {
			uint32_t index = _HashTable_get_hash(key) % table->size; ///< uz pomoc hash funkcije izracunaj index "bucket-a" elementa.
			if (node == table->_table[index]) {
				table->_table[index] = node->next;
			}
			else {
				HashNode* last;
				/// pronadji element koji se nalazi pre elementa za brisanje,
				for (last = table->_table[index]; last != NULL && last->next != NULL; last = last->next) 
					if (last->next == node)
						break;
				
				last->next = node->next; ///< izbaci element za brisanje iz tabele.
			}

			table->entries--;
			*out_value = node->value;
			table->node_free_function(node);
			if (table->size > table->minimal_size&& table->entries <= table->size * 0.25)
				_HashTable_rebuild_table(table, FALSE);
			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL HashTable_deinitialize_table(HashTable* table) {
	if (table != NULL) {
		HashNode* current = NULL;
		HashNode* next = NULL;
		/// prolazak kroz tabelu i oslobadjanje svih ulancanih elemenata.
		for (int i = 0; i < table->size; i++) {
			current = table->_table[i];
			while (current != NULL) {
				next = current->next;
				table->node_free_function(current);
				current = next;
			}
		}
		table->bucket_list_free_function(table->_table); ///< oslobadjanje same tabele.
		table->size = 0;
		table->entries = 0;
		return TRUE;
	}
	else
		return FALSE;
}
