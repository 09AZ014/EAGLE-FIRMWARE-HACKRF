@echo off

echo *** Re-flash the HackRF with PortaPack EAGLE-FIRMWARE ***
echo.
echo Connect your HackRF One to a USB port on your computer.
echo.
echo If using a PortaPack, put the PortaPack in HackRF mode by selecting
echo the "HackRF" option from the main menu.
echo.
pause

echo.

REM Check if the firmware file exists
if not exist portapack-eagle-firmware.bin (
    echo The firmware file "portapack-eagle-firmware.bin" does not exist.
    echo Please ensure that you have built or downloaded the EAGLE-FIRMWARE binary.
    echo.
    pause
    exit /b
)

"utils/hackrf_update.exe" portapack-eagle-firmware.bin
echo.
echo If your device does not boot after flashing, refer to the troubleshooting notes in the repository wiki.
echo.
pause
