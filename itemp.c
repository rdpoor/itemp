/** @file itemp.c
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

// =============================================================================
// includes

#include "itemp.h"

// =============================================================================
// local types and definitions

#define F_100_OFFSET 1552
#define C_100_OFFSET 2640
#define F_100_SLOPE 5
#define C_100_SLOPE 9

// =============================================================================
// local (forward) declarations

// =============================================================================
// local storage

// =============================================================================
// public code

itemp_t fahrenheit_1_to_itemp(int16_t fahrenheit_1) {
  return fahrenheit_100_to_itemp(fahrenheit_1 * 100);
}

itemp_t fahrenheit_10_to_itemp(int16_t fahrenheit_10) {
  return fahrenheit_100_to_itemp(fahrenheit_10 * 10);
}

itemp_t fahrenheit_100_to_itemp(int16_t fahrenheit_100) {
  return (fahrenheit_100 + F_100_OFFSET) * F_100_SLOPE;
}

itemp_t fahrenheit_to_itemp(float fahrenheit) {
  return (fahrenheit * 100.0 + F_100_OFFSET) * F_100_SLOPE;
}

int16_t itemp_to_fahrenheit_1(itemp_t itemp) {
  return itemp_to_fahrenheit_100(itemp) / 100;
}

int16_t itemp_to_fahrenheit_10(itemp_t itemp) {
  return itemp_to_fahrenheit_100(itemp) / 10;
}

int16_t itemp_to_fahrenheit_100(itemp_t itemp) {
  return (itemp / F_100_SLOPE) - F_100_OFFSET;
}

float itemp_to_fahrenheit(itemp_t itemp) {
  return ((itemp / (float)F_100_SLOPE) - F_100_OFFSET) / 100.0;
}

// celsius

itemp_t celsius_1_to_itemp(int16_t celsius_1) {
  return celsius_100_to_itemp(celsius_1 * 100);
}

itemp_t celsius_10_to_itemp(int16_t celsius_10) {
  return celsius_100_to_itemp(celsius_10 * 10);
}

itemp_t celsius_100_to_itemp(int16_t celsius_100) {
  return (celsius_100 + C_100_OFFSET) * C_100_SLOPE;
}

itemp_t celsius_to_itemp(float celsius) {
  return (celsius * 100.0 + C_100_OFFSET) * C_100_SLOPE;
}

int16_t itemp_to_celsius_1(itemp_t itemp) {
  return itemp_to_celsius_100(itemp) / 100;
}

int16_t itemp_to_celsius_10(itemp_t itemp) {
  return itemp_to_celsius_100(itemp) / 10;
}

int16_t itemp_to_celsius_100(itemp_t itemp) {
  return (itemp / C_100_SLOPE) - C_100_OFFSET;
}

float itemp_to_celsius(itemp_t itemp) {
  return ((itemp / (float)C_100_SLOPE) - C_100_OFFSET) / 100.0;
}

// =============================================================================
// local (static) code

// =============================================================================
// self test

// To run tests on a unix-like system:
//   cc -g -Wall -DUNIT_TEST -o itemp itemp.c && ./itemp && rm -f itemp

#ifdef UNIT_TEST

#include <stdio.h>

#define ASSERT_INT(observed, expected)                                  \
  unit_test_assert_eq_int((observed), (expected), #observed, #expected, \
                          __FILE__, __LINE__)
void unit_test_assert_eq_int(const int observed, const int expected,
                             const char *observed_expr,
                             const char *expected_expr, const char *const file,
                             const int line);

#define ASSERT_EPS(f0, f1, eps) \
  unit_test_float_eps((f0), (f1), (eps), #f0, #f1, #eps, __FILE__, __LINE__)
void unit_test_float_eps(const float f0, const float f1, const float eps,
                         const char *const f0_expr, const char *const f1_expr,
                         const char *const eps_expr, const char *const file,
                         const int line);

/**
 * @brief pass the test if observed_expr and expected_expr are integer equal
 */
void unit_test_assert_eq_int(const int observed, const int expected,
                             const char *observed_expr,
                             const char *expected_expr, const char *const file,
                             const int line) {
  if (observed != expected) {
    printf("\r\n%d != %d in %s == %s at %s:%d", observed, expected,
           observed_expr, expected_expr, file, line);
    fflush(stdout);
  }
}

