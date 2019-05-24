#pragma once

typedef int hours;
typedef int minutes;
typedef struct timeOfDay {
  hours hour;
  minutes minute;
  bool operator<(const timeOfDay& timeB) {
    if (this->hour < timeB.hour) return true;
    if (this->hour > timeB.hour) return false;
    if (this->minute < timeB.minute) return true;
    return false;
  }
  minutes toMinutes() { return this->hour * 60 + this->minute; }
} timeOfDay;
