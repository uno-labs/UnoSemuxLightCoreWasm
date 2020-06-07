AccountHD class
===============

The `AccountHD` class and its methods.

An object of this class is not created using the ``new`` operator,
but is returned by a static function ``sImportFromMnemonic`` importing a mnemonic phrase.


Static methods
--------------

- ``sNewMnemonic()`` - generates a new mnemonic phrase.

Returns ``string`` containing generated `mnemonic phrase`. Usage:

.. code-block:: html

  <script>
      var mnemonic_rs = Module.UnoSemuxAccountHD.sNewMnemonic();

      if (typeof mnemonic_rs.error != "undefined") {
          console.log(mnemonic_rs.error);
          return;
      }

      console.log("New mnemonic phrase '" + mnemonic_rs.res + "'");
  </script>

|

- ``sImportFromMnemonic(mnemonicStr, passwordStr)`` - imports the mnemonic phrase (with optional password).

Returns an ``object`` of :doc:`AccountHD`. After that, you can get a sequence of key pairs. Usage:

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
  </script>

|

Class methods
-------------

- ``addrAddNextHD()`` - derives the next key pair from the account.

Returns an ``object`` of :doc:`Addr`. Usage:

.. code-block:: html

  <script>
      //Generate next HD address
      console.log("Add next HD address...");
      var next_hd_addr_rs = account_hd.addrAddNextHD();

      if (typeof next_hd_addr_rs.error != "undefined") {
          console.log(next_hd_addr_rs.error);
          return;
      }

      window.next_hd_addr = next_hd_addr_rs.res;
  </script>

|

- ``addrFindByName(strName)`` - find an address by its name.

Returns an ``object`` of :doc:`Addr`.

|

- ``addrFindByHexStr(strHex)`` - find an address by its HEX representation.

Returns an ``object`` of :doc:`Addr`.

|

- ``addrHexStrByName(strAddressName)`` - returns the HEX representation of an address by its name.

Returns a ``string`` containing the HEX representation of an address.

