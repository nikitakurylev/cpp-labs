#pragma once

#include <gtest/gtest.h>

#include "Sort.h"

TEST(InsertionSortInt, Random)
{
	const int N = 10000;

	int *a = new int[N];
	for (int i = 0; i < N; i++)
		a[i] = rand();

	insertionSort(a, a + N, [](int a, int b)
		  { return a < b; });

	for (int i = 1; i < N; i++)
	{
		ASSERT_LE(a[i - 1], a[i]);
	}
}

TEST(QuickSortInt, Random)
{
	const int N = 10000;

	int *a = new int[N];
	for (int i = 0; i < N; i++)
		a[i] = rand();

	qsort(a, a + N, [](int a, int b)
		  { return a < b; }, 60);

	for (int i = 1; i < N; i++)
	{
		ASSERT_LE(a[i - 1], a[i]);
	}
}

TEST(QuickSortInt, Worst)
{
	const int N = 10000;

	int *a = new int[N];
	for (int i = 0; i < N; i++)
		a[i] = N - i;

	qsort(a, a + N, [](int a, int b)
		  { return a < b; }, 60);

	for (int i = 1; i < N; i++)
	{
		ASSERT_LE(a[i - 1], a[i]);
	}
}

TEST(QuickSortInt, Sorted)
{
	const int N = 10000;

	int *a = new int[N];
	for (int i = 0; i < N; i++)
		a[i] = i;

	qsort(a, a + N, [](int a, int b)
		  { return a < b; }, 60);

	for (int i = 1; i < N; i++)
	{
		ASSERT_LE(a[i - 1], a[i]);
	}
}

TEST(QuickSortInt, Empty)
{
	const int N = 0;

	int *a = new int[N];

	ASSERT_NO_THROW(qsort(a, a + N, [](int a, int b)
						  { return a < b; }, 60));
}

TEST(QuickSortInt, One)
{
	const int N = 1;

	int *a = new int[N];
	for (int i = 0; i < N; i++)
		a[i] = i;

	ASSERT_NO_THROW(qsort(a, a + N, [](int a, int b)
						  { return a < b; }, 60));
}

TEST(QuickSortString, Reverse)
{
	const int N = 5;
	const std::string strings[N] {"Alice", "Bob", "Chris", "Ivan", "Nikita"};
	std::string stringsReverse[N];

	for (int i = 1; i <= N; i++)
		new (&stringsReverse[i - 1]) std::string(strings[N - i]);

    std::string* ptr_to_arr = stringsReverse;

	qsort(stringsReverse, stringsReverse + N - 1, [](std::string a, std::string b)
		  { return a[0] < b[0]; });

	for (int i = 0; i < N; i++)
	{
		ASSERT_EQ(stringsReverse[i], strings[i]);
	}
}