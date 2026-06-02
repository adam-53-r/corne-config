{
  pkgs,
  config,
  ...
}: let
  # Your keymap lives at <repo>/config and is symlinked into the QMK tree as
  # the "adam" keymap. Only qmk/ is a git submodule now; config/ is just a
  # directory in this repo.
  kbDir   = "qmk/keyboards/keebart/corne_choc_pro/keymaps";
  kbPath  = "${kbDir}/adam";
in {
  packages = with pkgs; [
    qmk              # CLI + drives the build
    gcc-arm-embedded # arm-none-eabi toolchain w/ newlib-nano (QMK needs nano.specs)
    git
    picotool         # RP2040 flashing / inspection
  ];

  enterShell = ''
    # 1. Ensure QMK's own (nested) submodules are present. The --recursive is
    #    for chibios/pico-sdk/etc. inside the qmk submodule, not for this repo.
    git -C "${config.git.root}" submodule update --init --recursive qmk

    # 2. Symlink config/ into the QMK keymaps tree as "adam".
    #    -n stops ln from dereferencing an existing symlink-to-dir; we replace
    #    any stale/incorrect link so re-entering the shell self-heals.
    mkdir -p "${config.git.root}/${kbDir}"
    target="${config.git.root}/${kbPath}"
    if [ ! -L "$target" ] || [ "$(readlink "$target")" != "${config.git.root}/config" ]; then
      ln -sfn "${config.git.root}/config" "$target"
      echo "Linked config -> ${kbPath}"
    fi
  '';

  # Build the firmware (.uf2 lands in qmk/).
  scripts.kb-build.exec = ''
    cd "${config.git.root}/qmk" && make keebart/corne_choc_pro/mini:adam
  '';

  # Compile-check only, no .uf2 (faster; catches errors).
  scripts.kb-validate.exec = ''
    cd "${config.git.root}/qmk" && qmk compile -kb keebart/corne_choc_pro/mini -km adam
  '';

  # Build then flash. Put a half into bootloader first (double-tap reset, or
  # hold the boot key on plug-in, or the QK_BOOT key on the SYS layer).
  scripts.kb-flash.exec = ''
    cd "${config.git.root}/qmk" && make keebart/corne_choc_pro/mini:adam:flash
  '';
}
