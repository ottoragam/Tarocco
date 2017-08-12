# Tarocco
Open Source Closed Loop Motor Controller

----------------------------------------------------------------------
Tarocco (c) by Gino Magarotto

Tarocco is licensed under a
Creative Commons Attribution-ShareAlike 3.0 Unported License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/3.0/>.

----------------------------------------------------------------------
Low cost servo drive for small CNC machinery

Get yours on https://www.crowdsupply.com/citrus-cnc/tarocco

Changelog

2017-08-12

* TX_SEND timer period changed to 1874. This makes the reporting frequency exactly 100 Hz (not taking clock tolerance into account)
* Added a serial command to clear any fault flag. Useful when calibrating the controller parameters
* Holding the reset pin low before powering the board puts the microcontroller into bootloader mode. You won't have to worry about the three second timeout window anymore
*V1.1 board and schematic files with fiducials and test points for pogo pins instead of a programming connectos are available.


2017-05-24

* Fixed motor stutter every third of a second
* Fixed serial communications bug that froze the status reporting
* Made status reporting frequency exactly 100 Hz, to help with plotting and tunning
* Increased maximum following error value to 32000
* User can now switch between current or PWM output for status reporting

Thanks to Patrick Dussud for all the help

![drive](/Images/tarocco-extras.jpg)
