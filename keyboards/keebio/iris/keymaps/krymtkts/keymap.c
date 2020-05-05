#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _SYMBOL 1
#define _FUNCS 2
#define _ADJUST 3

#define KC_LNG LALT(KC_GRV)
#define SFT_BS SFT_T(KC_BSPC)
#define CTL_TB CTL_T(KC_TAB)
#define SFT_EQL SFT_T(KC_EQL)
#define CTL_QOT CTL_T(KC_QUOT)
#define SYM_ENT LT(_SYMBOL,KC_ENT)
#define FNC_SPC LT(_FUNCS,KC_SPC)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOL,
  FUNCS,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CTL_QOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    CTL_TB,       SFT_BS,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_EQL,
                                        KC_LGUI, FNC_SPC, CTL_TB,       SFT_BS,  SYM_ENT, KC_RALT
  ),

  [_SYMBOL] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PIPE,
    _______, _______, _______, _______, KC_LPRN, KC_LBRC,                        KC_RBRC, KC_RPRN, KC_GRV,  KC_TILD, KC_COLN, KC_DQT,
    _______, _______, _______, _______, _______, KC_LCBR, KC_DEL,       _______, KC_RCBR, _______, KC_LABK, KC_RABK, KC_QUES, KC_PLUS,
                                        _______, _______, KC_DEL,       _______, _______, _______
  ),

  [_FUNCS] = LAYOUT(
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, KC_UP,   _______, _______, RGB_TOG,                        KC_INS,  KC_PSCR, RGB_HUI, RGB_SAI, RGB_VAI, KC_F12,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_LNG,  RGB_MOD,                        KC_HOME, KC_PGUP, RGB_HUD, RGB_SAD, RGB_VAD, KC_PAUS,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSTP, KC_MPLY, _______,      _______, KC_END,  KC_PGDN, BL_STEP, BL_TOGG, BL_DEC,  BL_INC,
                                        _______, _______, _______,      _______, _______, _______
  ),

  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,      _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case SYMBOL:
      if (record->event.pressed) {
        layer_on(_SYMBOL);
        update_tri_layer(_SYMBOL, _FUNCS, _ADJUST);
      } else {
        layer_off(_SYMBOL);
        update_tri_layer(_SYMBOL, _FUNCS, _ADJUST);
      }
      return false;
      break;
    case FUNCS:
      if (record->event.pressed) {
        layer_on(_FUNCS);
        update_tri_layer(_SYMBOL, _FUNCS, _ADJUST);
      } else {
        layer_off(_FUNCS);
        update_tri_layer(_SYMBOL, _FUNCS, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
