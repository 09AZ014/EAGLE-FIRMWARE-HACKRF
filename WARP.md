# WARP.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

---

## Project Overview

**EAGLE-FIRMWARE** is a fork of PortaPack Mayhem firmware for the HackRF One + PortaPack platform. This is an embedded systems project targeting ARM Cortex-M microcontrollers, specifically the LPC43xx (M4F + M0 dual-core).

**Key characteristics:**
- Embedded C++ firmware (C++17/C++20)
- Real-time operating system (ChibiOS RTOS)
- Dual-core architecture: M4F (application) and M0 (baseband DSP)
- Cross-compiled for ARM using `arm-none-eabi-gcc 9.2.1`
- External apps system for modular features

---

## Build Commands

### Docker Build (Recommended)
```powershell
# Build Docker image
docker build -t eagle-firmware:latest .

# Compile firmware (output to build-output/)
docker run --rm -v "${PWD}/build-output:/eaglebin" eagle-firmware:latest
```

### Native Build (Linux/WSL)
```bash
# Initial setup
mkdir build && cd build
cmake ..

# Full build (parallel)
make -j$(nproc)

# Specific targets
make firmware           # Main firmware only
make standalone_apps    # External apps only
make ppfw              # Create .ppfw bundle for SD card
```

### Clean Build
```bash
# From build directory
rm -rf *
cmake ..
make -j$(nproc)
```

---

## Development Commands

### Code Formatting
```bash
# Format all source files
./format-code.sh
```
Uses `clang-format-13` on all `.h`, `.hpp`, `.cpp`, `.c` files in firmware directories.

### Testing
There is a test framework in `firmware/test/`:
```bash
# Build tests (from build directory)
make test_application
make test_baseband

# Run tests (if compiled for host)
./test/application/test_application
./test/baseband/test_baseband
```

**Note:** Tests are primarily unit tests for specific components (circular_buffer, string_format, etc.). Hardware-specific features cannot be tested on host.

### Flashing Firmware

**Via PortaPack UI (easiest):**
1. Copy firmware `.bin` to SD card `FIRMWARE/` folder
2. Settings → Update Firmware → Select file
3. Confirm and reboot

**Via DFU (Windows):**
```powershell
cd flashing
.\flash_portapack_eagle.bat
```

**Via DFU (Linux/Mac):**
```bash
cd flashing
sudo python3 flash.py path/to/firmware.bin
```

---

## Architecture

### Dual-Core Design
This firmware runs on a **dual-core ARM architecture**:

1. **M4F Core (Application Processor)**
   - Runs main UI and application logic
   - Located in `firmware/application/`
   - Uses ChibiOS RTOS for task scheduling
   - Handles user input, graphics, file I/O

2. **M0 Core (Baseband Processor)**
   - Runs DSP and signal processing
   - Located in `firmware/baseband/`
   - Processes RF samples from HackRF
   - Implements modulation/demodulation

Communication between cores uses **shared memory** (`portapack_shared_memory.cpp`).

### Directory Structure

```
firmware/
├── application/          # M4F application code
│   ├── apps/            # Core built-in apps
│   ├── external/        # External/plugin apps (games, RF tools)
│   ├── ui/              # UI framework and widgets
│   ├── hw/              # Hardware drivers (MAX2837, RFFC507x, etc.)
│   └── protocols/       # Protocol implementations
├── baseband/            # M0 baseband DSP code
│   ├── fprotos/         # Sub-GHz protocol decoders
│   └── proc_*.cpp       # Signal processors (AM, FM, ADS-B, etc.)
├── common/              # Shared code between M4F/M0
├── standalone/          # Standalone external apps
├── bootstrap/           # Bootloader
└── tools/               # Build utilities

hackrf/                  # HackRF One hardware support
├── firmware/            # USB firmware for HackRF
└── hardware/            # PCB schematics

sdcard-eagle/            # SD card structure
├── APPS/                # External app binaries (.ppma, .ppmp)
├── FIRMWARE/            # Firmware binaries
└── README_SD.txt
```

### External Apps System

External apps are **dynamically loaded** from SD card at runtime:

- **Built with:** CMake compiles each external app separately
- **Location:** `firmware/application/external/`
- **Output format:** `.ppma` (application) or `.ppmp` (standalone)
- **Loading:** Apps are loaded into RAM when launched

**Adding a new external app:**
1. Create directory in `firmware/application/external/myapp/`
2. Add source files (`ui_myapp.cpp`, `ui_myapp.hpp`)
3. Register in `external/external.cmake`
4. Build produces `myapp.ppma` in `build/application/`

Example apps: pong, snake, tetris, rf_mapper, protocol_decoder

### Hardware Abstraction

Key hardware components:
- **MAX2837** (`hw/max2837.*`) - RF transceiver
- **RFFC507x** (`hw/rffc507x.*`) - Mixer/synthesizer
- **Si5351** (`hw/clock_generator.*`) - Clock generator
- **CPLD** (`common/cpld_max5.cpp`) - Programmable logic for SGPIO
- **LCD ILI9341** (`common/lcd_ili9341.cpp`) - Display driver

### Build System Flow

