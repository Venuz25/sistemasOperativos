@echo off
cls

echo "----------- Captura fecha --------------"
for /F "tokens=1,2,3 delims=/" %%V in ('date /t') do set "dia=%%V%%W%%X"
set "tiempo=%time: =0%"
for /F "tokens=1,2,3 delims=:." %%V in ("%tiempo%") do set "tiempo=%%V%%W%%X"
set "fecha=%dia%%tiempo%"
echo "Fecha y hora capturadas: %fecha%"

echo "---------- Empacando ------------------"
tar -cvf ".\respaldo%fecha%.tar" ".\directorio1" ".\directorio2" ".\directorio3"

echo "----------- Comprimiendo -------------"
rar a -c- ".\respaldo%fecha%.rar" ".\respaldo%fecha%.tar"

echo "------------ Enviando a otro directorio ----------------"
copy ".\respaldo%fecha%.rar" ".\respaldos\"

echo "---------------- Limpiando -------------------------"
del ".\respaldo%fecha%.rar"
del ".\respaldo%fecha%.tar"

echo "---------------- Terminado --------------------------"
pause
exit /b 0
