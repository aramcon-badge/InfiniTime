#pragma once

#include <cstdint>
#include "app_timer.h"

namespace Pinetime {
  namespace Controllers {
    static constexpr uint8_t pinMotor = 16;

    class MotorController {
    public:
      MotorController() = default;

      void Init();
      void RunForDuration(uint8_t motorDuration);
      void StartRinging();
      static void StopRinging();

    private:
      static void Ring(void* p_context);
      static void StopMotor(void* p_context);
    };
  }
}
