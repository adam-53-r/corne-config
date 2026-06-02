// =============================================================================
//  Corne Choc Pro (mini, OLED) — Hands Down Vibranium-f + OLED
// =============================================================================
//
//  This file MERGES two sources:
//    1. Your twin's Vibranium-f keymap (home-row mods, smart digraph combos,
//       smart QU/Z, mod-morph punctuation, Unicode accents, RGB pulses).
//    2. Keebart's stock `vial_mini_oled` keymap (OLED rendering, split sync,
//       splash screen, charge-pump init).
//
//  WHY A MERGE (not a copy): QMK allows only ONE definition of each *_user
//  hook per build. Both sources define keyboard_post_init_user,
//  housekeeping_task_user, and process_record_user. They are combined here so
//  the OLEDs work AND your twin's typing logic works.
//
//  LAYOUT CONVERSION: twin's file used LAYOUT_split_3x5_3_ex2 (40 keys, inner
//  columns). The OLED board has no inner keys (screens replace them), so every
//  layer here uses LAYOUT_split_3x5_3 (36 keys). The two lost-but-needed base
//  functions were folded onto existing thumbs as holds:
//        left thumb 1:  KC_CAPS -> LT(_SYS,  KC_CAPS)   tap=Caps / hold=System
//        left thumb 2:  KC_R    -> LT(_LANG, KC_R)      tap=R    / hold=Language
//  No alpha moved; only two hold behaviours were added.
// =============================================================================

#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#include "bitmaps.h"
#endif

// -----------------------------------------------------------------------------
//  Layers
// -----------------------------------------------------------------------------
enum layers {
    _BASE,    // Hands Down Vibranium-f alphas
    _NAV,     // navigation + editing
    _SYM,     // symbols / punctuation
    _NUM,     // numbers + F-keys
    _LANG,    // Catalan/Spanish accents (Unicode)
    _SYS,     // system: media, brightness, bootloader, layout toggles
    _QWERTY   // QWERTY rescue layer
};

// -----------------------------------------------------------------------------
//  Layer / mod aliases
//    MO=momentary  OSL=one-shot  PDF=persistent default  LT/MT used inline
// -----------------------------------------------------------------------------
#define NAV     MO(_NAV)
#define SYM     MO(_SYM)
#define NUM     MO(_NUM)
#define LANG    OSL(_LANG)            // kept for optional reuse
#define SYS     MO(_SYS)
#define VIBRA   PDF(_BASE)
#define QWERTY  PDF(_QWERTY)

#define TH_CAPS LT(_SYS,  KC_CAPS)    // left thumb 1: tap Caps / hold System
#define TH_R    LT(_LANG, KC_R)       // left thumb 2: tap R    / hold Language

// Home-row mods (GACS). xxxx_T(kc): tap=kc, hold=modifier.
#define HRM_S   LALT_T(KC_S)
#define HRM_C   LCTL_T(KC_C)
#define HRM_N   LGUI_T(KC_N)
#define HRM_T   LSFT_T(KC_T)
#define HRM_A   LSFT_T(KC_A)
#define HRM_E   LGUI_T(KC_E)
#define HRM_I   LCTL_T(KC_I)
#define HRM_H   LALT_T(KC_H)

// Editing shortcuts
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

// -----------------------------------------------------------------------------
//  Unicode map — Catalan / Spanish (+ ç ñ ¿ ¡ · € ß)
// -----------------------------------------------------------------------------
enum unicode_names {
    U_AACU, U_AACU_CAP, U_EACU, U_EACU_CAP, U_IACU, U_IACU_CAP,
    U_OACU, U_OACU_CAP, U_UACU, U_UACU_CAP,
    U_AGRV, U_AGRV_CAP, U_EGRV, U_EGRV_CAP, U_IGRV, U_IGRV_CAP,
    U_OGRV, U_OGRV_CAP, U_UGRV, U_UGRV_CAP,
    U_AUML, U_AUML_CAP, U_EUML, U_EUML_CAP, U_IUML, U_IUML_CAP,
    U_OUML, U_OUML_CAP, U_UUML, U_UUML_CAP,
    U_ENYE, U_ENYE_CAP, U_CCED, U_CCED_CAP, U_ESZ, U_ESZ_CAP,
    U_IQUE, U_IEXC, U_EURO, U_MDOT
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
    [U_IQUE] = 0x00BF, [U_IEXC] = 0x00A1, [U_EURO] = 0x20AC, [U_MDOT] = 0x00B7
};

