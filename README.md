Semux light core webassembly library
====================================

This project is a **WebAssembly** version of the [Semux light core library](https://github.com/uno-labs/semux-light-core) 
(written in C++) for the ability to work with Semux cryptographic functions in the JavaScript projects.

Look how easy it is to use:

    // Mnemonic phrase generation
    var mnemonic_rs = Module.UnoSemuxAccountHD.sNewMnemonic();

    if (typeof mnemonic_rs.error != "undefined")
        console.log(mnemonic_rs.error);
    else
        console.log("New mnemonic phrase '" + mnemonic_rs.res + "'");


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

Download an archive `uno_semux_light_core.tar.gz` from assets on release page of this project.
Then unpack the archive into your project folder.

For use it in the browser project you have to import `UnoSemuxLightCoreWasm.js` into your HTML page: 

    <script src="UnoSemuxLightCoreWasm.js"></script>

Documentation
-------------

The actual online version of the documentation you can find at:

https://light-core-wasm.readthedocs.io/en/docs/

License
-------

The project is licensed under the MIT license.
