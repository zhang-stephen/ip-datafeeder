// UTILITY: Meyers' Singleton
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

namespace ipdf::utility
{
template <typename T>
class Singleton
{
public:
    static T& instance()
    {
        static auto instance_ = T();
        return instance_;
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
