#include <ctime>
#include <array>
#include <chrono>

#include "displayapp/TouchEvents.h"
#include "displayapp/screens/Sched.hpp"
#include "displayapp/DisplayApp.h"
#include "lvgl/src/lv_core/lv_disp.h"
#include "lvgl/src/lv_core/lv_obj.h"
#include "lvgl/src/lv_misc/lv_area.h"
#include "lvgl/src/lv_widgets/lv_label.h"

using namespace std::literals::chrono_literals;

struct Entry {
  const char* what;
  const char* where;
  std::tm when;
  std::chrono::minutes length;
};

static constexpr int year_for_tm(int year) {
  return year - 1900;
}

static constexpr std::array<Entry, 4> SCHEDULE = {
  // TODO: Fill with real entries
  Entry {
    "Planing",
    "Bar",
    std::tm {
      .tm_min = 30,
      .tm_hour = 10,
      .tm_mday = 01,
      .tm_mon = 01,
      .tm_year = year_for_tm(2021),
    },
    60min,
  },
  Entry {
    "Opening",
    "Lobby",
    std::tm {
      .tm_min = 30,
      .tm_hour = 10,
      .tm_mday = 1,
      .tm_mon = 8,
      .tm_year = year_for_tm(2022),
    },
    60min,
  },
  Entry {
    "Some lecture",
    "Some room",
    std::tm {
      .tm_min = 45,
      .tm_hour = 13,
      .tm_mday = 1,
      .tm_mon = 8,
      .tm_year = year_for_tm(2022),
    },
    120min,
  },
  Entry {
    "Ending",
    "Lobby",
    std::tm {
      .tm_min = 30,
      .tm_hour = 10,
      .tm_mday = 3,
      .tm_mon = 8,
      .tm_year = year_for_tm(2022),
    },
    10min,
  },
};

// TODO: Set alarms for each entry

static auto constexpr INSTRUCTIONS = "<-- NEXT\n--> PREV";

static std::chrono::system_clock::time_point time_point_from_tm(std::tm const& date) {
  auto tmp_date = date;
  return std::chrono::system_clock::from_time_t(std::mktime(&tmp_date));
}

namespace Pinetime::Applications::Screens {

  Schedule::Schedule(DisplayApp* app)
    : Screen {app},
      scroll_index {0},
      sched_entry_label {::lv_label_create(lv_scr_act(), nullptr)},
      instructions_label {::lv_label_create(lv_scr_act(), nullptr)} {

    // Find first event that didn't conclude yet
    while (true) {
      if (this->scroll_index == SCHEDULE.size() - 1) {
        break;
      }

      auto const& entry = SCHEDULE.at(this->scroll_index);

      if (time_point_from_tm(entry.when) + entry.length >= std::chrono::system_clock::now()) {
        break;
      }

      ++this->scroll_index;
    }

    ::lv_obj_align(this->sched_entry_label, nullptr, ::LV_ALIGN_IN_TOP_LEFT, 0, 0);
    ::lv_label_set_long_mode(this->sched_entry_label, ::LV_LABEL_LONG_BREAK);
    ::lv_obj_set_width(this->sched_entry_label, LV_HOR_RES);
    this->refreshText();

    ::lv_label_set_text_static(this->instructions_label, INSTRUCTIONS);
    ::lv_obj_align(this->instructions_label, nullptr, ::LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    ::lv_obj_set_width(this->instructions_label, LV_HOR_RES);
  }

  Schedule::~Schedule() {
    ::lv_obj_clean(::lv_scr_act());
  }

  bool Schedule::OnTouchEvent(TouchEvents event) {
    switch (event) {
      case TouchEvents::SwipeLeft:
        this->scroll_index += 1;
        break;
      case TouchEvents::SwipeRight:
        if (this->scroll_index == 0) {
          this->scroll_index = SCHEDULE.size() - 1;
        } else {
          this->scroll_index -= 1;
        }
        break;
      default:
        break;
    }
    this->scroll_index %= SCHEDULE.size();

    this->refreshText();

    return false;
  }

  void Schedule::refreshText() {
    auto formatted_date_buffer = std::array<char, 0x50> {};
    auto const& entry = SCHEDULE.at(this->scroll_index);
    (void) std::strftime(formatted_date_buffer.data(), formatted_date_buffer.size(), "%d/%m %H:%M", &entry.when);

    ::lv_label_set_text_fmt(
      this->sched_entry_label, "%s\n%d minutes\n%s %s", formatted_date_buffer.data(), entry.length.count(), entry.what, entry.where);
  }
}
