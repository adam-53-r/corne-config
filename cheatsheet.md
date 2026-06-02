# Corne Choc Pro (OLED) — Hands Down Vibranium-f Cheatsheet

Your board: 36 keys (3×5 + 3 thumbs per hand), OLED mini. Built as **plain QMK**
(not Vial) so all the smart features below work. Layout is **Hands Down
Vibranium-f** (the "R-on-thumb" variant, a.k.a. Vibranium-vf) by R. Alan Reiser.

> Notation: `tap` = quick press. `hold` = press and keep down. `A+B` = press
> both keys together (a combo).

---

## 1. Base layer (what each key types)

```
 X   W   M   G   J   │   #   .   /   "   '
 S   C   N   T   K   │   ,   A   E   I   H
 F   P   L   D   V   │   -   U   O   Y   B
         ┌───┬───┬───┤   ├───┬───┬───┐
         │Cap│ R │Nav│   │Sym│Spc│Bsp│
         └───┴───┴───┘   └───┴───┴───┘
```

The home row is `S C N T` (left) and `A E I H` (right). Rest your eight fingers
there. Index fingers reach `K` and `,`/comma area.

---

## 2. Home-row mods (hold a home-row key = a modifier)

Tap the letter normally; **hold** it to get the modifier. Mirror image per hand.

| Finger | Left (hold) | Right (hold) |
|--------|-------------|--------------|
| Pinky  | **S** → Alt | **H** → Alt  |
| Ring   | **C** → Ctrl| **I** → Ctrl |
| Middle | **N** → Gui/Super | **E** → Gui/Super |
| Index  | **T** → Shift | **A** → Shift |

Memory aid: **GACS** outward from the middle — **G**ui, **A**lt is the pinky,
no wait — easier: middle=Gui, ring=Ctrl, pinky=Alt, index=Shift. The strongest
finger (index) gets the most-used mod (Shift).

**Tip:** to type a same-hand combo of letter+mod, the firmware uses *Chordal
Hold* — a hold only triggers the modifier when you also press a key on the
**opposite** hand. Same-hand rolls just type letters. This kills accidental
mod-triggers. (So: Shift+a letter = use opposite hands.)

---

## 3. Thumb keys

| Thumb | Tap | Hold |
|-------|-----|------|
| Left 1 | Caps Lock | **System** layer |
| Left 2 | **R** | **Language** layer (accents) |
| Left 3 | (Nav momentary) | Nav layer |
| Right 1 | (Sym momentary) | Sym layer |
| Right 2 | Space | — |
| Right 3 | Backspace | — |

> These two holds (System on Caps, Language on R) are the conversion's only
> change vs. your twin's 40-key board — his inner keys became thumb-holds.
> Everything else is identical to his layout.

---

## 4. Smart combos (press two keys together)

### H-digraphs (the signature Hands Down feature)
Reduces awkward same-finger motions for common English pairs.

| Press together | Types |
|----------------|-------|
| **T + N** | th |
| **C + N** | ch |
| **S + C** | sh |
| **W + M** | wh |
| **G + M** | gh |
| **F + P** | ph |

Shift while combo-ing → capitalises only the first letter (Th, not TH).

### Smart letters
| Press together | Types | Note |
|----------------|-------|------|
| **J + G** | z | z has no home key; this is how you type it |
| **T + K** | qu | the common English pair |
| **T + K**, then *hold* | q | hold past ~175 ms deletes the "u", leaving a bare q |

These live in C code (not the Vial GUI) because the smart-q hold-logic can't be
expressed in a GUI. To change them, edit `keymap.c`.

---

## 5. Layers

Hold the thumb/key shown to reach each layer. Release to return to base.

### NAV (hold left thumb 3) — navigation & editing
```
Undo Cut  Copy Paste Save │ PgUp Home  ↑   End  Del
Alt  Ctrl Gui  Sft  Tab   │ PgDn  ←    ↓   →    Bspc
Find S-Tb Prv  Nxt  A-Tb  │ Ins  Wrd←  Wrd→ ⌃Bsp ⌃Del
                          │ →NUM  Esc  Enter
```
(`Wrd←/→` = jump word. `⌃Bsp/⌃Del` = delete word. Prv/Nxt = prev/next tab.)

### SYM (hold right thumb 1) — symbols
```
!  @  #  $  %  │  [  ]  {  }  |
^  &  *  +  =  │  (  )  <  >  /
~  -  _  :  ;  │  `  '  "  ?  \
               │ →NUM
