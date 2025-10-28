========================================================
   PROTOCOL DECODER PRO - LOG FOLDER
========================================================

Esta pasta armazena os logs de pacotes decodificados
pela app "Protocol Decoder Pro" do EAGLE-FIRMWARE.

FORMATO DOS FICHEIROS:
----------------------
log_YYYYMMDD_HHMMSS.txt

Exemplo: log_20251028_145530.txt

CONTEUDO:
---------
# EAGLE Protocol Decoder Log
# Timestamp: 2025-10-28 14:55:30
# Frequency: 433920000 Hz
# Total Packets: 45

[1635789456] POCSAG | RSSI: -68 dB | Conf: 95% | ADDR: 1234567 MSG: "Test"
[1635789460] APRS | RSSI: -72 dB | Conf: 92% | WB2OSZ>APRS:Position data
[1635789465] AIS | RSSI: -65 dB | Conf: 88% | MMSI: 123456789 LAT:40.7N
...

PROTOCOLOS SUPORTADOS (19):
----------------------------
- OOK Manchester / PWM
- FSK-2 / FSK-4
- ASK / PSK
- POCSAG (Pagers)
- APRS (Position Reports)
- AIS (Marine Tracking)
- ACARS (Aircraft Comms)
- ADS-B (Aircraft Position)
- DMR / D-STAR / P25
- NXDN / YSF / TETRA

COMO USAR:
----------
1. Abre "Protocol Decoder Pro" no PortaPack
2. Define frequencia ou activa AUTO scan
3. Aguarda deteccao automatica
4. Pacotes aparecem no console em tempo real
5. Press SAVE para exportar log completo
6. Ficheiro e gravado nesta pasta

CORES DO CONSOLE:
-----------------
- VERDE: Alta confianca (>90%)
- AMARELO: Media confianca (70-90%)
- VERMELHO: Baixa confianca (<70%)

========================================================
Made by 09AZO14 for EAGLE-FIRMWARE
========================================================
