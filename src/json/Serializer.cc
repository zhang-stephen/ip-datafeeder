// **EXPERIMENTAL**
// json serializer
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#include "Serializer.hh"

namespace ipdf::json
{
Serializer::Serializer()
{
    reset();
}

void Serializer::reset()
{
    tokens_.clear();
}
}

// EOF
