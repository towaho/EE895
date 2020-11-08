#include "EE895.h"

EE895::EE895(){
}

uint16_t EE895::calculateCRC(const unsigned char* data, size_t length){
  uint16_t crc = 0xFFFF;

  for (size_t pos = 0; pos < length; pos++) {
    crc ^= (uint16_t)data[pos];
    for (uint8_t bit = 8; bit > 0; bit--) {
      if ((crc & 0x0001) != 0) {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
        crc >>= 1;
    }
  }
  return crc;
}
