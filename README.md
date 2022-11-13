# A LAN(Local Area Network) DataFeeder for FPGA/embedded Debugging

<p>
<a href='https://github.com/zhang-stephen/ip-datafeeder/blob/master/LICENSE'>
    <img alt='license' src='https://img.shields.io/badge/License-MIT-informational?style=flat-square'>
</a>
<img alt='Language' src='https://img.shields.io/badge/language-C%2B%2B20-orange?style=flat-square&logo=c%2B%2B'/>
</p>

### Preface

I am learning FPGA developing for data processing of mmW radar(77GHz or higher) for my master degree. And I need a simple tool as a radar simulator, which could send data to my FPGA board periodically, and other utility to help debugging.

I want to make it as a general-purpose tool, with LAN interface. And more feature is on the road.

### Design Principles

- Easy to Use
- Performance
- Cross-Platform

### Features

#### Long-Term Goals

- [ ] IPv6 support
- [ ] data transfer over the UDP
- [ ] configurable Timer with 0.5 micro-second precision
- [ ] extensible data frame definitions
- [ ] provide the pure-header library for embedded client
- [ ] provide protocol layer implementation for FPGA use Verilog HDL or SystemVerilog(with public Ethernet interface, e.g. W5300/RTL8211)
- [ ] auto-detect slave boards
- [ ] Performance
- [ ] graphics UI(low-priority)

#### Short-Term Goals

- [ ] Fast Prototype
- [ ] IPv4 support
- [ ] data transfer over the TCP

### Implementation

#### Logger

This logger is implemented by `boost::log` v2.

### Usage

Pre-Requisites:

- Boost 1.71.0+
- GCC/LLVM with C++20 Support, e.g.:
    - gcc 10.0+
    - clang 12.0.0+
- cmake 3.20+

Using [msys2](https://www.msys2.org/) to install all of pre-requisites is recommended if you are using Windows 10/11.

Then build this repo following these steps:

1. make a new directory, e.g. `build`,
2. run `cmake -S ./ -B build` to generate the building configuration, `Ninja` or `Unix Makefiles` is supported,
3. run `cmake --build build` to build the executable binary, `debug.exe` for windows and `debug` for unix-like systems,
4. run `./build/debug[.exe]` to run this demo.
