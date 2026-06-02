# Corne Choc Pro (mini, OLED) — plain-QMK build (no Vial)
# Built as pure QMK so the static-C combos (smart-QU, digraphs) work. Vial
# derives VIAL_COMBO_ENABLE from COMBO_ENABLE and takes over key_combos, which
# is incompatible with custom process_combo_event logic — so Vial is disabled.

MOUSEKEY_ENABLE  = no
EXTRAKEY_ENABLE  = yes       # media/system keys
COMBO_ENABLE     = yes       # Hands Down digraphs + smart Q/Z (static C)
UNICODEMAP_ENABLE = yes      # UP()/UM() accents
RGBLIGHT_ENABLE  = no
RGB_MATRIX_ENABLE = yes      # per-key RGB + pulses
CAPS_WORD_ENABLE = yes
REPEAT_KEY_ENABLE = yes

# OLED (this board's screens)
OLED_ENABLE      = yes
OLED_DRIVER      = ssd1306
OLED_TRANSPORT   = i2c
WPM_ENABLE       = yes
KEYCODE_STRING_ENABLE = yes  # OLED "Last Key"
