Getting started
===============

Important notes
---------------

Some methods are **static**
and can be called without creating an object. For example:

.. code-block:: javascript

   var result = Module.UnoSemux<SomeClass>.<someStaticMethod>();


Other methods are members of objects of certain classes.
So at first you have to create an object of certain class and then to call its methods.
In fact, in this library almost always objects are created by some factory method, e.g.:

.. code-block:: javascript

   var myObject = Module.UnoSemux<SomeClass>.<someFactoryMethod>();
   var result = myObject.<someMethod>();


All methods return a result object that always has two important fields -
``error`` and ``res``:

- ``result.error`` - if successful, takes an ``undefined`` value;
- ``result.res`` -  contains the result.

.. warning::
   The methods never throw exceptions related to the logic of the library.
   But the system exceptions can be thrown nonetheless!


Typical usage
-------------

First of all you have to include corresponding JavaScript file into your HTML page:

.. code-block:: html

   <script src="UnoSemuxLightCoreWasm.js"></script>



Mnemonic phrase generation
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: html

   <script>
       function NewMnemonicPhrase() {

           var mnemonic_rs = Module.UnoSemuxAccountHD.sNewMnemonic();

           if (typeof mnemonic_rs.error != "undefined") {
               console.log(mnemonic_rs.error);
               return;
           }

           console.log("New mnemonic phrase '" + mnemonic_rs.res + "'");
       }
   </script>


Import mnemonic phrase
~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: html

   <script>
       function ImportMnemonicPhrase() {

           //Mnemonic
           var mnemonic = prompt("Please enter your phrase ");
           var password = "";  //optional

           console.log("HD mnemonic phrase '" + mnemonic + "', password = '" + password + "'");

           //Import HD
           var account_hd_rs = Module.UnoSemuxAccountHD.sImportFromMnemonic(mnemonic, password);

           if (typeof account_hd_rs.error != "undefined") {
               console.log(account_hd_rs.error);
               return;
           }

           var account_hd = account_hd_rs.res;

           //Generate next HD address
           console.log("Add next HD address...");
           var next_hd_addr_rs = account_hd.addrAddNextHD();

           if (typeof next_hd_addr_rs.error != "undefined") {
               console.log(next_hd_addr_rs.error);
               return;
           }

           window.next_hd_addr = next_hd_addr_rs.res;

           //Get address as str hex
           var addr_str_hex_rs = window.next_hd_addr.addrStrHex();
           if (typeof addr_str_hex_rs.error != "undefined") {
               console.log(addr_str_hex_rs.error);
               return;
           }

           var addr_str_hex = addr_str_hex_rs.res;

           console.log("New address: " + "0x" + addr_str_hex);
       }
   </script>

Transaction signature
~~~~~~~~~~~~~~~~~~~~~

.. code-block:: html

    <script>
        function SignTransaction() {

            console.log("New transaction...");

            var d = new Date();

            var network = document.getElementById("transaction_network_source").value;
            var type = document.getElementById("transaction_type_source").value;
            var to = document.getElementById("transaction_to_source").value;
            var value = document.getElementById("transaction_value_source").value;
            var fee = document.getElementById("transaction_fee_source").value;
            var nonce = document.getElementById("transaction_nonce_source").value;
            var data = document.getElementById("transaction_data_source").value;
            var gas = document.getElementById("transaction_gas_source").value;
            var gas_price = document.getElementById("transaction_gas_price_source").value;

            var network_type = Module.UnoSemuxNetworkType.TESTNET;
            if (network == "MAINNET") network_type = Module.UnoSemuxNetworkType.MAINNET;
            else network_type = Module.UnoSemuxNetworkType.TESTNET;

            var transaction_type = Module.UnoSemuxTransactionType.COINBASE;
            if (type == "TRANSFER") transaction_type = Module.UnoSemuxTransactionType.TRANSFER;
            else if (type == "DELEGATE") transaction_type = Module.UnoSemuxTransactionType.DELEGATE;
            else if (type == "VOTE") transaction_type = Module.UnoSemuxTransactionType.VOTE;
            else if (type == "UNVOTE") transaction_type = Module.UnoSemuxTransactionType.UNVOTE;
            else if (type == "CREATE") transaction_type = Module.UnoSemuxTransactionType.CREATE;
            else if (type == "CALL") transaction_type = Module.UnoSemuxTransactionType.CALL;

            var transaction_rs = new Module.UnoSemuxTransaction.sNew(network_type,
                transaction_type,
                String(to),
                String(value),
                String(fee),
                String(nonce),
                String(d.getTime()),
                String(data),
                String(gas),
                String(gas_price));


            if (typeof transaction_rs.error != "undefined") {
                console.log(transaction_rs.error);
                return;
            }

            var transaction = transaction_rs.res;

            console.log("Sign transaction...");
            var sign_rs = window.next_hd_addr.sign1(transaction);

            if (typeof sign_rs.error != "undefined") {
                console.log(sign_rs.error);
                return;
            }

            var sign = sign_rs.res;

            var sign_tx_hash_rs = sign.txHash();

            if (typeof sign_tx_hash_rs.error != "undefined") {
                console.log(sign_tx_hash_rs.error);
                return;
            }
            console.log("Transaction hash '" + sign_tx_hash_rs.res + "'");

            var sign_encode_rs = sign.encode()

            if (typeof sign_encode_rs.error != "undefined") {
                console.log(sign_encode_rs.error);
                return;
            }

            console.log("Transaction sign hex str '" + sign_encode_rs.res + "'");

            document.getElementById("transaction_hash_source").value = sign_tx_hash_rs.res;
            document.getElementById("sign_source").value = sign_encode_rs.res;
        }
    </script>
