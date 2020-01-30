/** @file itemp.h
 * itemp provides a compact representation of temperature and uses integer
 * arithmentic to convert between Celsius and Fahrenheit with accuracy down to
 * 0.01 degree.
 *
 * itemp allows easy manipulation and conversion of temperatures:
 *
 * @code
 * itemp_t itemp = fahrenheit_1_to_itemp(70);  // 70 degrees F
 * itemp -= ITEMP_ONE_DEGREE_F * 2;            // 68 degrees F
 * int16_t f = itemp_to_fahrenheit_1(itemp);   // convert to degrees F
 * int16_t c = itemp_to_celsius_1(itemp);      // convert to degrees C
 * printf("Temperature is %dF (%dC)\n", f, c);
 * @code
 *
 * @author R. Dunbar Poor
 * @version 1.0
 * @date January 2020
 *
 * MIT License
 *
 * Copyright (c) 2020 R. Dunbar Poor
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _ITEMP_H_
#define _ITEMP_H_

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// includes

#include <stdbool.h>
#include <stdint.h>

// =============================================================================
// types and definitions

/**
 * @brief Internally, itemp_t is a 16 bit integer value.
 */
typedef uint16_t itemp_t;

#define ITEMP_ONE_DEGREE_F 500
#define ITEMP_ONE_TENTH_DEGREE_F 50
#define ITEMP_ONE_HUNDRETH_DEGREE_F 5
#define ITEMP_ONE_DEGREE_C 900
#define ITEMP_ONE_TENTH_DEGREE_C 90
#define ITEMP_ONE_HUNDRETH_DEGREE_C 9

// =============================================================================
// declarations

/**
 * Convert Fahrenheit to an itemp value.
 *
 * @param fahrenheit_1 Temperature in degrees Fahrenheit.
 * @returns The corresponding itemp value.
 */
itemp_t fahrenheit_1_to_itemp(int16_t fahrenheit_1);

/**
 * Convert tenths of a degree Fahrenheit to an itemp value.
 *
 * @param fahrenheit_10 Temperature in tenths of a degree Fahrenheit.
 * @returns The corresponding itemp value.
 */
itemp_t fahrenheit_10_to_itemp(int16_t fahrenheit_10);

/**
 * Convert hundreths of a degree Fahrenheit to an itemp value.
 *
 * @param fahrenheit_100 Temperature in hundreths of a degree Fahrenheit.
 * @returns The corresponding itemp value.
 */
itemp_t fahrenheit_100_to_itemp(int16_t fahrenheit_100);

/**
 * Convert Fahrenheit to an itemp value.
 *
 * @param fahrenheit Temperature in Fahrenheit.
 * @returns The corresponding itemp value.
 */
itemp_t fahrenheit_to_itemp(float fahrenheit_1);

/**
 * Convert an itemp value to degrees Fahrenheit.
 *
 * @param itemp An itemp value.
 * @returns The temperature in degrees Fahrenheit.
 */
int16_t itemp_to_fahrenheit_1(itemp_t itemp);

/**
 * Convert an itemp value to tenths of a degree Fahrenheit.
 *
 * @param itemp An itemp value.
 * @returns The temperature in tenths of a degree Fahrenheit.
 */
int16_t itemp_to_fahrenheit_10(itemp_t itemp);

/**
 * Convert an itemp value to hundreths of a degree Fahrenheit.
 *
 * @param itemp An itemp value.
 * @returns The temperature in hundreths of a degree Fahrenheit.
 */
int16_t itemp_to_fahrenheit_100(itemp_t itemp);

/**
 * Convert an itemp value to degrees Fahrenheit.
 *
 * @param itemp An itemp value.
 * @returns The temperature in degrees Fahrenheit.
 */
float itemp_to_fahrenheit(itemp_t itemp);

itemp_t celsius_1_to_itemp(int16_t celsius_1);
itemp_t celsius_10_to_itemp(int16_t celsius_10);
itemp_t celsius_100_to_itemp(int16_t celsius_100);
itemp_t celsius_to_itemp(float celsius);

int16_t itemp_to_celsius_1(itemp_t itemp);
int16_t itemp_to_celsius_10(itemp_t itemp);
int16_t itemp_to_celsius_100(itemp_t itemp);
float itemp_to_celsius(itemp_t itemp);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _ITEMP_H_ */
