AccountHD class
===============

.. js:class:: AccountHD

   An object of this class is not created using the ``new`` operator,
   but is returned by the static function :js:func:`sImportFromMnemonic` importing a `mnemonic phrase`.

   .. note::
      The concept of `HD Address` means an object of the :js:class:`Addr` class, which is essentially a key pair.

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


.. js:function:: addrFindByName(name)

   :param string name: A name of an address.
   :returns: An ``object`` of :js:class:`Addr` class.

   | Finds an address by its name.


.. js:function:: addrFindByHexStr(hex)

   :param string hex: A hex form of an address.
   :returns: An ``object`` of :js:class:`Addr` class.

   | Finds an address by its HEX representation.


.. js:function:: addrHexStrByName(addressName)

   :param string addressName: A name of an address.
   :returns: A ``string`` containing the HEX representation of an address.

   | Returns the HEX representation of an address by its name.

