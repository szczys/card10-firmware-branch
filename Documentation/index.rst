card10 firmware docs
====================

**Dear traveller,**

these transcripts describe how you can write code for your card10.  This
includes the Python modules that are available but also documentation of the
lower level firmware components.

If you want to write Python code for card10, you will want to take a look at
the :ref:`Pycardium <pycardium_overview>` docs.  If you are interested in writing applications
in other languages, you'll probably want to interface with
:ref:`Epicardium API <epicardium_api_overview>` directly.

Last but not least, if you want to start hacking the lower-level firmware, the
:ref:`Firmware <firmware_overview>` section of these docs is a good starting place.


.. toctree::
   :maxdepth: 1
   :caption: Pycardium

   pycardium/overview
   pycardium/stdlib
   pycardium/bhi160
   pycardium/bme680
   pycardium/max30001
   pycardium/buttons
   pycardium/color
   pycardium/display
   pycardium/gpio
   pycardium/leds
   pycardium/light-sensor
   pycardium/os
   pycardium/personal_state
   pycardium/power
   pycardium/pride
   pycardium/simple_menu
   pycardium/utime
   pycardium/vibra
   pycardium/ws2812

.. toctree::
   :maxdepth: 1
   :caption: Firmware

   overview
   how-to-build
   how-to-flash
   debugger
   pycardium-guide
   memorymap
   epicardium/sensor-streams

.. toctree::
   :maxdepth: 1
   :caption: Epicardium API

   epicardium/overview
   epicardium/api
   epicardium-guide

.. toctree::
   :maxdepth: 1
   :caption: Bluetooth

   bluetooth/file-transfer
   bluetooth/card10

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
