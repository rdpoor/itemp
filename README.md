# itemp
compact representation of temperature

`itemp` represents temperature at a 16 bit integer and uses integer arithmetic
to convert between Fahrenheit and Celsius.  It provides accuracy down to 0.01
degrees (Fahrenheit or Celsius).

## brief example

    #include "itemp.h"
    #include <stdio.h>

    int main() {
      int16_t f100;     // temperature in 100th's of a degree F
      int16_t c100;     // temperature in 100th's of a degree C
      itemp_t itemp;    // common representation of temperature

      itemp = fahrenheit_1_to_itemp(70);      // start with 70F

      f100 = itemp_to_fahrenheit_100(itemp);  // convert to 100ths F
      printf("Temperature is %d (100th's of a degree F)\n", f100); // "7000"

      itemp -= 2 * ITEMP_ONE_DEGREE_F;        // subtract two degrees F

      f100 = itemp_to_fahrenheit_100(itemp);  // convert to 100ths F
      printf("Temperature is %d (100th's of a degree F)\n", f100); // "6800"

      c100 = itemp_to_celsius_100(itemp);     // convert to 100ths C
      printf("Temperature is %d (100th's of a degree C)\n", c100); // "2000"

      itemp += 18 * ITEMP_ONE_HUNDRETH_DEGREE_F; // add 0.18 degrees F

      f100 = itemp_to_fahrenheit_100(itemp);  // convert to 100ths F
      printf("Temperature is %d (100th's of a degree F)\n", f100); // "6818"

      c100 = itemp_to_celsius_100(itemp);     // convert to 100ths C
      printf("Temperature is %d (100th's of a degree C)\n", c100); // "2100"

      // You can also work in tenths of a degree
      int16_t f10;     // temperature in 10ths of a degree F
      int16_t c10;     // temperature in 10ths of a degree C

      itemp = celsius_10_to_itemp(200);            // start at 20C
      itemp += 10 * ITEMP_ONE_TENTH_DEGREE_C;      // add one degree C

      f10 = itemp_to_fahrenheit_10(itemp);
      printf("Temperature is %d (10th's of a degree F)\n", c10); // "698"
      c10 = itemp_to_celsius_10(itemp);
      printf("Temperature is %d (10th's of a degree C)\n", c10); // "210"

    }

## Unit Tests

See the bottom half of itemp.c for unit tests and how to run them.
