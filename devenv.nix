{
  pkgs,
  config,
  ...
}: let
  kbPath = "qmk/keyboards/keebart/corne_choc_pro/keymaps/adam";
in {
  packages = with pkgs; [
    qmk # CLI + drives the build
    gcc-arm-embedded # arm-none-eabi toolchain for RP2040
    git
    picotool # RP2040 flashing / inspection
  ];

  # Wire the config submodule into the QMK tree and ensure QMK's own
  # submodules are present before any build.
  enterShell = ''
    git -C "${config.git.root}" submodule update --init --recursive

    if [ ! -e "${config.git.root}/${kbPath}" ]; then
      ln -sfn "${config.git.root}/config" "${config.git.root}/${kbPath}"
      echo "Linked config -> ${kbPath}"
    fi
  '';

  # Convenience build wrappers. Validate against the _ex2 (inner-key) target
  # first to confirm the twin's base is sound, then build your own.
  scripts.kb-validate.exec = ''
    cd "${config.git.root}/qmk" && make keebart/corne_choc_pro/mini:adam
  '';
  scripts.kb-flash.exec = ''
    cd "${config.git.root}/qmk" && make keebart/corne_choc_pro/mini:adam:flash
  '';
}
