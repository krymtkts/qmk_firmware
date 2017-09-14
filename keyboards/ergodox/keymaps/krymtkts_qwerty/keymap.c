#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define MOFUNC 1 // momentary function and any other keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Basic layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * | Esc    |   1  |   2  |   3  |   4  |   5  | ALT` |           |  `   |   6  |   7  |   8  |   9  |   0  |   -    |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * | Tab    |   Q  |   W  |   E  |   R  |   T  |CtlCmd|           |CtlCmd|   Y  |   U  |   I  |   O  |   P  |   \    |
   * |--------+------+------+------+------+------| Left |           | Right|------+------+------+------+------+--------|
   * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '/RCtl |
   * |--------+------+------+------+------+------|  [/  |           |  ]/  |------+------+------+------+------+--------|
   * | LShift |   Z  |   X  |   C  |   V  |   B  | Shift|           | Shift|   N  |   M  |   ,  |   .  |   /  | =/RSft |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   | Alt  |SftAlt|SftCtl| Caps |  Cmd |                                       |  Cmd |      |AltCtl|  Meh | AltGr |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        | Esc  |      |       |      |  Del |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |      |      |
   *                                 |Space/| Back/|------|       |------| Tab/ |Enter/|
   *                                 |  LT1 | Ctrl |      |       |      | Ctrl | LT1  |
   *                                 `--------------------'       `--------------------'
   */
  // If it accepts an argument (i.e, is a function), it doesn't need KC_.
  // Otherwise, it needs KC_*
  // Default layer.
  [BASE] = KEYMAP(
    // Left hand.
    KC_ESC,              KC_1,           KC_2,          KC_3,         KC_4,    KC_5,    LALT(KC_GRV),
    KC_TAB,              KC_Q,           KC_W,          KC_E,         KC_R,    KC_T,    LCTL(LGUI(KC_LEFT)),
    KC_LCTL,             KC_A,           KC_S,          KC_D,         KC_F,    KC_G,
    KC_LSFT,             KC_Z,           KC_X,          KC_C,         KC_V,    KC_B,    SFT_T(KC_LBRC),
    KC_LALT,             LSFT(KC_LALT),  LSFT(KC_LCTL), KC_CAPS,      KC_LGUI,

    // Left thumb.
    KC_ESC,              KC_TRNS,
                         KC_TRNS,
    LT(1,KC_SPC),        CTL_T(KC_TAB),  KC_TRNS,

    // Right hand.
    KC_GRV,              KC_6,           KC_7,          KC_8,         KC_9,    KC_0,    KC_MINS,
    RCTL(RGUI(KC_RGHT)), KC_Y,           KC_U,          KC_I,         KC_O,    KC_P,    KC_BSLS,
                         KC_H,           KC_J,          KC_K,         KC_L,    KC_SCLN, CTL_T(KC_QUOT),
    SFT_T(KC_RBRC),      KC_N,           KC_M,          KC_COMM,      KC_DOT,  KC_SLSH, SFT_T(KC_EQL),
    KC_RGUI,             KC_TRNS,        RALT(KC_RCTL), MEH_T(KC_NO), KC_RALT,

    // Right thumb.
    KC_TRNS,             KC_DEL,
    KC_TRNS,
    KC_TRNS,             CTL_T(KC_BSPC), LT(1,KC_ENT)
  ),

  /* Keymap 1: Function keys Layer
   *
   * ,---------------------------------------------------.           ,--------------------------------------------------.
   * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
   * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
   * |         |      |  Up  |      |      |      |      |           |      |  Ins | PrSc |      |  MUp |      |   F12  |
   * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |         | Left | Down | Right|      |      |------|           |------| Home | PgUp | MLeft| MDown|MRight|        |
   * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |         |      |      |      |      |      |      |           |      |  End | PgDn | LClk | MClk | RClk |        |
   * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |       |      |      |      |      |                                       |      | Pause|      |      |      |
   *   `-----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |      |      |
   *                                 |      |      |------|       |------|      |      |
   *                                 |  LT1 |      |      |       |      |      | LT1  |
   *                                 `--------------------'       `--------------------'
   */
  // Function and any other keys.
  [MOFUNC] = KEYMAP(
    // left hand.
    M(0),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
    KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
             KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,

    // Right hand.
    KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    KC_TRNS, KC_INS,  KC_PSCR, KC_TRNS, KC_MS_U, KC_TRNS, KC_F12,
             KC_HOME, KC_PGUP, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
    KC_TRNS, KC_END,  KC_PGDN, KC_BTN1, KC_BTN3, KC_BTN2, KC_TRNS,
    KC_TRNS, KC_PAUS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(MOFUNC) // FN1 - Momentary Layer 1 (Functions)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
