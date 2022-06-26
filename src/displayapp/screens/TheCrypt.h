#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

#include "displayapp/screens/Screen.h"
#include "displayapp/screens/TheCryptImage.h"
#include <lvgl/lvgl.h>
#include "components/datetime/DateTimeController.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class TheCrypt : public Screen {
      public:
        explicit TheCrypt(DisplayApp* app, Controllers::DateTime& dateTimeController);
        ~TheCrypt() override;

      private:
        DirtyValue<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime {};
        int timePointToTimestamp(std::chrono::system_clock::time_point& tp );
        int checkDate(Controllers::DateTime& dateTimeController);
      };
    }
  }
}
