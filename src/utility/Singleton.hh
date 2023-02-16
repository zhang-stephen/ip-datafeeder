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

protected:
    Singleton()          = default;
    virtual ~Singleton() = default;

private:
    Singleton(const Singleton&)            = delete;
    Singleton& operator=(const Singleton&) = delete;
};
} // namespace ipdf::utility

// EOF
