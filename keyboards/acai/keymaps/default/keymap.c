#include "acai.h"

enum custom_layers {
    _ALP,
    _NUM,
    _SYM,
    _OTH,
};

enum custom_keycodes {
    MY_DDOT = SAFE_RANGE,
    MY_DCOL,
    MY_LEAD,
    MY_E,
};

// backspace to del ... dot to comma
const key_override_t dot_comma_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COMMA);

const key_override_t back_del_override =
    ko_make_basic(MOD_MASK_CTRL, KC_BSPC, KC_DEL);

const key_override_t ctrl_n_override =
    ko_make_basic(MOD_MASK_CTRL, KC_N, KC_LEFT);
const key_override_t ctrl_a_override =
    ko_make_basic(MOD_MASK_CTRL, KC_A, KC_UP);
const key_override_t ctrl_i_override =
    ko_make_basic(MOD_MASK_CTRL, KC_I, KC_DOWN);
const key_override_t ctrl_o_override =
    ko_make_basic(MOD_MASK_CTRL, KC_O, KC_RIGHT);

const key_override_t ctrl_h_override =
    ko_make_basic(MOD_MASK_CTRL, KC_H, KC_ESC);

const key_override_t** key_overrides = (const key_override_t*[]){
    &dot_comma_override,
    &back_del_override,
    &ctrl_n_override,
    &ctrl_a_override,
    &ctrl_i_override,
    &ctrl_o_override,
    &ctrl_h_override,
    NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* alphas, space, liyers, shift, control, backspace, enter, tab, maybe capslock? */
[_ALP] = LAYOUT(
    KC_J,         KC_C,         KC_Y,         KC_F,         KC_K,           /**/          KC_Z,         KC_L,         KC_TAB,       KC_U,         KC_Q,
    KC_R,         KC_S,         KC_T,         KC_H,         KC_D,           /**/          KC_M,         KC_N,         KC_A,         KC_I,         KC_O,
    KC_ENT,       KC_V,         KC_G,         KC_P,         KC_B,           /**/          KC_X,         KC_W,         KC_DOT,       KC_SCLN,      KC_QUOT,
          XXXXXXX,MY_LEAD,      KC_BSPC,      KC_SPC,       TO(_SYM),       /**/          TO(_NUM),     MY_E,         OSM(MOD_LSFT),OSM(MOD_LCTL),XXXXXXX
),

/* numbers and math symbols */
[_NUM] = LAYOUT(
    KC_PERC,      KC_MINUS,     KC_PLUS,      KC_EQUAL,     XXXXXXX,        /**/          XXXXXXX,      KC_EQUAL,     KC_ASTERISK,  KC_SLASH,     KC_TILD,
    KC_1,         KC_2,         KC_3,         KC_4,         XXXXXXX,        /**/          XXXXXXX,      KC_5,         KC_6,         KC_7,         KC_8,
    _______,      KC_ESC,       KC_BSLS,      KC_0,         XXXXXXX,        /**/          XXXXXXX,      KC_9,         KC_DOT,       KC_COLN,      XXXXXXX,
          XXXXXXX,_______,      _______,      _______,      _______,        /**/          _______,      TO(_ALP),     _______,      _______,XXXXXXX
),

/* symbols: brc [],  cbr {},  abk <>,  prn (), circ ^ .. :: ? ! & | _ # $ @ ^ % \ */
[_SYM] = LAYOUT(
    XXXXXXX,      KC_CIRC,      KC_QUES,      KC_DLR,       XXXXXXX,        /**/          XXXXXXX,      KC_EQUAL,     KC_EXLM,      KC_UNDS,      XXXXXXX,
    XXXXXXX,      KC_AMPR,      KC_LCBR,      KC_RCBR,      XXXXXXX,        /**/          XXXXXXX,      KC_RPRN,      KC_LPRN,      KC_PIPE,      XXXXXXX,
    _______,      KC_HASH,      KC_LABK,      KC_RABK,      XXXXXXX,        /**/          XXXXXXX,      KC_RBRC,      KC_LBRC,      KC_AT,        XXXXXXX,
          XXXXXXX,_______,      _______,      _______,      _______,        /**/          _______,      TO(_ALP),     TO(_OTH),     XXXXXXX,XXXXXXX
),

//infrequent uaage that is still needed (most importantly bootloader mode)
//f keys arrow keys also bootloader.
[_OTH] = LAYOUT(
    KC_F9,        KC_F10,       KC_F11,       KC_F12,       XXXXXXX,        /**/          XXXXXXX,      OSM(MOD_LSFT),OSM(MOD_LCTL),OSM(MOD_LGUI),OSM(MOD_LALT),
    KC_F5,        KC_F6,        KC_F7,        KC_F8,        XXXXXXX,        /**/          XXXXXXX,      KC_LEFT,      KC_UP,        KC_DOWN,      KC_RIGHT,
    KC_F1,        KC_F2,        KC_F3,        KC_F4,        XXXXXXX,        /**/          XXXXXXX,      KC_HOME,      KC_PGUP,      KC_PGDN,      KC_END,
          XXXXXXX,_______,      _______,      _______,      _______,        /**/          _______,      TO(_ALP),     TO(_OTH),     QK_BOOT,XXXXXXX
),
};

bool leaderlock = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MY_LEAD:
            if (record -> event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LALT);
                leaderlock = true;
            }
            break;

        case MY_E:
            if (record -> event.pressed) {
                if (leaderlock) {
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LALT);
                    leaderlock = false;
                } else {
                    register_code(KC_E);
                }
            } else {
                unregister_code(KC_E);
            }
            break;

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
    }
    return true;
}
