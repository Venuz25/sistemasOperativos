@echo off
cls

echo "-----------------Enviando al directorio original-----------------"
set o_dir="C:\Users\areli\OneDrive\Documentos\Escuela\SO\P4"

move .\respaldos\*.rar %o_dir%

echo "-----------------Descomprimiendo-----------------"
rar e -y .\*.rar %o_dir%

echo "-----------------Desempacando-----------------"
"C:\Program Files\WinRAR\WinRAR.exe" x *.tar

echo "-----------------Limpiando-----------------"
del ".\*.rar"
del ".\*.tar"

echo "-----------------Terminado-----------------"
pause
exit /b 0