// -----------------------------------------------------------------------------
//  Custom keycodes (digraphs + mod-morph punctuation)
// -----------------------------------------------------------------------------
enum custom_keycodes {
    HD_TH = SAFE_RANGE, HD_CH, HD_SH, HD_WH, HD_GH, HD_PH,
    P_HASH_AT, P_DOT_COLN, P_SLSH_ASTR, P_DQUO_EXLM, P_QUOT_QUES, P_COMM_SCLN, P_MINS_PLUS
};

// -----------------------------------------------------------------------------
//  Chordal Hold handedness (36-key). 'L'/'R' = hands, '*' = thumbs exempt.
// -----------------------------------------------------------------------------
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x5_3(
        'L', 'L', 'L', 'L', 'L',     'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',     'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',     'R', 'R', 'R', 'R', 'R',
                  '*', '*', '*',     '*', '*', '*'
    );

// -----------------------------------------------------------------------------
//  Combos — Hands Down digraphs + smart Q/Z
// -----------------------------------------------------------------------------
enum combo_events { C_TH, C_CH, C_SH, C_WH, C_GH, C_PH, C_Z, C_QU };

const uint16_t PROGMEM th_combo[] = {HRM_T, HRM_N, COMBO_END};
const uint16_t PROGMEM ch_combo[] = {HRM_C, HRM_N, COMBO_END};
const uint16_t PROGMEM sh_combo[] = {HRM_S, HRM_C, COMBO_END};
const uint16_t PROGMEM wh_combo[] = {KC_W,  KC_M,  COMBO_END};
const uint16_t PROGMEM gh_combo[] = {KC_G,  KC_M,  COMBO_END};
const uint16_t PROGMEM ph_combo[] = {KC_F,  KC_P,  COMBO_END};
const uint16_t PROGMEM z_combo[]  = {KC_J,  KC_G,  COMBO_END};
const uint16_t PROGMEM qu_combo[] = {HRM_T, KC_K,  COMBO_END};

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
        case C_TH: case C_CH: case C_SH: return 45;
        case C_WH: case C_GH: case C_PH: case C_Z: return 55;
        case C_QU: return 70;
        default: return COMBO_TERM;
    }
}

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case C_QU: return false;
        default:   return true;
    }
}

// Smart QU: tap TK -> "qu"; hold past term -> backspace the "u" leaving "q".
static bool     smart_qu_active = false;
static uint16_t smart_qu_timer  = 0;
#define SMART_QU_DELETE_TERM 175

