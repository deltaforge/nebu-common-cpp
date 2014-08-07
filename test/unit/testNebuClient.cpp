
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/nebuClient.h"
#include "mocks/mockRestClientAdapter.h"

// Using declarations - standard library
using std::make_shared;
using std::shared_ptr;
// Using declarations - nebu-common
using nebu::common::NebuClient;
// Using declarations - nebu-test
using nebu::test::MockRestClientAdapter;

// Using declarations - gtest/gmock
using testing::Eq;
using testing::Return;

TEST(NebuClientTest, testPerformGet) {
	shared_ptr<MockRestClientAdapter> restClientAdapter = make_shared<MockRestClientAdapter>();
	NebuClient client(restClientAdapter, "http://localhost");

	RestClient::response preppedResponse;
	preppedResponse.code = 1234;
	preppedResponse.body = "Response BODY";

	EXPECT_CALL(*restClientAdapter, get("http://localhost/someURI"))
		.WillOnce(Return(preppedResponse));

	NebuClient::Response response = client.performGET("someURI");

	EXPECT_THAT(response.body, Eq(preppedResponse.body));
	EXPECT_THAT(response.status_code, Eq(preppedResponse.code));
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
