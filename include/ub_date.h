/**
 * @file ub_date.h
 * @brief Header file for the UbDate struct and related functions 
 */

#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


/**
 * @brief Struct that represents a date
 * in a straightforward way and little space
 */
typedef struct {
	uint16_t year; ///< year starting at 0
	uint8_t mon; ///< month number 1-12
	uint8_t day; ///< day number 1-31
} UbDate;


/**
 * @brief Converts an UbDate into a number with format yyyymmdd
 * @param date UbDate to convet
 * @return A number representing the date
 */
uint32_t UbDate_to_int(UbDate date);

/**
 * @brief Converts an integer with format yyymmdd into an UbDate
 */
UbDate int_to_UbDate(uint32_t date);

/**
 * @brief Converts an UbDate into a tm struct.
 * The tm_sec, tm_min and tm_hour fields are set to 0.
 * @param date UbDate to convert
 * @return A tm struct representig the date. It must be freed.
 */
struct tm* UbDate_to_tm(UbDate date);

/**
 * @brief Converts a tm struct into an UbDate.
 * @param tm tm struct to convert @return A  c representig the date. It must be freed.
 * @return An UbDate representig the date.
 */
UbDate tm_to_UbDate(const struct tm* tm);


/**
 * @brief Compares two dates
 * @return The difference in days between date1 and date2 (date1-date2), 0 if they are equal. 
 */
int cmp_UbDate(UbDate date1, UbDate date2);