static void send_hd_qu(void) {
    uint8_t mods = get_mods();
    uint8_t osm  = get_oneshot_mods();
    bool shifted = (mods | osm) & MOD_MASK_SHIFT;
    set_mods(mods & ~MOD_MASK_SHIFT);
    send_keyboard_report();
    set_oneshot_mods(osm & ~MOD_MASK_SHIFT);
    tap_code16(shifted ? S(KC_Q) : KC_Q);
    tap_code16(KC_U);
    set_mods(mods);
    send_keyboard_report();
    set_oneshot_mods(osm);
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case C_QU:
            if (pressed) {
                send_hd_qu();
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

// -----------------------------------------------------------------------------
//  Mod-morph helpers
// -----------------------------------------------------------------------------
static void tap_code16_without_user_shift(uint16_t keycode) {
    uint8_t mods = get_mods();
    uint8_t osm  = get_oneshot_mods();
    set_mods(mods & ~MOD_MASK_SHIFT);
    set_oneshot_mods(osm & ~MOD_MASK_SHIFT);
    send_keyboard_report();
    tap_code16(keycode);
    set_mods(mods);
    set_oneshot_mods(osm & ~MOD_MASK_SHIFT);
    send_keyboard_report();
}

static inline bool hd_shifted(void) {
    return (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
}

static void send_hd_digraph(uint16_t first, uint16_t second) {
    uint8_t mods = get_mods();
    uint8_t osm  = get_oneshot_mods();
    bool shifted = (mods | osm) & MOD_MASK_SHIFT;
    set_mods(mods & ~MOD_MASK_SHIFT);
    send_keyboard_report();
    set_oneshot_mods(osm & ~MOD_MASK_SHIFT);
    tap_code16(shifted ? S(first) : first);
    tap_code16(second);
    set_mods(mods);
    send_keyboard_report();
    set_oneshot_mods(osm);
}

// =============================================================================
//  LAYERS  (all LAYOUT_split_3x5_3, 36 keys)
// =============================================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* _BASE — Vibranium-f
     *   X W M G J     # . / " '
     *   S C N T K     , A E I H
     *   F P L D V     - U O Y B
     *   thumbs: Caps/SYS  R/LANG  NAV | SYM  Space  Bspc
     */
    [_BASE] = LAYOUT_split_3x5_3(
        KC_X,    KC_W,    KC_M,    KC_G,    KC_J,        P_HASH_AT,   P_DOT_COLN,  P_SLSH_ASTR, P_DQUO_EXLM, P_QUOT_QUES,
        HRM_S,   HRM_C,   HRM_N,   HRM_T,   KC_K,        P_COMM_SCLN, HRM_A,       HRM_E,       HRM_I,       HRM_H,
        KC_F,    KC_P,    KC_L,    KC_D,    KC_V,        P_MINS_PLUS, KC_U,        KC_O,        KC_Y,        KC_B,
                          TH_CAPS, TH_R,    NAV,         SYM,         KC_SPC,      KC_BSPC
    ),

    /* _NAV */
    [_NAV] = LAYOUT_split_3x5_3(
        UNDO,    CUT,     COPY,    PASTE,   SAVE,        KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,
        KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT, KC_TAB,      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        FIND,    S_TAB,   PREVT,   NEXTT,   ALT_TAB,     KC_INS,  WORD_L,  WORD_R,  C_BSPC,  C_DEL,
                          _______, _______, _______,     NUM,     KC_ESC,  KC_ENT
    ),

    /* _SYM */
    [_SYM] = LAYOUT_split_3x5_3(
        S(KC_1),   S(KC_2),   S(KC_3),    S(KC_4),    S(KC_5),     KC_LBRC, KC_RBRC, S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),
        S(KC_6),   S(KC_7),   S(KC_8),    S(KC_EQL),  KC_EQL,      S(KC_9), S(KC_0), S(KC_COMM), S(KC_DOT),  KC_SLSH,
        S(KC_GRV), KC_MINS,   S(KC_MINS), S(KC_SCLN), KC_SCLN,     KC_GRV,  KC_QUOT, S(KC_QUOT), S(KC_SLSH), KC_BSLS,
                              _______,    _______,    NUM,         _______, _______, _______
    ),

    /* _NUM */
    [_NUM] = LAYOUT_split_3x5_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,      S(KC_8), KC_4,    KC_5,    KC_6,    S(KC_EQL),
        KC_F11,  KC_F12,  KC_0,    KC_DOT,  KC_EQL,      S(KC_5), KC_1,    KC_2,    KC_3,    KC_0,
                          _______, _______, _______,     _______, _______, _______
    ),

    /* _LANG — hold R thumb; right hand = vowels, Shift = uppercase */
    [_LANG] = LAYOUT_split_3x5_3(
        _______, _______, UP(U_ENYE, U_ENYE_CAP), UP(U_CCED, U_CCED_CAP), UP(U_ESZ, U_ESZ_CAP),
                                                   UP(U_AACU, U_AACU_CAP), UP(U_EACU, U_EACU_CAP), UP(U_IACU, U_IACU_CAP), UP(U_OACU, U_OACU_CAP), UP(U_UACU, U_UACU_CAP),
        _______, _______, UM(U_IQUE), UM(U_MDOT), UM(U_EURO),
                                                   UP(U_AGRV, U_AGRV_CAP), UP(U_EGRV, U_EGRV_CAP), UP(U_IGRV, U_IGRV_CAP), UP(U_OGRV, U_OGRV_CAP), UP(U_UGRV, U_UGRV_CAP),
        _______, _______, UM(U_IEXC), _______, _______,
                                                   UP(U_AUML, U_AUML_CAP), UP(U_EUML, U_EUML_CAP), UP(U_IUML, U_IUML_CAP), UP(U_OUML, U_OUML_CAP), UP(U_UUML, U_UUML_CAP),
                          _______, _______, _______,     _______, _______, _______
    ),

    /* _SYS — hold Caps thumb */
    [_SYS] = LAYOUT_split_3x5_3(
        UC_LINX, UC_WIN,  VIBRA,   QWERTY,  XXXXXXX,     KC_PSCR, KC_SCRL, KC_PAUS, XXXXXXX, XXXXXXX,
        KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU,     KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, XXXXXXX,
        CM_TOGG, XXXXXXX, XXXXXXX, KC_NUM,  KC_APP,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          _______, _______, _______,     _______, _______, _______
    ),

    /* _QWERTY rescue */
    [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          TH_CAPS, KC_SPC,  NAV,         SYM,     KC_SPC,  KC_BSPC
    )
};

