#include <gtest/gtest.h>

#include <controller_impl.h>
#include <views/view.h>
#include <views/home.h>

#include <memory>

using std::make_shared;
using std::make_unique;
using std::move;
using std::shared_ptr;
using std::unique_ptr;

class FakeScreen : public Screen {
public:
	void clear() override {
	}
	void draw_line(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint8_t thickness) override {
	}
	void draw_header(std::string string) override {
	}
	void draw_divider_horizontal(uint8_t position_px, uint8_t thickness) override {
	}
	void draw_divider_vertical(uint8_t position_px, uint8_t thickness) override {
	}
	void draw_text(std::string text, uint8_t x, uint8_t y, FontSize size) override {
	}
	void draw_circle(uint8_t center_x, uint8_t center_y, uint8_t radius, Color color) override {
	}
	unsigned int get_width() override {
		return 0;
	}
	unsigned int get_height() override {
		return 0;
	}
};

class FakeHomeView : public Home {
public:
	FakeHomeView(shared_ptr<Session> session, shared_ptr<Screen> screen)
		: Home(session, screen) {

	}
	void draw() override {
		_drawn = true;
	}

	void clear() override {

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

	void clear() override {

	}

	bool is_drawn() const {
		return _drawn;
	}

	bool _drawn = false;
};

class FakeSession : public Session {

};

class ControllerImplTests : public ::testing::Test {
protected:
	void SetUp() override {
	}

	void TearDown() override {
	}

	ControllerImpl _c;
	shared_ptr<FakeScreen> screen = std::make_shared<FakeScreen>();
	shared_ptr<FakeSession> session = std::make_shared<FakeSession>();
	unique_ptr<FakeHomeView> view_fake_home = std::make_unique<FakeHomeView>(session, screen);
	unique_ptr<FakeSpecialView> view_fake_special = std::make_unique<FakeSpecialView>();
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

//TEST_F(ControllerImplTests, session_testing) {
//	auto my_home = view_fake_home.get();
//
//	_c.add_view(move(view_fake_home));
//	_c.draw_current_view();
//	_c.shot_detected(10);
//
//	EXPECT_TRUE(my_home->is_drawn());
//}
