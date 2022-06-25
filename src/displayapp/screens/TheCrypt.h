#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class TheCrypt : public Screen {
      public:
        TheCrypt(DisplayApp* app);
        ~TheCrypt() override;
      };
    }
  }
}