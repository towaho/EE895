#ifndef __EE895_ARDUINO_LIBARARY_H__
#define __EE895_ARDUINO_LIBARARY_H__

#include "Arduino.h"
#include <Wire.h>

#define EE895_ADDRESS_MODBUS 0x5F


class EE895 {
  public:
    EE895(void);

    uint16_t calculateCRC(const unsigned char* data, size_t length);

  private:
};

#endif /* !__EE895_ARDUINO_LIBARARY_H__ */
