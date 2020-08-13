Semux light core webassembly library
====================================

This project is a **WebAssembly** version of the [Semux light core library](https://github.com/uno-labs/semux-light-core) 
(written in C++, based on libSodium) for the ability to work with Semux cryptographic functions in the JavaScript projects.

Look how easy it is to use:

    // Mnemonic phrase generation
    var mnemonic_phrase = GetRes(Module.UnoSemuxWallet.new_mnemonic_pharase());
    console.log("New mnemonic phrase: '" + mnemonic_phrase + "'");


Features
--------

Since this project is a javascript wrapper around the corresponding C++ library, 
it contains all the functions of the parent project.

Capabilities:

- Generation and import a mnemonic phrase
- Derivation of key pairs (HD Wallet)
- Signature and verification of messages (e.g. transactions)
- and more...


Installation
------------

To build the project, QMAKE and EMSCRIPTEN compiler are used. The build process is quite complicated,
so the compiled files are laid out in the assets section.

Download an archive `uno_semux_light_core.tar.gz` from assets on release page of this project.
Then unpack the archive into your project folder.

For use it in the browser project you have to import `UnoSemuxLightCoreWasm.js` into your HTML page: 

    <script src="UnoSemuxLightCoreWasm.js"></script>
    

Build
-----    

*Environment*

- cmake 3.16 (for Ubuntu 18.04 nedeed [installing the latest CMake](https://graspingtech.com/upgrade-cmake/))
- standard for the C++ - 20
- gcc-10, g++-10

	sudo add-apt-repository ppa:ubuntu-toolchain-r/test #for gcc-10 g++-10
	sudo apt install cmake gcc-10 g++-10 build-essential libtool libboost-dev


*Workspace*

- create folders **_build/src_**
- go into **_src_** and clone this repo
- go to the repo folder and run


*Dependences*

[UnoSemuxLightCore](https://github.com/uno-labs/UnoSemuxLightCore.git)


*Build*

	emcmake cmake .
	emmake make -j4
	

Documentation
-------------

The actual online version of the documentation you can find at:

https://light-core-wasm.readthedocs.io/en/latest/

License
-------

The project is licensed under the MIT license.
