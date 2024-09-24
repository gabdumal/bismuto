#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

namespace Constants {

    namespace Commands {
#if defined(_WIN32) || defined(_WIN64)
        constexpr auto libreoffice = "start soffice --calc ";
#elif defined(__linux__)
        constexpr auto libreoffice = "libreoffice --calc ";
#endif
    }  // namespace Commands

}  // namespace Constants

#endif  // __CONSTANTS_HPP__
