#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _SYM,
    _NUM,
    _LANG,
    _SYS,
    _QWERTY
};

#define NAV     MO(_NAV)
#define SYM     MO(_SYM)
#define NUM     MO(_NUM)
#define LANG    OSL(_LANG)
#define SYS     MO(_SYS)
#define VIBRA   PDF(_BASE)
#define QWERTY  PDF(_QWERTY)

// Home-row mods for Vibranium-f home block
#define HRM_S   LGUI_T(KC_S)
#define HRM_C   LALT_T(KC_C)
#define HRM_N   LCTL_T(KC_N)
#define HRM_T   LSFT_T(KC_T)

#define HRM_A   LSFT_T(KC_A)
#define HRM_E   LCTL_T(KC_E)
#define HRM_I   LALT_T(KC_I)
#define HRM_H   LGUI_T(KC_H)

// Shortcuts
#define UNDO    C(KC_Z)
#define CUT     C(KC_X)
#define COPY    C(KC_C)
#define PASTE   C(KC_V)
#define SAVE    C(KC_S)
#define FIND    C(KC_F)

#define S_TAB   S(KC_TAB)
#define PREVT   C(S(KC_TAB))
#define NEXTT   C(KC_TAB)
#define ALT_TAB A(KC_TAB)

#define WORD_L  C(KC_LEFT)
#define WORD_R  C(KC_RGHT)
#define C_DEL   C(KC_DEL)
#define C_BSPC  C(KC_BSPC)

// Unicode map
enum unicode_names {
    U_AACU, U_AACU_CAP,
    U_EACU, U_EACU_CAP,
    U_IACU, U_IACU_CAP,
    U_OACU, U_OACU_CAP,
    U_UACU, U_UACU_CAP,

    U_AGRV, U_AGRV_CAP,
    U_EGRV, U_EGRV_CAP,
    U_IGRV, U_IGRV_CAP,
    U_OGRV, U_OGRV_CAP,
    U_UGRV, U_UGRV_CAP,

    U_AUML, U_AUML_CAP,
    U_EUML, U_EUML_CAP,
    U_IUML, U_IUML_CAP,
    U_OUML, U_OUML_CAP,
    U_UUML, U_UUML_CAP,

    U_ENYE, U_ENYE_CAP,
    U_CCED, U_CCED_CAP,
    U_ESZ,  U_ESZ_CAP,

    U_IQUE,
    U_IEXC,
    U_EURO,
    U_MDOT
};

const uint32_t PROGMEM unicode_map[] = {
    [U_AACU] = 0x00E1, [U_AACU_CAP] = 0x00C1,
    [U_EACU] = 0x00E9, [U_EACU_CAP] = 0x00C9,
    [U_IACU] = 0x00ED, [U_IACU_CAP] = 0x00CD,
    [U_OACU] = 0x00F3, [U_OACU_CAP] = 0x00D3,
    [U_UACU] = 0x00FA, [U_UACU_CAP] = 0x00DA,

    [U_AGRV] = 0x00E0, [U_AGRV_CAP] = 0x00C0,
    [U_EGRV] = 0x00E8, [U_EGRV_CAP] = 0x00C8,
    [U_IGRV] = 0x00EC, [U_IGRV_CAP] = 0x00CC,
    [U_OGRV] = 0x00F2, [U_OGRV_CAP] = 0x00D2,
    [U_UGRV] = 0x00F9, [U_UGRV_CAP] = 0x00D9,

    [U_AUML] = 0x00E4, [U_AUML_CAP] = 0x00C4,
    [U_EUML] = 0x00EB, [U_EUML_CAP] = 0x00CB,
    [U_IUML] = 0x00EF, [U_IUML_CAP] = 0x00CF,
    [U_OUML] = 0x00F6, [U_OUML_CAP] = 0x00D6,
    [U_UUML] = 0x00FC, [U_UUML_CAP] = 0x00DC,

    [U_ENYE] = 0x00F1, [U_ENYE_CAP] = 0x00D1,
    [U_CCED] = 0x00E7, [U_CCED_CAP] = 0x00C7,
    [U_ESZ]  = 0x00DF, [U_ESZ_CAP]  = 0x1E9E,

    [U_IQUE] = 0x00BF,
    [U_IEXC] = 0x00A1,
    [U_EURO] = 0x20AC,
    [U_MDOT] = 0x00B7
};

// Custom keycodes
enum custom_keycodes {
    HD_TH = SAFE_RANGE,
    HD_CH,
    HD_SH,
    HD_WH,
    HD_GH,
    HD_PH,
    SFT_CAPS,

