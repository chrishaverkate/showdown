#include <gtest/gtest.h>

#include <controller_impl.h>
#include <models/session.h>

#include <memory>
#include <vector>

using std::make_unique;
using std::move;
using std::unique_ptr;
using std::vector;

class SessionTests : public ::testing::Test {
protected:
	void SetUp() override {
	}

	void TearDown() override {
	}

	Session _s;
	vector<uint64_t> _expected_shot_times {};
	vector<uint64_t> _expected_shot_deltas {};
};

TEST_F(SessionTests, no_shots) {
	ASSERT_EQ(0, _s.get_last_shot_time());
	ASSERT_EQ(0, _s.get_shot_count());
	ASSERT_TRUE(_s.get_shots().empty());
}

TEST_F(SessionTests, one_shot) {
	uint64_t time = 1234;
	_s.add_shot(time);
	_expected_shot_times.emplace_back(time);

	ASSERT_EQ(time, _s.get_last_shot_time());
	ASSERT_EQ(1, _s.get_shot_count());
	ASSERT_EQ(_expected_shot_times, _s.get_shots());
}

TEST_F(SessionTests, get_deltas_between_shots) {
	uint64_t time1 = 10;
	uint64_t time2 = 25;
	uint64_t time3 = 45;
	_s.add_shot(time1);
	_s.add_shot(time2);
	_s.add_shot(time3);
	_expected_shot_times.emplace_back(time1 - 0);
	_expected_shot_times.emplace_back(time2 - time1);
	_expected_shot_times.emplace_back(time3 - time2);

	ASSERT_EQ(time3, _s.get_last_shot_time());
	ASSERT_EQ(3, _s.get_shot_count());
	ASSERT_EQ(_expected_shot_times, _s.get_shot_deltas());
}

TEST(SessionStaticTests, convert_time_to_seconds) {
	ASSERT_DOUBLE_EQ(0.00, Session::convert_time_to_seconds(0));
	ASSERT_DOUBLE_EQ(0.99, Session::convert_time_to_seconds(981111));
	ASSERT_DOUBLE_EQ(1.00, Session::convert_time_to_seconds(1000000));
	ASSERT_DOUBLE_EQ(1.99, Session::convert_time_to_seconds(1981111));
	ASSERT_DOUBLE_EQ(2.00, Session::convert_time_to_seconds(2000000));
	ASSERT_DOUBLE_EQ(2.99, Session::convert_time_to_seconds(2981111));
}

TEST_F(SessionTests, time_relative_to_start) {
	int start_time = 100;
	_s.start_new_session(start_time);
	uint64_t time1 = 110;
	uint64_t time2 = 125;
	uint64_t time3 = 145;
	_s.add_shot(time1);
	_s.add_shot(time2);
	_s.add_shot(time3);
	_expected_shot_times.emplace_back(time1 - 100);
	_expected_shot_times.emplace_back(time2 - 100);
	_expected_shot_times.emplace_back(time3 - 100);
	_expected_shot_deltas.emplace_back(time1 - start_time);
	_expected_shot_deltas.emplace_back(time2 - time1);
	_expected_shot_deltas.emplace_back(time3 - time2);

	ASSERT_EQ(time3 - start_time, _s.get_last_shot_time());
	ASSERT_EQ(3, _s.get_shot_count());
	ASSERT_EQ(_expected_shot_times, _s.get_shots());
	ASSERT_EQ(_expected_shot_deltas, _s.get_shot_deltas());
}
