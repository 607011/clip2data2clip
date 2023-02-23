# Clip2PNG2Clip

This program converts an image found in the clipboard to a PNG, then copies the PNG's [Data URL](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Data_URLs) as text to the clipboard. 

Data URLs are useful to embed images e.g. in HTML or Markdown documents.

## Build instructions

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

## Usage

```
./pic2dataurl
```




_Copyright ©️ 2023 [Oliver Lau](mailto:ola@ct.de), [Heise](https://www.heise.de/) Medien GmbH & Co. KG_
