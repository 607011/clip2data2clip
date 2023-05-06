cmake --build . --config Release
copy "%PROGRAMFILES%\Microsoft Visual Studio\2022\Community\Common7\Tools\api-ms-win-crt-heap-l1-1-0.dll" Release
copy "%PROGRAMFILES%\Microsoft Visual Studio\2022\Community\Common7\Tools\api-ms-win-crt-math-l1-1-0.dll" Release
copy "%PROGRAMFILES%\Microsoft Visual Studio\2022\Community\Common7\Tools\api-ms-win-crt-stdio-l1-1-0.dll" Release
copy "%PROGRAMFILES%\Microsoft Visual Studio\2022\Community\Common7\Tools\api-ms-win-crt-locale-l1-1-0.dll" Release
copy "%PROGRAMFILES%\Microsoft Visual Studio\2022\Community\Common7\Tools\api-ms-win-crt-runtime-l1-1-0.dll" Release
copy 3rdparty\zlib-1.2.13\Release\zlib.dll Release
copy 3rdparty\libspng\Release\spng.dll Release
