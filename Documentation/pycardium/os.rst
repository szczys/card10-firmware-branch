.. py:module:: os

``os`` - OS Functions
=====================
The ``os`` module allows access to a few core functionalities of Epicardium and
functions found in CPythons ``os`` module.

CPython-Like
------------

.. py:function:: unlink(path)

   Unlink (remove) a file.

   :param str path: The file to remove.

.. py:function:: listdir(dir)

   List contents of a directory.

   :param str dir: Path to the directory to list.
   :returns: A list of entities (files or subdirectories) in the directory
      ``dir``.

.. py:function:: urandom(n)

   Return ``n`` random bytes.

   .. versionadded:: 1.3

   :param int n: Number of random bytes to retrieve.
   :returns: ``bytes()`` object with ``n`` random bytes.


Card10-Specific
---------------

.. py:function:: exit(ret = None)

   Exit from the current app and return to the menu.


   :param int ret: Optional return code, same semantics as Posix (``0`` means
      success).
   :return: This function will never return.

.. py:function:: exec(name)

   Try executing a new app, stopping the currently running one.

   ``name`` is the path to either a l0dable (ending in ``.elf``) or a python
   script (ending in ``.py``).  If the path does not lead to an executable file,
   ``os.exec()`` will raise an exception.

   :param str name: Path to new app/script/l0dable.
   :return: This function never returns.  It can, however raise an exception.

.. py:function:: read_battery()

   Read the current battery voltage in V.  Please keep in mind that battery
   voltage behaves exponentially when interpreting this value.

   .. warning::

      Card10 will hard-shutdown once the voltage drops below 3.4 V

.. py:function:: reset()

   Reboot card10.

   .. warning::

      Please only call this function if absolutely necessary.  In most cases
      you'll want to just :py:func:`os.exit` instead.
