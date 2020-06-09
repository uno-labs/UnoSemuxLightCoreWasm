Terms and Definitions
=====================

   WebAssembly
      The `WebAssembly <https://webassembly.org/>`_ (abbreviated *Wasm*) is a software technology
      that allows you to use code written in C++ in the JavaScript environment.


   Wallet
      A wallet is software that stores a set of key pairs of asymmetric cryptography and 
      allows you to perform transaction signing operations using them.


   HD Wallet
      An *Hierarchical Deterministic* wallet is a wallet that allows deriving hierarchical chains of key pairs
      from the initial master seed in a deterministic way.


   HD Account
      An *HD Account* is a very specific intermediate node in the hierarchy of an HD Wallet (defined by the Semuks specification),
      from which all other key pairs are derived.


   Address
      The term *Address* here means an object of the :js:class:`Addr` class, which is essentially a key pair.


   HD Address
      An *HD Address* is one of the *Addresses* in the HD Wallet hierarchy.


   non-HD Address
      It is single *Address* not associated with the HD Wallet.
      It can be obtained by importing a private key or random generation.

      .. note::
         This library can simultaneously work with several non-HD addresses,
         but only with one HD Account (one hierarchy of HD Addresses).


   Mnemonic phrase
      *Mnemonic phrase* (or mnemonic sentence) - is a group of easy to remember words (space separated)
      for the determinate generation of the master seed (and, accordingly, HD Account) for HD Wallet.

      A mnemonic code or sentence is superior for human interaction compared to the handling of raw binary
      or hexadecimal representations of a wallet master seed. 
      The sentence could be written on paper or spoken over the telephone.


   Semux-address or Hex address or Recipient address
      It's a hexadecimal string that is the *"official address"* of some wallet
      to which you can, for example, transfer a certain amount of cryptocurrency.

      In fact, a *Semux-address* is obtained by taking a double hash (Blake2B-SHA256) from the public part of the *Address*.


   Nonce
      *Nonce* is a sequentially increasing and unique integer for the sender address. Varies from 0 to 9,223,372,036,854,775,807.
      Used to make transactions.

      In the parameters of the methods of this library, the *Nonce* is passed as a string decimal representation.

