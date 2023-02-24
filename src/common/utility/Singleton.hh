// UTILITY: Meyers' Singleton
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

namespace ipdf::utility
{
template <typename T>
class Singleton
{
public:
    static T& instance()
    {
        static auto instance = T();
        return instance;
    }

    Singleton(const Singleton&)            = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton()          = default;
    virtual ~Singleton() = default;
};
} // namespace ipdf::utility

// EOF
