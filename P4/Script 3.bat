@echo off
cls

echo "-------------Captura Fecha-------------"
for /F "tokens=1,2,3 delims=/" %%V in ('date /t') do set "dia=%%V%%W%%X"
set "tiempo=%time: =0%"
for /F "tokens=1,2,3 delims=:." %%V in ("%tiempo%") do set "tiempo=%%V%%W%%X"
set "fecha=%dia%%tiempo%"
echo "Fecha y hora capturadas: %fecha%"

echo "-------------Creando .rar-------------"
rar a -c- ".\respaldo%fecha%.rar" ".\prueba"

echo "-------------Empacando-------------"
tar -cvf ".\respaldo%fecha%.tar" ".\respaldo%fecha%.rar"

echo "-------------Comprimiendo-------------"
rar a -c- ".\respaldo%fecha%.rar" ".\respaldo%fecha%.tar"

echo "-------------Enviando a otro directorio-------------"
copy ".\respaldo%fecha%.rar" ".\respaldos\"

echo "-------------Descomprimiendo-------------"
rar e -y ".\respaldos\respaldo%fecha%.rar" ".\respaldos"

echo "-------------Desempacando-------------"
tar -xvf ".\respaldos\respaldo%fecha%.tar" -C ".\respaldos" "respaldo%fecha%.rar"

echo "-------------Limpiando-------------"
del ".\respaldo%fecha%.rar"
del ".\respaldo%fecha%.tar"

echo "-------------Terminado-------------"
