#include <gtest/gtest.h>
#include "hashtable.h"

TEST(HashTable, ClearCheck) {
	HashTable test;

	Value first("Ban", 26);
	Value second("Din", 37);

	test.insert("3349375", first);
	test.insert("11888888111", second);
	test.insert("7209", first);
	test.insert("7", second);

	test.clear();
	ASSERT_EQ(test.size(), 0);
}

TEST(HashTable, InsertCheck) {
	HashTable test;

	Value value1("Sara", 25);
	Value value2("Aria", 19);

	test.insert("393939", value1);
	test.insert("200939", value2);

	ASSERT_EQ(test.size(), 2);
	ASSERT_EQ(test["393939"].age, value1.age);
	ASSERT_EQ(test["393939"].name, value1.name);

	ASSERT_EQ(test["200939"].age, value2.age);
	ASSERT_EQ(test["200939"].name, value2.name);
}

TEST(HashTable, InsertReplaceCheck) {
	HashTable test;
	Value value1("Bella", 18);
	Value value2("Edward", 28);
	test.insert("7777", value1);

	ASSERT_FALSE(test.insert("7777", value2));

	ASSERT_EQ(test["7777"].age, value2.age);
	ASSERT_EQ(test["7777"].name, value2.name);
	ASSERT_EQ(test.size(), 1);
}

TEST(HashTable, ContainsTrueCheck) {
	HashTable test;

	Value value1("Richard", 57);
	Value value2("Larry", 3);
	Value value3("Olivia", 23);

	test.insert("3297284", value1);
	test.insert("88839", value2);
	test.insert("10101010", value3);

	ASSERT_TRUE(test.contains("3297284"));
	ASSERT_TRUE(test.contains("88839"));
	ASSERT_TRUE(test.contains("10101010"));
}

TEST(HashTable, ContainsFalseCheck) {
	HashTable test;

	ASSERT_FALSE(test.contains("3297284"));
}

TEST(HashTable, EraseTrueCheck) {
	HashTable test;

	Value value("Lia", 9);

	test.insert("8883939", value);

	test.erase("8883939");

	ASSERT_EQ(test.size(), 0);
	ASSERT_FALSE(test.contains("8883939"));
}

TEST(HashTable, EraseFalseCheck) {
	HashTable test;

	ASSERT_FALSE(test.erase("84385"));
}

TEST(HashTable, SizeCheck) {
	HashTable test;

	Value value1("Liza", 7);
	test.insert("6800232", value1);
	Value value2("Mary", 90);
	test.insert("89077700232", value2);
	Value value3("Ro", 29);
	test.insert("1818", value3);
	Value value4("Victor", 15);
	test.insert("9339200000", value4);
	test.erase("9339200000");

	ASSERT_EQ(test.size(), 3);
}

TEST(HashTable, SizeNullCheck) {
	HashTable test;

	ASSERT_EQ(test.size(), 0);
}

TEST(HashTable, EmptyCheck) {
	HashTable test;

	Value value1("Polo", 5);
	Value value2("Nick",19);
	Value value3("Anthony", 78);

	test.insert("3993", value1);
	test.insert("47329", value2);
	test.insert("9", value3);

	test.erase("3993");
	test.erase("47329");
	test.erase("9");

	ASSERT_TRUE(test.empty());
	ASSERT_FALSE(test.contains("3993"));
	ASSERT_FALSE(test.contains("47329"));
	ASSERT_FALSE(test.contains("9"));
}

TEST(HashTable, SwapCheck) {
	HashTable test1;
	Value value1("Inna", 20);
	test1.insert("13579", value1);
	Value value2("Elena", 18);
	test1.insert("6666666", value2);

	HashTable test2;
	Value value3("Mia", 36);
	test2.insert("999999", value3);
	Value value4("Alex", 99);
	test2.insert("2788", value4);

	HashTable test3;
	Value value5("Inna", 20);
	test3.insert("13579", value5);
	Value value6("Elena", 18);
	test3.insert("6666666", value6);

	HashTable test4;
	Value value7("Mia", 36);
	test4.insert("999999", value7);
	Value value8("Alex", 99);
	test4.insert("2788", value8);

	test1.swap(test2);
	ASSERT_EQ(test2, test3);
	ASSERT_EQ(test1, test4);
}

TEST(HashTable, AtCheck) {
	HashTable test;

	Value value("Max", 69);
	test.insert("90", value);

	ASSERT_EQ(test.at("90").age, value.age);
	ASSERT_EQ(test.at("90").name, value.name);
}

TEST(HashTable, CopyConstructorCheck) {
	HashTable test1;
	Value value1("Stiven", 17);
	test1.insert("8202173", value1);
	Value value2("Stefan", 20);
	test1.insert("6664666", value2);

	HashTable test2(test1);

	ASSERT_EQ(test1, test2);
}

