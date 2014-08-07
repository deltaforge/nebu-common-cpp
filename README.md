Nebu Common C++
===

Nebu Common C++ (libnebu-common) is a helper library for the Nebu project. It was written to ease development of Nebu extensions written in C++.

Features
---

Main features of libnebu-common include:

 * It provides classes for physical topology and virtual machine representations.
 * It provides wrappers for performing REST calls to the Nebu core.

Currently libnebu-common provides support for the following API calls:

| URI | Class and function |
| --- | --- |
| GET `/app/:id/phys` | `AppPhysRequest::getPhysicalTopology` |
| GET `/app/:id/virt` | `AppVirtRequest::getVirtualMachineIDs` |
| GET `/app/:id/virt/:id` | `AppVirtRequest::getVirtualMachine` |


Dependencies
---

Runtime dependencies:

 * [tinyxml2](https://github.com/leethomason/tinyxml2), version 2.1.0
 * [restclient-cpp](https://github.com/mrtazz/restclient-cpp), commit [ccfb8707b8](https://github.com/mrtazz/restclient-cpp/tree/ccfb8707b8766152e15568a29c778cb23d2cad68)
 
Compile dependencies:

 * automake, version 2.61
 * g++, version 4.4.7
 
Compiling
---

To compile libnebu-common, execute the following commands:

	./bootstrap
    ./configure
    make
    make install

License
---

The Nebu App Framework is distributed under the LGPL version 3 license. See the provided LICENSE file for more information.

