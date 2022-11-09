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
