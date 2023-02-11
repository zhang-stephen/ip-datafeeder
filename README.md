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

not cleared for now, but I will push code as soon as I can.

### Build

Use [vcpkg](https://github.com/microsoft/vcpkg) for managing dependencies for all platforms. Dependencies would be installed as declared in [vcpkg.json](./vcpkg.json) by vcpkg.

#### Mac OS Ventura(Apple Silicon)

*The prototype is being built on Mac OS with M1 pro.*
Use [homebrew](https://brew.sh) to install dependencies.

```bash
brew install pkg-config vcpkg
git clone git@github.com:microsoft/vcpkg.git --depth 1 <vcpkg_root>
```

Then use following command to build all targets(under the root of the repo):

```bash
mkdir build
cmake -B build -S ./ -DCMAKE_TOOLCHAIN_FILE=<vcpkg_root>/scripts/buildsystems/vcpkg.cmake # configure the project with vcpkg
cmake --build build  # build all targets
```

And the executable file could be found as `build/src/ipdf` and `build/src/ipdf_test`.

#### Windows 11 x64

Install vcpkg into your PC as you like.

If the visual studio is preferred, follow these commands:

```bash
mkdir build
cmake -B build -S ./ -DCMAKE_TOOLCHAIN_FILE=<vcpkg_root>/scripts/buildsystems/vcpkg.cmake -G "Visual Studio 17 2022" -DUSE_MSVC=on # configure the project with vcpkg
cmake --build build  # build all targets
```

vcpkg will install dependencies with triplet `x64-windows` if the `USE_MSVC` is true. Or dependencies will be installed with triplet `x64-mingw-static`. Run `vcpkg help triplet` to get more information.

__Not supported: cygwin/mingw64/msys2.__

Known issue on windows:
- `ctest` cannot find test targets after building.
