@echo off
setlocal enabledelayedexpansion

set "letra=e"

for %%F in (".\*") do (
    set "nombre=%%~nF"
    if "!nombre:~1,1!"=="%letra%" (
        del "%%F" /q
        echo Eliminando: %%F
    )
)

echo Eliminacion completada.
pause