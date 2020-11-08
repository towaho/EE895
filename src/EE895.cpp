#include "EE895.h"

EE895::EE895(){
}

uint16_t EE895::updateCRC(uint16_t data, uint16_t crc) {
  return EE895::updateCRC((uint8_t)data, EE895::updateCRC((uint8_t)(data >> 8), crc));
}

uint16_t EE895::updateCRC(uint8_t data, uint16_t crc) {
  crc ^= data;
  for (uint8_t bit = 8; bit > 0; bit--) {
    if ((crc & 0x0001) != 0) {
      crc >>= 1;
      crc ^= 0xA001;
    }
    else
      crc >>= 1;
  }
  return crc;
}
