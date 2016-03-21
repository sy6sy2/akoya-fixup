# akoya-fixup

A Linux kernel module to fix the keyboard for my Medion(R) Akoya P2214T Notebook (and possibly other models too!).

# Technical description

The USB report descriptor of some(?) Elan based keyboard devices specifies an excessively large number of *consumer usages* (2^16), which is more than HID_MAX_USAGES. This prevents proper parsing of the report descriptor, and the keyboard is unusable as a result.  
A commonly suggested remedy is to compile your own kernel with increased `HID_MAX_USAGES` - but that's a dirty hack which may have repercussions for other devices or the stability of the whole system (or maybe it just wastes a few thousand bytes). It's also relatively difficult for newcomers with lots of pitfalls and it may result in an unbootable system, frustration, etc.

## Disclaimer

Despite the very low chance of any kind of problem caused by this module, it should be considered experimental, unsupported and/or unfit for use on systems in production or in critical environments.

The software is provided "as is" and the author disclaims all warranties
with regard to this software including all implied warranties of
merchantability and fitness. In no event shall the author be liable for
any special, direct, indirect, or consequential damages or any damages
whatsoever resulting from loss of use, data or profits, whether in an
action of contract, negligence or other tortious action, arising out of
or in connection with the use or performance of this software.

# Installation

  1. Install required packages:  
    For **Ubuntu** or **Debian** (and derivates):  

        apt-get install build-essential gcc make linux-headers-`uname -r` git

  2. Clone this repository and enter it:  

        git clone https://github.com/schumann2k/akoya-fixup.git
        cd akoya-fixup

  3. Compile:

        make

    Hopefully you haven't been given any errors by this point, which would mean compilation was a success.

  4. Testing:

        sudo insmod akoya-fixup.ko
        dmesg | tail

    You should see something along the lines of:

        [....] akoya_keyboard 0003:04f3:0400.0003: fixing Medion Akoya USB keyboard report descriptor

    You may start using your keyboard now. :)

  5. Making the fix permanent:

        # still in the akoya-fixup directory
        sudo make install
        echo "akoya-fixup" | sudo tee -a /etc/modules

    The fixup module will now be loaded automatically at boot.


### If it didn't work for your notebook ...
... sorry. :/  
There may not be anything I can do about that. This module is designed to fix a very specific issue and I've only had the chance to develop and test it on this one specific model.  
We might be able to work out some kind of freelance contract for tailoring a fix for your device, send me an email if that sounds reasonable.


----
Copyright (c) 2015-2016 Hendrik Schumann < github at schumann.pw >

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your option)
any later version.