// =============================================================================
//  RGB feedback pulses (twin's logic) — merged into the shared hooks below.
// =============================================================================
#ifdef RGB_MATRIX_ENABLE
static bool     activity_pulse_active = false;
static uint16_t activity_pulse_timer  = 0;
static uint8_t  activity_pulse_hue    = 0;
static uint8_t  activity_pulse_sat    = 0;

static void start_activity_pulse(uint8_t hue, uint8_t sat) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(hue, sat, 1);
    activity_pulse_hue    = hue;
    activity_pulse_sat    = sat;
    activity_pulse_active = true;
    activity_pulse_timer  = timer_read();
}

static void activity_pulse_tick(void) {
    if (!activity_pulse_active) return;
    uint16_t t = timer_elapsed(activity_pulse_timer);
    uint8_t v;
    if (t < 140) {
        v = 8 + (uint8_t)((200 - 8) * t / 140);
    } else if (t < 1200) {
        v = 200 - (uint8_t)(200 * (t - 140) / 1060);
    } else {
        rgb_matrix_disable_noeeprom();
        activity_pulse_active = false;
        return;
    }
    rgb_matrix_sethsv_noeeprom(activity_pulse_hue, activity_pulse_sat, v);
}

void suspend_power_down_user(void) {
    rgb_matrix_disable_noeeprom();
    activity_pulse_active = false;
}

