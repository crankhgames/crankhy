#pragma once

namespace debug
{
    template <typename... Args>
    void log(const Args &...args);

    template <typename... Args>
    void warning(const Args &...args);

    template <typename... Args>
    void error(const Args &...args);
}

#include "debug.inl"