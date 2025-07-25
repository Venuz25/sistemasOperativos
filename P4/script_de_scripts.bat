@echo off
setlocal

rem Nombre del archivo de script a generar
set name=mi_script.bat

REM Contenido inicial del script
set contenido=echo Hola, este es mi script generado. & pause

echo Creando script ...
echo %contenido% > %name%

echo Editando el script...
notepad %name%

:menu
echo 1. Ejecutar el script generado
echo 2. Cambiar permisos para ejecutar el script
echo 3. Salir
set /p option=Selecciona una opcion:

if "%option%"=="1" goto execute
if "%option%"=="2" goto change_permissions
if "%option%"=="3" goto exit

echo Opcion no valida...
pause
cls
goto menu

:execute
echo Ejecutando el script generado...
call %name%
pause
cls
goto menu

:change_permissions
echo Cambiando permisos para ejecutar el script...
attrib +x %name%
echo Permisos cambiados correctamente.
pause
cls
goto menu

:exit
echo Saliendo...
pause
exit

endlocal
