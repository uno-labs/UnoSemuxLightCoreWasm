Transaction class
=================

.. js:class:: Transaction

   An object of :js:class:`Transaction` class is created with factory static method :js:meth:`sNew`.


Static methods
--------------

.. js:method:: sNew(networkType, transactionType, addressToHex, amount, fee, nonce, timestamp, dataHex, gas, gasPrice)

   :param NetworkType networkType: A type of network.
   :param TransactionType transactionType: A type of transaction.
   :param string addressToHex: Recipient address in string hexadecimal form.
   :param string amount: Amount of payment (`in nanosem`).
   :param string fee: Amount of fee (`in nanosem`).
   :param string nonce: A nonce (unique and sequential for the sender).
   :param string timestamp: A timestamp of the transaction (`in milliseconds`).
   :param string dataHex: Data of the transaction in string hexadecimal form.
   :param string gas: Amount of `gas`.
   :param string gasPrice: Gas price (`in nanosem`).
   :returns: ``object`` of :js:class:`Transaction` class.

   | Factory method for creating of :js:class:`Transaction` class object.
   | Example:

   .. code-block:: javascript

      var d = new Date();
      var network_type = Module.UnoSemuxNetworkType.TESTNET;
      var transaction_type = Module.UnoSemuxTransactionType.TRANSFER;

      var transaction_rs = new Module.UnoSemuxTransaction.sNew(
            network_type,
            transaction_type,
            String(to),
            String(value),
            String(fee),
            String(nonce),
            String(d.getTime()),
            String(data),
            String(gas),
            String(gas_price)
      );

      if (typeof transaction_rs.error != "undefined") {
          console.log(transaction_rs.error);
      } else {
          var transaction = transaction_rs.res;
      }


Class methods
-------------

.. js:method:: encode()

   :returns: An encoded ``string`` of :js:class:`Transaction` object.

   | Method to get an encoded representation of itself.

