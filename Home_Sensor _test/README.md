# ESP32-C3 WROOM-02 Custom Board Hardware Bring-up

troubleshooting steps and hardware corrections required to run an ESP32-C3-WROOM-02 module on custom PCB

## Hardware Corrections 

the following hardware issues were identified and corrected:

- UART TX/RX Swap: The communication lines between the USB-to-UART bridge and the ESP32-C3 (GPIO 20 & 21) were originally swapped.
- Missing GPIO 8 Pull-up: GPIO 8 is a strapping pin for the ESP32-C3 was floating6
- changed C14 for 1k Ohm 

Test 1
<img src="Test1.jpeg" alt="Test1" width="500"/>

Test 2
<img src="Test2.jpeg" alt="Test2" width="500"/>


## Notes

- ESP32 IO 19 and IO 18 need swapp in the Symbol (Symbol is wrong)

- manual flashing works
- RTS DTR logic works
- LED 1-3 works
- Switch works