TEST(HashTable, OperatorAssignmentCheck) {
	HashTable test1;
	Value value1("Stiven", 17);
	test1.insert("8202173", value1);
	Value value2("Stefan", 20);
	test1.insert("6664666", value2);

	HashTable test2;
    Value value3("Sam", 50);
	test2.insert("89992173", value3);
	Value value4("Damon", 28);
	test2.insert("68632000", value4);
	Value value5("Jonny", 70);
	test2.insert("8888", value5);

	test2 = test1;

	ASSERT_EQ(test1, test2);

	ASSERT_TRUE(test2.contains("8202173"));
	ASSERT_TRUE(test2.contains("6664666"));

	ASSERT_FALSE(test2.contains("89992173"));
	ASSERT_FALSE(test2.contains("68632000"));
	ASSERT_FALSE(test2.contains("8888"));
}

TEST(HashTable, OperatorEqualityCheck) {
	HashTable test1;
	Value value1("Inna", 20);
	test1.insert("13579", value1);
	Value value2("Elena", 18);
	test1.insert("6666666", value2);

	HashTable test2;
	Value value3("Inna", 20);
	test2.insert("13579", value3);
	Value value4("Elena", 18);
	test2.insert("6666666", value4);

	ASSERT_TRUE(test1 == test2);
}

TEST(HashTable, OperatorEqualityFalseCheck) {
	HashTable test1;
	Value value1("Inna", 20);
	test1.insert("13579", value1);
	Value value2("Elena", 18);
	test1.insert("6666666", value2);

	HashTable test2;
	Value value3("Mary", 5);
	test2.insert("13579", value3);
	Value value4("Ava", 27);
	test2.insert("6666666", value4);

	ASSERT_FALSE(test1 == test2);
}

TEST(HashTable, OperatorInequalityCheck) {
	HashTable test1;
	Value value1("Rimma", 20);
	test1.insert("13579", value1);
	Value value2("Jo", 18);
	test1.insert("6666666", value2);

	HashTable test2;
	Value value3("Camila", 36);
	test2.insert("999999", value3);

	ASSERT_TRUE(test1 != test2);
}

TEST(HashTable, OperatorInequalityCheck1) {
	HashTable test1;
	Value value1("Violetta", 20);
	test1.insert("13579", value1);
	Value value2("Liana", 18);
	test1.insert("6666666", value2);

	HashTable test2;
	Value value3("Sam", 36);
	test2.insert("999999", value3);
	Value value4("Oliver", 99);
	test2.insert("2788", value4);

	ASSERT_TRUE(test1 != test2);
}

TEST(HashTable, OperatorIndexCheck) {
	HashTable test;
	Value first("Sara", 50);

	test.insert("757474", first);

	ASSERT_EQ(test["757474"].age, first.age);
	ASSERT_EQ(test["757474"].name, first.name);
}

TEST(HashTable, OperatorIndexNullCheck1) {
	HashTable test;
	Value val("", 0);

	ASSERT_EQ(test["8888"].name, val.name);
	ASSERT_EQ(test["8888"].age, val.age);
}

TEST(HashTable, OperatorIndexNullCheck2) {
	HashTable test;
	Value v1("Jonny", 67);
	test.insert("888", v1);
	Value val("", 0);

	ASSERT_EQ(test["928366600"].name, val.name);
	ASSERT_EQ(test["928366600"].age, val.age);
}

TEST(HashTable, Resize_Check) {
	HashTable test;
	Value v1("Jonny", 67);
	Value v2("Lily", 20);
	Value v3("Lion", 5);
	Value v4("Margo", 27);
	Value v5("Jinny", 15);
	Value v6("Piter", 90);
	test.insert("888", v1);
	test.insert("928366600", v2);
	test.insert("2993746", v3);
	test.insert("742749", v4);
	test.insert("82479427", v5);
	test.insert("10", v6);

	ASSERT_TRUE(test.contains("888"));
	ASSERT_TRUE(test.contains("928366600"));
	ASSERT_TRUE(test.contains("2993746"));
	ASSERT_TRUE(test.contains("742749"));
	ASSERT_TRUE(test.contains("82479427"));
	ASSERT_TRUE(test.contains("10"));

	ASSERT_EQ(test["888"].age, v1.age);
	ASSERT_EQ(test["888"].name, v1.name);

	ASSERT_EQ(test["928366600"].age, v2.age);
	ASSERT_EQ(test["928366600"].name, v2.name);

	ASSERT_EQ(test["2993746"].age, v3.age);
	ASSERT_EQ(test["2993746"].name, v3.name);

	ASSERT_EQ(test["742749"].age, v4.age);
	ASSERT_EQ(test["742749"].name, v4.name);

	ASSERT_EQ(test["82479427"].age, v5.age);
	ASSERT_EQ(test["82479427"].name, v5.name);

	ASSERT_EQ(test["10"].age, v6.age);
	ASSERT_EQ(test["10"].name, v6.name);
}
