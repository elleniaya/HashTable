#include "pch.h"
#include "hashtable.h"


HashTable::HashTable() {
	mSize = 0;
	size_vector_table = 0;
	Table.resize(start_size, nullptr);
}

HashTable::~HashTable() {
	Table.clear();
}

int HashTable::hash_func(const Key& s) const {
	int ind = 0;
	for (size_t i = 0; i < s.size(); i++)
		ind += (s[i] % 4) * 30 + 1024;
	return ind % Table.size();
}

void HashTable::resize_Table(size_t new_size) {
	Table.resize(new_size, nullptr);
}

bool HashTable::insert(const Key& k, const Value& v) {
	std::pair <Key, Value> data(k, v); 

	if (size_vector_table >= RESIZE_CONST * Table.size()) {
		resize_Table(2 * Table.size());
	}

	int ind = hash_func(k);

	std::list<std::pair<Key, Value>>*& collision_list = Table[ind];

	if (collision_list == nullptr) {
		collision_list = new std::list<std::pair<Key, Value>>;
	}

	if (collision_list->empty()) {
		collision_list->push_back(data);
		size_vector_table++;
	}
	else {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [k](const std::pair<Key, Value>& p) {
			return (p.first == k);
		});

		if (val == collision_list->end()) {
			collision_list->push_back(data);
		}
		else return false;
	}

	mSize++;
	return true;
}

bool HashTable::contains(const Key& k) const {
    int ind = hash_func(k);
	std::list<std::pair<Key, Value>>* collision_list = Table[ind];
	if (collision_list != nullptr) {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [k](const std::pair<Key, Value>& p) {
			return(p.first == k);
			});

		if (val != collision_list->end()) {
			return true;
		}
	}
	return false;
}

bool HashTable::erase(const Key& k) {
	int ind = hash_func(k);
	std::list<std::pair<Key, Value>>* collision_list = Table[ind];
	if (collision_list != nullptr) {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [k](const std::pair<Key, Value>& p) { 
			return(p.first == k); 
			});
	    if (val != collision_list->end()) {
			collision_list->erase(val); 
			mSize--;
			return true;
		}
	}
	return false;
}

Value& HashTable::at(const Key& k) {
	int ind = hash_func(k);
	std::list<std::pair<Key, Value>>* collision_list = Table[ind];
	if (collision_list != nullptr) {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [k](const std::pair<Key, Value>& p) { 
			return(p.first == k);
			});
		if (val != collision_list->end()) {
			return val->second;
		}
	}
	throw "There is no element in the table for the given key";
}


const Value& HashTable::at(const Key& k) const {
	int ind = hash_func(k);
	std::list<std::pair<Key, Value>>* collision_list = Table[ind];
	if (collision_list != nullptr) {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [k](const std::pair<Key, Value>& p) {
			return(p.first == k);
			});
		if (val != collision_list->end()) {
			return val->second;
		}
	}
	throw "There is no element in the table for the given key";
}

size_t HashTable::size() const {
	return mSize;
}

bool HashTable::empty() const {
	return mSize == 0;
}

void HashTable::clear() {
	for (size_t i = 0; i < mSize; i++) {
		if (Table[i] != nullptr) {
			delete Table[i];
		}
	}
	Table.clear();
	mSize = 0;
}

HashTable& HashTable::operator=(const HashTable& b) {
	if (this != &b) {
		for (size_t i = 0; i < Table.capacity(); i++) {
			if (Table[i] != nullptr) delete Table[i];
		}
		Table.clear();
		mSize = b.mSize;
		Table.resize(b.Table.capacity());
		for (size_t i = 0; i < b.Table.capacity(); i++) {
			if (b.Table[i] != nullptr && Table[i] == nullptr) {
				Table[i] = new std::list<std::pair<Key, Value>>;
				std::list<std::pair<Key, Value>>* collision_list_b = b.Table[i];
				std::list<std::pair<Key, Value>>*& collision_list_a = Table[i];
				for (auto itr = collision_list_b->begin(); itr != collision_list_b->end(); itr++) {
					collision_list_a->push_back(*itr);
				}
			}
		}
	}

	return *this;
}

HashTable::HashTable(const HashTable& b) { 
	*this = b;
}  

void HashTable::swap(HashTable& b) {
	std::swap(mSize, b.mSize);
	std::swap(Table, b.Table);
}

Value& HashTable::operator[](const Key& k) {
	int ind = hash_func(k);
	if (Table[ind] == nullptr) {
		throw "There is no element in the table for the given key";
	}
	std::list<std::pair<Key, Value>>* collision_list = Table[ind];
	if (collision_list != nullptr) {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [k](const std::pair<Key, Value>& p) {
			return(p.first == k);
			});
		if (val != collision_list->end()) {
			return val->second;
		}
	}
	throw "There is no element in the table for the given key";
}

bool operator==(const HashTable& a, const HashTable& b) {
	if (a.mSize != b.mSize) return false;
	for (size_t i = 0; i < a.Table.size(); i++) {
		if ((a.Table[i] == nullptr && b.Table[i] != nullptr) || (a.Table[i] != nullptr && b.Table[i] == nullptr)) return false;
		if (a.Table[i] == nullptr && b.Table[i] == nullptr) { continue; }
		else {
			std::list<std::pair<Key, Value>>* collision_list_a = a.Table[i];
			std::list<std::pair<Key, Value>>* collision_list_b = b.Table[i];

			if (collision_list_a->size() != collision_list_b->size()) return false;

			if (collision_list_a != nullptr && collision_list_b != nullptr) {
				for (auto& itr = collision_list_a->begin(); itr != collision_list_a->end(); itr++) {
					Key* k = &itr->first;
					auto val = std::find_if(collision_list_b->begin(), collision_list_b->end(), [&k](const std::pair<Key, Value>& p) {
						return(p.first == *k);
						});
					if (val == collision_list_b->end()) {
						return false;
					}
					else if ((val->second.age == itr->second.age) && (val->second.name == itr->second.name)) continue;
				}
			}
			else continue;
		}
	}
	return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
	return !(a == b);
}