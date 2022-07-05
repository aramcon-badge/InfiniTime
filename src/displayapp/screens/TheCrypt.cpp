#include "displayapp/screens/TheCrypt.h"
#include "displayapp/DisplayApp.h"

using namespace Pinetime::Applications::Screens;

// 4 Ajaw 8 Kumk’u 
static auto constexpr DEFAULT = "The Crypt Will\nOpen On The\nDay of Reckoning";
static auto constexpr LAST_CREATION = "Arise, shine,\nfor your light \nhas come,\nand the glory\nof the Lord has\nrisen upon you.";
static auto constexpr OBLIVION = "Wail, for the\nday of the\nLord is near;\nas destruction from\nthe Almighty it\nwill come!";

static size_t quirigua_dimension = 64;
static lv_img_dsc_t quirigua;


namespace Pinetime::Applications::Screens {

  TheCrypt::TheCrypt(DisplayApp* app, Controllers::DateTime& dateTimeController) : Screen(app) {
    int image_offset = 50;

    lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);

    switch(checkDate(dateTimeController)) {
      case 0:
        lv_label_set_text_static(title, LAST_CREATION); 
        lv_obj_align(title, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 10);
        image_offset = 70;
        break;
      case 1:
        lv_label_set_text_static(title, OBLIVION);
        lv_obj_align(title, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 10);
        image_offset = 70;
        break;
      case 2:
        lv_label_set_text_static(title, DEFAULT);
        lv_obj_align(title, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 30);
        image_offset = 50;
        break;
    };
    
    

  quirigua.header.always_zero = 0;
  quirigua.header.w = quirigua_dimension;
  quirigua.header.h = quirigua_dimension;
  quirigua.data_size = quirigua.header.w * quirigua.header.h * LV_COLOR_SIZE / 8;
  quirigua.header.cf = LV_IMG_CF_TRUE_COLOR;
  quirigua.data = long_count;

  lv_obj_t *quirigua_img = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(quirigua_img, &quirigua);
  lv_obj_align(quirigua_img, lv_scr_act(), LV_ALIGN_CENTER, 0, image_offset);
  }

  TheCrypt::~TheCrypt() {
    lv_obj_clean(lv_scr_act());
  }

  int TheCrypt::timePointToTimestamp(std::chrono::system_clock::time_point& tp ) {
      using namespace date;

      sys_days unix_epoch = day(1)/jan/1970;
      days days_since_epoch = floor<days>(tp) - unix_epoch;

      auto secs = tp - floor<days>(tp);
      auto tz_offset = std::chrono::hours(0);

      return (days_since_epoch + secs + tz_offset) / std::chrono::seconds(1);
  }


  int TheCrypt::checkDate(Controllers::DateTime& dateTimeController) {
    unsigned int hour_begin, hour_end, unix_timestamp;

    std::tm four_ahau_eight_kumku = {};
    four_ahau_eight_kumku.tm_year = 112;
    four_ahau_eight_kumku.tm_mon = 11;
    four_ahau_eight_kumku.tm_mday = 21;
    four_ahau_eight_kumku.tm_hour = 13;
    four_ahau_eight_kumku.tm_min = 37;
    four_ahau_eight_kumku.tm_isdst = 0;
	  std::time_t armageddon = mktime(&four_ahau_eight_kumku);

    currentDateTime = dateTimeController.CurrentDateTime();

    if (currentDateTime.IsUpdated()) {
      auto newDateTime = currentDateTime.Get();

      auto dp = date::floor<date::days>(newDateTime);
      auto yearMonthDay = date::year_month_day(dp);

      unix_timestamp = timePointToTimestamp(newDateTime);

      auto year = static_cast<int>(yearMonthDay.year());
      auto month = static_cast<unsigned>(static_cast<unsigned>(yearMonthDay.month()));
      auto day = static_cast<unsigned>(yearMonthDay.day());

      if (year == 2012 && month == 12 && day == 21) {
        return 1;
      }
      
      hour_begin = armageddon;
      four_ahau_eight_kumku.tm_hour += 1;
      hour_end = mktime(&four_ahau_eight_kumku);

      if (hour_begin <= unix_timestamp && unix_timestamp <= hour_end) {
        Pinetime::Controllers::Ctf* ctfController = Pinetime::Controllers::Ctf::getInstance();
        ctfController->addSolve(4);
        return 0;
      }
    }
    return 2;
  }
}