1. **CMake configuration** (`CMakeLists.txt`) sets up targets
2. **Application build** creates `application.bin` (M4F firmware)
3. **Baseband build** creates multiple baseband processors → `baseband.img`
4. **Firmware merge** combines application + baseband → `portapack-eagle-firmware.bin`
5. **PPFW packaging** bundles firmware + apps → `.ppfw.tar` for SD card

**Version string** is set in root `CMakeLists.txt`:
```cmake
set(VERSION_NOHASH "EAGLE-1.0.0-09AZO14")
```

---

## Coding Conventions

- **Language:** C++17/C++20 (no RTTI, no exceptions)
- **Formatting:** Use `./format-code.sh` (clang-format-13)
- **Naming:**
  - Classes: `PascalCase` (e.g., `ProtocolDecoderView`)
  - Functions: `snake_case` (e.g., `decode_packet()`)
  - Members: `snake_case_` with trailing underscore
  - Constants: `UPPER_CASE`
- **UI Views:** Inherit from `View` class, implement `title()` method
- **Event handling:** Use message passing via `MessageHandlerRegistration`

### Memory Constraints
- **M4F RAM:** ~256KB total
- **M0 RAM:** ~32KB for baseband
- **Avoid dynamic allocation** - use static buffers where possible
- External apps loaded into limited runtime memory

### Important Patterns

**UI View Pattern:**
```cpp
class MyAppView : public View {
public:
    MyAppView(NavigationView& nav);
    ~MyAppView();
    
    std::string title() const override { return "My App"; }
    void focus() override;
    
private:
    NavigationView& nav_;
    // UI widgets...
};
```

**Baseband Processor Pattern:**
```cpp
class MyProcessor : public BasebandProcessor {
public:
    void execute(buffer_c8_t buffer) override;
    void on_message(const Message* const msg) override;
    
private:
    // DSP state...
};
```

---

## Hardware-Specific Notes

### PortaPack Models
This firmware targets:
- **H1/H2/H2+/H2M** - Original and common models
- **H4M** - Latest model with improvements

### SD Card Requirements
- **Format:** FAT32
- **Size:** 8GB+ recommended
- **Structure:** See `sdcard-eagle/` for required folders

### RF Safety
- **Always check local regulations** before transmitting
- **Default frequencies** may be illegal in your region
- **Power limits** vary by country and band

---

## Troubleshooting

### Build Issues

**"arm-none-eabi-gcc not found":**
```bash
# Ubuntu/Debian
sudo apt install gcc-arm-none-eabi

# macOS
brew install arm-none-eabi-gcc

# Verify version (must be 9.2.1 for official builds)
arm-none-eabi-gcc --version
```

**"submodules not initialized":**
```bash
git submodule update --init --recursive
```

**CMake version too old:**
```bash
# Need CMake 3.16+
cmake --version
```

### Runtime Issues

**External app won't load:**
- Check `.ppma` file is in `SD:/APPS/`
- Verify SD card formatted as FAT32
- Check app file not corrupted (re-copy from build output)

**Firmware update fails:**
- Ensure `.bin` file in `SD:/FIRMWARE/`
- Battery must have sufficient charge
- Try different SD card if persistent

---

## Related Documentation

- **README_EAGLE.md** - Full feature list, installation guide, changelog
- **INSTALLATION_GUIDE.md** - Detailed setup instructions
- **firmware/tools/bitmap_tools/README.md** - Creating custom graphics
- **PortaPack Mayhem Wiki** - https://github.com/portapack-mayhem/mayhem-firmware/wiki

---

## Common Tasks

### Adding a new frequency preset
Edit `firmware/application/freqman_db.cpp` and add entry to frequency database.

### Creating a new UI widget
1. Create `ui/ui_mywidget.hpp` and `.cpp`
2. Inherit from `Widget` base class
3. Implement `paint()` and event handlers
4. Add to parent view's constructor

### Implementing a new signal processor
1. Create `baseband/proc_mysignal.hpp` and `.cpp`
2. Inherit from `BasebandProcessor`
3. Implement `execute()` for sample processing
4. Register processor in `baseband/baseband_thread.cpp`

### Modifying version string
Edit `CMakeLists.txt` in root:
```cmake
set(VERSION_NOHASH "EAGLE-X.X.X-YOURNAME")
```

---

## Contribution Notes

- This is a **personal fork** of PortaPack Mayhem
- Upstream: https://github.com/portapack-mayhem/mayhem-firmware
- Base license: **GPL-2.0**
- When adding features, consider contributing upstream to benefit the community

---

## Windows Development Notes

Since you're on Windows:
- Use **Docker** for building (easiest)
- Or use **WSL2** with Ubuntu for native builds
- **PowerShell** scripts provided for common tasks
- DFU flashing on Windows requires **Zadig** drivers for HackRF

---

## Performance Considerations

- **UI refresh rate:** 30-60 FPS target
- **Baseband sample rate:** Up to 20 MSPS (HackRF limit)
- **Minimize allocations** in hot paths (baseband processing)
- **Use const references** to avoid copies
- **Profile before optimizing** - embedded systems are different than desktop

---

## Debugging

**Serial Debug Output:**
- Connect USB serial (CDC ACM)
- Baudrate: 115200
- Debug prints via `chprintf()` (ChibiOS printf)

**LED Indicators:**
- HackRF LED behavior indicates firmware state
- Check hardware for visual debugging

**No hardware debugger access** - mostly printf-style debugging or logic analyzer for digital signals.
