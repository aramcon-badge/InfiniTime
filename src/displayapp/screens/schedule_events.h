static std::array<Entry, 1> constexpr SCHEDULE = {
	Entry{
		.what = "Doing Something",
		.where = "Somewhere",
		.when = std::tm {
			.tm_min = 0,
			.tm_hour= 6,
			.tm_mday= 29,
			.tm_mon= 6,
			.tm_year= 122,
		},
		.length = 100min
	}
};
