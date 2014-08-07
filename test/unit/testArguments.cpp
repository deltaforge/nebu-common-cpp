
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/util/arguments.h"

// Using declarations - nebu-common
using nebu::common::Arguments;
using nebu::common::IllegalArgumentException;

TEST(ArgumentTest, testThrowsIfNullWithNull) {
	try {
		NEBU_THROWIFNULL(NULL);
		FAIL() << "Expected IllegalArgumentException";
	} catch (IllegalArgumentException &expected) {
		SUCCEED();
	}
}

TEST(ArgumentTest, testThrowsIfNullWithGoodValue) {
	int someValue = 0;
	int *somePointer = &someValue;
	NEBU_THROWIFNULL(somePointer);
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
