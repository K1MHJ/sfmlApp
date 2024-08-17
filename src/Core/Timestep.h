#pragma once

class Timestep {
public:
  Timestep(uint64_t time_msec = 0.0f) : m_Time_msec(time_msec) {}

  operator uint64_t() const { return m_Time_msec; }

  uint64_t GetSeconds() const { return m_Time_msec / 1000; }
  uint64_t GetMilliseconds() const { return m_Time_msec; }

private:
  uint64_t m_Time_msec;
};
