#include <cstdlib>
#include <string>
#include <iostream>

#include <spng.h>

#include "3rdparty/clip/clip.h"
#include "base64.hpp"


int main(int argc, char *argv[])
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
        std::cerr << "spng_encode_image() failed: " << spng_strerror(rc) << std::endl;
        spng_ctx_free(ctx);
        return EXIT_FAILURE;
    }
    size_t png_size;
    auto *png_buf = reinterpret_cast<uint8_t *>(spng_get_png_buffer(ctx, &png_size, &rc));
    if (png_buf == nullptr)
    {
        std::cerr << "spng_get_png_buffer() failed." << std::endl;
        spng_ctx_free(ctx);
        return EXIT_FAILURE;
    }
    spng_ctx_free(ctx);

    std::string b64 = base64_encode(png_buf, png_size);
#ifdef DEBUG
    std::cout << "PNG size: " << png_size << std::endl;
#endif
    free(png_buf);

    std::string url = "data:image/png;base64," + b64;
    clip::set_text(url);
    std::cout << "Data URL copied to clipboard." << std::endl;

    return EXIT_SUCCESS;
}