```

### NUM (hold Nav+Sym, or the →NUM key) — numbers & F-keys
```
F1  F2  F3  F4  F5  │  /  7  8  9  -
F6  F7  F8  F9  F10 │  *  4  5  6  +
F11 F12 0   .   =   │  %  1  2  3  0
```
Right hand is a numpad. Reach NUM from inside NAV or SYM (the bottom-row key).

### LANG (hold R thumb) — Catalan/Spanish accents
```
 ·   ·   ñ   ç   ß  │   á   é   í   ó   ú       (acute)
 ·   ·   ¿   ·   €  │   à   è   ì   ò   ù       (grave)
 ·   ·   ¡   ·   ·  │   ä   ë   ï   ö   ü       (umlaut)
```
**Workflow:** hold **R**, tap the vowel, release. Shift → uppercase (Á, É…).
The three rows on the right hand are acute / grave / umlaut accents.
Left hand has ñ ç ß and ¿ ¡ · €.

### SYS (hold Caps thumb) — system
```
UcLin UcWin Vibra Qwerty ·  │ PrSc ScLk Pause  ·   ·
Mute  Vol-  Vol+  Bri-  Bri+│ Prev Play Next  Stop ·
RGB    ·     ·    NumLk Menu│  ·    ·    ·     ·   ·
```
- `UcLin`/`UcWin` = switch Unicode input mode (Linux ibus vs Windows). Set this
  once to match the machine, or it'll mistype accents.
- `Vibra`/`Qwerty` = permanently switch base layer.
- `RGB` = toggle per-key lighting.

### QWERTY (from SYS → Qwerty) — rescue layer
Standard QWERTY for guests or fallback. Switch back via SYS → Vibra.

---

## 6. The OLED screens

- **Left screen:** current layer name, lock indicators (Num/Caps/Scroll),
  left-hand keypress %, last key pressed, QMK logo.
- **Right screen:** uptime, average typing speed (WPM), right-hand keypress %,
  Keebart logo.
- Screens show a splash for ~2.5 s on boot, then sleep after 60 s idle.

---

## 7. Unicode input mode (important first step)

Accents use QMK Unicode, which needs the OS mode set correctly:
- **Linux (ibus or X compose with Unicode hex):** press `UcLin` on the SYS layer.
- **Windows:** `UcWin` (uses WinCompose — install it from
  <https://github.com/samhocevar/wincompose>).

On NixOS/Wayland with ibus, Hands Down's `UNICODE_MODE_LINUX` sends Ctrl+Shift+U
hex codes. If accents misfire, that's almost always the Unicode mode, not the
keymap.

---

## 8. Learning the layout (resources)

- **Official Hands Down site** (layout, philosophy, all variants):
  <https://sites.google.com/alanreiser.com/handsdown/home>
- **Vibranium specifics & stats:**
  <https://sites.google.com/alanreiser.com/handsdown/home/hands-down-neu>
- **Reiser's own QMK templates** (incl. Vibranium-vf, the digraph/pronoun code
  your twin's config derives from):
  <https://sites.google.com/alanreiser.com/handsdown/download>
- **Practice typing the layout** (interactive, downloadable lessons):
  <https://keyboard-design.com/letterlayout.html?layout=hands-down-vibranium-vf.ts.eu.ergodox>
- **QMK docs you'll actually use:**
  - Combos: <https://docs.qmk.fm/features/combo>
  - Tap-hold tuning: <https://docs.qmk.fm/tap_hold>
  - Layers: <https://docs.qmk.fm/feature_layers>
  - Unicode: <https://docs.qmk.fm/features/unicode>

---

## 9. Practical learning plan

1. **Week 1 — alphas only.** Type slowly. Don't worry about mods or combos.
   Use a tool like [keybr](https://www.keybr.com) or [monkeytype](https://monkeytype.com)
   set to "custom layout" practice, or the keyboard-design.com lessons above.
2. **Week 2 — home-row mods.** Add Shift first (index), then the others. The
   opposite-hand rule (Chordal Hold) means you barely have to think.
3. **Week 3 — H-digraphs + z/qu.** These feel magical once they're automatic.
4. **Then layers.** NAV and SYM become muscle memory fastest because they're
   used constantly. LANG/NUM/SYS you'll reach for as needed.

Expect ~10–20 hrs to regain rough fluency, longer for full speed. Accuracy
first, speed second.

---

## 10. Flashing the firmware

The board has two halves, each flashed separately:
1. Enter bootloader: hold the top-left key while plugging in (left half:
   hold **Q**-position; right half: hold **P**-position), **or** double-tap the
   reset button, **or** use the `QK_BOOT` key (it's on the SYS layer top-left).
2. The half mounts as a USB drive (`RPI-RP2`).
3. Drag the `.uf2` onto it (or `make keebart/corne_choc_pro/mini:adam:flash`).
4. Repeat for the other half.

The compiled firmware is `keebart_corne_choc_pro_mini_adam.uf2`.
