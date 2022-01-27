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
	HashTable& operator=(const HashTable& b);
	HashTable(const HashTable& b);
	void swap(HashTable& b);
	void clear();
	bool erase(const Key& k);
	bool insert(const Key& k, const Value& v);
	bool contains(const Key& k) const;
	Value& operator[](const Key& k);
	Value& at(const Key& k);
	const Value& at(const Key& k) const;
	size_t size() const;
	bool empty() const;
	friend bool operator==(const HashTable& a, const HashTable& b);
	friend bool operator!=(const HashTable& a, const HashTable& b);
	int hash_func(const Key& s) const;
private:
	std::vector <std::list <std::pair <Key, Value>>> Table;
	size_t mSize;
	int start_size = 100;
};
