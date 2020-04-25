#include QMK_KEYBOARD_H

enum layer {
    LAYER_DEFAULT,
    LAYER_FUNCTION_1,
    LAYER_FUNCTION_2,
};

#define LY_FN1 MO(LAYER_FUNCTION_1)
#define LY_FN2 MO(LAYER_FUNCTION_2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default layer: http://www.keyboard-layout-editor.com/#/gists/86b33d75aa6f56d8781ab3d8475f4e77 */
    [LAYER_DEFAULT] = LAYOUT_60_tsangan_hhkb(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  KC_GRV,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,
        KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,                      LY_FN1,
        KC_LCTL,  LY_FN2,   KC_LALT,                                KC_SPC,                                           KC_RALT,  KC_RGUI,            KC_RCTL
    ),

    /* Function 1 layer: http://www.keyboard-layout-editor.com/#/gists/f6311fd7e315de781143b80eb040a551 */
    [LAYER_FUNCTION_1] = LAYOUT_60_tsangan_hhkb(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_DEL,
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_UP,    _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_LEFT,  KC_RGHT,            _______,
        _______,  KC_APP,   _______,  _______,  _______,  _______,  _______,  _______,  KC_END,   KC_PGDN,  KC_DOWN,  _______,                      _______,
        _______,  _______,  _______,                                _______,                                          _______,  _______,            _______
    ),

    /* Function 2 layer: http://www.keyboard-layout-editor.com/#/gists/65ac939caec878401603bc36290852d4 */
    [LAYER_FUNCTION_2] = LAYOUT_60_tsangan_hhkb(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,
        _______,  BL_BRTG,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,  EEP_RST,  RESET,    _______,  _______,  _______,  RGB_VAI,  _______,  _______,
        _______,  BL_INC,   KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,  _______,  RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_RMOD, RGB_MOD,            RGB_TOG,
        _______,  BL_DEC,   _______,  KC_MUTE,  _______,  _______,  _______,  RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  _______,                      _______,
        _______,  _______,  _______,                                _______,                                          _______,  _______,            _______
    ),
};
