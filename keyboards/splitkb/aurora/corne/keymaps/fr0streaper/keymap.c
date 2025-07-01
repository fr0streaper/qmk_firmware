#include QMK_KEYBOARD_H

#include "callum/oneshot.h"
#include "callum/swapper.h"

#define DQUOT S(KC_QUOT)
#define LTAG S(KC_COMM)
#define RTAG S(KC_DOT)

// callum

// #define HOME G(KC_LEFT)
// #define END G(KC_RGHT)
// #define FWD G(KC_RBRC)
// #define BACK G(KC_LBRC)
// #define TABL G(S(KC_LBRC))
// #define TABR G(S(KC_RBRC))
// #define SPCL A(G(KC_LEFT))
// #define SPC_R A(G(KC_RGHT))

#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

// wellum

// #define QUOT S(KC_GRV)
// #define PIPE S(KC_BSLS)
// #define DPIPE S(RALT(KC_BSLS))
// #define SCLN S(KC_LBRC)
// #define CLN S(KC_RBRC)
// #define GRV RALT(KC_GRV)
// #define BSL RALT(KC_BSLS)

#define SPACE_L C(G(KC_LEFT))
#define SPACE_R C(G(KC_RGHT))

#define WIN_L S(G(KC_LEFT))
#define WIN_R S(G(KC_RGHT))

#define TAB_L C(S(KC_TAB))
#define TAB_R C(KC_TAB)

#define LANGDEF A(S(KC_0))
#define LANGSEC A(S(KC_3))
#define CTRLESC MT(MOD_LCTL, KC_ESC)
#define PRNTSCR S(G(KC_S))
#define ATAMANL A(S(KC_D))
#define TDBLMOD TD(TD_DOUBLE_MOD)
#define TLNGSWT TD(TD_LANG_SWITCH)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    SW_TAB,  // Switch to next browser tab    (ctrl-tab)
    SW_LANG, // Switch to next input language (alt-shift)
    SW_WIN, // Switch to next input language (alt-shift)
};

// ----- COMBOS -----

enum combo_events {
    CMB_RESET,
    CMB_RU_H,
    CMB_RU_E,
};

const uint16_t PROGMEM reset_combo[] = {KC_Q, KC_A, KC_Z, KC_P, KC_SCLN, KC_SLSH, COMBO_END};
const uint16_t PROGMEM ru_h_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM ru_e_combo[] = {KC_L, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
    [CMB_RESET] = COMBO(reset_combo, QK_BOOT),
    [CMB_RU_H] = COMBO(ru_h_combo, KC_LBRC),
    [CMB_RU_E] = COMBO(ru_e_combo, KC_QUOT),
};

// ----- TAP DANCE -----

enum {
    TD_DOUBLE_MOD,
    TD_LANG_SWITCH,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_DOUBLE_MOD] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LCTL),
    [TD_LANG_SWITCH] = ACTION_TAP_DANCE_DOUBLE(LANGDEF, LANGSEC),
};

// ----- KEYMAP -----

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TLNGSWT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, ATAMANL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          TDBLMOD,  KC_SPC,  LA_NAV,     LA_SYM, KC_LSFT,  KC_ESC
                                      //`--------------------------'  `--------------------------'

  ),

    //[_NAV] = LAYOUT_split_3x5_3(
        //SW_TAB,  SW_WIN,  TAB_L,   TAB_R,   KC_ESC,         KC_ESC,  KC_HOME, KC_END,  KC_BSPC, KC_DEL,
        //OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, KC_ENT,         KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        //SPACE_L, SPACE_R, DF(_GAM), KC_PSCR, KC_TAB,        KC_TAB,  KC_PGUP, KC_PGDN, KC_QUOT, KC_NUM,
                          //_______, _______, _______,        _______, _______, _______
    //),

    //[NAV] = LAYOUT_callum(
        //KC_TAB,  SW_WIN,  TABL,    TABR,    KC_VOLU, QK_BOOT, HOME,    KC_UP,   END,     KC_DEL,
        //OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD, KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        //SPCL,    SPC_R,   BACK,    FWD,     KC_MPLY, XXXXXXX, KC_PGDN, KC_PGUP, SW_LANG, KC_ENT,
                                   //_______, _______, _______, _______
    //),

    [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_TAB,  SW_WIN,   WIN_L,   WIN_R, KC_VOLU,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  OS_CMD,  OS_ALT, OS_CTRL, OS_SHFT, KC_VOLD,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BSPC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, SPACE_L, SPACE_R, KC_MPRV, KC_MNXT, KC_MPLY,                       KC_APP, CW_TOGG, PRNTSCR, SW_LANG,  KC_ENT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    //[_SYM] = LAYOUT_split_3x5_3(
        //KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        //KC_SCLN, GRV,     KC_GRV,  QUOT,    KC_MINS,        KC_PLUS, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,
        //BSL,     DPIPE,   SCLN,    KC_LBRC, KC_UNDS,        KC_EQL,  KC_RBRC, CLN,     PIPE,    KC_BSLS,
                          //_______, _______, _______,        _______, _______, _______
    //),

    //[SYM] = LAYOUT_callum(
        //KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        //KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_HASH, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        //KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC, XXXXXXX, KC_AMPR, KC_SCLN, KC_COLN, KC_EXLM,
                                   //_______, _______, _______, _______
    //),
    //
    //
    // *\?/<>,.
    // =+-"'~!#@$%&
    //
    //
    //
    //
    //
    //
    //

    [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_EXLM,                      KC_BSLS, KC_RPRN, KC_RCBR, KC_RBRC, KC_CIRC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_MINS, KC_QUOT,  KC_EQL,   DQUOT, KC_PLUS,                      KC_ASTR, OS_SHFT, OS_CTRL,  OS_ALT,  OS_CMD, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_HASH,   KC_AT,  KC_DLR, KC_UNDS, KC_PERC,                      KC_AMPR, KC_PIPE,    LTAG,    RTAG,  KC_GRV, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RGB_SAI,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_SAD,  OS_CMD,  OS_ALT, OS_CTRL, OS_SHFT,  KC_F11,                       KC_F12, OS_SHFT, OS_CTRL,  OS_ALT,  OS_CMD, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_HUI,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_tab_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_tab_active, KC_LCTL, KC_TAB, SW_TAB,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LALT, KC_LSFT, SW_LANG,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
