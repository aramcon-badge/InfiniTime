#pragma once

#include "displayapp/screens/Screen.h"
#include "components/brightness/BrightnessController.h"
#include "components/datetime/DateTimeController.h"
#include "systemtask/SystemTask.h"
#include <cstdint>
#include <lvgl/lvgl.h>

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class ColorLight : public Screen {
      public:
        ColorLight(DisplayApp* app, System::SystemTask& systemTask, Controllers::BrightnessController& brightness,
                   Controllers::DateTime& dateTimeController);
        ~ColorLight() override;

      private:
        void SetColors();

        Pinetime::System::SystemTask& systemTask;
        Controllers::BrightnessController& brightnessController;

        Controllers::BrightnessController::Levels brightnessLevel;
      };
    }
  }
}
