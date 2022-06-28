#pragma message("[!] This is a default schedule to avoid build errors - GENERATE FROM REAL ICS") 

static std::array<Entry, 4> constexpr SCHEDULE = {
	Entry{
		.what = "Planning",
		.where = "Cave",
		.when = std::tm {
			.tm_min = 0,
			.tm_hour= 10,
			.tm_mday= 1,
			.tm_mon= 1,
			.tm_year= 119,
		},
		.length = 120min,
	},
	Entry{
		.what = "Opening",
		.where = "Underworld",
		.when = std::tm {
			.tm_min = 0,
			.tm_hour= 10,
			.tm_mday= 1,
			.tm_mon= 1,
			.tm_year= 123,
		},
		.length = 30min,
	},
	Entry{
		.what = "some lecture",
		.where = "building",
		.when = std::tm {
			.tm_min = 30,
			.tm_hour= 10,
			.tm_mday= 1,
			.tm_mon= 1,
			.tm_year= 123,
		},
		.length = 60min,
	},
	Entry{
		.what = "Ending",
		.where = "Outer space",
		.when = std::tm {
			.tm_min = 30,
			.tm_hour= 10,
			.tm_mday= 2,
			.tm_mon= 1,
			.tm_year= 123,
		},
		.length = 10min,
	},
};
