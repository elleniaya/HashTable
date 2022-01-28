#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>

typedef std::string Key;
struct Value {
	Value(std::string n, unsigned a = 0) : name(n), age(a) {}
	std::string name;
	unsigned age;
};
class HashTable {
public:
    HashTable();

	~HashTable();

	//Copy table b to given table.
	HashTable& operator=(const HashTable& b);

	//Copy table b to given table.
	HashTable(const HashTable& b);

	//Swaps hash table values.
	void swap(HashTable& b);

	//Clearing the hash table of all elements.
	void clear();

	//Delete value, given key k. 
	//If the element with the key k, in the table exists, it will be removedand return true, otherwise false.
	bool erase(const Key& k);

	//Inserting a value pair <k, v>.
	//If there is already an element with the same key in the table, replace it.
	bool insert(const Key& k, const Value& v);

	//Search for a value, given key k. 
	//If the element is found, true is returned, in otherwise false.
	bool contains(const Key& k) const;

	//Referencing the hash table element with key k, using []. 
	//If there is no element with that key, returns an error.
	Value& operator[](const Key& k);

	//Search for a value, given key k. 
	//If found, the value is returned, otherwise error.
	Value& at(const Key& k);
    const Value& at(const Key& k) const;

	//The number of elements in the hash table.
	size_t size() const;

	//Empty check.
	bool empty() const;

	//Comparison of hash table values.
	friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);
private:
	int hash_func(const Key& s) const;
	void resize_Table(size_t new_size);
	std::vector <std::list <std::pair <Key, Value>>*> Table;  
	size_t mSize;
	size_t size_vector_table;
	size_t start_size = 100;
	double RESIZE_CONST = 0.3;
};
