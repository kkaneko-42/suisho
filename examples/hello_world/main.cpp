#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

int main() {
    // TODO: Engine features demo
    FT_Library ft_lib;
    FT_Error err = FT_Init_FreeType(&ft_lib);
    if (err != FT_Err_Ok) {
        std::cerr << "Failed to init freetype" << std::endl;
        return EXIT_FAILURE;
    }

    err = FT_Done_FreeType(ft_lib);
    if (err != FT_Err_Ok) {
        std::cerr << "Failed to init freetype" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Hello, World!" << std::endl;
    return EXIT_SUCCESS;
}
