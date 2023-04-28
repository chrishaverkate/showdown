#include <gtest/gtest.h>

#include <pico-demo/message.h>

TEST(MessageTests, get_hello) {
	Message m;
	ASSERT_STREQ("Hello World!", m.get_hello()->c_str());
}
