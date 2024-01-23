@echo off

pushd "%~dp0\..\.."

set CMAKE_OPTIONS=-DCMAKE_INSTALL_PREFIX=_install ^
-DECALCORE_BUILD_SAMPLES=ON ^
-DECALCORE_BUILD_SAMPLES_PROTOBUF=OFF ^
-DECALCORE_BUILD_ECAL_TESTS=ON ^
-DECALCORE_BUILD_ECAL_TESTS_PROTOBUF=OFF ^
-DECALCORE_CONFIG_INIFILE=OFF ^
-DECALCORE_COMMAND_LINE=OFF ^
-DECALCORE_REGISTRATION=ON ^
-DECALCORE_REGISTRATION_SHM=ON ^
-DECALCORE_PUBLISHER=OFF ^
-DECALCORE_SUBSCRIBER=OFF ^
-DECALCORE_SERVICE=ON ^
-DECALCORE_TIMEPLUGIN=OFF ^
-DECALCORE_TRANSPORT_UDP=OFF ^
-DECALCORE_TRANSPORT_TCP=OFF ^
-DECALCORE_TRANSPORT_SHM=OFF ^
-DECALCORE_NPCAP_SUPPORT=OFF

mkdir _08_build_clientserver
cd _08_build_clientserver

cmake .. -A x64 %CMAKE_OPTIONS%
cmake --build . --parallel --config Release
ctest -C Release -V

popd
