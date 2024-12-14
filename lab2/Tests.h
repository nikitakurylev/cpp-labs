#pragma once

#include <gtest/gtest.h>
#include "Array.h"

TEST(ConstructArray, Default)
{
	Array<int> intArray;
	ASSERT_EQ(intArray.size(), 0);
	Array<Array<int>> arrMoveInt;
	ASSERT_EQ(arrMoveInt.size(), 0);
}

TEST(ConstructArray, Copying)
{
	Array<int> intArray1(5);
	intArray1.insert(1);
	intArray1.insert(2);
	Array<int> intArray2 = intArray1;
	ASSERT_EQ(intArray2.size(), 2);
	ASSERT_EQ(intArray2[0], 1);
	ASSERT_EQ(intArray2[1], 2);
	intArray1.insert(3);
	ASSERT_EQ(intArray2.size(), 2);

	Array<std::string> stringArray(5);
	stringArray.insert("test1");
	stringArray.insert("test2");
	Array<std::string> intArray4 = stringArray;
	ASSERT_EQ(intArray4.size(), 2);
	ASSERT_EQ(intArray4[0], "test1");
	ASSERT_EQ(intArray4[1], "test2");
	stringArray.insert("test3");
	ASSERT_EQ(intArray4.size(), 2);
}

TEST(ConstructArray, Moving)
{
	Array<int> intArray1(5);
	intArray1.insert(1);
	intArray1.insert(2);
	Array<int> intArray2 = std::move(intArray1);
	ASSERT_EQ(intArray2.size(), 2);
	ASSERT_EQ(intArray2[0], 1);
	ASSERT_EQ(intArray2[1], 2);
	ASSERT_EQ(intArray1.size(), 0);

	Array<std::string> stringArray(5);
	stringArray.insert("test1");
	stringArray.insert("test2");
	Array<std::string> intArray4 = std::move(stringArray);
	ASSERT_EQ(intArray4.size(), 2);
	ASSERT_EQ(intArray4[0], "test1");
	ASSERT_EQ(intArray4[1], "test2");
	ASSERT_EQ(stringArray.size(), 0);
}

TEST(AssignArray, Moving)
{
	Array<int> intArray1(5);
	intArray1.insert(1);
	intArray1.insert(2);
	Array<int> intArray2;
	intArray2 = std::move(intArray1);
	ASSERT_EQ(intArray2.size(), 2);
	ASSERT_EQ(intArray2[0], 1);
	ASSERT_EQ(intArray2[1], 2);
	ASSERT_EQ(intArray1.size(), 0);

	Array<std::string> stringArray(5);
	stringArray.insert("test1");
	stringArray.insert("test2");
	Array<std::string> intArray4;
	intArray4 = std::move(stringArray);
	ASSERT_EQ(intArray4.size(), 2);
	ASSERT_EQ(intArray4[0], "test1");
	ASSERT_EQ(intArray4[1], "test2");
	ASSERT_EQ(stringArray.size(), 0);
}

TEST(ArrayInsert, End)
{
	Array<int> intArray;
	intArray.insert(1);
	ASSERT_EQ(intArray.size(), 1);
	ASSERT_EQ(intArray[0], 1);
	intArray.insert(2);
	ASSERT_EQ(intArray.size(), 2);
	ASSERT_EQ(intArray[1], 2);

	Array<std::string> stringArray;
	stringArray.insert("test1");
	ASSERT_EQ(stringArray.size(), 1);
	ASSERT_EQ(stringArray[0], "test1");
	stringArray.insert("test2");
	ASSERT_EQ(stringArray.size(), 2);
	ASSERT_EQ(stringArray[1], "test2");
}

TEST(ArrayInsert, Start)
{
	Array<int> intArray;
	intArray.insert(0, 1);
	ASSERT_EQ(intArray.size(), 1);
	ASSERT_EQ(intArray[0], 1);
	intArray.insert(0, 2);
	ASSERT_EQ(intArray.size(), 2);
	ASSERT_EQ(intArray[0], 2);

	Array<std::string> stringArray;
	stringArray.insert(0, "test1");
	ASSERT_EQ(stringArray.size(), 1);
	ASSERT_EQ(stringArray[0], "test1");
	stringArray.insert(0, "test2");
	ASSERT_EQ(stringArray.size(), 2);
	ASSERT_EQ(stringArray[0], "test2");
}

TEST(ArrayInsert, Index)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.insert(1, 3);
	ASSERT_EQ(intArray.size(), 3);
	ASSERT_EQ(intArray[1], 3);

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.insert(1, "test3");
	ASSERT_EQ(stringArray.size(), 3);
	ASSERT_EQ(stringArray[1], "test3");
}

