
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/util/exceptions.h"
#include "nebu/util/stringUtil.h"

// Using declarations - standard library
using std::string;
// Using declarations - nebu-common
using nebu::common::IllegalArgumentException;
using nebu::common::StringUtil;
// Using declarations - gtest/gmock
using testing::Eq;

TEST(StringUtilTest, testConcatWithDelimiterForEmptyA) {
	string A = "";
	string B = "BString";
	char delimiter = ':';

	EXPECT_THAT(StringUtil::concatWithDelimiter(A, B, delimiter), Eq(":BString"));
}

TEST(StringUtilTest, testConcatWithDelimiterForEmptyB) {
	string A = "AString";
	string B = "";
	char delimiter = ':';

	EXPECT_THAT(StringUtil::concatWithDelimiter(A, B, delimiter), Eq("AString:"));
}

TEST(StringUtilTest, testConcatWithDelimiterForEmptyDelimiter) {
	string A = "AString";
	string B = "BString";
	char delimiter = '\0';

	try {
		StringUtil::concatWithDelimiter(A, B, delimiter);
		FAIL() << "Expected IllegalArgumentException";
	} catch (IllegalArgumentException &ex) {
		SUCCEED();
	}
}

TEST(StringUtilTest, testConcatWithDelimiterWithoutPresentDelimiter) {
	string A = "AString";
	string B = "BString";
	char delimiter = ':';

	EXPECT_THAT(StringUtil::concatWithDelimiter(A, B, delimiter), Eq("AString:BString"));
}

TEST(StringUtilTest, testConcatWithDelimiterVerifyOuterDelimitersStay) {
	string A = "::AString";
	string B = "BString::";
	char delimiter = ':';

	EXPECT_THAT(StringUtil::concatWithDelimiter(A, B, delimiter), Eq("::AString:BString::"));
}

TEST(StringUtilTest, testConcatWithDelimiterWithDelimiterOnA) {
	string A = "AString:";
	string B = "BString";
	char delimiter = ':';

	EXPECT_THAT(StringUtil::concatWithDelimiter(A, B, delimiter), Eq("AString:BString"));
}

TEST(StringUtilTest, testConcatWithDelimiterWithDelimiterOnB) {
	string A = "AString";
	string B = ":BString";
	char delimiter = ':';

	EXPECT_THAT(StringUtil::concatWithDelimiter(A, B, delimiter), Eq("AString:BString"));
}

TEST(StringUtilTest, testConcatWithDelimiterWithMultipleDelimiters) {
	string A = "AString:::";
	string B = "::BString";
	char delimiter = ':';

	EXPECT_THAT(StringUtil::concatWithDelimiter(A, B, delimiter), Eq("AString:BString"));
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