/**
 * @brief pass the test if f0 and f1 differ by less than eps
 */
void unit_test_float_eps(const float f0, const float f1, const float eps,
                         const char *const f0_expr, const char *const f1_expr,
                         const char *const eps_expr, const char *const file,
                         const int line) {
  float diff = f0 - f1;
  if (diff < 0) diff = -diff;
  if (diff >= eps) {
    printf(
        "\r\n%e and %e differ by more than %e in UTEST_FLOAT_EPS(%s, %s, %s) "
        "at %s:%d",
        f0, f1, eps, f0_expr, f1_expr, eps_expr, file, line);
    fflush(stdout);
  }
}

int main() {
  printf("Beginning unit tests...");

  // ===========================================
  // Fahrenheit

  ASSERT_INT(itemp_to_fahrenheit_100(0), -1552);     // Min Lim -15.52F
  ASSERT_EPS(itemp_to_fahrenheit(0), -15.52, 0.01);  // Min Lim -15.52F

  ASSERT_INT(itemp_to_fahrenheit_100(7760), 0);      // 0F
  ASSERT_INT(itemp_to_fahrenheit_10(7760), 0);       // 0F
  ASSERT_INT(itemp_to_fahrenheit_1(7760), 0);        // 0F
  ASSERT_EPS(itemp_to_fahrenheit(7760), 0.0, 0.01);  // 0F

  ASSERT_INT(itemp_to_fahrenheit_100(12760), 1000);    // 10F
  ASSERT_INT(itemp_to_fahrenheit_10(12760), 100);      // 10F
  ASSERT_INT(itemp_to_fahrenheit_1(12760), 10);        // 10F
  ASSERT_EPS(itemp_to_fahrenheit(12760), 10.0, 0.01);  // 10F

  ASSERT_INT(itemp_to_fahrenheit_100(17760), 2000);    // 20F
  ASSERT_INT(itemp_to_fahrenheit_10(17760), 200);      // 20F
  ASSERT_INT(itemp_to_fahrenheit_1(17760), 20);        // 20F
  ASSERT_EPS(itemp_to_fahrenheit(17760), 20.0, 0.01);  // 20F

  ASSERT_INT(itemp_to_fahrenheit_100(22760), 3000);    // 30F
  ASSERT_INT(itemp_to_fahrenheit_10(22760), 300);      // 30F
  ASSERT_INT(itemp_to_fahrenheit_1(22760), 30);        // 30F
  ASSERT_EPS(itemp_to_fahrenheit(22760), 30.0, 0.01);  // 30F

  ASSERT_INT(itemp_to_fahrenheit_100(23760), 3200);    // freezing
  ASSERT_INT(itemp_to_fahrenheit_10(23760), 320);      // freezing
  ASSERT_INT(itemp_to_fahrenheit_1(23760), 32);        // freezing
  ASSERT_EPS(itemp_to_fahrenheit(23760), 32.0, 0.01);  // freezing

  ASSERT_INT(itemp_to_fahrenheit_100(27760), 4000);    // 40F
  ASSERT_INT(itemp_to_fahrenheit_10(27760), 400);      // 40F
  ASSERT_INT(itemp_to_fahrenheit_1(27760), 40);        // 40F
  ASSERT_EPS(itemp_to_fahrenheit(27760), 40.0, 0.01);  // 40F

  ASSERT_INT(itemp_to_fahrenheit_100(32760), 5000);    // 50F
  ASSERT_INT(itemp_to_fahrenheit_10(32760), 500);      // 50F
  ASSERT_INT(itemp_to_fahrenheit_1(32760), 50);        // 50F
  ASSERT_EPS(itemp_to_fahrenheit(32760), 50.0, 0.01);  // 50F

  ASSERT_INT(itemp_to_fahrenheit_100(37760), 6000);    // 60F
  ASSERT_INT(itemp_to_fahrenheit_10(37760), 600);      // 60F
  ASSERT_INT(itemp_to_fahrenheit_1(37760), 60);        // 60F
  ASSERT_EPS(itemp_to_fahrenheit(37760), 60.0, 0.01);  // 60F

  ASSERT_INT(itemp_to_fahrenheit_100(42760), 7000);    // 70F
  ASSERT_INT(itemp_to_fahrenheit_10(42760), 700);      // 70F
  ASSERT_INT(itemp_to_fahrenheit_1(42760), 70);        // 70F
  ASSERT_EPS(itemp_to_fahrenheit(42760), 70.0, 0.01);  // 70F

  ASSERT_INT(itemp_to_fahrenheit_100(47760), 8000);    // 80F
  ASSERT_INT(itemp_to_fahrenheit_10(47760), 800);      // 80F
  ASSERT_INT(itemp_to_fahrenheit_1(47760), 80);        // 80F
  ASSERT_EPS(itemp_to_fahrenheit(47760), 80.0, 0.01);  // 80F

  ASSERT_INT(itemp_to_fahrenheit_100(52760), 9000);    // 90F
  ASSERT_INT(itemp_to_fahrenheit_10(52760), 900);      // 90F
  ASSERT_INT(itemp_to_fahrenheit_1(52760), 90);        // 90F
  ASSERT_EPS(itemp_to_fahrenheit(52760), 90.0, 0.01);  // 90F

  ASSERT_INT(itemp_to_fahrenheit_100(57760), 10000);    // 100F
  ASSERT_INT(itemp_to_fahrenheit_10(57760), 1000);      // 100F
  ASSERT_INT(itemp_to_fahrenheit_1(57760), 100);        // 100F
  ASSERT_EPS(itemp_to_fahrenheit(57760), 100.0, 0.01);  // 100F

  ASSERT_INT(itemp_to_fahrenheit_100(62760), 11000);    // 110F
  ASSERT_INT(itemp_to_fahrenheit_10(62760), 1100);      // 110F
  ASSERT_INT(itemp_to_fahrenheit_1(62760), 110);        // 110F
  ASSERT_EPS(itemp_to_fahrenheit(62760), 110.0, 0.01);  // 110F

  ASSERT_INT(itemp_to_fahrenheit_100(65535), 11555);     // Max Lim 115.55F
  ASSERT_EPS(itemp_to_fahrenheit(65535), 115.55, 0.01);  // Max Lim 115.55F

  // ===========================================

  ASSERT_INT(fahrenheit_100_to_itemp(-1552), 0);     // Min Lim -15.52F
  ASSERT_EPS(fahrenheit_to_itemp(-15.52), 0, 0.01);  // Min Lim -15.52F

  ASSERT_INT(fahrenheit_100_to_itemp(0), 7760);      // 0F
  ASSERT_INT(fahrenheit_10_to_itemp(0), 7760);       // 0F
  ASSERT_INT(fahrenheit_1_to_itemp(0), 7760);        // 0F
  ASSERT_EPS(fahrenheit_to_itemp(0.0), 7760, 0.01);  // 0F

  ASSERT_INT(fahrenheit_100_to_itemp(1000), 12760);    // 10F
  ASSERT_INT(fahrenheit_10_to_itemp(100), 12760);      // 10F
  ASSERT_INT(fahrenheit_1_to_itemp(10), 12760);        // 10F
  ASSERT_EPS(fahrenheit_to_itemp(10.0), 12760, 0.01);  // 10F

  ASSERT_INT(fahrenheit_100_to_itemp(2000), 17760);    // 20F
  ASSERT_INT(fahrenheit_10_to_itemp(200), 17760);      // 20F
  ASSERT_INT(fahrenheit_1_to_itemp(20), 17760);        // 20F
  ASSERT_EPS(fahrenheit_to_itemp(20.0), 17760, 0.01);  // 20F

  ASSERT_INT(fahrenheit_100_to_itemp(3000), 22760);    // 30F
  ASSERT_INT(fahrenheit_10_to_itemp(300), 22760);      // 30F
  ASSERT_INT(fahrenheit_1_to_itemp(30), 22760);        // 30F
  ASSERT_EPS(fahrenheit_to_itemp(30.0), 22760, 0.01);  // 30F

  ASSERT_INT(fahrenheit_100_to_itemp(3200), 23760);    // freezing
  ASSERT_INT(fahrenheit_10_to_itemp(320), 23760);      // freezing
  ASSERT_INT(fahrenheit_1_to_itemp(32), 23760);        // freezing
  ASSERT_EPS(fahrenheit_to_itemp(32.0), 23760, 0.01);  // freezing

  ASSERT_INT(fahrenheit_100_to_itemp(4000), 27760);    // 40F
  ASSERT_INT(fahrenheit_10_to_itemp(400), 27760);      // 40F
  ASSERT_INT(fahrenheit_1_to_itemp(40), 27760);        // 40F
  ASSERT_EPS(fahrenheit_to_itemp(40.0), 27760, 0.01);  // 40F

  ASSERT_INT(fahrenheit_100_to_itemp(5000), 32760);    // 50F
  ASSERT_INT(fahrenheit_10_to_itemp(500), 32760);      // 50F
  ASSERT_INT(fahrenheit_1_to_itemp(50), 32760);        // 50F
  ASSERT_EPS(fahrenheit_to_itemp(50.0), 32760, 0.01);  // 50F

  ASSERT_INT(fahrenheit_100_to_itemp(6000), 37760);    // 60F
  ASSERT_INT(fahrenheit_10_to_itemp(600), 37760);      // 60F
  ASSERT_INT(fahrenheit_1_to_itemp(60), 37760);        // 60F
  ASSERT_EPS(fahrenheit_to_itemp(60.0), 37760, 0.01);  // 60F

  ASSERT_INT(fahrenheit_100_to_itemp(7000), 42760);    // 70F
  ASSERT_INT(fahrenheit_10_to_itemp(700), 42760);      // 70F
  ASSERT_INT(fahrenheit_1_to_itemp(70), 42760);        // 70F
  ASSERT_EPS(fahrenheit_to_itemp(70.0), 42760, 0.01);  // 70F

  ASSERT_INT(fahrenheit_100_to_itemp(8000), 47760);    // 80F
  ASSERT_INT(fahrenheit_10_to_itemp(800), 47760);      // 80F
  ASSERT_INT(fahrenheit_1_to_itemp(80), 47760);        // 80F
  ASSERT_EPS(fahrenheit_to_itemp(80.0), 47760, 0.01);  // 80F

  ASSERT_INT(fahrenheit_100_to_itemp(9000), 52760);    // 90F
  ASSERT_INT(fahrenheit_10_to_itemp(900), 52760);      // 90F
  ASSERT_INT(fahrenheit_1_to_itemp(90), 52760);        // 90F
  ASSERT_EPS(fahrenheit_to_itemp(90.0), 52760, 0.01);  // 90F

  ASSERT_INT(fahrenheit_100_to_itemp(10000), 57760);    // 100F
  ASSERT_INT(fahrenheit_10_to_itemp(1000), 57760);      // 100F
  ASSERT_INT(fahrenheit_1_to_itemp(100), 57760);        // 100F
  ASSERT_EPS(fahrenheit_to_itemp(100.0), 57760, 0.01);  // 100F

  ASSERT_INT(fahrenheit_100_to_itemp(11000), 62760);    // 110F
  ASSERT_INT(fahrenheit_10_to_itemp(1100), 62760);      // 110F
  ASSERT_INT(fahrenheit_1_to_itemp(110), 62760);        // 110F
  ASSERT_EPS(fahrenheit_to_itemp(110.0), 62760, 0.01);  // 110F

  ASSERT_INT(fahrenheit_100_to_itemp(11555), 65535);     // Max Lim 115.55F
  ASSERT_EPS(fahrenheit_to_itemp(115.55), 65535, 0.01);  // Max Lim 115.55F

  // ===========================================
  // Celsius

  ASSERT_INT(itemp_to_celsius_100(0), -2640);    // Min Lim -15.52C
  ASSERT_EPS(itemp_to_celsius(0), -26.4, 0.01);  // Min Lim -15.52C

  ASSERT_INT(itemp_to_celsius_100(23760), 0);      // freezing
  ASSERT_INT(itemp_to_celsius_10(23760), 0);       // freezing
  ASSERT_INT(itemp_to_celsius_1(23760), 0);        // freezing
  ASSERT_EPS(itemp_to_celsius(23760), 0.0, 0.01);  // freezing

  ASSERT_INT(itemp_to_celsius_100(28260), 500);    // 5C
  ASSERT_INT(itemp_to_celsius_10(28260), 50);      // 5C
  ASSERT_INT(itemp_to_celsius_1(28260), 5);        // 5C
  ASSERT_EPS(itemp_to_celsius(28260), 5.0, 0.01);  // 5C

  ASSERT_INT(itemp_to_celsius_100(32760), 1000);    // 10C
  ASSERT_INT(itemp_to_celsius_10(32760), 100);      // 10C
  ASSERT_INT(itemp_to_celsius_1(32760), 10);        // 10C
  ASSERT_EPS(itemp_to_celsius(32760), 10.0, 0.01);  // 10C

  ASSERT_INT(itemp_to_celsius_100(37260), 1500);    // 15C
  ASSERT_INT(itemp_to_celsius_10(37260), 150);      // 15C
  ASSERT_INT(itemp_to_celsius_1(37260), 15);        // 15C
  ASSERT_EPS(itemp_to_celsius(37260), 15.0, 0.01);  // 15C

  ASSERT_INT(itemp_to_celsius_100(41760), 2000);    // 20C
  ASSERT_INT(itemp_to_celsius_10(41760), 200);      // 20C
  ASSERT_INT(itemp_to_celsius_1(41760), 20);        // 20C
  ASSERT_EPS(itemp_to_celsius(41760), 20.0, 0.01);  // 20C

  ASSERT_INT(itemp_to_celsius_100(46260), 2500);    // 25C
  ASSERT_INT(itemp_to_celsius_10(46260), 250);      // 25C
  ASSERT_INT(itemp_to_celsius_1(46260), 25);        // 25C
  ASSERT_EPS(itemp_to_celsius(46260), 25.0, 0.01);  // 25C

  ASSERT_INT(itemp_to_celsius_100(50760), 3000);    // 30C
  ASSERT_INT(itemp_to_celsius_10(50760), 300);      // 30C
  ASSERT_INT(itemp_to_celsius_1(50760), 30);        // 30C
  ASSERT_EPS(itemp_to_celsius(50760), 30.0, 0.01);  // 30C

  ASSERT_INT(itemp_to_celsius_100(55260), 3500);    // 35C
  ASSERT_INT(itemp_to_celsius_10(55260), 350);      // 35C
  ASSERT_INT(itemp_to_celsius_1(55260), 35);        // 35C
  ASSERT_EPS(itemp_to_celsius(55260), 35.0, 0.01);  // 35C

  ASSERT_INT(itemp_to_celsius_100(59760), 4000);    // 40C
  ASSERT_INT(itemp_to_celsius_10(59760), 400);      // 40C
  ASSERT_INT(itemp_to_celsius_1(59760), 40);        // 40C
  ASSERT_EPS(itemp_to_celsius(59760), 40.0, 0.01);  // 40C

  ASSERT_INT(itemp_to_celsius_100(64260), 4500);    // 45C
  ASSERT_INT(itemp_to_celsius_10(64260), 450);      // 45C
  ASSERT_INT(itemp_to_celsius_1(64260), 45);        // 45C
  ASSERT_EPS(itemp_to_celsius(64260), 45.0, 0.01);  // 110C

  ASSERT_INT(itemp_to_celsius_100(65535), 4641);       // Max Lim 46.4167.55C
  ASSERT_EPS(itemp_to_celsius(65535), 46.4167, 0.01);  // Max Lim 46.4167C

  // ===========================================

  ASSERT_INT(celsius_100_to_itemp(-2640), 0);    // Min Lim -26.40C
  ASSERT_EPS(celsius_to_itemp(-26.4), 0, 0.01);  // Min Lim -26.40C

  ASSERT_INT(celsius_100_to_itemp(0), 23760);      // freezing
  ASSERT_INT(celsius_10_to_itemp(0), 23760);       // freezing
  ASSERT_INT(celsius_1_to_itemp(0), 23760);        // freezing
  ASSERT_EPS(celsius_to_itemp(0.0), 23760, 0.01);  // freezing

  ASSERT_INT(celsius_100_to_itemp(500), 28260);    // 5C
  ASSERT_INT(celsius_10_to_itemp(50), 28260);      // 5C
  ASSERT_INT(celsius_1_to_itemp(5), 28260);        // 5C
  ASSERT_EPS(celsius_to_itemp(5.0), 28260, 0.01);  // 5C

  ASSERT_INT(celsius_100_to_itemp(1000), 32760);    // 10C
  ASSERT_INT(celsius_10_to_itemp(100), 32760);      // 10C
  ASSERT_INT(celsius_1_to_itemp(10), 32760);        // 10C
  ASSERT_EPS(celsius_to_itemp(10.0), 32760, 0.01);  // 10C

  ASSERT_INT(celsius_100_to_itemp(1500), 37260);    // 15C
  ASSERT_INT(celsius_10_to_itemp(150), 37260);      // 15C
  ASSERT_INT(celsius_1_to_itemp(15), 37260);        // 15C
  ASSERT_EPS(celsius_to_itemp(15.0), 37260, 0.01);  // 15C

  ASSERT_INT(celsius_100_to_itemp(2000), 41760);    // 20C
  ASSERT_INT(celsius_10_to_itemp(200), 41760);      // 20C
  ASSERT_INT(celsius_1_to_itemp(20), 41760);        // 20C
  ASSERT_EPS(celsius_to_itemp(20.0), 41760, 0.01);  // 20C

  ASSERT_INT(celsius_100_to_itemp(2500), 46260);    // 25C
  ASSERT_INT(celsius_10_to_itemp(250), 46260);      // 25C
  ASSERT_INT(celsius_1_to_itemp(25), 46260);        // 25C
  ASSERT_EPS(celsius_to_itemp(25.0), 46260, 0.01);  // 25C

  ASSERT_INT(celsius_100_to_itemp(3000), 50760);    // 30C
  ASSERT_INT(celsius_10_to_itemp(300), 50760);      // 30C
  ASSERT_INT(celsius_1_to_itemp(30), 50760);        // 30C
  ASSERT_EPS(celsius_to_itemp(30.0), 50760, 0.01);  // 30C

  ASSERT_INT(celsius_100_to_itemp(3500), 55260);    // 35C
  ASSERT_INT(celsius_10_to_itemp(350), 55260);      // 35C
  ASSERT_INT(celsius_1_to_itemp(35), 55260);        // 35C
  ASSERT_EPS(celsius_to_itemp(35.0), 55260, 0.01);  // 35C

  ASSERT_INT(celsius_100_to_itemp(4000), 59760);    // 40C
  ASSERT_INT(celsius_10_to_itemp(400), 59760);      // 40C
  ASSERT_INT(celsius_1_to_itemp(40), 59760);        // 40C
  ASSERT_EPS(celsius_to_itemp(40.0), 59760, 0.01);  // 40C

  ASSERT_INT(celsius_100_to_itemp(4500), 64260);    // 45C
  ASSERT_INT(celsius_10_to_itemp(450), 64260);      // 45C
  ASSERT_INT(celsius_1_to_itemp(45), 64260);        // 45C
  ASSERT_EPS(celsius_to_itemp(45.0), 64260, 0.01);  // 110C

  // Cannot exactly represent max limit in celsius
  // ASSERT_INT(celsius_100_to_itemp(4641), 65535);   // Max Lim 46.4167.55C
  ASSERT_EPS(celsius_to_itemp(46.4167), 65535, 0.01);  // Max Lim 46.4167C

  // ===========================================
  // Adjusting and converting itemp

  itemp_t itemp = fahrenheit_1_to_itemp(70);
  ASSERT_INT(itemp_to_fahrenheit_100(itemp), 7000);  // 70F

  itemp -= 2 * ITEMP_ONE_DEGREE_F;
  ASSERT_INT(itemp_to_fahrenheit_100(itemp), 6800);  // 68F
  ASSERT_INT(itemp_to_celsius_100(itemp), 2000);     // 20C

  itemp += 18 * ITEMP_ONE_HUNDRETH_DEGREE_F;
  ASSERT_INT(itemp_to_fahrenheit_100(itemp), 6818);  // 68.18F
  ASSERT_INT(itemp_to_celsius_100(itemp), 2010);     // 20.10C

  itemp -= 10 * ITEMP_ONE_HUNDRETH_DEGREE_C;
  ASSERT_INT(itemp_to_fahrenheit_100(itemp), 6800);  // 68F
  ASSERT_INT(itemp_to_celsius_100(itemp), 2000);     // 20C

  printf("\r\n...unit tests complete.\r\n");
}

#endif