TEST(ArrayRemove, Start)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.remove(0);
	ASSERT_EQ(intArray.size(), 1);
	ASSERT_EQ(intArray[0], 2);
	intArray.remove(0);
	ASSERT_EQ(intArray.size(), 0);

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.remove(0);
	ASSERT_EQ(stringArray.size(), 1);
	ASSERT_EQ(stringArray[0], "test2");
	stringArray.remove(0);
	ASSERT_EQ(stringArray.size(), 0);
}

TEST(ArrayRemove, End)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.remove(1);
	ASSERT_EQ(intArray.size(), 1);
	ASSERT_EQ(intArray[0], 1);
	intArray.remove(0);
	ASSERT_EQ(intArray.size(), 0);

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.remove(1);
	ASSERT_EQ(stringArray.size(), 1);
	ASSERT_EQ(stringArray[0], "test1");
	stringArray.remove(0);
	ASSERT_EQ(stringArray.size(), 0);
}

TEST(ArrayRemove, Index)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.insert(3);
	intArray.remove(1);
	ASSERT_EQ(intArray.size(), 2);
	ASSERT_EQ(intArray[0], 1);
	ASSERT_EQ(intArray[1], 3);

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.insert("test3");
	stringArray.remove(1);
	ASSERT_EQ(stringArray.size(), 2);
	ASSERT_EQ(stringArray[0], "test1");
	ASSERT_EQ(stringArray[1], "test3");
}

TEST(ArrayIndex, Read)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	ASSERT_EQ(intArray[0], 1);
	ASSERT_EQ(intArray[1], 2);

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	ASSERT_EQ(stringArray[0], "test1");
	ASSERT_EQ(stringArray[1], "test2");
}

TEST(ArrayIndex, Write)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray[0] = 3;
	intArray[1] = 4;
	ASSERT_EQ(intArray[0], 3);
	ASSERT_EQ(intArray[1], 4);

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray[0] = std::move("test3");
	stringArray[1] = std::move("test4");
	ASSERT_EQ(stringArray[0], "test3");
	ASSERT_EQ(stringArray[1], "test4");
}

TEST(ArrayIterator, Forward)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.insert(3);
	int i = 1;
	for (auto it = intArray.iterator(); it.hasNext(); it.next())
	{
		ASSERT_EQ(it.get(), i);
		i++;
	}

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.insert("test3");
	std::string strings[3] = { "test1", "test2", "test3"};
	int j = 0;
	for (auto it = stringArray.iterator(); it.hasNext(); it.next())
	{
		ASSERT_EQ(it.get(), strings[j]);
		j++;
	}
}

TEST(ArrayIterator, Reverse)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.insert(3);
	int i = 3;
	for (auto it = intArray.reverseIterator(); it.hasNext(); it.next())
	{
		ASSERT_EQ(it.get(), i);
		i--;
	}

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.insert("test3");
	std::string strings[3] = { "test1", "test2", "test3"};
	int j = 2;
	for (auto it = stringArray.reverseIterator(); it.hasNext(); it.next())
	{
		ASSERT_EQ(it.get(), strings[j]);
		j--;
	}
}

TEST(ArrayIterator, Write)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.insert(3);
	int i = 3;
	for (auto it = intArray.iterator(); it.hasNext(); it.next())
	{
		it.set(i);
		ASSERT_EQ(it.get(), i);
		i--;
	}

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.insert("test3");
	std::string strings[3] = { "test1", "test2", "test3"};
	int j = 2;
	for (auto it = stringArray.iterator(); it.hasNext(); it.next())
	{
		it.set(std::move(strings[j]));
		ASSERT_EQ(it.get(), strings[j]);
		j--;
	}
}

TEST(ArrayConstIterator, Forward)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.insert(3);
	const auto *constIntArray = &intArray;
	int i = 1;
	for (auto it = constIntArray->iterator(); it.hasNext(); it.next())
	{
		ASSERT_EQ(it.get(), i);
		i++;
	}

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.insert("test3");
	const auto *constStringArray = &stringArray;
	std::string strings[3] = { "test1", "test2", "test3"};
	int j = 0;
	for (auto it = constStringArray->iterator(); it.hasNext(); it.next())
	{
		ASSERT_EQ(it.get(), strings[j]);
		j++;
	}
}

TEST(ArrayConstIterator, Reverse)
{
	Array<int> intArray;
	intArray.insert(1);
	intArray.insert(2);
	intArray.insert(3);
	const auto *constIntArray = &intArray;
	int i = 3;
	for (auto it = constIntArray->reverseIterator(); it.hasNext(); it.next())
	{
		ASSERT_EQ(it.get(), i);
		i--;
	}

	Array<std::string> stringArray;
	stringArray.insert("test1");
	stringArray.insert("test2");
	stringArray.insert("test3");
	const auto *constStringArray = &stringArray;
	std::string strings[3] = { "test1", "test2", "test3"};
	int j = 2;
	for (auto it = constStringArray->reverseIterator(); it.hasNext(); it.next())
	{
		ASSERT_EQ(it.get(), strings[j]);
		j--;
	}
}