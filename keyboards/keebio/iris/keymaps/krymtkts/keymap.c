#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _SYMBOL 1
#define _FUNCS 2
#define _ADJUST 3

#define KC_LNG LALT(KC_GRV)
#define CTL_BS CTL_T(KC_BSPC)
#define CTL_TB CTL_T(KC_TAB)
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
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_LNG,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CTL_T(KC_QUOT),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRV,       KC_DEL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_EQL),
                                        KC_LGUI, FNC_SPC, CTL_TB,       CTL_BS,  SYM_ENT, KC_RALT
  ),

  [_SYMBOL] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PGUP,
    RESET,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PGDN,
    KC_DEL,  _______, KC_LEFT, KC_RGHT, KC_UP,   KC_LBRC,                        KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_HOME,
    BL_STEP, _______, _______, _______, KC_DOWN, KC_LCBR, KC_LPRN,      KC_RPRN, KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, KC_END,
                                        _______, _______, KC_DEL,       KC_DEL,  _______, KC_P0
  ),

  [_FUNCS] = LAYOUT(
    M(0),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    RGB_TOG, _______, KC_UP,   _______, _______, _______,                        KC_INS,  KC_PSCR, _______, KC_MS_U, _______, KC_F12,
    RGB_MOD, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                        KC_HOME, KC_PGUP, KC_MS_L, KC_MS_D, KC_MS_R, KC_PAUS,
    KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, _______, _______, _______,      _______, KC_END,  KC_PGDN, KC_BTN1, KC_BTN3, KC_BTN2, _______,
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
