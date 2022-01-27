#include "pch.h"
#include "hashtable.h"

TEST(HashTable, ClearCheck) { 
	HashTable test;

	Value first("Masha", 22);
	Value second("Ivan", 80);

	test.insert("334959375", first);
	test.insert("11111", second);
	test.insert("2929", first);
	test.insert("2", second);

	test.clear();
    EXPECT_EQ(test.size(), 0);
    //EXPECT_TRUE(true);
}

TEST(HashTable, InsertCheck) {
	HashTable test;

	Value value("Aria", 19);

	test.insert("393939", value);
	bool a = test.contains("393939");
	EXPECT_EQ(a, true);
}

TEST(HashTable, ContainsCheck) { 
	HashTable test;

	Value value("Richard", 57);

	test.insert("3297284", value);

	bool a = false;
	if (test.contains("3297284")) a = true;
	EXPECT_EQ(a, true);
}

TEST(HashTable, EraseCheck) {
	HashTable test;

	Value value("Lia", 9);

	test.insert("8883939", value);
	int start_size = test.size();

	test.erase("8883939");
	int finish_size = test.size();

	EXPECT_EQ(start_size - 1, finish_size);
}

TEST(HashTable, SizeCheck) {
	HashTable test;

	Value value1("Лиза", 7);
	test.insert("6800232", value1);
	Value value2("Оля", 90);
	test.insert("89077700232", value2);
	Value value3("Андрей", 29);
	test.insert("1818", value3);
	Value value4("Виктор", 15);
	test.insert("9339200000", value4);
	test.erase("89077700232");

	int size = test.size();
	EXPECT_EQ(size, 3);
}

TEST(HashTable, EmptyCheck) {
	HashTable test;

	Value value("Polo", 5);
	test.insert("3993", value);

	EXPECT_EQ(test.empty(), false);
}

/*TEST(HashTable, SwapCheck) {
	HashTable test1;
	Value value1("Инна", 20);
	test1.insert("13579", value1);
	Value value2("Лена", 18);
	test1.insert("6666666", value2);

	HashTable test2;
	Value value3("Ира", 36);
	test2.insert("999999", value3);
	Value value4("Александр", 99);
	test2.insert("2788", value4);

	HashTable test3;
	Value value5("Инна", 20);
	test3.insert("8202173", value5);
	Value value6("Лена", 18);
	test3.insert("6666666", value6);

	test1.swap(test2);

	EXPECT_EQ(test2, test3);
}

TEST(HashTable, AtCheck) {
	HashTable test;

	Value value("Max", 69);

	test.insert("90", value);
	Value val = test.at("90");
	EXPECT_EQ(val, value);
}

TEST(HashTable, OperatorAssignmentCheck) {
	HashTable test1;
	Value value1("Инна", 20);
	test1.insert("8202173", value1);
	Value value2("Лена", 18);
	test1.insert("6666666", value2);

	HashTable test2;

	test2 = test1;
	EXPECT_EQ(test2, test1);
}
*/

/*TEST(HashTable, OperatorEqualityCheck) {
	HashTable test1;
	Value value1("Инна", 20);
	test1.insert("13579", value1);
	Value value2("Лена", 18);
	test1.insert("6666666", value2);

	HashTable test2;
	Value value3("Инна", 20);
	test2.insert("13579", value3);
	Value value4("Лена", 18);
	test2.insert("6666666", value4);

	bool a = false;
	if (test1 == test2) a = true;
	EXPECT_EQ(a, true);
}
*/

/*TEST(HashTable, OperatorInequalityCheck) {
	HashTable test1;
	Value value1("Инна", 20);
	test1.insert("13579", value1);
	Value value2("Лена", 18);
	test1.insert("6666666", value2);

	HashTable test2;
	Value value3("Инна", 20);
	test2.insert("13579", value3);
	Value value4("Лена", 18);
	test2.insert("6666666", value4);

	bool a = false;
	if (test1 != test2) a = true;
	EXPECT_EQ(a, true);
}
*/

/*TEST(HashTable, OperatorIndexCheck) {
	HashTable test;
	Value first("Sara", 50);

	test.insert("757474", first);
	Value val = test["757474"];

	EXPECT_EQ(val, first);
}
*/






