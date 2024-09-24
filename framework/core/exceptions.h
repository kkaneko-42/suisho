#ifndef SUISHO_CORE_EXCEPTIONS_H_
#define SUISHO_CORE_EXCEPTIONS_H_

#include <stdexcept>

namespace suisho {

/// @brief Reports the feature is not implemented
class NotImplementedException : public std::logic_error {
public:
    /// @brief @brief Creates a new exception
    /// @param feature Feature description not implemented
    NotImplementedException(const std::string& feature);

    /// @brief Creates a new exception
    /// @param feature Feature description not implemented
    NotImplementedException(const char* feature);
};

} // namespace suisho

#endif // SUISHO_CORE_EXCEPTIONS_H_
