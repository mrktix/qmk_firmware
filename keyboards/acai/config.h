/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#pragma once

/* Planck PCB default pin-out */
#define MATRIX_ROW_PINS { B4, B5, B2, B6 } /* row, top to bottom */
#define MATRIX_COL_PINS { D0, D4, C6, D7, E6, /**/ B3, B1, F7, F6, F5 } /* cols, left to right */

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* the number of times you tap the osm until it toggles on (holds for more than one key) */
#define ONESHOT_TAP_TOGGLE 2
#define TAPPING_TOGGLE 2

/* #define VENDOR_ID       0x0000 */
/* #define PRODUCT_ID      0x0000 */
/* #define DEVICE_VER      0x0000 */

/* if needed */
/* #define DEBOUNCE 5 */
