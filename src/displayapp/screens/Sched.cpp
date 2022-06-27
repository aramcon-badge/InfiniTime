#include <ctime>
#include <array>
#include <chrono>

#include "displayapp/TouchEvents.h"
#include "displayapp/screens/Sched.h"
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

#include "schedule_events.h"

// TODO: Set alarms for each entry

static auto constexpr INSTRUCTIONS = "<- ->";

static std::chrono::system_clock::time_point time_point_from_tm(std::tm const& date) {
  auto tmp_date = date;
  return std::chrono::system_clock::from_time_t(std::mktime(&tmp_date));
}

namespace Pinetime::Applications::Screens {

  Schedule::Schedule(DisplayApp* app)
    : Screen {app},
      scroll_index {0},
      entry_what_label {::lv_label_create(lv_scr_act(), nullptr)},
      entry_where_label {::lv_label_create(lv_scr_act(), nullptr)},
      entry_when_label {::lv_label_create(lv_scr_act(), nullptr)},
      entry_length_label {::lv_label_create(lv_scr_act(), nullptr)},
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

    for (auto const& [label, mode] : {std::make_tuple(this->entry_what_label, ::LV_LABEL_LONG_BREAK),
                                      std::make_tuple(this->entry_where_label, ::LV_LABEL_LONG_SROLL_CIRC)}) {
      ::lv_label_set_long_mode(label, mode);
      ::lv_obj_set_width(label, LV_HOR_RES);
    }

    auto y_offset = ::lv_coord_t {0};
    for (auto const& label : {this->entry_when_label, this->entry_where_label, this->entry_length_label, this->entry_what_label}) {
      ::lv_obj_align(label, nullptr, ::LV_ALIGN_IN_TOP_LEFT, 0, y_offset);
      y_offset += 20;
    }

    this->refreshText();

    ::lv_label_set_text_static(this->instructions_label, INSTRUCTIONS);
    ::lv_obj_align(this->instructions_label, nullptr, ::LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    ::lv_obj_set_width(this->instructions_label, LV_HOR_RES);


    Pinetime::Controllers::Ctf* ctfController = Pinetime::Controllers::Ctf::getInstance();
    if (!ctfController->checkSolve(2)) {
      ctfController->addSolve(2);

      ::lv_obj_t* ctf_flag_solved_label = lv_label_create(lv_scr_act(), nullptr);
      ::lv_label_set_recolor(ctf_flag_solved_label, true);
      ::lv_label_set_text_static(ctf_flag_solved_label, "#30c803 GOT FLAG#");
      ::lv_obj_align(ctf_flag_solved_label, nullptr, ::LV_ALIGN_CENTER, 0, 0);
    }
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

    ::lv_label_set_text(this->entry_what_label, entry.what);
    ::lv_label_set_text(this->entry_when_label, formatted_date_buffer.data());
    ::lv_label_set_text(this->entry_where_label, entry.where);
    ::lv_label_set_text_fmt(this->entry_length_label, "%d minutes", entry.length.count());
  }
}
