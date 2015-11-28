#ifndef RTC_H
#define RTC_H

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

/**
 * @brief Reads from RTC's registers
 *
 * @param address Address of the register to read from
 * @param result Where to store the result
 *
 * @return Returns 0 on success, returning non-zero otherwise
 */
int read_from_RTC(unsigned char address, unsigned char *result);

/**
 * @brief Writes to RTC's registers
 *
 * @param address Address of the register to write to
 * @param write What to write
 *
 * @param Returns 0 on success, returning non-zero otherwise
 */
int write_to_RTC(unsigned char address, unsigned char write);

#endif
