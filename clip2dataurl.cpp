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
#include <vector>

#include <spng.h>

#include "3rdparty/clip/clip.h"
#include "base64.hpp"
#include "convert.hpp"

int main(void)
{
    std::string data_url;
    if (clip::has(clip::file_format()))
    {
        std::cout << "Found file." << std::endl;
        std::vector<uint8_t> file_data;
        if (!clip::get_file(file_data))
        {
            return EXIT_FAILURE;
        }
        std::string mime_type;
        clip::get_mime_type(clip::file_format(), mime_type);        
        data_url = "data:" + mime_type + ";base64," + base64_encode(file_data.data(), file_data.size());
    }
    else if (clip::has(clip::image_format()))
    {
        std::cout << "Found image data." << std::endl;
        clip::image img;
        if (!clip::get_image(img))
        {
            std::cerr << "Cannot read image data from clipboard." << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "Found image (" << img.spec().width << "x" << img.spec().height << ")."
                  << std::endl;

        size_t png_size;
        uint8_t *png_buf = convert(img, &png_size);
        if (png_buf == nullptr)
        {
            std::cerr << "Conversion to PNG failed." << std::endl;
            return EXIT_FAILURE;
        }
        std::string mime_type;
        clip::get_mime_type(clip::image_format(), mime_type);        
        data_url = "data:" + mime_type + ";base64," + base64_encode(png_buf, png_size);
        free(png_buf);
    }
    else if (clip::has(clip::text_format()))
    {
        std::cout << "Found text data." << std::endl;
        std::string text;
        if (!clip::get_text(text))
        {
            std::cerr << "Cannot read text from clipboard." << std::endl;
            return EXIT_FAILURE;
        }
        std::string mime_type;
        clip::get_mime_type(clip::text_format(), mime_type);        
        data_url = "data:" + mime_type + ";base64," + base64_encode(reinterpret_cast<uint8_t *>(text.data()), text.length());
    }
    else
    {
        std::cerr << "No image or file or text in clipboard." << std::endl;
        return EXIT_FAILURE;
    }

    clip::set_text(data_url);
    std::cout << "Data URL copied to clipboard." << std::endl;

    return EXIT_SUCCESS;
}
