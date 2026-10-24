/*************************************************************************
 * This file is part of input-overlay
 * git.vrsal.cc/alex/input-overlay
 * Copyright 2025 univrsal <uni@vrsal.xyz>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

#pragma once

/* OBS 33 replaced the gs_image_file/2/3/4 API with gs_image_file_ex.
 * io_image_t is the image object the overlay owns, io_image_base_t is what
 * elements draw from (both expose texture, cx, cy and loaded). */

extern "C" {
#include <obs-config.h>
#include <graphics/image-file.h>
}

#if LIBOBS_API_MAJOR_VER >= 33
typedef gs_image_file_ex_t io_image_t;
typedef gs_image_file_ex_t io_image_base_t;

static inline void io_image_init(io_image_t *image, const char *file, enum gs_image_alpha_mode alpha_mode)
{
    gs_image_file_ex_init(image, file, alpha_mode);
}
static inline void io_image_init_texture(io_image_t *image)
{
    gs_image_file_ex_init_texture(image);
}
static inline void io_image_free(io_image_t *image)
{
    gs_image_file_ex_free(image);
}
static inline io_image_base_t *io_image_base(io_image_t *image)
{
    return image;
}
#else
typedef gs_image_file4_t io_image_t;
typedef gs_image_file_t io_image_base_t;

static inline void io_image_init(io_image_t *image, const char *file, enum gs_image_alpha_mode alpha_mode)
{
    gs_image_file4_init(image, file, alpha_mode);
}
static inline void io_image_init_texture(io_image_t *image)
{
    gs_image_file4_init_texture(image);
}
static inline void io_image_free(io_image_t *image)
{
    gs_image_file4_free(image);
}
static inline io_image_base_t *io_image_base(io_image_t *image)
{
    return image ? &image->image3.image2.image : nullptr;
}
#endif
