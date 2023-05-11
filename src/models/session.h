#pragma once
#include <cstdint>
#include <cstdlib>
#include <vector>

class Session {
public:
	constexpr static const uint64_t MICROSECONDS_PER_SECOND = 1000000;

	void start_new_session(uint64_t time);

	[[nodiscard]] uint64_t get_last_shot_time() const;
	[[nodiscard]] unsigned int get_shot_count() const;

	[[nodiscard]] const std::vector<uint64_t>& get_shots() const;
	[[nodiscard]] const std::vector<uint64_t>& get_shot_deltas() const;

	void add_shot(uint64_t time);

	static double convert_time_to_seconds(uint64_t time);

protected:
	std::vector<uint64_t> _shots {};
	std::vector<uint64_t> _shot_deltas {};
	uint64_t _start_time = 0;
};
