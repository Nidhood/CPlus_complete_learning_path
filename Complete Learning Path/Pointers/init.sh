#!/bin/bash

# Borramos los archivos anteriores
rm -rf cmake-build-debug
rm -f Declaration_Usage

# Compilamos el proyecto
mkdir -p cmake-build-debug
# shellcheck disable=SC2164
cd cmake-build-debug
cmake ..
make
# shellcheck disable=SC2103
cd ..
echo "La inicialización del proyecto ha finalizado. Los ejecutables están en la carpeta raíz."