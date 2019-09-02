import sys_displaybuffer

class Displaybuffer:
    """
    The displaybuffer class provides methods to allow the 
    display buffer features of thee lcd display
    in card10 to be used. All draw methods return
    the display object so that it is possible to chain calls.
    It is recommended to use a context manager as following:

    .. code-block:: python

        import displaybuffer
        with displaybuffer.open() as disp:
            disp.rainbowbuff(0).showbuff()
    """

    def __init__(self):
        """
        Opens the display. Will fail the display can't be locked
        """
        sys_displaybuffer.open()

    def __enter__(self):
        return self

    def __exit__(self, _et, _ev, _t):
        self.close()

    @classmethod
    def open(cls):
        """
        Opens the display. Will fail the display can't be locked
        """
        return cls()

    @staticmethod
    def close():
        """
        Closes and unlocks the display. To be able to use it again,
        it is necessary to open and lock it again with Display.open()
        """
        sys_displaybuffer.close()

    def setbuff(self, x, y, msb, lsb):
        """
        Writes a pixel to the buffer.

        :param x: x coordinate in buffer, 0 <= x <= 159
        :param y: y coordinate in buffer, 0 <= y <= 79
        :param msb: most significant Byte of 16-bit color
        :param lsb: least significant Byte of 16-bit color
        """
        
        sys_displaybuffer.setbuff(x, y, msb, lsb)
        return self

    def rainbowbuff(self, offset):
        """
        Writes a rainbow pattern to the buffer.

        :param offset: x offset for color pattern, 0 <= x <= 95
        """
        
        sys_displaybuffer.rainbowbuff(offset)
        return self

    def clrbuff(self):
        """
        Clears the framebuffer.
        """
        sys_displaybuffer.clrbuff()
        return self

    def showbuff(self):
        """
        Blits the framebuffer to the display.
        """
        sys_displaybuffer.showbuff()
        return self

    def wrencher(self):
        """
        Draws a Hackaday logo on the framebuffer.
        """
        sys_displaybuffer.wrencher()
        return self


open = Displaybuffer.open
close = Displaybuffer.close
