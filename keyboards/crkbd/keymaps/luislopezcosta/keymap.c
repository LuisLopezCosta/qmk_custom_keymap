// Copyright 2022 Soundmonster (@soundmonster)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

//Tap Dance Declarations
enum {
  TD_LGUI_ALTSPC = 0,
  TD_LSFT_TAB = 1,
  TD_2_F2 = 2,
  TD_4_F4 = 3,
  TD_5_F5 = 4,
  TD_0_F10 = 5,
  TD_LSFTTAB_CAPS = 6
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_LGUI_ALTSPC]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LALT(KC_SPC)),
  [TD_LSFT_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT,KC_TAB), 
  [TD_2_F2] = ACTION_TAP_DANCE_DOUBLE(KC_2,KC_F2),
  [TD_4_F4] = ACTION_TAP_DANCE_DOUBLE(KC_4,KC_F4),
  [TD_5_F5] = ACTION_TAP_DANCE_DOUBLE(KC_5,KC_F5),
  [TD_0_F10] = ACTION_TAP_DANCE_DOUBLE(KC_0,KC_F10),
  [TD_LSFTTAB_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_CAPS,LSFT(KC_TAB))
};
 

// Custom keycodes for layer keys
// Dual function escape with left command
#define KC_LGALT LALT_T(KC_LGUI)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  BSPC_DEL,

  //Excel
  EXC_F,
  EXC_V
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,---------------------------------------------.
    KC_ESC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  BSPC_DEL,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    TD(TD_LSFT_TAB),  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,          KC_H,  KC_J,  KC_K,  KC_L, KC_SCLN,KC_QUOT,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    KC_LCTL,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                  KC_N,  KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RALT,
  //|------+------+------+------+------+------+------|  |------+------+------+-------+------+-------+--------|
                    TD(TD_LGUI_ALTSPC), LOWER, KC_SPC,   KC_ENT, RAISE, KC_LALT
                                  //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,---------------------------------------------.                ,-----------------------------------------.
     KC_ESC, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,                   KC_HOME, KC_PGUP, KC_UP, KC_PGDN, KC_NO, BSPC_DEL,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    TD(TD_LSFT_TAB), KC_1,   TD(TD_2_F2),   KC_3,  TD(TD_4_F4), TD(TD_5_F5), KC_END, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    KC_LCTL, KC_6,   KC_7,   KC_8,  KC_9, TD(TD_0_F10),              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    KC_LGUI, LOWER, KC_SPC,  KC_ENT, RAISE, KC_LALT
                                  //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_ESC,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,              KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,BSPC_DEL,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    TD(TD_LSFTTAB_CAPS), KC_NO, KC_NO, KC_NO, EXC_F, KC_NO,                KC_MINS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,KC_GRV,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LCTL, KC_NO, KC_NO, KC_NO, EXC_V,KC_NO,                KC_UNDS,KC_EQL,KC_LBRC,KC_RBRC,KC_BSLS,KC_TILD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER, KC_SPC,  KC_ENT, RAISE, KC_LALT
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,-----------------------------------------.
    QK_BOOT,RGBRST, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,KC_NO,               KC_BRIU, KC_MPRV,KC_MPLY, KC_MNXT, KC_NO, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD,KC_NO,               KC_BRID, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, RGB_RMOD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER, KC_SPC,  KC_ENT, RAISE, KC_LALT
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

bool oled_task_user(void) {
    // Renders the current keyboard state (layers and mods)
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    return false;
}

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t saved_mods   = 0;

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        rgb_matrix_set_color_all(0, 0, 255);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case EXC_F:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_UP));
          clear_keyboard();
          SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_DOWN));
          clear_keyboard();
          SEND_STRING(SS_TAP(X_B));

        } else {
          clear_keyboard();
        }
        return false;
    case EXC_V:
        if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_APP) SS_TAP(X_R) SS_TAP(X_ENT) SS_TAP(X_V));
        } else {
          clear_keyboard();
        }
        return false;
    case BSPC_DEL:
        if (record->event.pressed) {
          saved_mods = get_mods() & MOD_MASK_SHIFT;

          if (saved_mods == MOD_MASK_SHIFT) { // Both shifts pressed
            register_code(KC_DEL);
          } else if (saved_mods) {  // One shift pressed
            del_mods(saved_mods); // Remove any Shifts present
            register_code(KC_DEL);
            add_mods(saved_mods); // Add shifts again
          } else {
            register_code(KC_BSPC);
          }
        } else {
          unregister_code(KC_DEL);
          unregister_code(KC_BSPC);
        }
        return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif

