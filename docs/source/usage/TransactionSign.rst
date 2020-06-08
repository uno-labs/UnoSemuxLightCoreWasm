TransactionSign class
=====================

.. js:class:: TransactionSign

   An object of this class is not created using the ``new`` operator,
   but is returned by the :js:func:`sign1` or :js:func:`sign2` methods of :js:class:`Addr` object.

   Actually, the :js:class:`TransactionSign` objects are storage for the following data:

      - encoded transaction data;
      - a transaction hash (Blake2B);
      - a sign of hash;
      - the public key (with no prefix) of the `key pair` with which the signature was made.


Class methods
-------------

.. js:method:: txData()

   :returns: A ``string`` containing encoded transaction data.

   | Method to get encoded transaction data.


.. js:method:: txHash()

   :returns: A ``string`` containing a hash (Blake2B) of the transaction data.

   | Method to get a hash of the transaction data.
   | Example:

   .. code-block:: javascript

      var sign_tx_hash_rs = sign.txHash();

      if (typeof sign_tx_hash_rs.error != "undefined") {
          console.log(sign_tx_hash_rs.error);
      } else {
          console.log("Transaction hash '" + sign_tx_hash_rs.res + "'");
      }


.. js:method:: sign()

   :returns: A ``string`` containing a sign of the transaction data hash.

   | Method to get a sign of the transaction data hash.


.. js:method:: pubKeyNoPrefix()

   :returns: A ``string`` containing the public key.

   | Method to get the public key (with no prefix) of the `key pair` with which the signature was made.


.. js:method:: encode()

   :returns: A ``string`` containing encoded :js:class:`TransactionSign` object.

   | Encode all data contained in this object in order to prepare before sending to the Semux network.
   | Example:

   .. code-block:: javascript

      var sign_encode_rs = sign.encode()

      if (typeof sign_encode_rs.error != "undefined") {
          console.log(sign_encode_rs.error);
      } else {
          console.log("Transaction sign hex str '" + sign_encode_rs.res + "'");
      }