    P_HASH_AT,
    P_DOT_COLN,
    P_SLSH_ASTR,
    P_DQUO_EXLM,
    P_QUOT_QUES,
    P_COMM_SCLN,
    P_MINS_PLUS
};

// Chordal Hold handedness
// L/R mark true sides; thumbs are exempted with '*'
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x5_3_ex2(
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',       'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*',  '*', '*', '*'
    );

// Combos
enum combo_events {
    C_TH,
    C_CH,
    C_SH,
    C_WH,
    C_GH,
    C_PH,
    C_Z,
    C_QU
};

const uint16_t PROGMEM th_combo[] = {HRM_T, HRM_N, COMBO_END}; // TN -> TH
const uint16_t PROGMEM ch_combo[] = {HRM_C, HRM_T, COMBO_END}; // CT -> CH
const uint16_t PROGMEM sh_combo[] = {HRM_S, HRM_N, COMBO_END}; // SN -> SH
const uint16_t PROGMEM wh_combo[] = {KC_W,  KC_M,  COMBO_END}; // WM -> WH
const uint16_t PROGMEM gh_combo[] = {KC_G,  KC_M,  COMBO_END}; // GM -> GH
const uint16_t PROGMEM ph_combo[] = {KC_F,  KC_D,  COMBO_END}; // FD -> PH
const uint16_t PROGMEM z_combo[]  = {KC_J,  KC_G,  COMBO_END}; // JG -> Z
const uint16_t PROGMEM qu_combo[] = {KC_G,  KC_P,  COMBO_END}; // GP -> QU, hold -> Q

combo_t key_combos[] = {
    [C_TH] = COMBO(th_combo, HD_TH),
    [C_CH] = COMBO(ch_combo, HD_CH),
    [C_SH] = COMBO(sh_combo, HD_SH),
    [C_WH] = COMBO(wh_combo, HD_WH),
    [C_GH] = COMBO(gh_combo, HD_GH),
    [C_PH] = COMBO(ph_combo, HD_PH),
    [C_Z]  = COMBO(z_combo, KC_Z),
    [C_QU] = COMBO_ACTION(qu_combo)
};

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case C_TH:
        case C_CH:
        case C_SH:
            return 45;
        case C_WH:
        case C_GH:
        case C_PH:
        case C_Z:
            return 55;
        case C_QU:
            return 70;
        default:
            return COMBO_TERM;
    }
}

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case C_QU:
            return false; // we need hold behavior here
        default:
            return true;  // all other smart combos are tap-only
    }
}

// GP -> QU, hold long enough -> delete the auto U, leaving Q
static bool     smart_qu_active = false;
static uint16_t smart_qu_timer  = 0;
#define SMART_QU_DELETE_TERM 175

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case C_QU:
            if (pressed) {
                tap_code(KC_Q);
                tap_code(KC_U);
                smart_qu_active = true;
                smart_qu_timer  = timer_read();
            } else {
                if (smart_qu_active && timer_elapsed(smart_qu_timer) > SMART_QU_DELETE_TERM) {
                    tap_code(KC_BSPC);
                }
                smart_qu_active = false;
            }
            break;
    }
}

// Real Shift key with double-tap Caps Lock
static bool     sft_caps_pressed      = false;
static bool     sft_caps_interrupted  = false;
static bool     sft_caps_tap_pending  = false;
static uint16_t sft_caps_timer        = 0;

// Startup / wake pulse
#ifdef RGB_MATRIX_ENABLE
static bool     activity_pulse_active = false;
static uint16_t activity_pulse_timer  = 0;
static uint8_t  activity_pulse_hue    = 0;
static uint8_t  activity_pulse_sat    = 0;

static void start_activity_pulse(uint8_t hue, uint8_t sat) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(hue, sat, 1);
    activity_pulse_hue   = hue;
    activity_pulse_sat   = sat;
    activity_pulse_active = true;
    activity_pulse_timer  = timer_read();
}

void keyboard_post_init_user(void) {
    start_activity_pulse(0, 0); // white startup pulse
}

void suspend_power_down_user(void) {
    rgb_matrix_disable_noeeprom();
    activity_pulse_active = false;
}

void suspend_wakeup_init_user(void) {
    start_activity_pulse(85, 255); // green wake pulse
}

void housekeeping_task_user(void) {
    if (!activity_pulse_active) {
        return;
    }

    uint16_t t = timer_elapsed(activity_pulse_timer);
    uint8_t v  = 0;

    if (t < 140) {
        v = 8 + (uint8_t)((200 - 8) * t / 140);            // rise
    } else if (t < 1200) {
        v = 200 - (uint8_t)(200 * (t - 140) / 1060);       // fade
    } else {
        rgb_matrix_disable_noeeprom();
        activity_pulse_active = false;
        return;
    }

    rgb_matrix_sethsv_noeeprom(activity_pulse_hue, activity_pulse_sat, v);
}

