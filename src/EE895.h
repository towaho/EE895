#ifndef __EE895_ARDUINO_LIBARARY_H__
#define __EE895_ARDUINO_LIBARARY_H__

#include "Arduino.h"
#include <Wire.h>

#define EE895_ADDRESS_MODBUS 0x5F


class EE895 {
  public:
    EE895(void);

    uint16_t updateCRC(uint8_t data, uint16_t crc = 0xFFFF);

  private:
};

#endif /* !__EE895_ARDUINO_LIBARARY_H__ */
