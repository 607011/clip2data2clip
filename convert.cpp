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

#include <spng.h>
#include "convert.hpp"

uint8_t *convert(const clip::image &img, size_t *png_size)
{
    spng_ctx *ctx = spng_ctx_new(SPNG_CTX_ENCODER);
    spng_set_option(ctx, SPNG_ENCODE_TO_BUFFER, 1);
    struct spng_ihdr ihdr = {0};
    ihdr.width = img.spec().width;
    ihdr.height = img.spec().height;
    ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;
    ihdr.bit_depth = 8;
    spng_set_ihdr(ctx, &ihdr);
    int rc = spng_encode_image(ctx, img.data(), img.spec().required_data_size(), SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
    if (rc)
    {
        spng_ctx_free(ctx);
        return nullptr;
    }
    uint8_t *const png_buf = reinterpret_cast<uint8_t *>(spng_get_png_buffer(ctx, png_size, &rc));
    spng_ctx_free(ctx);
    return png_buf;
}