bool shutdown_user(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        rgb_matrix_enable_noeeprom();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(0, 255, 255); // red
        rgb_matrix_update_pwm_buffers();
    }
    return true;
}
#endif

static inline bool hd_shifted(void) {
    return (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Cancel pending double-tap Caps Lock sequence when another key intervenes.
    if (record->event.pressed && keycode != SFT_CAPS) {
        if (sft_caps_pressed) {
            sft_caps_interrupted = true;
        }
        if (sft_caps_tap_pending) {
            sft_caps_tap_pending = false;
        }
    }

    switch (keycode) {
        case HD_TH:
            if (record->event.pressed) {
                tap_code(KC_T);
                tap_code(KC_H);
            }
            return false;

        case HD_CH:
            if (record->event.pressed) {
                tap_code(KC_C);
                tap_code(KC_H);
            }
            return false;

        case HD_SH:
            if (record->event.pressed) {
                tap_code(KC_S);
                tap_code(KC_H);
            }
            return false;

        case HD_WH:
            if (record->event.pressed) {
                tap_code(KC_W);
                tap_code(KC_H);
            }
            return false;

        case HD_GH:
            if (record->event.pressed) {
                tap_code(KC_G);
                tap_code(KC_H);
            }
            return false;

        case HD_PH:
            if (record->event.pressed) {
                tap_code(KC_P);
                tap_code(KC_H);
            }
            return false;

        case SFT_CAPS:
            if (record->event.pressed) {
                if (sft_caps_tap_pending && timer_elapsed(sft_caps_timer) > TAPPING_TERM) {
                    sft_caps_tap_pending = false;
                }

                register_code(KC_LSFT);
                sft_caps_pressed     = true;
                sft_caps_interrupted = false;
            } else {
                unregister_code(KC_LSFT);
                sft_caps_pressed = false;

                if (!sft_caps_interrupted) {
                    if (sft_caps_tap_pending && timer_elapsed(sft_caps_timer) <= TAPPING_TERM) {
                        tap_code(KC_CAPS);
                        sft_caps_tap_pending = false;
                    } else {
                        sft_caps_tap_pending = true;
                        sft_caps_timer       = timer_read();
                    }
                } else {
                    sft_caps_tap_pending = false;
                }
            }
            return false;

        case P_HASH_AT:
            if (record->event.pressed) {
                tap_code16(hd_shifted() ? S(KC_2)    : S(KC_3));
            }
            return false;

        case P_DOT_COLN:
            if (record->event.pressed) {
                tap_code16(hd_shifted() ? S(KC_SCLN) : KC_DOT);
            }
            return false;

        case P_SLSH_ASTR:
            if (record->event.pressed) {
                tap_code16(hd_shifted() ? S(KC_8)    : KC_SLSH);
            }
            return false;

        case P_DQUO_EXLM:
            if (record->event.pressed) {
                tap_code16(hd_shifted() ? S(KC_1)    : S(KC_QUOT));
            }
            return false;

        case P_QUOT_QUES:
            if (record->event.pressed) {
                tap_code16(hd_shifted() ? S(KC_SLSH) : KC_QUOT);
            }
            return false;

        case P_COMM_SCLN:
            if (record->event.pressed) {
                tap_code16(hd_shifted() ? S(KC_COMM) : KC_COMM);
            }
            return false;

        case P_MINS_PLUS:
            if (record->event.pressed) {
                tap_code16(hd_shifted() ? S(KC_EQL)  : KC_MINS);
            }
            return false;
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * Layer 0 — Vibranium-f + smart Q/Z behavior
     *
     * X   W   M   G   J      Lang      Enter     #    .    /    "    '
     * S   C   N   T   K      Sys       Sys       ,    A    E    I    H
     * F   P   L   D   V                          -    U    O    Y    B
     *
     *            Nav   R   Shift/Caps      Sym   Space   Backspace
     *
     * Smart behavior:
     * - JG -> Z
     * - GP -> QU
     * - Hold GP long enough -> Q
     * - TN/CT/SN/WM/GM/FD -> TH/CH/SH/WH/GH/PH
     */
    [_BASE] = LAYOUT_split_3x5_3_ex2(
        KC_X,    KC_W,    KC_M,    KC_G,    KC_J,    LANG,        KC_ENT,  P_HASH_AT,   P_DOT_COLN,   P_SLSH_ASTR, P_DQUO_EXLM, P_QUOT_QUES,
        HRM_S,   HRM_C,   HRM_N,   HRM_T,   KC_K,    SYS,         SYS,     P_COMM_SCLN, HRM_A,        HRM_E,       HRM_I,       HRM_H,
        KC_F,    KC_P,    KC_L,    KC_D,    KC_V,                          P_MINS_PLUS, KC_U,         KC_O,        KC_Y,        KC_B,
                                   NAV,     KC_R,    SFT_CAPS,    SYM,     KC_SPC,      KC_BSPC
    ),

    /*
     * Layer 1 — Nav/Edit
     */
    [_NAV] = LAYOUT_split_3x5_3_ex2(
        UNDO,    CUT,     COPY,    PASTE,   SAVE,    _______,     _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TAB,  _______,     _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        FIND,    S_TAB,   PREVT,   NEXTT,   ALT_TAB,                         KC_INS,  WORD_L,  WORD_R,  C_BSPC,  C_DEL,
                                      _______, _______, _______,     NUM,     KC_ESC,  KC_ENT
    ),

    /*
     * Layer 2 — Symbols
     */
    [_SYM] = LAYOUT_split_3x5_3_ex2(
        S(KC_1),   S(KC_2),   S(KC_3),   S(KC_4),   S(KC_5),   _______,     _______, KC_LBRC, KC_RBRC, S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),
        S(KC_6),   S(KC_7),   S(KC_8),   S(KC_EQL), KC_EQL,    _______,     _______, S(KC_9), S(KC_0), S(KC_COMM), S(KC_DOT),  KC_SLSH,
        S(KC_GRV), KC_MINS,   S(KC_MINS), S(KC_SCLN), KC_SCLN,                        KC_GRV,  KC_QUOT, S(KC_QUOT), S(KC_SLSH), KC_BSLS,
                                          NUM,        KC_BSPC,   KC_ENT,     _______, _______, _______
    ),

    /*
     * Layer 3 — Numbers/Fn
     */
    [_NUM] = LAYOUT_split_3x5_3_ex2(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,     _______, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,     _______, S(KC_8), KC_4,    KC_5,    KC_6,    S(KC_EQL),
        KC_F11,  KC_F12,  KC_EQL,  KC_DOT,  KC_0,                            S(KC_5), KC_1,    KC_2,    KC_3,    KC_ENT,
                                      _______, _______, _______,     _______, _______, _______
    ),

    /*
     * Layer 4 — Language / Unicode
     */
    [_LANG] = LAYOUT_split_3x5_3_ex2(
        _______, _______, UP(U_ENYE, U_ENYE_CAP), UP(U_CCED, U_CCED_CAP), UP(U_ESZ, U_ESZ_CAP), _______, _______,
        UP(U_AACU, U_AACU_CAP), UP(U_EACU, U_EACU_CAP), UP(U_IACU, U_IACU_CAP), UP(U_OACU, U_OACU_CAP), UP(U_UACU, U_UACU_CAP),

        _______, _______, UM(U_IQUE), UM(U_MDOT), UM(U_EURO), _______, _______,
        UP(U_AGRV, U_AGRV_CAP), UP(U_EGRV, U_EGRV_CAP), UP(U_IGRV, U_IGRV_CAP), UP(U_OGRV, U_OGRV_CAP), UP(U_UGRV, U_UGRV_CAP),

        _______, _______, UM(U_IEXC), _______, _______,                       UP(U_AUML, U_AUML_CAP), UP(U_EUML, U_EUML_CAP), UP(U_IUML, U_IUML_CAP), UP(U_OUML, U_OUML_CAP), UP(U_UUML, U_UUML_CAP),
                                      _______, _______, _______,     _______, _______, _______
    ),

    /*
     * Layer 5 — System
     */
    [_SYS] = LAYOUT_split_3x5_3_ex2(
        UC_LINX, UC_WIN,  VIBRA,   QWERTY, XXXXXXX, QK_BOOT,    QK_BOOT, KC_PSCR, KC_SCRL, KC_PAUS, XXXXXXX, XXXXXXX,
        KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, _______,     _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, XXXXXXX,
        CM_TOGG, XXXXXXX, XXXXXXX, KC_NUM,  KC_APP,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                      _______, _______, _______,     _______, _______, _______
    ),

    /*
     * Layer 6 — QWERTY rescue
     */
    [_QWERTY] = LAYOUT_split_3x5_3_ex2(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    LANG,        KC_ENT,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    SYS,         SYS,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                      NAV,     KC_SPC,  SFT_CAPS,     SYM,    KC_SPC,  KC_BSPC
    )
};
