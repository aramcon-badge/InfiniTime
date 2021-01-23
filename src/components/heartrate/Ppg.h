#pragma once

#include <array>
#include "Biquad.h"
#include "Ptagc.h"

namespace Pinetime {
  namespace Controllers {
    class Ppg {
    public:
      explicit Ppg(float spl);

      int Preprocess(float spl);
      float HeartRate();

      void SetOffset(uint16_t i);
      void Reset();

    private:
      std::array<int, 200> data;
      size_t dataIndex = 0;
      float offset;
      Biquad hpf;
      Ptagc agc;
      Biquad lpf;


      float ProcessHeartRate();
    };
  }
}