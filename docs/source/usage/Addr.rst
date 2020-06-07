Addr class
==========

The `Addr` class and its methods.


Static methods
--------------

- ``sImportPrivateKeyStrHex(strHexPrivate)`` - imports a private key.

Returns an ``object`` of :doc:`Addr`.

|

- ``sGenerateNew()`` - generates a new key pair.

Returns an `object` of :doc:`Addr`.


Class methods
-------------

- ``addrStrHex()`` - returns the HEX representation of itself.

Returns ``string`` containing HEX representation of itself. Usage:

.. code-block:: html

  <script>
      //Get address as str hex
      var addr_str_hex_rs = window.next_hd_addr.addrStrHex();

      if (typeof addr_str_hex_rs.error != "undefined") {
          console.log(addr_str_hex_rs.error);
          return;
      }

      var addr_str_hex = addr_str_hex_rs.res;

      console.log("HEX address: " + "0x" + addr_str_hex);
  </script>

|

- ``sign1(objectTransaction)`` - performs a signature of a :doc:`Transaction` object.

Returns an ``object`` of :doc:`TransactionSign`. Usage:

.. code-block:: html

  <script>
      var sign_rs = window.next_hd_addr.sign1(transaction);

      if (typeof sign_rs.error != "undefined") {
          console.log(sign_rs.error);
          return;
      }

      var sign = sign_rs.res;
  </script>

|

- ``sign2(objectTransaction)`` - performs a signature of a :doc:`Transaction` object. It's similar to ``sing1`` method.

Returns an ``object`` of :doc:`TransactionSign`.

|

- ``setNonce(strNonce)`` - set the nonce for this address.

Returns ``void``.

