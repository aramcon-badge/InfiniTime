#include <ctime>

#include "displayapp/TouchEvents.h"
#include "displayapp/screens/Sched.hpp"
#include "displayapp/DisplayApp.h"
#include "lvgl/src/lv_core/lv_disp.h"
#include "lvgl/src/lv_core/lv_obj.h"
#include "lvgl/src/lv_misc/lv_area.h"
#include "lvgl/src/lv_widgets/lv_label.h"

struct Entry {
  const char* what;
  const char* where;
  ::time_t when;
};

static constexpr std::array<Entry, 3> SCHEDULE = {
  // TODO: Fill with real entries
  Entry {"Opening", "Lobby", 0},
  Entry {"Some lecture", "Some room", 0},
  Entry {"Ending", "Lobby", 0},
};

// TODO: Set alarms for each entry
// TODO: Filter out events from the past

static auto constexpr INSTRUCTIONS = "<-- NEXT\n--> PREV";

namespace Pinetime::Applications::Screens {

  Schedule::Schedule(DisplayApp* app)
    : Screen {app},
      sched_entry_label {::lv_label_create(lv_scr_act(), nullptr)},
      instructions_label {::lv_label_create(lv_scr_act(), nullptr)} {

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
    auto const& entry = SCHEDULE.at(this->scroll_index);
    ::lv_label_set_text_fmt(this->sched_entry_label, "%s %s %d", entry.what, entry.where, entry.when);
  }
}
