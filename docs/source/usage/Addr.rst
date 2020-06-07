Addr class
==========

.. js:class:: Addr

   This class is designed to work with a specific key pair (not with an HD wallet).

   .. note::
      The concept of `HD Address` means an object of the :js:class:`Addr` class, which is essentially a key pair.


Static methods
--------------

.. js:function:: sImportPrivateKeyStrHex(hexPrivate)

   :param string hexPrivate: A HEX form of an importing private key.
   :returns: An ``object`` of :js:class:`Addr` class.

   | Imports a private key.


.. js:function:: sGenerateNew()

   :returns: An ``object`` of :js:class:`Addr` class.

   | Generates a new key pair.


Class methods
-------------

.. js:function:: addrStrHex()

   :returns: A ``string`` containing HEX representation of itself.

   | Method to get the HEX representation of itself.
   | Example:

   .. code-block:: javascript

      // Get address as str hex
      var addr_str_hex_rs = next_hd_addr.addrStrHex();

      if (typeof addr_str_hex_rs.error != "undefined") {
          console.log(addr_str_hex_rs.error);
      } else {
          var addr_str_hex = addr_str_hex_rs.res;
          console.log("HEX address: " + "0x" + addr_str_hex);
      }


.. js:function:: sign1(transaction)

   :param transaction: An object of :js:class:`Transaction` class.
   :returns: An ``object`` of :js:class:`TransactionSign` class.

   | Performs a signature of a :js:class:`Transaction` object.
   | Example:

   .. code-block:: javascript

      var sign_rs = next_hd_addr.sign1(transaction);

      if (typeof sign_rs.error != "undefined") {
          console.log(sign_rs.error);
      } else {
          var sign = sign_rs.res;
      }


.. js:function:: sign2(transaction)

   :param transaction: An object of :js:class:`Transaction` class.
   :returns: An ``object`` of :js:class:`TransactionSign` class.

   | Performs a signature of a :js:class:`Transaction` object. It's similar to :js:func:`sign1` method.


.. js:function:: setNonce(nonce)

   :param string nonce: A `nonce`.
   :returns: ``void``.

   | Set the nonce for this address.

