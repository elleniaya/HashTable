#include "hashtable.h"

HashTable::HashTable() : size_(0), size_vector_table(0), table_(start_size, nullptr) {}

HashTable::~HashTable() {
	for (size_t i = 0; i < size_; i++) {
		if (table_[i] != nullptr) {
			delete table_[i];
		}
	}
}

int HashTable::hash_func(const Key& s) const {
	int ind = 0;
	for (size_t i = 0; i < s.size(); i++)
		ind += (s[i] % 4) * 30 + 1024;
	return ind % table_.size();
}

void HashTable::resize_table(size_t new_size) {
	size_t size = table_.size();
	table_.resize(new_size, nullptr);
	for (size_t i = 0; i < size; i++) {
		if (table_[i] == nullptr) { continue; }
		else {
			std::list< std::pair <Key, Value>> collision_list = *table_[i];
			table_[i]->clear();
			int new_hash;
			for (auto itr = collision_list.begin(); itr != collision_list.end(); itr++) {
				new_hash = hash_func(itr->first);
				if (table_[new_hash] == nullptr) {
					table_[new_hash] = new std::list <std::pair <Key, Value>>;
				}
				table_[new_hash]->push_back(*itr);
			}
		}
	}
}

bool HashTable::insert(const Key& k, const Value& v) {
	std::pair <Key, Value> data(k, v);

	if (size_vector_table >= RESIZE_CONST * table_.size()) {
		resize_table(2 * table_.size());
	}

	int ind = hash_func(k);

	std::list<std::pair<Key, Value>>*& collision_list = table_[ind];

	if (collision_list == nullptr) {
		collision_list = new std::list<std::pair<Key, Value>>;
	}

	if (collision_list->empty()) {
		collision_list->push_back(data);
		size_vector_table++;
		size_++;
	}
	else {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [&k](const std::pair<Key, Value>& p) {
			return (p.first == k);
		});

		if (val == collision_list->end()) {
			collision_list->push_back(data);
			size_++;
		}
		else {
			*val = data;
			return false;
		}
	}

	return true;
}

bool HashTable::contains(const Key& k) const {
	int ind = hash_func(k);
	std::list<std::pair<Key, Value>>* collision_list = table_[ind];
	if (collision_list != nullptr) {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [&k](const std::pair<Key, Value>& p) {
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
	std::list<std::pair<Key, Value>>* collision_list = table_[ind];
	if (collision_list != nullptr) {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [&k](const std::pair<Key, Value>& p) {
			return(p.first == k);
			});
		if (val != collision_list->end()) {
			collision_list->erase(val);
			size_--;
			if (collision_list->size() == 0) size_vector_table--;
			return true;
		}
	}
	return false;
}

Value& HashTable::const_at(const Key& k) const {
	int ind = hash_func(k);
	std::list<std::pair<Key, Value>>* collision_list = table_[ind];
	if (collision_list != nullptr) {
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [&k](const std::pair<Key, Value>& p) {
			return(p.first == k);
			});
		if (val != collision_list->end()) {
			return val->second;
		}
	}
	throw std::runtime_error("There is no element in the table for the given key");
}

Value& HashTable::at(const Key& k) {
	return const_at(k);
}


const Value& HashTable::at(const Key& k) const {
	return const_cast<Value&>(const_at(k));
}

size_t HashTable::size() const {
	return size_;
}

bool HashTable::empty() const {
	return size_ == 0;
}

void HashTable::clear() {
	if (table_.empty()) return;
	for (size_t i = 0; i < size_; i++) {
		if (table_[i] != nullptr) {
			delete table_[i];
		}
	}
	table_.clear();
	size_ = 0;
	size_vector_table = 0;
}

void HashTable::copy_table(const HashTable& a, const HashTable& b) {
	for (size_t i = 0; i < b.table_.size(); i++) {
		if (b.table_[i] != nullptr) {
			table_[i] = new std::list<std::pair<Key, Value>>;
			std::list<std::pair<Key, Value>>* collision_list_b = b.table_[i];
			std::list<std::pair<Key, Value>>*& collision_list_a = table_[i];
			for (auto itr = collision_list_b->begin(); itr != collision_list_b->end(); itr++) {
				collision_list_a->push_back(*itr);
			}
		}
	}
}

HashTable& HashTable::operator=(const HashTable& b) {
	if (this != &b) {
		clear();
		size_ = b.size_;
		size_vector_table = b.size_vector_table;
		table_.resize(b.table_.size(), nullptr);
		copy_table(*this, b);
	}

	return *this;
}

HashTable::HashTable(const HashTable& b) : size_(b.size_), size_vector_table(b.size_vector_table), table_(start_size, nullptr) {
	copy_table(*this, b);
}

void HashTable::swap(HashTable& b) {
	std::swap(size_, b.size_);
	std::swap(size_vector_table, b.size_vector_table);
	std::swap(table_, b.table_);
}

Value& HashTable::operator[](const Key& k) {
	int ind = hash_func(k);
	if (table_[ind] == nullptr) {
		Value v("", 0);
		insert(k, v);
	}
	std::list<std::pair<Key, Value>>* collision_list = table_[ind];
	auto val = std::find_if(collision_list->begin(), collision_list->end(), [&k](const std::pair<Key, Value>& p) {
		return(p.first == k);
	});
	if (val != collision_list->end()) {
		return val->second;
	}
	else {
		Value v("", 0);
		insert(k, v);
		auto val = std::find_if(collision_list->begin(), collision_list->end(), [&k](const std::pair<Key, Value>& p) {
			return(p.first == k);
		});
		if (val != collision_list->end()) {
			return val->second;
		}
	}
}

bool operator==(const HashTable& a, const HashTable& b) {
	if (a.size_ != b.size_) return false;
	for (size_t i = 0; i < a.table_.size(); i++) {
		if (a.table_[i] == nullptr) { continue; }
		else {
			std::list<std::pair<Key, Value>>* collision_list_a = a.table_[i];

			for (auto itr = collision_list_a->begin(); itr != collision_list_a->end(); itr++) {

				if (b.contains(itr->first)) {
					if (itr->second.age == b.at(itr->first).age && itr->second.name == b.at(itr->first).name) {
						continue;
					}
					else return false;
				}
				else return false;
			}
		}
	}
	return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
	return !(a == b);
}
