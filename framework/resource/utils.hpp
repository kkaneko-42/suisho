// FIXME: util系で一か所にまとめる

#ifndef SUISHO_RESOURCE_UTILS_H_
#define SUISHO_RESOURCE_UTILS_H_

#include <string>

namespace suisho {

std::string getExtension(const std::string& path) {
    const size_t pos = path.rfind(".");
    if (pos == std::string::npos) {
        return "";
    } else {
        return path.substr(pos + 1);
    }
}

}

#endif
