Addr class
==========

.. js:class:: Addr

   This class is designed to work with a specific key pair (not with an :term:`HD wallet`).


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

   :returns: A ``string`` containing a :term:`Semux-address` (without leading '0x').

   | Method to get a HEX representation of itself (aka :term:`Semux-address`).
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


.. js:function:: nonce()

   :returns: A ``string`` containing the current :term:`Nonce` (string representation of SINT64 - max value is 9,223,372,036,854,775,807).

   | Method to get the current :term:`Nonce`, which was set by :js:func:`setNonce` method or
     was incremented by :js:func:`incNonce` method.


.. js:function:: setNonce(nonce)

   :param string nonce: A string representation of :term:`Nonce` to set.
   :returns: ``void``.

   | Set the :term:`Nonce` for this :term:`Address`.


.. js:function:: incNonce()

   :returns: A ``string`` containing the incremented :term:`Nonce`.

   | Method to increment the current :term:`Nonce`.


