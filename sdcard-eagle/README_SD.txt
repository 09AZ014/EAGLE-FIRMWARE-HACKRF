========================================================
   EAGLE-FIRMWARE v2.0.0 - SD CARD STRUCTURE
========================================================

INSTRUCOES DE INSTALACAO:
--------------------------

1. Formata o teu cartao microSD como FAT32

2. Copia TODO o conteudo desta pasta (sdcard-eagle) 
   para a RAIZ do cartao SD

3. Estrutura final no SD deve ficar:
   SD:/
   ├── APPS/              (61 apps externas)
   ├── FIRMWARE/          (firmware binarios)
   ├── RFMAP/             (RF Signal Mapper data)
   ├── DECODER/           (Protocol Decoder logs)
   ├── ADSB/
   ├── AIS/
   ├── FREQMAN/
   └── ... (outras pastas Mayhem)

4. Insere o SD no PortaPack H2

5. Flash firmware:
   - Settings → Update Firmware
   - Seleciona: portapack-eagle-vXX.bin
   - Aguarda flash completo
   - Reboot

========================================================
NOVAS PASTAS EAGLE:
========================================================

📁 RFMAP/
   - Armazena mapas de RF Signal Mapper
   - Ficheiros CSV com coordenadas GPS + RSSI
   - Formato: map_YYYYMMDD_HHMMSS.txt

📁 DECODER/
   - Logs do Protocol Decoder Pro
   - Pacotes decodificados de multiplos protocolos
   - Formato: log_YYYYMMDD_HHMMSS.txt

========================================================
APPS DISPONIVEIS (61 total):
========================================================

JOGOS:
- Pong
- Snake
- Tetris
- Breakout
- Space Invaders
- Doom
- Pac-Man
- Flappy Bird
- Dino Game
- Battleship
- Blackjack

RF TOOLS:
- RF Signal Mapper (NEW!)
- Protocol Decoder (NEW!)
- Scanner
- Spectrum Painter
- Jammer
- Hopper
- ProtoView
- Fox Hunt RX

TX APPS:
- ADS-B TX
- GPS Simulator
- MORSE TX
- SSTV TX
- Key Fob
- Flipper TX
- BLE Spam

... e muito mais!

========================================================
SUPORTE:
========================================================

- GitHub: https://github.com/09AZO14/eagle-firmware
- Issues: https://github.com/09AZO14/eagle-firmware/issues

========================================================
Made with love by 09AZO14
Fly Higher with EAGLE!
========================================================
