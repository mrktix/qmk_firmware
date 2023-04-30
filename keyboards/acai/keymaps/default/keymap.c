/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum custom_layers {
    _ALP,
    _NUM,
    _SYM,
    _OTH,
};

enum custom_keycodes {
    MY_DOT = SAFE_RANGE,
    MY_QUOT,
    MY_SFT,
    MY_DDOT,
    MY_DCOL,
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//abc,

//alphas, space, layers, shift, control, backspace, enter, tab, maybe capslock?
[_ALP] = LAYOUT(
    KC_J,         KC_C,         KC_Y,         KC_F,         KC_K,           /**/          KC_Z,         KC_L,         KC_TAB,       KC_U,         KC_Q,
    KC_R,         KC_S,         KC_T,         KC_H,         KC_D,           /**/          KC_M,         KC_N,         KC_A,         KC_I,         KC_O,
    KC_ENT,       KC_V,         KC_G,         KC_P,         KC_B,           /**/          KC_X,         KC_W,         MY_DOT,       KC_SCLN,      MY_QUOT,
                  HYPR(KC_ESC), KC_BSPC,      KC_SPC,       TO(_SYM),       /**/          TO(_NUM),     KC_E,         MY_SFT,       OSM(MOD_LCTL)
),

//numbers and math symbols
[_NUM] = LAYOUT(
    _______,      KC_MINUS,     KC_PLUS,      KC_EQUAL,     _______,        /**/          _______,      KC_EQUAL,     KC_ASTERISK,  KC_SLASH,     _______,
    KC_2,         KC_3,         KC_4,         KC_5,         _______,        /**/          _______,      KC_6,         KC_7,         KC_8,         KC_9,
    _______,      _______,      _______,      KC_TILD,      _______,        /**/          _______,      KC_ESC,       KC_DOT,       TO(_OTH),     _______,
                  _______,      KC_0,         KC_1,         TO(_SYM),       /**/          TO(_NUM),     TO(_ALP),     _______,      _______
),

//symbols
//brc [],  cbr {},  abk <>,  prn (), circ ^
//.. :: ? ! & | _ # $ @ ^ % \

[_SYM] = LAYOUT(
    _______,      KC_PERC,      KC_LABK,      KC_RABK,      _______,        /**/          _______,      KC_EQUAL,     KC_CIRC,      KC_BSLS,      _______,
    KC_HASH,      KC_AMPR,      KC_LCBR,      KC_RCBR,      _______,        /**/          _______,      KC_RPRN,      KC_LPRN,      KC_PIPE,      KC_UNDS,
    _______,      KC_AT,        KC_LBRC,      KC_RBRC,      _______,        /**/          _______,      KC_DLR,       MY_DDOT,      MY_DCOL,      _______,
                  _______,      _______,      TO(_ALP),     TO(_SYM),       /**/          TO(_NUM),     KC_EXLM,      KC_QUES,      _______
),

//infrequent usage that is still needed (most importantly bootloader mode)
[_OTH] = LAYOUT(
    _______,      _______,      _______,      _______,      _______,        /**/          _______,      OSM(MOD_LSFT),OSM(MOD_LCTL),OSM(MOD_LGUI),OSM(MOD_LALT),
    _______,      _______,      _______,      KC_DEL,       _______,        /**/          _______,      KC_LEFT,      KC_UP,        KC_DOWN,      KC_RIGHT,
    _______,      _______,      _______,      _______,      _______,        /**/          _______,      _______,      _______,      _______,      QK_BOOT,
                  _______,      _______,      _______,      TO(_SYM),       /**/          TO(_NUM),     TO(_ALP),     _______,      _______
),

};

//taken from gippitty so might be buggy
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MY_DDOT:
            if (record -> event.pressed) {
                SEND_STRING("..");
            }
            break;

        case MY_DCOL:
            if (record -> event.pressed) {
                SEND_STRING("::");
            }
            break;

        case MY_DOT:
            if (record -> event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    register_code(KC_COMMA);
                } else {
                    register_code(KC_DOT);
                }
            } else {
                unregister_code(KC_COMMA);
                unregister_code(KC_DOT);
            }
            break;

        case MY_QUOT:
            if (record -> event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    register_code(KC_QUOT); //key when shift is held
                } else {
                    register_code(KC_DQT);
                }
            } else {
                unregister_code(KC_QUOT);
                unregister_code(KC_DOT);
            }
            break;

        case MY_SFT:
            if (record -> event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    register_code(KC_CAPS); //key when shift is held
                } else {
                    register_code(OSM(MOD_LSFT));
                }
            } else {
                unregister_code(KC_CAPS);
                unregister_code(OSM(MOD_LSFT));
            }
            break;
    }
    return true;
}
