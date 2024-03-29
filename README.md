# Clip2Data2Clip

The programs in this repository convert data found in the clipboard to a [Data URL](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Data_URLs), then copy the URL's text back to the clipboard. The data can be a file, RGB image data or text. RGB image data will be converted to represent a PNG file before being converted to a Data URL.

Data URLs are useful to embed images e.g. in HTML or Markdown documents.

## Build instructions

### Ubuntu Linux

```
sudo apt update
sudo apt install libspng-dev
git clone https://github.com/607011/clip2png2clip.git
cd clip2png2clip
git submodule init
git submodule update --remote --merge
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### macOS

```
brew update
brew install cmake libspng zlib
git clone https://github.com/607011/clip2png2clip.git
cd clip2png2clip
git submodule init
git submodule update --remote --merge
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### Windows

If not already present, install Git and Git bash:

```
winget install --id Git.Git -e --source winget
```

Launch Visual Studio Developer Command Prompt. Then:

```
git clone https://github.com/607011/clip2png2clip.git
cd clip2png2clip
git submodule init
git submodule update --remote --merge
cd 3rdparty/zlib-1.2.13
cmake .
cmake --build . --config Release
cp Release/zlib.lib .
cd ../..
cmake . -DZLIB_ROOT="3rdparty/zlib-1.2.13"
cmake --build . --config Release
```

You'll find the compiled binaries in the subdirectory "Release".

To execute they need some DLLs shipped with the Microsoft compiler:

 - api-ms-win-crt-heap-l1-1-0.dll
 - api-ms-win-crt-math-l1-1-0.dll
 - api-ms-win-crt-stdio-l1-1-0.dll
 - api-ms-win-crt-locale-l1-1-0.dll
 - api-ms-win-crt-runtime-l1-1-0.dll

On Windows 11 using Visual Studio Community Edition you'll find them in 
%PROGRAMFILES%/Microsoft Visual Studio/2022/Community/Common7/Tools

Copy the DLLs from there to "Release".

Do the same with 3rdparty/libspng/Release/spng.dll and 3rdparty/zlib-1.2.13/Release/zlib.dll.

Now `Release/clip2dataurl` will run properly.

## Usage

Convert clipboard contents to Data URL and copy it to the clipboard:

```
./clip2dataurl
```

Same as above but write Data URL to stdout:

```
./clip2stdout
```


## Nutzungshinweise

**Diese Software wurde zu Lehr- und Demonstrationszwecken geschaffen und ist nicht für den produktiven Einsatz vorgesehen.** Heise Medien und der Autor haften daher nicht für Schäden, die aus der Nutzung der Software entstehen, und übernehmen keine Gewähr für ihre Vollständigkeit, Fehlerfreiheit und Eignung für einen bestimmten Zweck.

## Copyright

Copyright ©️ 2023 Oliver Lau, Heise Medien GmbH & Co. KG

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
