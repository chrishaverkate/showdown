#include <gtest/gtest.h>

#include <views/view.h>
#include <ControllerImpl.h>

#include <memory>

using std::make_unique;
using std::move;
using std::unique_ptr;

class FakeHomeView : public View {
public:
	void draw() override {
		_drawn = true;
	}

	bool is_drawn() const {
		return _drawn;
	}

	bool _drawn = false;
};

class FakeSpecialView : public View {
public:
	void draw() override {
		_drawn = true;
	}

	bool is_drawn() const {
		return _drawn;
	}

	bool _drawn = false;
};

class ControllerImplTests : public ::testing::Test {
protected:
	void SetUp() override {
	}

	void TearDown() override {
	}

	ControllerImpl _c;
	std::unique_ptr<FakeHomeView> view_fake_home = std::make_unique<FakeHomeView>();
	std::unique_ptr<FakeSpecialView> view_fake_special = std::make_unique<FakeSpecialView>();
};

TEST_F(ControllerImplTests, add_view) {
	// Workaround to keep a ref to the fake view to assert against later.
	auto my_home = view_fake_home.get();

	_c.add_view(move(view_fake_home));
	_c.draw_current_view();

	EXPECT_TRUE(my_home->is_drawn());
}

TEST_F(ControllerImplTests, add_view_multiple_views_and_draw_first_view) {
	auto my_home = view_fake_home.get();
	_c.add_view(move(view_fake_home));
	_c.add_view(move(view_fake_special));

	_c.draw_current_view();

	EXPECT_TRUE(my_home->is_drawn());
}

TEST_F(ControllerImplTests, press_right_switches_view_and_wrapps_to_first_view) {
	auto my_home = view_fake_home.get();
	auto my_special = view_fake_special.get();
	_c.add_view(move(view_fake_home));
	_c.add_view(move(view_fake_special));

	_c.button_pressed_right(10);
	_c.draw_current_view();
	EXPECT_TRUE(my_special->is_drawn());

	_c.button_pressed_right(10);
	_c.draw_current_view();
	EXPECT_TRUE(my_home->is_drawn());
}

TEST_F(ControllerImplTests, press_left_switches_view_and_wrapps_to_first_view) {
	auto my_home = view_fake_home.get();
	auto my_special = view_fake_special.get();
	_c.add_view(move(view_fake_home));
	_c.add_view(move(view_fake_special));

	_c.button_pressed_left(10);
	_c.draw_current_view();
	EXPECT_TRUE(my_special->is_drawn());

	_c.button_pressed_left(10);
	_c.draw_current_view();
	EXPECT_TRUE(my_home->is_drawn());
}
