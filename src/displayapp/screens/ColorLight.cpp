#include "displayapp/screens/ColorLight.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Symbols.h"
#include "components/ble/BleController.h"
#include "displayapp/TouchEvents.h"
#include <cstdlib>
#include <nrf_log.h>
#include <random>

using namespace Pinetime::Applications::Screens;


ColorLight::ColorLight(Pinetime::Applications::DisplayApp* app,
                       System::SystemTask& systemTask,
                       Controllers::BrightnessController& brightnessController,
                       Controllers::Ble& bleController)
  : Screen(app),
    systemTask {systemTask},
    brightnessController {brightnessController},
    bleController {bleController}
{
  brightnessController.Backup();

  brightnessLevel = brightnessController.Level();

  systemTask.PushMessage(Pinetime::System::Messages::DisableSleeping);

  brightnessLevel = Controllers::BrightnessController::Levels::High;
  brightnessController.Set(brightnessLevel);
  SetColors();
}

ColorLight::~ColorLight() {
  lv_obj_clean(lv_scr_act());
  lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

  brightnessController.Restore();
  systemTask.PushMessage(Pinetime::System::Messages::EnableSleeping);
}

void ColorLight::SetColors() {

    lv_color_t colors[8] = {
      LV_COLOR_RED    ,
      LV_COLOR_YELLOW ,
      LV_COLOR_GREEN  ,
      LV_COLOR_CYAN   ,
      LV_COLOR_BLUE   ,
      LV_COLOR_MAGENTA,
      LV_COLOR_PURPLE ,
      LV_COLOR_ORANGE ,
    };

    auto& bleAddr = bleController.Address();

    uint32_t ble_sum = 0;
    for (uint32_t i=0; i<6;i ++)
    {
      ble_sum += bleAddr[i];
    }

    lv_obj_set_style_local_bg_color(lv_scr_act(), 
                                    LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 
                                    colors[ble_sum % 8]);
}

bool ColorLight::OnTouchEvent(TouchEvents event) {
    switch (event) {
      case TouchEvents::Tap:
        randomColor = LV_COLOR_MAKE(rand() % 255, rand() % 255, rand() % 255);
        lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, randomColor);
        break;
      default:
        break;
    }
    return true;
  }
