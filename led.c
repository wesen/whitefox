/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "hal.h"

#include "led.h"

#include "led_controller.h"

#define IS_BIT_SET(v, n) ((v) & (1 << (n)))
#define IS_LED_SET(name) IS_BIT_SET(usb_led, USB_LED_ ## name)
#define SET_LED(port, num, name) if (IS_LED_SET(name)) \
    { palSetPad((port), (num)); } \
    else { palClearPad((port), (num)); }

// CAPS: PE0
// SCROLL: PB18
// NUM: PA4

/* WARNING! This function needs to be callable from
 * both regular threads and ISRs, unlocked (during resume-from-sleep).
 * In particular, I2C functions (interrupt-driven) should NOT be called from here.
 */
void led_set(uint8_t usb_led) {
//    SET_LED(GPIOE, 0, CAPS_LOCK);
//    SET_LED(GPIOB, 18, SCROLL_LOCK);
//    SET_LED(GPIOA, 4, NUM_LOCK);
}