void suspend_wakeup_init_user(void) {
    start_activity_pulse(0, 0); // white wake pulse
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
#endif // RGB_MATRIX_ENABLE

// =============================================================================
//  OLED support (Keebart) + merged hooks
// =============================================================================
#ifdef OLED_ENABLE

#include "transactions.h"

static const uint8_t OLED_WIDTH = OLED_DISPLAY_HEIGHT;
static const uint16_t SPLASH_DURATION_MS = 2500;

static const char PROGMEM QMK_LOGO_1[] = { 0x81, 0x82, 0x83, 0x84, 0x00 };
static const char PROGMEM QMK_LOGO_2[] = { 0xA1, 0xA2, 0xA3, 0xA4, 0x00 };
static const char PROGMEM QMK_LOGO_3[] = { 0xC1, 0xC2, 0xC3, 0xC4, 0x00 };

typedef struct { bool oled_on; } oled_state_m2s_t;
typedef struct { uint16_t keycode; } lastkey_m2s_t;
typedef struct { uint32_t left; uint32_t right; } presses_m2s_t;

static bool g_oled_init_done = false;
static uint8_t g_oled_max_char;
static uint8_t g_oled_max_line;
static bool g_splash_active = true;
static bool g_splash_rendered = false;
static uint32_t g_splash_start_ms = 0;
static uint32_t g_user_ontime = 0;
static uint16_t g_last_keycode = KC_NO;
static uint32_t g_press_left = 0;
static uint32_t g_press_right = 0;
static oled_state_m2s_t g_remote_oled_state = { false };
static presses_m2s_t g_remote_presses = {0, 0};

static inline pin_t get_charge_pump_enable_pin(void) {
    return is_keyboard_left() ? GP5 : GP25;
}

void oled_blit_16x16_P(const char *icon, uint8_t x, uint8_t page) {
    for (uint8_t i = 0; i < 16; i++) {
        char top = pgm_read_byte(&icon[i]);
        char bot = pgm_read_byte(&icon[16 + i]);
        oled_write_raw_byte(top, page       * OLED_WIDTH + x + i);
        oled_write_raw_byte(bot, (page + 1) * OLED_WIDTH + x + i);
    }
}

void oled_blit_24x24_P(const char *icon, uint8_t x, uint8_t page) {
    for (uint8_t i = 0; i < 24; i++) {
        char top = pgm_read_byte(&icon[i]);
        char mid = pgm_read_byte(&icon[24 + i]);
        char bot = pgm_read_byte(&icon[48 + i]);
        oled_write_raw_byte(top, page       * OLED_WIDTH + x + i);
        oled_write_raw_byte(mid, (page + 1) * OLED_WIDTH + x + i);
        oled_write_raw_byte(bot, (page + 2) * OLED_WIDTH + x + i);
    }
}

uint16_t unwrap_keycode(uint16_t kc) {
    if (kc >= QK_MOD_TAP && kc <= QK_MOD_TAP_MAX)   return QK_MOD_TAP_GET_TAP_KEYCODE(kc);
    if (kc >= QK_LAYER_TAP && kc <= QK_LAYER_TAP_MAX) return QK_LAYER_TAP_GET_TAP_KEYCODE(kc);
    return kc;
}

uint16_t get_current_dwpm(void) { return (uint16_t)get_current_wpm() * 10u; }

uint8_t round_percentage(float x) {
    float f = x + 0.5f;
    uint8_t r = (uint8_t)f;
    if ((f - (float)r) == 0.0f && (r & 1)) r--;
    return r;
}

void oled_print_right_aligned(const char *text, const uint8_t width) {
    uint8_t len = strlen(text);
    uint8_t pad = (len < width) ? (width - len) : 0;
    for (uint8_t i = 0; i < pad; i++) oled_write_P(PSTR(" "), false);
    oled_write(text, false);
}

// Layer names updated to the Vibranium layer set (was Base/Lower/Raise/Adjust).
void print_current_layer(uint8_t row) {
    char layer_str[8];
    switch (get_highest_layer(layer_state)) {
        case _BASE:   strcpy(layer_str, "Base");  break;
        case _NAV:    strcpy(layer_str, "Nav");   break;
        case _SYM:    strcpy(layer_str, "Sym");   break;
        case _NUM:    strcpy(layer_str, "Num");   break;
        case _LANG:   strcpy(layer_str, "Lang");  break;
        case _SYS:    strcpy(layer_str, "Sys");   break;
        case _QWERTY: strcpy(layer_str, "Qwrt");  break;
        default:
            snprintf(layer_str, sizeof(layer_str), "%d", get_highest_layer(layer_state));
    }
    oled_set_cursor(0, row);
    oled_print_right_aligned(layer_str, g_oled_max_char);
}

void print_uptime(uint8_t row) {
    uint32_t total_min = timer_read32() / 60000u;
    uint32_t hours = total_min / 60u, minutes = total_min % 60u;
    if (hours > 999u) { hours = 999u; minutes = 59u; }
    char buf[8];
    snprintf(buf, sizeof(buf), "%3luh%02lum", (unsigned long)hours, (unsigned long)minutes);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void print_wpm(uint8_t row) {
    uint16_t wpm = get_current_dwpm();
    char buf[11];
    snprintf(buf, sizeof(buf), "%3u.%1u WPM", wpm / 10u, wpm % 10u);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void print_balance(uint8_t row, uint8_t pct) {
    char buf[6];
    snprintf(buf, sizeof(buf), "%3u %%", pct);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void render_splash(void) {
    if (g_splash_rendered) return;
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_raw_P(STARTUP_BITMAP, sizeof(STARTUP_BITMAP));
    g_splash_rendered = true;
}

static void user_sync_oled_state_slave(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
    if (in_len >= sizeof(oled_state_m2s_t)) memcpy(&g_remote_oled_state, in_data, sizeof(oled_state_m2s_t));
}
static void user_sync_lastkey_slave(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
    if (in_len >= sizeof(lastkey_m2s_t)) { const lastkey_m2s_t* p = (const lastkey_m2s_t*)in_data; g_last_keycode = p->keycode; }
}
static void user_sync_presses_slave(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
    if (in_len >= sizeof(presses_m2s_t)) memcpy(&g_remote_presses, in_data, sizeof(presses_m2s_t));
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_90; }

bool oled_post_init(void) {
    if (!g_oled_init_done) {
        g_oled_max_char = oled_max_chars();
        g_oled_max_line = oled_max_lines();
        pin_t dsp_pen_pin = get_charge_pump_enable_pin();
        gpio_write_pin_high(dsp_pen_pin);
        wait_ms(20);
        oled_clear();
        g_splash_start_ms = timer_read32();
        g_splash_active = true;
        g_oled_init_done = true;
    }
    return false;
}

bool oled_task_user(void) {
    oled_post_init();

    if (g_splash_active) {
        if (timer_elapsed32(g_splash_start_ms) > SPLASH_DURATION_MS) {
            g_splash_active = false;
            oled_clear();
            g_user_ontime = timer_read32();
        } else {
            render_splash();
        }
        return false;
    }

    uint32_t local_presses_left, local_presses_right;
    if (is_keyboard_master()) {
        local_presses_left = g_press_left;
        local_presses_right = g_press_right;
    } else {
        local_presses_left = g_remote_presses.left;
        local_presses_right = g_remote_presses.right;
    }

    if (is_keyboard_master()) {
        const uint32_t idle_time = timer_elapsed32(g_user_ontime);
        if (!is_oled_on()) {
            if (idle_time > OLED_TIMEOUT_USER) { return false; }
            oled_on();
            oled_state_m2s_t pkt = { true };
            (void)transaction_rpc_send(USER_SYNC_OLED_STATE, sizeof(pkt), &pkt);
        } else if (idle_time > OLED_TIMEOUT_USER) {
            oled_off();
            oled_state_m2s_t pkt = { false };
            (void)transaction_rpc_send(USER_SYNC_OLED_STATE, sizeof(pkt), &pkt);
            return false;
        }
    } else {
        if (g_remote_oled_state.oled_on) {
            if (!is_oled_on()) oled_on();
        } else {
            if (is_oled_on()) oled_off();
            return false;
        }
    }

    uint32_t total = local_presses_left + local_presses_right;
    if (total == 0) total = 1;
    uint8_t pct_left  = round_percentage((100.0f * local_presses_left) / total);
    uint8_t pct_right = round_percentage((100.0f * local_presses_right) / total);

    if (is_keyboard_left()) {
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Layer:"), false);
        print_current_layer(1);

        led_t led_state = host_keyboard_led_state();
        oled_blit_16x16_P(led_state.num_lock    ? NUM_LOCK_BITMAP    : EMPTY_BITMAP, 0,  3);
        oled_blit_16x16_P(led_state.caps_lock   ? CAPS_LOCK_BITMAP   : EMPTY_BITMAP, 24, 3);
        oled_blit_16x16_P(led_state.scroll_lock ? SCROLL_LOCK_BITMAP : EMPTY_BITMAP, 48, 3);

        oled_set_cursor(0, 7);
        oled_write_P(PSTR("Left:"), false);
        print_balance(8, pct_left);

        oled_set_cursor(0, 10);
        oled_write_P(PSTR("Last Key:"), false);
        oled_set_cursor(0, 11);
        oled_print_right_aligned(get_keycode_string(unwrap_keycode(g_last_keycode)), g_oled_max_char);

        oled_set_cursor(0, 13); oled_write_P(QMK_LOGO_1, false);
        oled_set_cursor(0, 14); oled_write_P(QMK_LOGO_2, false);
        oled_set_cursor(0, 15); oled_write_P(QMK_LOGO_3, false);
        oled_set_cursor(7, 15); oled_write_P(PSTR("QMK"), false);
    } else {
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Uptime:"), false);
        print_uptime(1);

        oled_set_cursor(0, 3); oled_write_P(PSTR("Avg Speed"), false);
        oled_set_cursor(0, 4); oled_write_P(PSTR("(25 s):"), false);
        print_wpm(5);

        oled_set_cursor(0, 7);
        oled_write_P(PSTR("Right:"), false);
        print_balance(8, pct_right);

        oled_blit_24x24_P(KEEBART_BITMAP_24x24, 20, 11);
        oled_set_cursor(2, 15); oled_write_P(PSTR("KEEBART"), false);
    }
    return false;
}
#endif // OLED_ENABLE

// =============================================================================
//  MERGED SHARED HOOKS
//  These combine Keebart's OLED/split-sync work with twin's RGB pulses and
//  custom-keycode handling. Only ONE definition of each may exist, so the two
//  sources' bodies are interleaved here.
// =============================================================================

void keyboard_post_init_user(void) {
#ifdef OLED_ENABLE
    // Keebart: bring up the OLED charge-pump enable pin and register RPCs.
    pin_t dsp_pen_pin = get_charge_pump_enable_pin();
    gpio_set_pin_output(dsp_pen_pin);
    gpio_write_pin_low(dsp_pen_pin);
    wait_ms(5);

    transaction_register_rpc(USER_SYNC_OLED_STATE, user_sync_oled_state_slave);
    transaction_register_rpc(USER_SYNC_LASTKEY,    user_sync_lastkey_slave);
    transaction_register_rpc(USER_SYNC_PRESSES,    user_sync_presses_slave);

    if (!is_keyboard_master()) {
        wait_ms(90);
    }
#endif

#ifdef RGB_MATRIX_ENABLE
    start_activity_pulse(170, 200); // twin: blue startup pulse
#endif
}

void housekeeping_task_user(void) {
#ifdef OLED_ENABLE
    // Keebart: master periodically pushes OLED on/off state to the slave.
    if (is_keyboard_master()) {
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            oled_state_m2s_t pkt = { is_oled_on() };
            (void)transaction_rpc_send(USER_SYNC_OLED_STATE, sizeof(pkt), &pkt);
            last_sync = timer_read32();
        }
    }
#endif

#ifdef RGB_MATRIX_ENABLE
    activity_pulse_tick(); // twin: drive the RGB pulse envelope
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    // Keebart: track activity time, last keycode, and per-half press counts.
    g_user_ontime = timer_read32();
    if (record->event.pressed) {
        g_last_keycode = keycode;
        if (record->event.key.row < MATRIX_ROWS / 2) g_press_left++;
        else                                          g_press_right++;
        if (is_keyboard_master()) {
            lastkey_m2s_t kp = { g_last_keycode };
            (void)transaction_rpc_send(USER_SYNC_LASTKEY, sizeof(kp), &kp);
            presses_m2s_t pp = { g_press_left, g_press_right };
            (void)transaction_rpc_send(USER_SYNC_PRESSES, sizeof(pp), &pp);
        }
    }
#endif

    // twin: digraphs + mod-morph punctuation.
    switch (keycode) {
        case HD_TH: if (record->event.pressed) send_hd_digraph(KC_T, KC_H); return false;
        case HD_CH: if (record->event.pressed) send_hd_digraph(KC_C, KC_H); return false;
        case HD_SH: if (record->event.pressed) send_hd_digraph(KC_S, KC_H); return false;
        case HD_WH: if (record->event.pressed) send_hd_digraph(KC_W, KC_H); return false;
        case HD_GH: if (record->event.pressed) send_hd_digraph(KC_G, KC_H); return false;
        case HD_PH: if (record->event.pressed) send_hd_digraph(KC_P, KC_H); return false;

        case P_HASH_AT:   if (record->event.pressed) tap_code16_without_user_shift(hd_shifted() ? S(KC_2)    : S(KC_3));    return false;
        case P_DOT_COLN:  if (record->event.pressed) tap_code16_without_user_shift(hd_shifted() ? S(KC_SCLN) : KC_DOT);     return false;
        case P_SLSH_ASTR: if (record->event.pressed) tap_code16_without_user_shift(hd_shifted() ? S(KC_8)    : KC_SLSH);    return false;
        case P_DQUO_EXLM: if (record->event.pressed) tap_code16_without_user_shift(hd_shifted() ? S(KC_1)    : S(KC_QUOT)); return false;
        case P_QUOT_QUES: if (record->event.pressed) tap_code16_without_user_shift(hd_shifted() ? S(KC_SLSH) : KC_QUOT);    return false;
        case P_COMM_SCLN: if (record->event.pressed) tap_code16_without_user_shift(hd_shifted() ? KC_SCLN    : KC_COMM);    return false;
        case P_MINS_PLUS: if (record->event.pressed) tap_code16_without_user_shift(hd_shifted() ? S(KC_EQL)  : KC_MINS);    return false;
    }
    return true;
}
