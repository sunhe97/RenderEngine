//
// Created by SunHe on 2023/7/30.
//

#pragma once

namespace Hazel {
  class Timestep {
  public:
    Timestep(float time = 0.0f) : m_Time(time) {}
    ~Timestep() = default;

    operator float() const { return m_Time; }

    // Returns time in seconds
    float GetSeconds() const { return m_Time; }
    // Returns time in milliseconds
    float GetMilliseconds() const { return m_Time * 1000.0f; }

  private:
    float m_Time;
  };
}