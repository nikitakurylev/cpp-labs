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
		  { return a < b; });

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
		  { return a < b; });

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
		  { return a < b; });

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
						  { return a < b; }));
}

TEST(QuickSortInt, One)
{
	const int N = 1;

	int *a = new int[N];
	for (int i = 0; i < N; i++)
		a[i] = i;

	ASSERT_NO_THROW(qsort(a, a + N, [](int a, int b)
						  { return a < b; }));
}