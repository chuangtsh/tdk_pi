// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2015 Intel Corporation. All Rights Reserved.
#pragma once

#include "types.h"

namespace librealsense
{
    size_t           get_image_size                 (int width, int height, rs2_format format);
    int              get_image_bpp                  (rs2_format format);

    template<class SOURCE, class SPLIT_A, class SPLIT_B> void split_frame( uint8_t * const dest[], int count, const SOURCE * source, SPLIT_A split_a, SPLIT_B split_b)
    {
        if (dest)
        {
            auto a = reinterpret_cast<decltype(split_a(SOURCE()))*>(dest[0]);
            auto b = reinterpret_cast<decltype(split_b(SOURCE()))*>(dest[1]);
            for (int i = 0; i < count; ++i)
            {
                *a++ = split_a(*source);
                *b++ = split_b(*source++);
            }
        }
    }

    template<class SOURCE, class SPLIT_A, class SPLIT_B> void split_frame_mipi(uint8_t* const dest[], int count, const SOURCE* source, SPLIT_A split_a, SPLIT_B split_b)
    {
        if (dest)
        {
            auto a = reinterpret_cast<decltype(split_a(SOURCE()))*>(dest[0]);
            auto b = reinterpret_cast<decltype(split_b(SOURCE()))*>(dest[1]);
            for (int i = 0; i < count; i += 2)
            {
                // temporary workaround - swapping ordering of left, caused due to received frame
                // when fixed we can use the regular split_frame
                a[i] = split_a(source[i + 1]);
                b[i] = split_b(source[i]);

                a[i + 1] = split_a(source[i]);
                b[i + 1] = split_b(source[i + 1]);
            }
        }
    }
}
