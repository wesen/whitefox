#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "matrix.h"


/*
 * Matt3o's WhiteFox
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PB17, PD0, PA12, PA13, PD7, PD4, PD2, PD3, PC3, PC4, PC6, PC7, PC5,
 *            PD1, PC0, PB0, PB1, PB3, PB2, PD5, PD6 }
 *     row: { PA5, PB19, PE1, PC9, PC8, PC10 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;


void matrix_init(void)
{
    debug_matrix = true;
    /* Column(sense) */
    // jakob = 21 columns (pin 1 bis 21, 1 -> esc)

    palSetPadMode(GPIOB, 17, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 0, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 12, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 13, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 7, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 4, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 2, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 3, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 3, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 4, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 6, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 7, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 1, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 0, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 0, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 1, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 3, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 2, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 6, PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
    // jakob = 6 rows (pins 24 bis 29 von unten nach oben)

    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 19, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOE, 1, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 9, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 8, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 10, PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS);
    memset(matrix_debouncing, 0, MATRIX_ROWS);
}

#define GET_BIT(v, n) (((v) & (1 << (n))) ? 1 : 0)
#define SET_BIT(dest, n, val) (dest) |= (val << (n))

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        // strobe row
        switch (row) {
        case 0: palSetPad(GPIOA, 5); break;
        case 1: palSetPad(GPIOB, 19); break;
        case 2: palSetPad(GPIOE, 1); break;
        case 3: palSetPad(GPIOC, 9); break;
        case 4: palSetPad(GPIOC, 8); break;
        case 5: palSetPad(GPIOC, 10); break;
        }

        wait_us(1); // need wait to settle pin state

        // read col data: { PTD0, PTD1, PTD4, PTD5, PTD6, PTD7, PTC1, PTC2 }

        //     col: { PB17, PD0, PA12, PA13, PD7, PD4, PD2, PD3, PC3, PC4, PC6, PC7, PC5,
        //           PD1, PC0, PB0, PB1, PB3, PB2, PD5, PD6 }

        uint32_t gpio_a = palReadPort(GPIOA);
        uint32_t gpio_b = palReadPort(GPIOB);
        uint32_t gpio_c = palReadPort(GPIOC);
        uint32_t gpio_d = palReadPort(GPIOD);

        SET_BIT(data, 0, GET_BIT(gpio_b, 17));
        SET_BIT(data, 1, GET_BIT(gpio_d, 0));
        SET_BIT(data, 2, GET_BIT(gpio_a, 12));
        SET_BIT(data, 3, GET_BIT(gpio_a, 13));
        SET_BIT(data, 4, GET_BIT(gpio_d, 7));
        SET_BIT(data, 5, GET_BIT(gpio_d, 4));
        SET_BIT(data, 6, GET_BIT(gpio_d, 2));
        SET_BIT(data, 7, GET_BIT(gpio_d, 3));
        SET_BIT(data, 8, GET_BIT(gpio_c, 3));
        SET_BIT(data, 9, GET_BIT(gpio_c, 4));
        SET_BIT(data, 10, GET_BIT(gpio_c, 6));
        SET_BIT(data, 11, GET_BIT(gpio_c, 7));
        SET_BIT(data, 12, GET_BIT(gpio_c, 5));
        SET_BIT(data, 13, GET_BIT(gpio_d, 1));
        SET_BIT(data, 14, GET_BIT(gpio_c, 0));
        SET_BIT(data, 15, GET_BIT(gpio_b, 0));
        SET_BIT(data, 16, GET_BIT(gpio_b, 1));
        SET_BIT(data, 17, GET_BIT(gpio_b, 3));
        SET_BIT(data, 18, GET_BIT(gpio_b, 2));
        SET_BIT(data, 19, GET_BIT(gpio_d, 5));
        SET_BIT(data, 20, GET_BIT(gpio_d, 6));

        // un-strobe row
        switch (row) {
        case 0: palClearPad(GPIOA, 5); break;
        case 1: palClearPad(GPIOB, 19); break;
        case 2: palClearPad(GPIOE, 1); break;
        case 3: palClearPad(GPIOC, 9); break;
        case 4: palClearPad(GPIOC, 8); break;
        case 5: palClearPad(GPIOC, 10); break;
        }

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    xprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                xprintf("1");
            else
                xprintf("0");
        }
        xprintf("\n");
    }
}
