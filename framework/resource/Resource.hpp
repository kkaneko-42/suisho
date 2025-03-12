#ifndef SUISHO_RESOURCE_RESOURCE_H_
#define SUISHO_RESOURCE_RESOURCE_H_

#include <string>

namespace suisho {

class Resource {
public:
    virtual ~Resource() {}

    void setUri(const std::string& uri) { uri_ = uri; }
    const std::string& getUri() const { return uri_; }

protected:
    std::string uri_;
};

}


#endif
