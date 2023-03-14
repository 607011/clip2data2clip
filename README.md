# Clip2Data2Clip

The programs in this repository converts data found in the clipboard to a [Data URL](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Data_URLs), then copies the URL's text back to the clipboard. The data can be a file, RGB image data or text. RGB image data will be converted to represent a PNG file before being converted to a Data URL.

Data URLs are useful to embed images e.g. in HTML or Markdown documents.

## Build instructions

### Ubuntu Linux

```
sudo apt update
sudo apt install libspng-dev
git clone https://github.com/607011/clip2png2clip.git
cd clip2png2clip
git submodule init
git submodule update
CMAKE_BUILD_TYPE=Release cmake .
cmake --build .
```

### macOS

```
brew update
brew install cmake libspng
git clone https://github.com/607011/clip2png2clip.git
cd clip2png2clip
git submodule init
git submodule update
CMAKE_BUILD_TYPE=Release cmake .
cmake --build .
```

### Windows

TODO


## Usage

Convert clipboard contents to Data URL and copy it to the clipboard:

```
./clip2dataurl
```

Same as above but write Data URL to stdout:

```
./clip2stdout
```

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
