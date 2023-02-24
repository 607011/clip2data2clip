/*
 Copyright © 2023 Oliver Lau <ola@ct.de>, Heise Medien GmbH & Co. KG - Redaktion c't

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
 */

#include <cstdlib>
#include <string>
#include <iostream>

#include <spng.h>

#include "3rdparty/clip/clip.h"
#include "base64.hpp"
#include "convert.hpp"

int main(void)
{
    if (!clip::has(clip::image_format()))
    {
        std::cerr << "No image in clipboard." << std::endl;
        return EXIT_FAILURE;
    }

    clip::image img;
    clip::get_image(img);

    std::cout << "Found image (" << img.spec().width << "x" << img.spec().height << ")."
              << std::endl;

    size_t png_size;
    uint8_t *png_buf = convert(img, &png_size);
    if (png_buf == nullptr)
    {
        std::cerr << "Conversion to PNG failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::string b64 = base64_encode(png_buf, png_size);
    free(png_buf);

    std::string url = "data:image/png;base64," + b64;
    clip::set_text(url);
    std::cout << "Data URL copied to clipboard." << std::endl;

    return EXIT_SUCCESS;
}
