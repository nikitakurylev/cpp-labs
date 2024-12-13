#pragma once

#include <gtest/gtest.h>
#include <cstdint>
#include "Array.h"

TEST(ArrayConstruct, DefaultSizeEqualsZero) {
	Array<int> arrInt;
	ASSERT_EQ(arrInt.size(), 0);
	Array<Array<int>> arrMoveInt;
	ASSERT_EQ(arrMoveInt.size(), 0);
}
