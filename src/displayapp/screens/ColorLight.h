#pragma once

#include "displayapp/screens/Screen.h"
#include "components/brightness/BrightnessController.h"
#include "components/ble/BleController.h"
#include "systemtask/SystemTask.h"
#include <cstdint>
#include <lvgl/lvgl.h>

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class ColorLight : public Screen {
      public:
        ColorLight(DisplayApp* app, System::SystemTask& systemTask, Controllers::BrightnessController& brightness,
                   Controllers::Ble& bleController);
        bool OnTouchEvent(TouchEvents event) override;
        ~ColorLight() override;

      private:
        void SetColors();

        lv_color_t randomColor;
        Pinetime::System::SystemTask& systemTask;
        Controllers::BrightnessController& brightnessController;
        Controllers::Ble& bleController;

        Controllers::BrightnessController::Levels brightnessLevel;
      };
    }
  }
}
