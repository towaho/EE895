/* 
 * Please note: The CRC16 shall be calculated including the unshifted slave address.
 *
 * Example of command reading the temperature (floating point value) T = 25.30 °C from the register 0x3EA:
 *
 * Request [Hex]:  S BE 03 03 EA 00 02 E8 C5 P
 * +-------+---------------+----------+------------+------------+-------------+-------------+-------+------+
 * | START | Slave address | Function |  Starting  | Starting   |    No. of   |    No. of   |  CRC  | STOP |
 * |       | 7-bit shifted |   code   | address Hi | address Lo | register Hi | register Lo |       |      |
 * +-------+---------------+----------+------------+------------+-------------+-------------+-------+------+
 * |   S   |      BE       |    03    |    03      |     EA     |     00      |     02      | E8 C5 |  P   |
 * +-------+---------------+----------+------------+------------+-------------+-------------+-------+------+
 *
 * Response [Hex]: S BF 03 04 00 00 41 DC 74 3F P
 * +-------+---------------+----------+-------+------------+------------+------------+------------+-------+------+
 * | START | Slave address | Function | Byte  | Register 1 | Register 1 | Register 2 | Register 2 |  CRC  | STOP |
 * |       | 7-bit shifted |   code   | count |  value Hi  |  value Lo  |  value Hi  |  value Lo  |       |      |
 * +-------+---------------+----------+-------+------------+------------+------------+------------+-------+------+
 * |   S   |      BF       |    03    |  04   |    00      |     00     |    41      |    DC      | 74 3F |  P   |
 * +-------+---------------+----------+-------+------------+------------+------------+------------+-------+------+
 *
 *  For decoding of float values stored according standard IEEE 754, please refer also to the Modbus Application Note AN0103.
 *
 *  Example of Decoding:
 * +-------------------+-------------------+-------------------+-------------------+---------------+
 * |       Byte 1      |       Byte 2      |       Byte 3      |       Byte 4      | Decimal value |
 * | (Register 2 - Hi) | (Register 2 – Lo) | (Register 1 - Hi) | (Register 1 - Lo) |               |
 * +-------------------+-------------------+-------------------+-------------------+---------------+
 * |         41        |         DC        |         00        |         00        |     27.50     |
 * +-------------------+-------------------+-------------------+-------------------+---------------+
 *
 */

#include <ArduinoUnitTests.h>
#include "EE895.h"

EE895 sensor = EE895();

unittest(crcTestSent)
{
  uint16_t crc = sensor.updateCRC(0xBE>>1);
  crc = sensor.updateCRC(0x03, crc);
  crc = sensor.updateCRC(0x03, crc);
  crc = sensor.updateCRC(0xEA, crc);
  crc = sensor.updateCRC(0x00, crc);
  crc = sensor.updateCRC(0x02, crc);
  uint16_t crcExpected = 0xC5E8;
  assertEqual(crcExpected, crc);
}

unittest(crcTestReceived)
{
  uint16_t crc = sensor.updateCRC(0xBF>>1);
  crc = sensor.updateCRC(0x03, crc);
  crc = sensor.updateCRC(0x04, crc);
  crc = sensor.updateCRC(0x00, crc);
  crc = sensor.updateCRC(0x00, crc);
  crc = sensor.updateCRC(0x41, crc);
  crc = sensor.updateCRC(0xDC, crc);
  uint16_t crcExpected = 0x3F74;
  assertEqual(crcExpected, crc);
}

unittest_main()
