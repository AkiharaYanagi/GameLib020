@echo off
mkdir cleaned
for %%f in (*.png) do (
  D:\Utility\pngcrush_1_8_11_w64.exe -rem allb -reduce "%%f" "cleaned\%%f"
)
pause
