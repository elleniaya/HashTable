#include "pch.h"
#include "hashtable.h"

HashTable::HashTable() : mSize(0)
{
	Table.resize(start_size);
}

HashTable::~HashTable() {}

int HashTable::hash_func(const Key& s) const
{
	int ind = 0;
	for (size_t i = 0; i < s.size(); i++)
		ind += s[i] + 1;
	return ind % Table.capacity(); //???
	//return ind % 100;
}

bool HashTable::insert(const Key& k, const Value& v)
{
	std::pair <Key, Value> data(k, v);  //создаем из полученные k и v пару, т.к. элементы list пары значение (pair)
	int ind = hash_func(k);

	if (Table.size() >= (0.3 * Table.capacity())) {
		Table.reserve(start_size);
	}

	if (Table[ind].empty()) {      //list пуст, коллизий нет 
		Table[ind].push_back(data);
	}
	else {
		bool ch = true;
		for (auto itr = Table[ind].begin(); itr != Table[ind].end(); itr++) {
			if (itr->first == k) return false;
			if (itr->first > k) {
				Table[ind].insert(itr, data);
				ch = false;
				break;
			}
		}
		if (ch) {
			Table[ind].push_back(data);
		}
	}
	mSize++;
	return true;
}

bool HashTable::contains(const Key& k) const
{
	int ind = hash_func(k);
	if (!Table[ind].empty()) {
		for (auto itr = Table[ind].begin(); itr != Table[ind].end(); itr++) {
			if (itr->first == k) return true;
			if (itr->first > k) {
				break;
			}
		}
	}
	return false;
}

bool HashTable::erase(const Key& k)
{
	int ind = hash_func(k);
	if (!Table[ind].empty())
	{
		for (auto itr = Table[ind].begin(); itr != Table[ind].end(); itr++)
		{
			if (itr->first == k)
			{
				Table[ind].erase(itr);
				mSize--;
				return true; //элемент удален из таблицы
			}
			if (itr->first > k)
			{
				break;
			}
		}
	}
	return false;
}

Value& HashTable::at(const Key& k)
{
	Value val("");
	int ind = hash_func(k);
	if (!Table[ind].empty())
	{
		for (auto itr = Table[ind].begin(); itr != Table[ind].end(); itr++)
		{
			if (itr->first == k)
			{
				return itr->second;
			}
			if (itr->first > k)
			{
				break;
			}
		}
	}
	return val;
}


const Value& HashTable::at(const Key& k) const
{
	Value val("");
	int ind = hash_func(k);
	if (!Table[ind].empty())
	{
		for (auto itr = Table[ind].begin(); itr != Table[ind].end(); itr++)
		{
			if (itr->first == k)
			{
				val = itr->second;
			}
			if (itr->first > k)
			{
				break;
			}
		}
	}
	return val;
}

size_t HashTable::size() const
{
	return mSize;
}

bool HashTable::empty() const
{
	return mSize == 0;
}

void HashTable::clear()
{
	Table.clear();
}

HashTable::HashTable(const HashTable& b) : Table(b.Table), mSize(b.mSize) {}  // конструктор копирования

HashTable& HashTable::operator=(const HashTable& b)
{
	Table = b.Table;
	mSize = b.mSize;
	return *this;
}

void HashTable::swap(HashTable& b)
{
	HashTable tmp = *this;
	*this = b;
	b = tmp;
}

Value& HashTable::operator[](const Key& k)
{
	return at(k);
}

bool operator==(const HashTable& a, const HashTable& b)
{
	if (a.mSize != b.mSize) return false;
	for (int i = 0; i < a.Table.size(); i++)
	{
		if (a.Table[i].size() != b.Table[i].size()) return false;
		for (auto itr1 = a.Table[i].begin(), itr2 = b.Table[i].begin(); itr1 != a.Table[i].end(); itr1++, itr2++)
		{
			if (itr1->first != itr2->first || itr1->second.age != itr2->second.age || itr1->second.name != itr2->second.name) return false;
		}
	}
	return true;
}

bool operator!=(const HashTable& a, const HashTable& b)
{
	return !(a == b);
}
