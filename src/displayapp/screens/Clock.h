#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "Screen.h"
#include "ScreenList.h"
#include "components/datetime/DateTimeController.h"

namespace Pinetime {
  namespace Drivers {
    class BMA421;
  }
  namespace Controllers {
    class Settings;
    class Battery;
    class Ble;
    class NotificationManager;
    class MotionController;
  }

  namespace Applications {
    namespace Screens {
      class Clock : public Screen {
        public:
          Clock(DisplayApp* app,
                  Controllers::DateTime& dateTimeController,
                  Controllers::Battery& batteryController,
                  Controllers::Ble& bleController,
                  Controllers::NotificationManager& notificatioManager,
                  Controllers::Settings &settingsController,
                  Controllers::HeartRateController& heartRateController,
                  Controllers::MotionController& motionController);
          ~Clock() override;

          bool Refresh() override;
          bool OnButtonPushed() override;
          bool OnTouchEvent(TouchEvents event) override;

        private:

          Controllers::DateTime& dateTimeController;
          Controllers::Battery& batteryController;
          Controllers::Ble& bleController;
          Controllers::NotificationManager& notificatioManager;
          Controllers::Settings& settingsController;
          Controllers::HeartRateController& heartRateController;
          Controllers::MotionController& motionController;


          ScreenList<2> screens;
          std::unique_ptr<Screen> WatchFaceDigitalScreen();
          std::unique_ptr<Screen> WatchFaceAnalogScreen();

          // Examples for more watch faces
          //std::unique_ptr<Screen> WatchFaceMinimalScreen();
          //std::unique_ptr<Screen> WatchFaceCustomScreen();

          bool running = true;

      };
    }
  }
}
