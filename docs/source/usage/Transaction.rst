Transaction class
=================

.. js:class:: Transaction

   An object of :js:class:`Transaction` class is created with factory static method :js:meth:`sNew`.


Static methods
--------------

.. js:method:: sNew(networkType, transactionType, addressToHex, amount, fee, nonce, timestamp, dataHex, gas, gasPrice)

   :param NetworkType networkType: A type of network.
   :param TransactionType transactionType: A type of transaction.
   :param string addressToHex: :term:`Semux-address` in string hexadecimal form.
   :param string amount: Amount of payment (integer value `in nanosem`).
   :param string fee: Amount of fee (integer value `in nanosem`).
   :param string nonce: A :term:`Nonce` (unique and sequential for the sender).
   :param string timestamp: A timestamp of the transaction (`in milliseconds`).
   :param string dataHex: Some arbitrary text data in string hexadecimal form.
   :param string gas: Amount of `gas`.
   :param string gasPrice: Gas price (integer value `in nanosem`).
   :returns: ``object`` of :js:class:`Transaction` class.

   | Factory method for creating of :js:class:`Transaction` class object.
   | Example:

   .. code-block:: javascript

      var d = new Date();
      var network_type = Module.UnoSemuxNetworkType.TESTNET;
      var transaction_type = Module.UnoSemuxTransactionType.TRANSFER;
      var to = "0x82c38263217817de2ef28937c7747716eb1e7228";
      var data = "0x756E6F2D6C616273206C696768742077616C6C65742064656D6F"; // uno-labs light wallet demo
      var value = "100000000"; // nanosem
      var fee = "5000000";     // nanosem
      var nonce = "533";       // Actually, you have to get it from Node API
      var gas = "0";
      var gas_price = "0";     // nanosem

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

