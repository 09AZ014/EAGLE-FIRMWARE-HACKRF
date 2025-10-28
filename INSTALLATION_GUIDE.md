# 🦅 EAGLE-FIRMWARE v2.0.0 - INSTALLATION GUIDE

## 📦 **PACKAGE CONTENTS**

Este projeto está **100% PRONTO** para uso! Inclui:

- ✅ **Source Code Completo** (firmware/)
- ✅ **SD Card Structure** (sdcard-eagle/)
- ✅ **Documentação Completa** (README_EAGLE.md)
- ✅ **GitHub Actions CI/CD** (.github/workflows/)
- ✅ **Docker Build System** (Dockerfile)

---

## 🎯 **QUICK START - 3 STEPS**

### **STEP 1: CRIAR REPOSITÓRIO GITHUB** ⏱️ 2 minutos

Executa o script automático:

```powershell
cd 'C:\Users\AZO\Desktop\Firmware Hack RF one\EAGLE-FIRMWARE'
.\create_github_repo.ps1
```

**O script vai:**
1. Pedir o teu username do GitHub
2. Pedir um Personal Access Token (PAT)
3. Criar o repositório automaticamente
4. Fazer push do código
5. Dar-te o link do repo criado!

**Se não tiveres PAT:**
- Vai a: https://github.com/settings/tokens
- "Generate new token (classic)"
- Seleciona: `repo` (full control)
- Copia o token e usa no script

---

### **STEP 2: PREPARAR SD CARD** ⏱️ 5 minutos

1. **Formata** o cartão microSD como **FAT32**

2. **Copia TODO** o conteúdo de `sdcard-eagle/` para a **RAIZ** do SD:

```
SD:/
├── APPS/              ← 61 apps externas
├── FIRMWARE/          ← Firmware binaries
├── RFMAP/             ← RF Signal Mapper data
├── DECODER/           ← Protocol Decoder logs
└── README_SD.txt      ← Instruções
```

3. **Lê o ficheiro:** `SD:/README_SD.txt` para detalhes

---

### **STEP 3: INSTALAR NO PORTAPACK** ⏱️ 3 minutos

1. **Insere** o SD card no PortaPack H2

2. **Liga** o HackRF One + PortaPack

3. No PortaPack:
   - `Settings` → `Update Firmware`
   - Seleciona: `portapack-eagle-vXX.bin`
   - Aguarda flash completo (não desliges!)
   - Reboot automático

4. **Verifica versão:**
   - `Settings` → `About`
   - Deve mostrar: `EAGLE-2.0.0-09AZO14`

---

## 🎮 **TESTING THE NEW FEATURES**

### **Test RF Signal Mapper:**
1. `Main Menu` → `RF Tools` → `RF Signal Mapper`
2. Define frequência (ex: 433.920 MHz)
3. Press `START`
4. Move-te pela casa/área
5. Vê o heatmap em tempo real!
6. Press `SAVE` para guardar

### **Test Protocol Decoder:**
1. `Main Menu` → `RF Tools` → `Protocol Decoder`
2. Ativa `AUTO: ON`
3. Aguarda detecção automática
4. Testa com remote control 433MHz
5. Vê os pacotes decodificados!

### **Test Games:**
1. `Main Menu` → `Utilities` → `Games`
2. Escolhe: Snake, Tetris, Pong, etc
3. Diverte-te! 🎮

---

## 🔧 **ADVANCED: COMPILE FROM SOURCE**

Se quiseres compilar tu mesmo:

### **Option A: Docker (Recommended)**

```powershell
cd 'C:\Users\AZO\Desktop\Firmware Hack RF one\EAGLE-FIRMWARE'

# Build Docker image
docker build -t eagle-firmware:v2.0.0 .

# Compile firmware
docker run --rm -v "${PWD}/build-output:/eaglebin" eagle-firmware:v2.0.0

# Check output
ls build-output/*.bin
```

**Compilation time:** ~10-15 minutes

**Output files:**
- `portapack-h1_h2-eagle-EAGLE-XXXX.bin` ← Main firmware
- `hackrf_usb.dfu` ← HackRF USB firmware
- `*.bin` ← Baseband processors

### **Option B: Native Linux/WSL**

```bash
# Install dependencies
sudo apt update
sudo apt install git cmake gcc-arm-none-eabi python3

# Build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Output in: build/firmware/*.bin
```

