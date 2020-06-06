Get started
===========

Typical usage
-------------

First of all you have to include corresponding JS-library into your html page:

.. code-block:: html

   <script src="UnoSemuxLightCoreWasm.js"></script>


Generating mnemonic phrase
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

           document.getElementById("mnemonic_phrase_source").value = mnemonic_rs.res;
       }
   </script>


Importing the mnemonic phrase
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: html

   <script>
       function ImportMnemonicPhrase() {
           //Mnemonic
           var mnemonic = document.getElementById("mnemonic_phrase_source").value;
           var password = "";//optional

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

           console.log("New address: " + addr_str_hex);

           document.getElementById("hd_address_source").value = "0x" + addr_str_hex;
       }
   </script>
