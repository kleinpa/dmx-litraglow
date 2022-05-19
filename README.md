# Similar Projects

Khary Mendez appears to have been the first to document the HID commands required to control the Litra Glow.

- https://github.com/kharyam/litra-driver (Python)
- https://ultracrepidarian.phfactor.net/2022/03/09/controlling-the-logitech-litra-on-macos/ (shell + hidapitester)
  - `bazel run //:hidapitester -- --vidpid 046d/c900 --usagePage ff43 --open --send-output 0x11,0xFF,0x04,0x1D,0x01`
- https://github.com/zource-dev/litra-glow (TypeScript)
