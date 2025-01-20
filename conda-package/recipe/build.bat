mkdir build
cd build

cmake -DCMAKE_INSTALL_PREFIX=%CONDA_PREFIX% ..

cmake --build . --config Release
