mkdir build
cd build
cmake ..
cmake --build . --config Release
copy local\src\hk.exe hk.exe
mkdir %PREFIX%\bin
copy Release\hk.exe %PREFIX%\bin\