---

## 📊 **PROJECT STATISTICS**

```
Lines of Code:        50,000+
New Features:         2 (RF Mapper + Protocol Decoder)
Games:                8
External Apps:        61
Documentation:        1,000+ lines
Commits:              9
Git Status:           ✅ Clean, ready to push
```

---

## 🗂️ **PROJECT STRUCTURE**

```
EAGLE-FIRMWARE/
├── .github/
│   └── workflows/
│       └── build_eagle.yml          # CI/CD automation
├── firmware/
│   ├── application/
│   │   ├── apps/                    # Core apps
│   │   └── external/                # External apps
│   │       ├── rf_mapper/           # ✨ NEW
│   │       ├── protocol_decoder/    # ✨ NEW
│   │       ├── pong/
│   │       ├── snake/
│   │       ├── tetris/
│   │       └── ... (8 games total)
│   ├── baseband/                    # DSP processors
│   └── common/                      # Shared code
├── sdcard-eagle/                    # 💾 SD CARD CONTENT
│   ├── APPS/                        # 61 external apps
│   ├── FIRMWARE/                    # Firmware binaries
│   ├── RFMAP/                       # RF mapper data
│   ├── DECODER/                     # Decoder logs
│   └── README_SD.txt
├── README_EAGLE.md                  # Main documentation
├── INSTALLATION_GUIDE.md            # This file
├── GITHUB_SETUP.md                  # GitHub setup guide
├── QUICK_GITHUB_SETUP.txt           # Quick reference
├── create_github_repo.ps1           # Auto repo creator
├── banner.svg                       # Repository banner
└── Dockerfile                       # Docker build

9 commits ready to push!
```

---

## 🆘 **TROUBLESHOOTING**

### **Issue: Firmware não aparece no menu Update**
**Solution:** Verifica que o ficheiro `.bin` está em `SD:/FIRMWARE/`

### **Issue: Apps externas não aparecem**
**Solution:** Copia `APPS/` para a raiz do SD (não subpastas!)

### **Issue: RF Mapper não grava ficheiros**
**Solution:** Cria a pasta `RFMAP/` na raiz do SD

### **Issue: Docker build falha**
**Solution:** 
```powershell
# Clean and rebuild
docker system prune -a
docker build --no-cache -t eagle-firmware:v2.0.0 .
```

### **Issue: Git push falha**
**Solution:**
```powershell
# Check remotes
git remote -v

# If wrong, remove and re-add
git remote remove origin
git remote add origin https://github.com/YOUR_USERNAME/eagle-firmware.git
git push -u origin main
```

---

## 📞 **SUPPORT & COMMUNITY**

- **GitHub Issues:** Report bugs
- **Discussions:** Ask questions
- **Wiki:** Detailed documentation
- **Email:** eagle.firmware@proton.me

---

## 🎉 **YOU'RE ALL SET!**

### **Checklist:**
- [ ] Repository created on GitHub
- [ ] Code pushed successfully  
- [ ] SD card prepared
- [ ] Firmware installed on PortaPack
- [ ] New features tested
- [ ] Having fun! 🎮

---

## 🚀 **NEXT STEPS**

1. **Share with community:**
   - Post on Reddit: r/hackrf, r/RTLSDR
   - Discord: PortaPack Mayhem server
   - Twitter/X: #HackRF #PortaPack

2. **Create Release v2.0.0:**
   - On GitHub: Releases → "Draft new release"
   - Tag: `v2.0.0`
   - Upload compiled `.bin` files
   - Copy changelog from README_EAGLE.md

3. **Enable GitHub Actions:**
   - Go to Actions tab
   - Enable workflows
   - Auto-build on every push!

4. **Add topics to repo:**
   - Settings → Topics
   - Add: `hackrf`, `portapack`, `firmware`, `sdr`, `rf`, `eagle`

---

<div align="center">

## 🦅 **FLY HIGHER WITH EAGLE!** 🦅

**Made with ❤️ by 09AZO14**

[![Version](https://img.shields.io/badge/version-2.0.0-blue.svg)](https://github.com/09AZO14/eagle-firmware)
[![License](https://img.shields.io/badge/license-GPL--2.0-green.svg)](LICENSE)

**This is more than firmware. This is freedom.** 📡

</div>

