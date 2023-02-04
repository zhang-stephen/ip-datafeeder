// Main entry of ip-datafeeder
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#include "Logger.hh"
#include "Serializer.hh"

#include <iostream>

using namespace ipdf;

int main(int c [[maybe_unused]], char** v [[maybe_unused]])
{
    logger::setupSpdLog();
}

// EOF
