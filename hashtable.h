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

	//Clearing the hash table of all values.
	void clear();

	//Delete value, given key k. 
	//If the value with the key k, in the table exists, it will be removed and return true, otherwise false.
	bool erase(const Key& k);

	//Insert a pair of values <k, v>.
        //If no value with this key is found in the table, insert the value pair <k, v> and return true.
        //If the table has a value with this key, replace it and return false.
	bool insert(const Key& k, const Value& v);

	//Search for a value, given key k. 
	//If the value is found, return true, in otherwise false.
	bool contains(const Key& k) const;

	//Referencing the hash table value with key k, using []. 
	//If no value is found for that key, return a pair <k, Value("", 0)>.
	Value& operator[](const Key& k);

	//Search for a value, given key k. 
	//If found, return value, otherwise error.
	Value& at(const Key& k);
	const Value& at(const Key& k) const;

	//The number of values in the hash table.
	size_t size() const;

	//Empty check.
	bool empty() const;

	//Comparison of hash table values.
	friend bool operator==(const HashTable& a, const HashTable& b);
	friend bool operator!=(const HashTable& a, const HashTable& b);
private:
	int hash_func(const Key& s) const;
	void resize_table(size_t new_size);
	Value& const_at(const Key& k) const;
	void copy_table(const HashTable& a, const HashTable& b);

	std::vector <std::list <std::pair <Key, Value>>*> table_;

	size_t size_;
	size_t size_vector_table;
	static const size_t start_size = 8;
	static constexpr double RESIZE_CONST = 0.3;
};
