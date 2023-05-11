#include "session.h"

#include <cstdio>
#include <cmath>

using std::vector;

uint64_t Session::get_last_shot_time() const {
	if(_shots.empty()) {
		return 0;
	}
	return _shots.back();
}

unsigned int Session::get_shot_count() const {
	return _shots.size();
}

const vector<uint64_t>& Session::get_shots() const {
	return _shots;
}

void Session::add_shot(uint64_t time) {
	uint64_t relative_time = time - _start_time; // adjust to the start of the session
	_shot_deltas.push_back(relative_time - get_last_shot_time());
	_shots.push_back(relative_time);
}

const vector<uint64_t>& Session::get_shot_deltas() const {
	return _shot_deltas;
}

double Session::convert_time_to_seconds(uint64_t time) {
	double rounded_value = std::ceil(static_cast<double>(time) / MICROSECONDS_PER_SECOND * 100) / 100;
	return rounded_value;
}

void Session::start_new_session(uint64_t time) {
	printf("\tStarting new session at %llu\n", time);
	_shots.clear();
	_shot_deltas.clear();
	_start_time = time;
}
