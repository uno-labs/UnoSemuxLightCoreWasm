AccountHD class
===============

.. note::
   The concepts of `HD Address` and `non-HD Address` mean an object of the :js:class:`Addr` class, which is essentially a key pair.


.. js:class:: AccountHD

   An object of this class is not created using the ``new`` operator,
   but is returned by the static function :js:func:`sImportFromMnemonic` importing a `mnemonic phrase`.


Static methods
--------------

.. js:function:: sNewMnemonic()

   :returns: A ``string`` containing generated mnemonic phrase.

   | Generates a new mnemonic phrase.
   | Example:

   .. code-block:: javascript

      var mnemonic_rs = Module.UnoSemuxAccountHD.sNewMnemonic();

      if (typeof mnemonic_rs.error != "undefined") {
          console.log(mnemonic_rs.error);
      } else {
          console.log("New mnemonic phrase '" + mnemonic_rs.res + "'");
      }


.. js:function:: sImportFromMnemonic(mnemonic, password)

   :param string mnemonic: A mnemonic phrase.
   :param string password: A password (can be empty).
   :returns: An ``object`` of :js:class:`AccountHD` class.

   | Checks for control sum and imports a mnemonic phrase.
   | This is essentially a factory method for instantiating an object of :js:class:`AccountHD` class.
   | Using returned object you can further create a sequence of key pairs (objects of :js:class:`Addr` class).
   | Example:

   .. code-block:: javascript

      function ImportMnemonicPhrase() {

          var mnemonic = prompt("Please enter your mnemonic phrase: ");
          var password = "";  // optional

          // Import mnemonic phrase (transform it into AccountHD)
          var account_hd_rs = Module.UnoSemuxAccountHD.sImportFromMnemonic(mnemonic, password);

          if (typeof account_hd_rs.error != "undefined") {
              // If check of mnemonic phrase fails
              console.log(account_hd_rs.error);
          } else {
              var account_hd = account_hd_rs.res;
          }


Class methods
-------------

.. js:function:: addrAddNextHD()

   :returns: An ``object`` of :js:class:`Addr` class.

   | Derives the next key pair (HD Address) from the `account`.
   | Example:

   .. code-block:: javascript

      // Generate the next HD address
      var next_hd_addr_rs = account_hd.addrAddNextHD();

      if (typeof next_hd_addr_rs.error != "undefined") {
          console.log(next_hd_addr_rs.error);
      } else {
          var next_hd_addr = next_hd_addr_rs.res;
      }


.. js:function:: addrAdd(address)

   :param Addr address: An object of :js:class:`Addr` class.
   :returns: ``void``.

   | Add the `non-HD Address` to the collection of Addresses.
   | You can create such an object of :js:class:`Addr` class by :js:func:`sImportPrivateKeyStrHex` or :js:func:`sGenerateNew` methods.


.. js:function:: addrFindByName(name)

   :param string name: The name (alias) of the Address to search for.
   :returns: An ``object`` of :js:class:`Addr` class.

   | Finds the Address by its name (alias).


.. js:function:: addrFindByHexStr(hex)

   :param string hex: A hex form of the Address to search for.
   :returns: An ``object`` of :js:class:`Addr` class.

   | Finds the Address by its HEX representation.


.. js:function:: addrHexStrByName(name)

   :param string name: The name (alias) of the Address.
   :returns: A ``string`` containing the HEX representation of an Address.

   | Returns a HEX representation of the Address by its name (alias).


.. js:function:: addrDeleteByName(name)

   :param string name: The name (alias) of the Address to be deleted.
   :returns: ``void``.

   | Deletes the Address having the given name.


.. js:function:: addrDeleteByHexStr(hex)

   :param string name: A hex form of the Address to be deleted.
   :returns: ``void``.

   | Deletes the Address by its HEX representation.

