#pragma once

#include <cstdint>

namespace Pinetime {
  namespace Controllers {
    class MotionController {
    public:
      void Update(int16_t x, int16_t y, int16_t z, uint32_t nbSteps);

      int16_t X() const {
        return x;
      }
      int16_t Y() const {
        return y;
      }
      int16_t Z() const {
        return z;
      }
      uint32_t NbSteps() const {
        return nbSteps;
      }
      bool ShouldWakeUp(bool isSleeping);

      void IsSensorOk(bool isOk);
      bool IsSensorOk() const {
        return isSensorOk;
      }

    private:
      uint32_t nbSteps;
      int16_t x;
      int16_t y;
      int16_t z;
      int16_t lastYForWakeUp = 0;
      bool isSensorOk = false;
    };
  }
}