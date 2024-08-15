Write a driver yo create a device file named/dev/sample_led. Each time the user writes 1 to
the device file, the LED will turn on, and when the user writes 0, the LED will turn off. If
the LED is on, reading the file will return 1; if the LED is off, reading the file will return 0.


How to run?
	1.make
	2.sudo insmod sample_led.ko
	3.echo 1 > /dev/sample_led ( turn on LED )
	4.echo 0 > /dev/sample_lde ( turn off LED )
	5.cat /dev/sample_led/ (read data return)
	6.sudo rmmod sample_led
