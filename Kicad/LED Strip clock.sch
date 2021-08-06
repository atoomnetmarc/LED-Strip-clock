EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Driver for LED Strip clock"
Date "2021-08-06"
Rev "V1.0"
Comp "https://github.com/atoomnetmarc/LED-Strip-clock"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74HCT244 U5
U 1 1 608C7AB1
P 4700 4050
F 0 "U5" H 4950 4700 50  0000 C CNN
F 1 "74HCT244" H 4900 3400 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm_LongPads" H 4700 4050 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT244.pdf" H 4700 4050 50  0001 C CNN
	1    4700 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR041
U 1 1 608CF759
P 4700 5000
F 0 "#PWR041" H 4700 4750 50  0001 C CNN
F 1 "GND" H 4705 4827 50  0000 C CNN
F 2 "" H 4700 5000 50  0001 C CNN
F 3 "" H 4700 5000 50  0001 C CNN
	1    4700 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR040
U 1 1 608D1492
P 4100 5000
F 0 "#PWR040" H 4100 4750 50  0001 C CNN
F 1 "GND" H 4105 4827 50  0000 C CNN
F 2 "" H 4100 5000 50  0001 C CNN
F 3 "" H 4100 5000 50  0001 C CNN
	1    4100 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4550 4100 4550
Wire Wire Line
	4100 4550 4100 5000
Wire Wire Line
	4200 4450 4100 4450
Wire Wire Line
	4100 4450 4100 4550
Connection ~ 4100 4550
Wire Wire Line
	4700 4850 4700 5000
Wire Wire Line
	5200 3750 5600 3750
Wire Wire Line
	5200 3650 5600 3650
$Comp
L power:+5V #PWR031
U 1 1 608D4D74
P 4700 3150
F 0 "#PWR031" H 4700 3000 50  0001 C CNN
F 1 "+5V" H 4715 3323 50  0000 C CNN
F 2 "" H 4700 3150 50  0001 C CNN
F 3 "" H 4700 3150 50  0001 C CNN
	1    4700 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3250 4700 3150
Wire Wire Line
	5200 3850 5600 3850
Wire Wire Line
	5200 3550 5600 3550
Wire Wire Line
	4000 3850 4200 3850
Wire Wire Line
	3900 3750 4200 3750
Wire Wire Line
	3700 3650 4200 3650
Wire Wire Line
	3600 3550 4200 3550
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 6092D456
P 11050 5100
F 0 "J5" H 11100 5300 50  0000 R CNN
F 1 "Conn_01x04_Male" H 11650 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 11050 5100 50  0001 C CNN
F 3 "~" H 11050 5100 50  0001 C CNN
	1    11050 5100
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR038
U 1 1 6093ED9B
P 10800 6150
F 0 "#PWR038" H 10800 5900 50  0001 C CNN
F 1 "GND" H 10805 5977 50  0000 C CNN
F 2 "" H 10800 6150 50  0001 C CNN
F 3 "" H 10800 6150 50  0001 C CNN
	1    10800 6150
	1    0    0    -1  
$EndComp
Text Label 10550 5000 0    50   ~ 0
ROT_A
Text Label 10550 5100 0    50   ~ 0
ROT_B
Text Label 10550 5200 0    50   ~ 0
ROT_SW
Wire Wire Line
	10800 5300 10800 6150
Wire Wire Line
	10800 5300 10850 5300
Text Label 5250 3550 0    50   ~ 0
~OE_5V
Text Label 5250 3850 0    50   ~ 0
LATCH_5V
Text Label 5250 3650 0    50   ~ 0
CLK_5V
Text Label 5250 3750 0    50   ~ 0
DATA_5V
$Comp
L Device:C C5
U 1 1 60AB1FB4
P 3350 3750
F 0 "C5" H 3450 3850 50  0000 R CNN
F 1 "10uF" H 3550 3650 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3388 3600 50  0001 C CNN
F 3 "~" H 3350 3750 50  0001 C CNN
	1    3350 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR030
U 1 1 60AB2382
P 3350 3150
F 0 "#PWR030" H 3350 3000 50  0001 C CNN
F 1 "+5V" H 3365 3323 50  0000 C CNN
F 2 "" H 3350 3150 50  0001 C CNN
F 3 "" H 3350 3150 50  0001 C CNN
	1    3350 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR039
U 1 1 60AB278A
P 3350 5000
F 0 "#PWR039" H 3350 4750 50  0001 C CNN
F 1 "GND" H 3355 4827 50  0000 C CNN
F 2 "" H 3350 5000 50  0001 C CNN
F 3 "" H 3350 5000 50  0001 C CNN
	1    3350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 5000 3350 3900
Wire Wire Line
	3350 3150 3350 3600
$Comp
L power:GND #PWR023
U 1 1 60A99CD3
P 7800 2500
F 0 "#PWR023" H 7800 2250 50  0001 C CNN
F 1 "GND" H 7805 2327 50  0000 C CNN
F 2 "" H 7800 2500 50  0001 C CNN
F 3 "" H 7800 2500 50  0001 C CNN
	1    7800 2500
	1    0    0    -1  
$EndComp
Text Label 9600 1750 0    50   ~ 0
S4DP
Text Label 9600 1650 0    50   ~ 0
S4G
Text Label 9600 1550 0    50   ~ 0
S4F
Text Label 9600 1450 0    50   ~ 0
S4E
Text Label 9600 1350 0    50   ~ 0
S4D
Text Label 9600 1250 0    50   ~ 0
S4C
Text Label 9600 1150 0    50   ~ 0
S4B
Text Label 9600 1050 0    50   ~ 0
S4A
Wire Wire Line
	9550 850  9550 1850
Wire Wire Line
	9550 1850 9800 1850
$Comp
L power:+12V #PWR016
U 1 1 60A92FAC
P 9550 850
F 0 "#PWR016" H 9550 700 50  0001 C CNN
F 1 "+12V" H 9565 1023 50  0000 C CNN
F 2 "" H 9550 850 50  0001 C CNN
F 3 "" H 9550 850 50  0001 C CNN
	1    9550 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 1750 9800 1750
Wire Wire Line
	9800 1650 9450 1650
Wire Wire Line
	9800 1550 9450 1550
Wire Wire Line
	9450 1450 9800 1450
Wire Wire Line
	9800 1350 9450 1350
Wire Wire Line
	9450 1250 9800 1250
Wire Wire Line
	9800 1150 9450 1150
Wire Wire Line
	9450 1050 9800 1050
$Comp
L Connector:Conn_01x09_Male J4
U 1 1 60A92F9E
P 10000 1450
F 0 "J4" H 10000 1900 50  0000 R CNN
F 1 "Conn_01x09_Male" H 10500 1000 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 10000 1450 50  0001 C CNN
F 3 "~" H 10000 1450 50  0001 C CNN
	1    10000 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7800 1550 7800 2500
Wire Wire Line
	7800 850  7800 1250
$Comp
L power:+5V #PWR013
U 1 1 60A8AF49
P 7800 850
F 0 "#PWR013" H 7800 700 50  0001 C CNN
F 1 "+5V" H 7815 1023 50  0000 C CNN
F 2 "" H 7800 850 50  0001 C CNN
F 3 "" H 7800 850 50  0001 C CNN
	1    7800 850 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 60A8AF43
P 7800 1400
F 0 "C4" H 7900 1500 50  0000 R CNN
F 1 "10uF" H 8000 1300 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7838 1250 50  0001 C CNN
F 3 "~" H 7800 1400 50  0001 C CNN
	1    7800 1400
	1    0    0    -1  
$EndComp
Text Label 7200 1750 0    50   ~ 0
S3DP
Text Label 7200 1650 0    50   ~ 0
S3G
Text Label 7200 1550 0    50   ~ 0
S3F
Text Label 7200 1450 0    50   ~ 0
S3E
Text Label 7200 1350 0    50   ~ 0
S3D
Text Label 7200 1250 0    50   ~ 0
S3C
Text Label 7200 1150 0    50   ~ 0
S3B
Text Label 7200 1050 0    50   ~ 0
S3A
Wire Wire Line
	7150 850  7150 1850
Wire Wire Line
	7150 1850 7400 1850
$Comp
L power:+12V #PWR012
U 1 1 60A8AF33
P 7150 850
F 0 "#PWR012" H 7150 700 50  0001 C CNN
F 1 "+12V" H 7165 1023 50  0000 C CNN
F 2 "" H 7150 850 50  0001 C CNN
F 3 "" H 7150 850 50  0001 C CNN
	1    7150 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 1750 7400 1750
Wire Wire Line
	7400 1650 7050 1650
Wire Wire Line
	7400 1550 7050 1550
Wire Wire Line
	7050 1450 7400 1450
Wire Wire Line
	7400 1350 7050 1350
Wire Wire Line
	7050 1250 7400 1250
Wire Wire Line
	7400 1150 7050 1150
Wire Wire Line
	7050 1050 7400 1050
$Comp
L Connector:Conn_01x09_Male J3
U 1 1 60A8AF25
P 7600 1450
F 0 "J3" H 7600 1900 50  0000 R CNN
F 1 "Conn_01x09_Male" H 8100 1000 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 7600 1450 50  0001 C CNN
F 3 "~" H 7600 1450 50  0001 C CNN
	1    7600 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5400 1550 5400 2500
$Comp
L power:GND #PWR021
U 1 1 60A74F2C
P 5400 2500
F 0 "#PWR021" H 5400 2250 50  0001 C CNN
F 1 "GND" H 5405 2327 50  0000 C CNN
F 2 "" H 5400 2500 50  0001 C CNN
F 3 "" H 5400 2500 50  0001 C CNN
	1    5400 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 850  5400 1250
$Comp
L power:+5V #PWR09
U 1 1 60A74F25
P 5400 850
F 0 "#PWR09" H 5400 700 50  0001 C CNN
F 1 "+5V" H 5415 1023 50  0000 C CNN
F 2 "" H 5400 850 50  0001 C CNN
F 3 "" H 5400 850 50  0001 C CNN
	1    5400 850 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 60A74F1F
P 5400 1400
F 0 "C3" H 5500 1500 50  0000 R CNN
F 1 "10uF" H 5600 1300 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5438 1250 50  0001 C CNN
F 3 "~" H 5400 1400 50  0001 C CNN
	1    5400 1400
	1    0    0    -1  
$EndComp
Text Label 4800 1750 0    50   ~ 0
S2DP
Text Label 4800 1650 0    50   ~ 0
S2G
Text Label 4800 1550 0    50   ~ 0
S2F
Text Label 4800 1450 0    50   ~ 0
S2E
Text Label 4800 1350 0    50   ~ 0
S2D
Text Label 4800 1250 0    50   ~ 0
S2C
Text Label 4800 1150 0    50   ~ 0
S2B
Text Label 4800 1050 0    50   ~ 0
S2A
Wire Wire Line
	4750 850  4750 1850
Wire Wire Line
	4750 1850 5000 1850
$Comp
L power:+12V #PWR08
U 1 1 60A6E625
P 4750 850
F 0 "#PWR08" H 4750 700 50  0001 C CNN
F 1 "+12V" H 4765 1023 50  0000 C CNN
F 2 "" H 4750 850 50  0001 C CNN
F 3 "" H 4750 850 50  0001 C CNN
	1    4750 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 1750 5000 1750
Wire Wire Line
	5000 1650 4650 1650
Wire Wire Line
	5000 1550 4650 1550
Wire Wire Line
	4650 1450 5000 1450
Wire Wire Line
	5000 1350 4650 1350
Wire Wire Line
	4650 1250 5000 1250
Wire Wire Line
	5000 1150 4650 1150
Wire Wire Line
	4650 1050 5000 1050
$Comp
L Connector:Conn_01x09_Male J2
U 1 1 60A6E617
P 5200 1450
F 0 "J2" H 5200 1900 50  0000 R CNN
F 1 "Conn_01x09_Male" H 5700 1000 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 5200 1450 50  0001 C CNN
F 3 "~" H 5200 1450 50  0001 C CNN
	1    5200 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3000 1550 3000 2500
$Comp
L power:GND #PWR019
U 1 1 60A5872D
P 3000 2500
F 0 "#PWR019" H 3000 2250 50  0001 C CNN
F 1 "GND" H 3005 2327 50  0000 C CNN
F 2 "" H 3000 2500 50  0001 C CNN
F 3 "" H 3000 2500 50  0001 C CNN
	1    3000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 850  3000 1250
$Comp
L power:+5V #PWR05
U 1 1 60A58726
P 3000 850
F 0 "#PWR05" H 3000 700 50  0001 C CNN
F 1 "+5V" H 3015 1023 50  0000 C CNN
F 2 "" H 3000 850 50  0001 C CNN
F 3 "" H 3000 850 50  0001 C CNN
	1    3000 850 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 60A58720
P 3000 1400
F 0 "C2" H 3100 1500 50  0000 R CNN
F 1 "10uF" H 3200 1300 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3038 1250 50  0001 C CNN
F 3 "~" H 3000 1400 50  0001 C CNN
	1    3000 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  1550 700  2500
$Comp
L power:GND #PWR017
U 1 1 60A49622
P 700 2500
F 0 "#PWR017" H 700 2250 50  0001 C CNN
F 1 "GND" H 705 2327 50  0000 C CNN
F 2 "" H 700 2500 50  0001 C CNN
F 3 "" H 700 2500 50  0001 C CNN
	1    700  2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  850  700  1250
$Comp
L power:+5V #PWR01
U 1 1 60A44B33
P 700 850
F 0 "#PWR01" H 700 700 50  0001 C CNN
F 1 "+5V" H 715 1023 50  0000 C CNN
F 2 "" H 700 850 50  0001 C CNN
F 3 "" H 700 850 50  0001 C CNN
	1    700  850 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 60A3C01C
P 700 1400
F 0 "C1" H 800 1500 50  0000 R CNN
F 1 "10uF" H 900 1300 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 738 1250 50  0001 C CNN
F 3 "~" H 700 1400 50  0001 C CNN
	1    700  1400
	1    0    0    -1  
$EndComp
Text Label 2400 1750 0    50   ~ 0
S1DP
Text Label 2400 1650 0    50   ~ 0
S1G
Text Label 2400 1550 0    50   ~ 0
S1F
Text Label 2400 1450 0    50   ~ 0
S1E
Text Label 2400 1350 0    50   ~ 0
S1D
Text Label 2400 1250 0    50   ~ 0
S1C
Text Label 2400 1150 0    50   ~ 0
S1B
Text Label 2400 1050 0    50   ~ 0
S1A
Wire Wire Line
	2350 850  2350 1850
Wire Wire Line
	2350 1850 2600 1850
$Comp
L power:+12V #PWR04
U 1 1 60A26D23
P 2350 850
F 0 "#PWR04" H 2350 700 50  0001 C CNN
F 1 "+12V" H 2365 1023 50  0000 C CNN
F 2 "" H 2350 850 50  0001 C CNN
F 3 "" H 2350 850 50  0001 C CNN
	1    2350 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1750 2600 1750
Wire Wire Line
	2600 1650 2250 1650
Wire Wire Line
	2600 1550 2250 1550
Wire Wire Line
	2250 1450 2600 1450
Wire Wire Line
	2600 1350 2250 1350
Wire Wire Line
	2250 1250 2600 1250
Wire Wire Line
	2600 1150 2250 1150
Wire Wire Line
	2250 1050 2600 1050
$Comp
L Connector:Conn_01x09_Male J1
U 1 1 60A019AE
P 2800 1450
F 0 "J1" H 2800 1900 50  0000 R CNN
F 1 "Conn_01x09_Male" H 3300 1000 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 2800 1450 50  0001 C CNN
F 3 "~" H 2800 1450 50  0001 C CNN
	1    2800 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1150 1650 1150 2250
Wire Wire Line
	1050 1550 1050 2350
Wire Wire Line
	950  1250 950  2450
Text Label 850  1050 0    50   ~ 0
DATA_5V
Text Label 1200 2450 0    50   ~ 0
CLK_5V
Text Label 1200 2350 0    50   ~ 0
LATCH_5V
Text Label 1200 2250 0    50   ~ 0
~OE_5V
Wire Wire Line
	8050 1050 8450 1050
Wire Wire Line
	8050 1950 8050 1050
Wire Wire Line
	7050 1950 8050 1950
Wire Wire Line
	5650 1050 6050 1050
Wire Wire Line
	5650 1950 5650 1050
Wire Wire Line
	4650 1950 5650 1950
Wire Wire Line
	3250 1050 3650 1050
Wire Wire Line
	3250 1950 3250 1050
Wire Wire Line
	2250 1950 3250 1950
Wire Wire Line
	8950 2150 8950 2500
$Comp
L power:GND #PWR024
U 1 1 608F173B
P 8950 2500
F 0 "#PWR024" H 8950 2250 50  0001 C CNN
F 1 "GND" H 8955 2327 50  0000 C CNN
F 2 "" H 8950 2500 50  0001 C CNN
F 3 "" H 8950 2500 50  0001 C CNN
	1    8950 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2150 6550 2500
$Comp
L power:GND #PWR022
U 1 1 608F02C1
P 6550 2500
F 0 "#PWR022" H 6550 2250 50  0001 C CNN
F 1 "GND" H 6555 2327 50  0000 C CNN
F 2 "" H 6550 2500 50  0001 C CNN
F 3 "" H 6550 2500 50  0001 C CNN
	1    6550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2150 4150 2500
$Comp
L power:GND #PWR020
U 1 1 608EEE47
P 4150 2500
F 0 "#PWR020" H 4150 2250 50  0001 C CNN
F 1 "GND" H 4155 2327 50  0000 C CNN
F 2 "" H 4150 2500 50  0001 C CNN
F 3 "" H 4150 2500 50  0001 C CNN
	1    4150 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 2150 1750 2500
$Comp
L power:GND #PWR018
U 1 1 608ED0D9
P 1750 2500
F 0 "#PWR018" H 1750 2250 50  0001 C CNN
F 1 "GND" H 1755 2327 50  0000 C CNN
F 2 "" H 1750 2500 50  0001 C CNN
F 3 "" H 1750 2500 50  0001 C CNN
	1    1750 2500
	1    0    0    -1  
$EndComp
NoConn ~ 9450 1950
Connection ~ 5750 2450
Wire Wire Line
	8150 1250 8450 1250
Wire Wire Line
	8150 2450 8150 1250
Wire Wire Line
	5750 2450 8150 2450
Connection ~ 3350 2450
Wire Wire Line
	5750 1250 6050 1250
Wire Wire Line
	5750 2450 5750 1250
Wire Wire Line
	3350 2450 5750 2450
Wire Wire Line
	3350 1250 3650 1250
Wire Wire Line
	3350 2450 3350 1250
Wire Wire Line
	950  2450 3350 2450
Connection ~ 5850 2350
Wire Wire Line
	8250 1550 8450 1550
Wire Wire Line
	8250 2350 8250 1550
Wire Wire Line
	5850 2350 8250 2350
Connection ~ 3450 2350
Wire Wire Line
	5850 1550 6050 1550
Wire Wire Line
	5850 2350 5850 1550
Wire Wire Line
	3450 2350 5850 2350
Wire Wire Line
	3450 1550 3650 1550
Wire Wire Line
	3450 2350 3450 1550
Wire Wire Line
	1050 2350 3450 2350
Connection ~ 3550 2250
Wire Wire Line
	3550 2250 1150 2250
Connection ~ 5950 2250
Wire Wire Line
	3550 2250 5950 2250
Wire Wire Line
	8350 2250 5950 2250
Wire Wire Line
	1250 1650 1150 1650
Wire Wire Line
	8350 1650 8350 2250
Wire Wire Line
	8450 1650 8350 1650
Wire Wire Line
	5950 1650 5950 2250
Wire Wire Line
	6050 1650 5950 1650
Wire Wire Line
	3550 1650 3550 2250
Wire Wire Line
	3650 1650 3550 1650
Wire Wire Line
	1050 1550 1250 1550
$Comp
L power:+5V #PWR014
U 1 1 608DBE7E
P 8300 850
F 0 "#PWR014" H 8300 700 50  0001 C CNN
F 1 "+5V" H 8315 1023 50  0000 C CNN
F 2 "" H 8300 850 50  0001 C CNN
F 3 "" H 8300 850 50  0001 C CNN
	1    8300 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 1350 8300 850 
Wire Wire Line
	8450 1350 8300 1350
$Comp
L power:+5V #PWR015
U 1 1 608DB8AE
P 8950 850
F 0 "#PWR015" H 8950 700 50  0001 C CNN
F 1 "+5V" H 8965 1023 50  0000 C CNN
F 2 "" H 8950 850 50  0001 C CNN
F 3 "" H 8950 850 50  0001 C CNN
	1    8950 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 608DB1D4
P 6550 850
F 0 "#PWR011" H 6550 700 50  0001 C CNN
F 1 "+5V" H 6565 1023 50  0000 C CNN
F 2 "" H 6550 850 50  0001 C CNN
F 3 "" H 6550 850 50  0001 C CNN
	1    6550 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 608DA82B
P 4150 850
F 0 "#PWR07" H 4150 700 50  0001 C CNN
F 1 "+5V" H 4165 1023 50  0000 C CNN
F 2 "" H 4150 850 50  0001 C CNN
F 3 "" H 4150 850 50  0001 C CNN
	1    4150 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 608D9FCC
P 5900 850
F 0 "#PWR010" H 5900 700 50  0001 C CNN
F 1 "+5V" H 5915 1023 50  0000 C CNN
F 2 "" H 5900 850 50  0001 C CNN
F 3 "" H 5900 850 50  0001 C CNN
	1    5900 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 1350 5900 850 
Wire Wire Line
	6050 1350 5900 1350
$Comp
L power:+5V #PWR06
U 1 1 608D94E5
P 3500 850
F 0 "#PWR06" H 3500 700 50  0001 C CNN
F 1 "+5V" H 3515 1023 50  0000 C CNN
F 2 "" H 3500 850 50  0001 C CNN
F 3 "" H 3500 850 50  0001 C CNN
	1    3500 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1350 3500 850 
Wire Wire Line
	3650 1350 3500 1350
Wire Wire Line
	1100 1350 1100 850 
Wire Wire Line
	1250 1350 1100 1350
$Comp
L power:+5V #PWR02
U 1 1 608D75E1
P 1100 850
F 0 "#PWR02" H 1100 700 50  0001 C CNN
F 1 "+5V" H 1115 1023 50  0000 C CNN
F 2 "" H 1100 850 50  0001 C CNN
F 3 "" H 1100 850 50  0001 C CNN
	1    1100 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 608D675F
P 1750 850
F 0 "#PWR03" H 1750 700 50  0001 C CNN
F 1 "+5V" H 1765 1023 50  0000 C CNN
F 2 "" H 1750 850 50  0001 C CNN
F 3 "" H 1750 850 50  0001 C CNN
	1    1750 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  1250 1250 1250
Wire Wire Line
	850  1050 1250 1050
$Comp
L Interface_Expansion-extra:TPIC6B595 U4
U 1 1 608CECE6
P 8950 1450
F 0 "U4" H 9300 2000 50  0000 C CNN
F 1 "TPIC6B595" H 9200 800 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm_LongPads" H 9600 800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpic6b595.pdf" H 8950 1400 50  0001 C CNN
	1    8950 1450
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion-extra:TPIC6B595 U3
U 1 1 608C9D52
P 6550 1450
F 0 "U3" H 6900 2000 50  0000 C CNN
F 1 "TPIC6B595" H 6800 800 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm_LongPads" H 7200 800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpic6b595.pdf" H 6550 1400 50  0001 C CNN
	1    6550 1450
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion-extra:TPIC6B595 U2
U 1 1 608C92E8
P 4150 1450
F 0 "U2" H 4500 2000 50  0000 C CNN
F 1 "TPIC6B595" H 4400 800 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm_LongPads" H 4800 800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpic6b595.pdf" H 4150 1400 50  0001 C CNN
	1    4150 1450
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion-extra:TPIC6B595 U1
U 1 1 608C5141
P 1750 1450
F 0 "U1" H 2100 2000 50  0000 C CNN
F 1 "TPIC6B595" H 2000 800 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm_LongPads" H 2400 800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpic6b595.pdf" H 1750 1400 50  0001 C CNN
	1    1750 1450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 60B0E9F6
P 10450 1300
F 0 "H4" H 10550 1346 50  0000 L CNN
F 1 "MountingHole" H 10550 1255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10450 1300 50  0001 C CNN
F 3 "~" H 10450 1300 50  0001 C CNN
	1    10450 1300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 60B0F50E
P 10450 1100
F 0 "H3" H 10550 1146 50  0000 L CNN
F 1 "MountingHole" H 10550 1055 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10450 1100 50  0001 C CNN
F 3 "~" H 10450 1100 50  0001 C CNN
	1    10450 1100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 60B0F70D
P 10450 900
F 0 "H2" H 10550 946 50  0000 L CNN
F 1 "MountingHole" H 10550 855 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10450 900 50  0001 C CNN
F 3 "~" H 10450 900 50  0001 C CNN
	1    10450 900 
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 60B0F91B
P 10450 700
F 0 "H1" H 10550 746 50  0000 L CNN
F 1 "MountingHole" H 10550 655 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10450 700 50  0001 C CNN
F 3 "~" H 10450 700 50  0001 C CNN
	1    10450 700 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR042
U 1 1 60B9587A
P 7400 4050
F 0 "#PWR042" H 7400 3800 50  0001 C CNN
F 1 "GND" H 7405 3877 50  0000 C CNN
F 2 "" H 7400 4050 50  0001 C CNN
F 3 "" H 7400 4050 50  0001 C CNN
	1    7400 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3700 7400 3700
$Comp
L Regulator_Linear:L7805 U8
U 1 1 60BAE561
P 10300 3500
F 0 "U8" H 10300 3742 50  0000 C CNN
F 1 "L7805" H 10300 3651 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-2" H 10325 3350 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 10300 3450 50  0001 C CNN
	1    10300 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR047
U 1 1 60BAF613
P 10300 4050
F 0 "#PWR047" H 10300 3800 50  0001 C CNN
F 1 "GND" H 10305 3877 50  0000 C CNN
F 2 "" H 10300 4050 50  0001 C CNN
F 3 "" H 10300 4050 50  0001 C CNN
	1    10300 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 4050 10300 3800
$Comp
L Diode:1N5819 D1
U 1 1 60BC18DD
P 9400 3500
F 0 "D1" H 9400 3283 50  0000 C CNN
F 1 "1N5819" H 9400 3374 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 9400 3325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 9400 3500 50  0001 C CNN
	1    9400 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	9550 3500 9700 3500
$Comp
L power:+5V #PWR034
U 1 1 60BDC6C1
P 10750 3150
F 0 "#PWR034" H 10750 3000 50  0001 C CNN
F 1 "+5V" H 10765 3323 50  0000 C CNN
F 2 "" H 10750 3150 50  0001 C CNN
F 3 "" H 10750 3150 50  0001 C CNN
	1    10750 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10600 3500 10750 3500
$Comp
L Device:CP C11
U 1 1 60BF9BB2
P 9700 3750
F 0 "C11" H 9750 3850 50  0000 L CNN
F 1 "100uF/16v" H 9500 3600 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 9738 3600 50  0001 C CNN
F 3 "~" H 9700 3750 50  0001 C CNN
	1    9700 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR046
U 1 1 60C16B64
P 9700 4050
F 0 "#PWR046" H 9700 3800 50  0001 C CNN
F 1 "GND" H 9705 3877 50  0000 C CNN
F 2 "" H 9700 4050 50  0001 C CNN
F 3 "" H 9700 4050 50  0001 C CNN
	1    9700 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 4050 9700 3900
Wire Wire Line
	9700 3600 9700 3500
Connection ~ 9700 3500
Wire Wire Line
	9700 3500 10000 3500
$Comp
L Device:CP C12
U 1 1 60C31A1A
P 10750 3750
F 0 "C12" H 10868 3796 50  0000 L CNN
F 1 "33uF/16v" H 10600 3600 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 10788 3600 50  0001 C CNN
F 3 "~" H 10750 3750 50  0001 C CNN
	1    10750 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR048
U 1 1 60C31FF2
P 10750 4050
F 0 "#PWR048" H 10750 3800 50  0001 C CNN
F 1 "GND" H 10755 3877 50  0000 C CNN
F 2 "" H 10750 4050 50  0001 C CNN
F 3 "" H 10750 4050 50  0001 C CNN
	1    10750 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 4050 10750 3900
Wire Wire Line
	10750 3600 10750 3500
$Comp
L Device:CP C10
U 1 1 60C778F6
P 9150 3750
F 0 "C10" H 9200 3850 50  0000 L CNN
F 1 "2200uF/16v" H 8950 3600 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 9188 3600 50  0001 C CNN
F 3 "~" H 9150 3750 50  0001 C CNN
	1    9150 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR045
U 1 1 60C77F12
P 9150 4050
F 0 "#PWR045" H 9150 3800 50  0001 C CNN
F 1 "GND" H 9155 3877 50  0000 C CNN
F 2 "" H 9150 4050 50  0001 C CNN
F 3 "" H 9150 4050 50  0001 C CNN
	1    9150 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 4050 9150 3900
Wire Wire Line
	9150 3600 9150 3500
Connection ~ 9150 3500
Wire Wire Line
	9150 3500 9250 3500
$Comp
L power:PWR_FLAG #FLG03
U 1 1 60CFC607
P 9700 3150
F 0 "#FLG03" H 9700 3225 50  0001 C CNN
F 1 "PWR_FLAG" H 9700 3323 50  0000 C CNN
F 2 "" H 9700 3150 50  0001 C CNN
F 3 "~" H 9700 3150 50  0001 C CNN
	1    9700 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 3500 9700 3150
$Comp
L power:PWR_FLAG #FLG04
U 1 1 60D274B7
P 7000 4050
F 0 "#FLG04" H 7000 4125 50  0001 C CNN
F 1 "PWR_FLAG" H 7000 4223 50  0000 C CNN
F 2 "" H 7000 4050 50  0001 C CNN
F 3 "~" H 7000 4050 50  0001 C CNN
	1    7000 4050
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 4050 7400 3950
Connection ~ 7400 3700
$Comp
L power:PWR_FLAG #FLG02
U 1 1 60D63559
P 9150 3150
F 0 "#FLG02" H 9150 3225 50  0001 C CNN
F 1 "PWR_FLAG" H 9150 3323 50  0000 C CNN
F 2 "" H 9150 3150 50  0001 C CNN
F 3 "~" H 9150 3150 50  0001 C CNN
	1    9150 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 3500 9150 3150
$Comp
L Connector:Barrel_Jack_Switch J6
U 1 1 609100A3
P 6950 3600
F 0 "J6" H 6950 3800 50  0000 C CNN
F 1 "Barrel_Jack_Switch" H 7000 3400 50  0000 C CNN
F 2 "Connector_BarrelJack-fixed:BarrelJack_Horizontal" H 7000 3560 50  0001 C CNN
F 3 "~" H 7000 3560 50  0001 C CNN
	1    6950 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3600 7400 3600
Wire Wire Line
	7400 3600 7400 3700
$Comp
L Display_Character-extra:5611BH U9
U 1 1 608F96BB
P 1600 7000
F 0 "U9" H 1600 7667 50  0000 C CNN
F 1 "5611BH" H 1600 7576 50  0000 C CNN
F 2 "Display_7Segment-extra:5611BH" H 1600 6400 50  0001 C CNN
F 3 "" H 1100 7475 50  0001 L CNN
	1    1600 7000
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR049
U 1 1 60962EEE
P 2000 5900
F 0 "#PWR049" H 2000 5750 50  0001 C CNN
F 1 "+12V" H 2015 6073 50  0000 C CNN
F 2 "" H 2000 5900 50  0001 C CNN
F 3 "" H 2000 5900 50  0001 C CNN
	1    2000 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 7400 2000 7400
Wire Wire Line
	2000 7400 2000 7300
Wire Wire Line
	1900 7300 2000 7300
Connection ~ 2000 7300
Wire Wire Line
	2000 7300 2000 5900
$Comp
L Display_Character-extra:5611BH U10
U 1 1 609A9715
P 3050 7000
F 0 "U10" H 3050 7667 50  0000 C CNN
F 1 "5611BH" H 3050 7576 50  0000 C CNN
F 2 "Display_7Segment-extra:5611BH" H 3050 6400 50  0001 C CNN
F 3 "" H 2550 7475 50  0001 L CNN
	1    3050 7000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 609A9EDB
P 2450 6700
F 0 "R3" V 2400 6900 50  0000 C CNN
F 1 "4K7" V 2450 6700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2380 6700 50  0001 C CNN
F 3 "~" H 2450 6700 50  0001 C CNN
	1    2450 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 6700 2750 6700
$Comp
L Device:R R7
U 1 1 609A9EE6
P 2450 6800
F 0 "R7" V 2400 7000 50  0000 C CNN
F 1 "4K7" V 2450 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2380 6800 50  0001 C CNN
F 3 "~" H 2450 6800 50  0001 C CNN
	1    2450 6800
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 6800 2750 6800
$Comp
L Device:R R11
U 1 1 609A9EF1
P 2450 6900
F 0 "R11" V 2400 7100 50  0000 C CNN
F 1 "4K7" V 2450 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2380 6900 50  0001 C CNN
F 3 "~" H 2450 6900 50  0001 C CNN
	1    2450 6900
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 6900 2750 6900
$Comp
L Device:R R15
U 1 1 609A9EFC
P 2450 7000
F 0 "R15" V 2400 7200 50  0000 C CNN
F 1 "4K7" V 2450 7000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2380 7000 50  0001 C CNN
F 3 "~" H 2450 7000 50  0001 C CNN
	1    2450 7000
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 7000 2750 7000
$Comp
L Device:R R19
U 1 1 609A9F07
P 2450 7100
F 0 "R19" V 2400 7300 50  0000 C CNN
F 1 "4K7" V 2450 7100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2380 7100 50  0001 C CNN
F 3 "~" H 2450 7100 50  0001 C CNN
	1    2450 7100
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 7100 2750 7100
$Comp
L Device:R R23
U 1 1 609A9F12
P 2450 7200
F 0 "R23" V 2400 7400 50  0000 C CNN
F 1 "4K7" V 2450 7200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2380 7200 50  0001 C CNN
F 3 "~" H 2450 7200 50  0001 C CNN
	1    2450 7200
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 7200 2750 7200
$Comp
L Device:R R27
U 1 1 609A9F1D
P 2450 7300
F 0 "R27" V 2400 7500 50  0000 C CNN
F 1 "4K7" V 2450 7300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2380 7300 50  0001 C CNN
F 3 "~" H 2450 7300 50  0001 C CNN
	1    2450 7300
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 7300 2750 7300
$Comp
L Device:R R31
U 1 1 609A9F28
P 2450 7400
F 0 "R31" V 2400 7600 50  0000 C CNN
F 1 "4K7" V 2450 7400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2380 7400 50  0001 C CNN
F 3 "~" H 2450 7400 50  0001 C CNN
	1    2450 7400
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 7400 2750 7400
$Comp
L power:+12V #PWR050
U 1 1 609A9F33
P 3450 5900
F 0 "#PWR050" H 3450 5750 50  0001 C CNN
F 1 "+12V" H 3465 6073 50  0000 C CNN
F 2 "" H 3450 5900 50  0001 C CNN
F 3 "" H 3450 5900 50  0001 C CNN
	1    3450 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 7400 3450 7400
Wire Wire Line
	3450 7400 3450 7300
Wire Wire Line
	3350 7300 3450 7300
Connection ~ 3450 7300
Wire Wire Line
	3450 7300 3450 5900
Text Label 2100 7400 0    50   ~ 0
S2DP
Text Label 2100 7300 0    50   ~ 0
S2G
Text Label 2100 7200 0    50   ~ 0
S2F
Text Label 2100 7100 0    50   ~ 0
S2E
Text Label 2100 7000 0    50   ~ 0
S2D
Text Label 2100 6900 0    50   ~ 0
S2C
Text Label 2100 6800 0    50   ~ 0
S2B
Text Label 2100 6700 0    50   ~ 0
S2A
Wire Wire Line
	2100 7400 2300 7400
Wire Wire Line
	2300 7300 2100 7300
Wire Wire Line
	2300 7200 2100 7200
Wire Wire Line
	2100 7100 2300 7100
Wire Wire Line
	2300 7000 2100 7000
Wire Wire Line
	2100 6900 2300 6900
Wire Wire Line
	2300 6800 2100 6800
Wire Wire Line
	2100 6700 2300 6700
$Comp
L Display_Character-extra:5611BH U11
U 1 1 60A7E4A4
P 4500 7000
F 0 "U11" H 4500 7667 50  0000 C CNN
F 1 "5611BH" H 4500 7576 50  0000 C CNN
F 2 "Display_7Segment-extra:5611BH" H 4500 6400 50  0001 C CNN
F 3 "" H 4000 7475 50  0001 L CNN
	1    4500 7000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 60A7E4AA
P 3900 6700
F 0 "R4" V 3850 6900 50  0000 C CNN
F 1 "4K7" V 3900 6700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 6700 50  0001 C CNN
F 3 "~" H 3900 6700 50  0001 C CNN
	1    3900 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 6700 4200 6700
$Comp
L Device:R R8
U 1 1 60A7E4B1
P 3900 6800
F 0 "R8" V 3850 7000 50  0000 C CNN
F 1 "4K7" V 3900 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 6800 50  0001 C CNN
F 3 "~" H 3900 6800 50  0001 C CNN
	1    3900 6800
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 6800 4200 6800
$Comp
L Device:R R12
U 1 1 60A7E4B8
P 3900 6900
F 0 "R12" V 3850 7100 50  0000 C CNN
F 1 "4K7" V 3900 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 6900 50  0001 C CNN
F 3 "~" H 3900 6900 50  0001 C CNN
	1    3900 6900
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 6900 4200 6900
$Comp
L Device:R R16
U 1 1 60A7E4BF
P 3900 7000
F 0 "R16" V 3850 7200 50  0000 C CNN
F 1 "4K7" V 3900 7000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 7000 50  0001 C CNN
F 3 "~" H 3900 7000 50  0001 C CNN
	1    3900 7000
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 7000 4200 7000
$Comp
L Device:R R20
U 1 1 60A7E4C6
P 3900 7100
F 0 "R20" V 3850 7300 50  0000 C CNN
F 1 "4K7" V 3900 7100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 7100 50  0001 C CNN
F 3 "~" H 3900 7100 50  0001 C CNN
	1    3900 7100
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 7100 4200 7100
$Comp
L Device:R R24
U 1 1 60A7E4CD
P 3900 7200
F 0 "R24" V 3850 7400 50  0000 C CNN
F 1 "4K7" V 3900 7200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 7200 50  0001 C CNN
F 3 "~" H 3900 7200 50  0001 C CNN
	1    3900 7200
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 7200 4200 7200
$Comp
L Device:R R28
U 1 1 60A7E4D4
P 3900 7300
F 0 "R28" V 3850 7500 50  0000 C CNN
F 1 "4K7" V 3900 7300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 7300 50  0001 C CNN
F 3 "~" H 3900 7300 50  0001 C CNN
	1    3900 7300
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 7300 4200 7300
$Comp
L Device:R R32
U 1 1 60A7E4DB
P 3900 7400
F 0 "R32" V 3850 7600 50  0000 C CNN
F 1 "4K7" V 3900 7400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 7400 50  0001 C CNN
F 3 "~" H 3900 7400 50  0001 C CNN
	1    3900 7400
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 7400 4200 7400
$Comp
L power:+12V #PWR051
U 1 1 60A7E4E2
P 4900 5900
F 0 "#PWR051" H 4900 5750 50  0001 C CNN
F 1 "+12V" H 4915 6073 50  0000 C CNN
F 2 "" H 4900 5900 50  0001 C CNN
F 3 "" H 4900 5900 50  0001 C CNN
	1    4900 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 7400 4900 7400
Wire Wire Line
	4900 7400 4900 7300
Wire Wire Line
	4800 7300 4900 7300
Connection ~ 4900 7300
Wire Wire Line
	4900 7300 4900 5900
Text Label 3550 7400 0    50   ~ 0
S3DP
Text Label 3550 7300 0    50   ~ 0
S3G
Text Label 3550 7200 0    50   ~ 0
S3F
Text Label 3550 7100 0    50   ~ 0
S3E
Text Label 3550 7000 0    50   ~ 0
S3D
Text Label 3550 6900 0    50   ~ 0
S3C
Text Label 3550 6800 0    50   ~ 0
S3B
Text Label 3550 6700 0    50   ~ 0
S3A
Wire Wire Line
	3550 7400 3750 7400
Wire Wire Line
	3750 7300 3550 7300
Wire Wire Line
	3750 7200 3550 7200
Wire Wire Line
	3550 7100 3750 7100
Wire Wire Line
	3750 7000 3550 7000
Wire Wire Line
	3550 6900 3750 6900
Wire Wire Line
	3750 6800 3550 6800
Wire Wire Line
	3550 6700 3750 6700
$Comp
L Display_Character-extra:5611BH U12
U 1 1 60ACA5C9
P 5950 7000
F 0 "U12" H 5950 7667 50  0000 C CNN
F 1 "5611BH" H 5950 7576 50  0000 C CNN
F 2 "Display_7Segment-extra:5611BH" H 5950 6400 50  0001 C CNN
F 3 "" H 5450 7475 50  0001 L CNN
	1    5950 7000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 60ACA5CF
P 5350 6700
F 0 "R5" V 5300 6900 50  0000 C CNN
F 1 "4K7" V 5350 6700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5280 6700 50  0001 C CNN
F 3 "~" H 5350 6700 50  0001 C CNN
	1    5350 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 6700 5650 6700
$Comp
L Device:R R9
U 1 1 60ACA5D6
P 5350 6800
F 0 "R9" V 5300 7000 50  0000 C CNN
F 1 "4K7" V 5350 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5280 6800 50  0001 C CNN
F 3 "~" H 5350 6800 50  0001 C CNN
	1    5350 6800
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 6800 5650 6800
$Comp
L Device:R R13
U 1 1 60ACA5DD
P 5350 6900
F 0 "R13" V 5300 7100 50  0000 C CNN
F 1 "4K7" V 5350 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5280 6900 50  0001 C CNN
F 3 "~" H 5350 6900 50  0001 C CNN
	1    5350 6900
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 6900 5650 6900
$Comp
L Device:R R17
U 1 1 60ACA5E4
P 5350 7000
F 0 "R17" V 5300 7200 50  0000 C CNN
F 1 "4K7" V 5350 7000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5280 7000 50  0001 C CNN
F 3 "~" H 5350 7000 50  0001 C CNN
	1    5350 7000
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 7000 5650 7000
$Comp
L Device:R R21
U 1 1 60ACA5EB
P 5350 7100
F 0 "R21" V 5300 7300 50  0000 C CNN
F 1 "4K7" V 5350 7100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5280 7100 50  0001 C CNN
F 3 "~" H 5350 7100 50  0001 C CNN
	1    5350 7100
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 7100 5650 7100
$Comp
L Device:R R25
U 1 1 60ACA5F2
P 5350 7200
F 0 "R25" V 5300 7400 50  0000 C CNN
F 1 "4K7" V 5350 7200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5280 7200 50  0001 C CNN
F 3 "~" H 5350 7200 50  0001 C CNN
	1    5350 7200
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 7200 5650 7200
$Comp
L Device:R R29
U 1 1 60ACA5F9
P 5350 7300
F 0 "R29" V 5300 7500 50  0000 C CNN
F 1 "4K7" V 5350 7300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5280 7300 50  0001 C CNN
F 3 "~" H 5350 7300 50  0001 C CNN
	1    5350 7300
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 7300 5650 7300
$Comp
L Device:R R33
U 1 1 60ACA600
P 5350 7400
F 0 "R33" V 5300 7600 50  0000 C CNN
F 1 "4K7" V 5350 7400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5280 7400 50  0001 C CNN
F 3 "~" H 5350 7400 50  0001 C CNN
	1    5350 7400
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 7400 5650 7400
$Comp
L power:+12V #PWR052
U 1 1 60ACA607
P 6350 5900
F 0 "#PWR052" H 6350 5750 50  0001 C CNN
F 1 "+12V" H 6365 6073 50  0000 C CNN
F 2 "" H 6350 5900 50  0001 C CNN
F 3 "" H 6350 5900 50  0001 C CNN
	1    6350 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 7400 6350 7400
Wire Wire Line
	6350 7400 6350 7300
Wire Wire Line
	6250 7300 6350 7300
Connection ~ 6350 7300
Wire Wire Line
	6350 7300 6350 5900
Text Label 5000 7400 0    50   ~ 0
S4DP
Text Label 5000 7300 0    50   ~ 0
S4G
Text Label 5000 7200 0    50   ~ 0
S4F
Text Label 5000 7100 0    50   ~ 0
S4E
Text Label 5000 7000 0    50   ~ 0
S4D
Text Label 5000 6900 0    50   ~ 0
S4C
Text Label 5000 6800 0    50   ~ 0
S4B
Text Label 5000 6700 0    50   ~ 0
S4A
Wire Wire Line
	5000 7400 5200 7400
Wire Wire Line
	5200 7300 5000 7300
Wire Wire Line
	5200 7200 5000 7200
Wire Wire Line
	5000 7100 5200 7100
Wire Wire Line
	5200 7000 5000 7000
Wire Wire Line
	5000 6900 5200 6900
Wire Wire Line
	5200 6800 5000 6800
Wire Wire Line
	5000 6700 5200 6700
Wire Wire Line
	4000 3850 4000 4500
Wire Wire Line
	3900 3750 3900 4400
Wire Wire Line
	3700 3650 3700 4200
Wire Wire Line
	3600 3550 3600 4100
NoConn ~ 5200 4150
NoConn ~ 5200 4250
Wire Wire Line
	4100 4450 4100 4250
Wire Wire Line
	4100 4250 4200 4250
Connection ~ 4100 4450
Wire Wire Line
	4100 4250 4100 4150
Wire Wire Line
	4100 4150 4200 4150
Connection ~ 4100 4250
Wire Wire Line
	10750 3500 10750 3150
Connection ~ 10750 3500
Wire Wire Line
	1150 7400 1300 7400
Wire Wire Line
	1150 7300 1300 7300
Wire Wire Line
	1150 7200 1300 7200
Wire Wire Line
	1150 7100 1300 7100
Wire Wire Line
	1150 7000 1300 7000
Wire Wire Line
	1150 6900 1300 6900
Wire Wire Line
	1150 6800 1300 6800
Wire Wire Line
	1150 6700 1300 6700
Wire Wire Line
	650  6700 850  6700
Wire Wire Line
	850  6800 650  6800
Wire Wire Line
	650  6900 850  6900
Wire Wire Line
	850  7000 650  7000
Wire Wire Line
	650  7100 850  7100
Wire Wire Line
	850  7200 650  7200
Wire Wire Line
	850  7300 650  7300
Wire Wire Line
	650  7400 850  7400
Text Label 650  6700 0    50   ~ 0
S1A
Text Label 650  6800 0    50   ~ 0
S1B
Text Label 650  6900 0    50   ~ 0
S1C
Text Label 650  7000 0    50   ~ 0
S1D
Text Label 650  7100 0    50   ~ 0
S1E
Text Label 650  7200 0    50   ~ 0
S1F
Text Label 650  7300 0    50   ~ 0
S1G
Text Label 650  7400 0    50   ~ 0
S1DP
$Comp
L Device:R R30
U 1 1 609571A2
P 1000 7400
F 0 "R30" V 950 7600 50  0000 C CNN
F 1 "4K7" V 1000 7400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 930 7400 50  0001 C CNN
F 3 "~" H 1000 7400 50  0001 C CNN
	1    1000 7400
	0    1    1    0   
$EndComp
$Comp
L Device:R R26
U 1 1 6094B4C5
P 1000 7300
F 0 "R26" V 950 7500 50  0000 C CNN
F 1 "4K7" V 1000 7300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 930 7300 50  0001 C CNN
F 3 "~" H 1000 7300 50  0001 C CNN
	1    1000 7300
	0    1    1    0   
$EndComp
$Comp
L Device:R R22
U 1 1 6093FA25
P 1000 7200
F 0 "R22" V 950 7400 50  0000 C CNN
F 1 "4K7" V 1000 7200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 930 7200 50  0001 C CNN
F 3 "~" H 1000 7200 50  0001 C CNN
	1    1000 7200
	0    1    1    0   
$EndComp
$Comp
L Device:R R18
U 1 1 6093415B
P 1000 7100
F 0 "R18" V 950 7300 50  0000 C CNN
F 1 "4K7" V 1000 7100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 930 7100 50  0001 C CNN
F 3 "~" H 1000 7100 50  0001 C CNN
	1    1000 7100
	0    1    1    0   
$EndComp
$Comp
L Device:R R14
U 1 1 609289EA
P 1000 7000
F 0 "R14" V 950 7200 50  0000 C CNN
F 1 "4K7" V 1000 7000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 930 7000 50  0001 C CNN
F 3 "~" H 1000 7000 50  0001 C CNN
	1    1000 7000
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 6091D317
P 1000 6900
F 0 "R10" V 950 7100 50  0000 C CNN
F 1 "4K7" V 1000 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 930 6900 50  0001 C CNN
F 3 "~" H 1000 6900 50  0001 C CNN
	1    1000 6900
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 60911E2B
P 1000 6800
F 0 "R6" V 950 7000 50  0000 C CNN
F 1 "4K7" V 1000 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 930 6800 50  0001 C CNN
F 3 "~" H 1000 6800 50  0001 C CNN
	1    1000 6800
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 608FA0A7
P 1000 6700
F 0 "R2" V 950 6900 50  0000 C CNN
F 1 "4K7" V 1000 6700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 930 6700 50  0001 C CNN
F 3 "~" H 1000 6700 50  0001 C CNN
	1    1000 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 4300 3800 4050
Wire Wire Line
	3800 4050 4200 4050
Wire Wire Line
	4200 3950 3200 3950
Wire Wire Line
	3200 3950 3200 3700
$Comp
L Connector:TestPoint TP1
U 1 1 611FE123
P 5450 3950
F 0 "TP1" V 5450 4138 50  0000 L CNN
F 1 "TestPoint" V 5495 4138 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 5650 3950 50  0001 C CNN
F 3 "~" H 5650 3950 50  0001 C CNN
	1    5450 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 3950 5450 3950
$Comp
L LED-extra:PL9823-F5 D2
U 1 1 61220BB0
P 6100 4050
F 0 "D2" H 6200 4300 50  0000 L CNN
F 1 "PL9823-F5" H 5600 3800 50  0000 L CNN
F 2 "LED_THT-extra:LED_D5.0mm-4_PL9823-F5" H 6150 3750 50  0001 L TNN
F 3 "" H 6200 3675 50  0001 L TNN
	1    6100 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR054
U 1 1 6122258F
P 6100 5000
F 0 "#PWR054" H 6100 4750 50  0001 C CNN
F 1 "GND" H 6105 4827 50  0000 C CNN
F 2 "" H 6100 5000 50  0001 C CNN
F 3 "" H 6100 5000 50  0001 C CNN
	1    6100 5000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR053
U 1 1 61222901
P 6100 3150
F 0 "#PWR053" H 6100 3000 50  0001 C CNN
F 1 "+5V" H 6115 3323 50  0000 C CNN
F 2 "" H 6100 3150 50  0001 C CNN
F 3 "" H 6100 3150 50  0001 C CNN
	1    6100 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3750 6100 3150
Wire Wire Line
	6100 5000 6100 4350
Wire Wire Line
	5200 4050 5800 4050
NoConn ~ 6400 4050
Text Label 5250 4050 0    50   ~ 0
NEOPIXEL_5V
Text GLabel 2950 4000 2    50   Input ~ 0
INT
Text GLabel 2950 3900 2    50   BiDi ~ 0
SDA
Text GLabel 2950 3800 2    50   Output ~ 0
SCL
Text Label 2800 4300 0    50   ~ 0
NEOPIXEL
Wire Wire Line
	3200 3700 2750 3700
$Comp
L MCU_Module:WeMos_D1_mini U6
U 1 1 608C5E6E
P 2350 4100
F 0 "U6" H 2600 4850 50  0000 C CNN
F 1 "WeMos_D1_mini" H 2650 3350 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 2350 2950 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 500 2950 50  0001 C CNN
	1    2350 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 4300 3800 4300
$Comp
L power:+3V3 #PWR027
U 1 1 60CFA625
P 1800 3150
F 0 "#PWR027" H 1800 3000 50  0001 C CNN
F 1 "+3V3" H 1815 3323 50  0000 C CNN
F 2 "" H 1800 3150 50  0001 C CNN
F 3 "" H 1800 3150 50  0001 C CNN
	1    1800 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4150 1800 3150
Wire Wire Line
	1800 5000 1800 4450
$Comp
L power:GND #PWR036
U 1 1 60CEFD2D
P 1800 5000
F 0 "#PWR036" H 1800 4750 50  0001 C CNN
F 1 "GND" H 1805 4827 50  0000 C CNN
F 2 "" H 1800 5000 50  0001 C CNN
F 3 "" H 1800 5000 50  0001 C CNN
	1    1800 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C7
U 1 1 60CEF6BD
P 1800 4300
F 0 "C7" H 1918 4346 50  0000 L CNN
F 1 "100uF/16v" V 1850 3800 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 1838 4150 50  0001 C CNN
F 3 "~" H 1800 4300 50  0001 C CNN
	1    1800 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR026
U 1 1 60CE2003
P 1450 3150
F 0 "#PWR026" H 1450 3000 50  0001 C CNN
F 1 "+5V" H 1465 3323 50  0000 C CNN
F 2 "" H 1450 3150 50  0001 C CNN
F 3 "" H 1450 3150 50  0001 C CNN
	1    1450 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 4150 1450 3150
Wire Wire Line
	1450 5000 1450 4450
$Comp
L power:GND #PWR035
U 1 1 60CCD814
P 1450 5000
F 0 "#PWR035" H 1450 4750 50  0001 C CNN
F 1 "GND" H 1455 4827 50  0000 C CNN
F 2 "" H 1450 5000 50  0001 C CNN
F 3 "" H 1450 5000 50  0001 C CNN
	1    1450 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 60CB870C
P 1450 4300
F 0 "C6" H 1568 4346 50  0000 L CNN
F 1 "100uF/16v" V 1500 3800 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 1488 4150 50  0001 C CNN
F 3 "~" H 1450 4300 50  0001 C CNN
	1    1450 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 3700 1950 3700
$Comp
L Device:R R1
U 1 1 609F006E
P 1350 3850
F 0 "R1" H 1419 3804 50  0000 L CNN
F 1 "100R" H 1419 3895 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1280 3850 50  0001 C CNN
F 3 "~" H 1350 3850 50  0001 C CNN
	1    1350 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	750  3150 750  3900
$Comp
L power:+3V3 #PWR025
U 1 1 609EB6A8
P 750 3150
F 0 "#PWR025" H 750 3000 50  0001 C CNN
F 1 "+3V3" H 765 3323 50  0000 C CNN
F 2 "" H 750 3150 50  0001 C CNN
F 3 "" H 750 3150 50  0001 C CNN
	1    750  3150
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR029
U 1 1 609EB137
P 2450 3150
F 0 "#PWR029" H 2450 3000 50  0001 C CNN
F 1 "+3V3" H 2465 3323 50  0000 C CNN
F 2 "" H 2450 3150 50  0001 C CNN
F 3 "" H 2450 3150 50  0001 C CNN
	1    2450 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3300 2450 3150
Wire Wire Line
	750  4500 750  5000
$Comp
L power:GND #PWR032
U 1 1 609E463D
P 750 5000
F 0 "#PWR032" H 750 4750 50  0001 C CNN
F 1 "GND" H 755 4827 50  0000 C CNN
F 2 "" H 750 5000 50  0001 C CNN
F 3 "" H 750 5000 50  0001 C CNN
	1    750  5000
	1    0    0    -1  
$EndComp
$Comp
L Power_Supervisor:TPS3839DBZ U7
U 1 1 609E251A
P 750 4200
F 0 "U7" H 1050 4450 50  0000 R CNN
F 1 "MAX809S" H 1150 3950 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 750 4200 50  0001 C CNN
F 3 "" H 750 4200 50  0001 C CNN
	1    750  4200
	1    0    0    -1  
$EndComp
Text Label 2800 4500 0    50   ~ 0
LATCH
Text Label 2800 4400 0    50   ~ 0
DATA
Text Label 2800 4200 0    50   ~ 0
CLK
Text Label 2800 4100 0    50   ~ 0
~OE
Wire Wire Line
	2750 4000 2950 4000
Wire Wire Line
	2750 3900 2950 3900
Wire Wire Line
	2750 3800 2950 3800
Wire Wire Line
	2350 5000 2350 4900
$Comp
L power:GND #PWR037
U 1 1 6092E300
P 2350 5000
F 0 "#PWR037" H 2350 4750 50  0001 C CNN
F 1 "GND" H 2355 4827 50  0000 C CNN
F 2 "" H 2350 5000 50  0001 C CNN
F 3 "" H 2350 5000 50  0001 C CNN
	1    2350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4100 2750 4100
NoConn ~ 2750 3600
Wire Wire Line
	2250 3150 2250 3300
$Comp
L power:+5V #PWR028
U 1 1 608D59AA
P 2250 3150
F 0 "#PWR028" H 2250 3000 50  0001 C CNN
F 1 "+5V" H 2265 3323 50  0000 C CNN
F 2 "" H 2250 3150 50  0001 C CNN
F 3 "" H 2250 3150 50  0001 C CNN
	1    2250 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 4500 4000 4500
Wire Wire Line
	2750 4200 3700 4200
Wire Wire Line
	2750 4400 3900 4400
NoConn ~ 1950 4000
NoConn ~ 1950 4100
Wire Notes Line
	550  550  550  2750
Wire Notes Line
	550  2750 10200 2750
Wire Notes Line
	10200 2750 10200 550 
Wire Notes Line
	10200 550  550  550 
Wire Notes Line
	10300 1500 11150 1500
Wire Notes Line
	11150 1500 11150 550 
Wire Notes Line
	11150 550  10300 550 
Wire Notes Line
	10300 550  10300 1500
Wire Notes Line
	550  2850 550  5300
Wire Notes Line
	550  5300 6500 5300
Wire Notes Line
	6500 5300 6500 2850
Wire Notes Line
	6500 2850 550  2850
Wire Wire Line
	1350 4000 1350 4200
Wire Wire Line
	1150 4200 1350 4200
Wire Notes Line
	6600 2850 6600 4350
Wire Notes Line
	6600 4350 11150 4350
Wire Notes Line
	11150 4350 11150 2850
Wire Notes Line
	11150 2850 6600 2850
Wire Notes Line
	550  5400 550  7700
Wire Notes Line
	550  7700 6500 7700
Wire Notes Line
	6500 7700 6500 5400
Wire Notes Line
	6500 5400 550  5400
Wire Notes Line
	8800 4450 8800 6450
Wire Notes Line
	8800 6450 11150 6450
Wire Notes Line
	11150 6450 11150 4450
Wire Notes Line
	11150 4450 8800 4450
$Comp
L Interface_Expansion:MCP23008-xSO U13
U 1 1 60EFAC14
P 9900 5400
F 0 "U13" H 10250 5950 50  0000 C CNN
F 1 "MCP23008-xSO" H 10250 4800 50  0000 C CNN
F 2 "Package_SO:SOIC-18W_7.5x11.6mm_P1.27mm" H 9900 4350 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/MCP23008-MCP23S08-Data-Sheet-20001919F.pdf" H 11200 4200 50  0001 C CNN
	1    9900 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 60EFE32F
P 8950 5400
F 0 "C13" H 9000 5500 50  0000 L CNN
F 1 "10uF" H 9000 5250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8988 5250 50  0001 C CNN
F 3 "~" H 8950 5400 50  0001 C CNN
	1    8950 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 4750 8950 5250
$Comp
L power:+3V3 #PWR056
U 1 1 60F17143
P 8950 4750
F 0 "#PWR056" H 8950 4600 50  0001 C CNN
F 1 "+3V3" H 8965 4923 50  0000 C CNN
F 2 "" H 8950 4750 50  0001 C CNN
F 3 "" H 8950 4750 50  0001 C CNN
	1    8950 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR059
U 1 1 60F17AE1
P 8950 6150
F 0 "#PWR059" H 8950 5900 50  0001 C CNN
F 1 "GND" H 8955 5977 50  0000 C CNN
F 2 "" H 8950 6150 50  0001 C CNN
F 3 "" H 8950 6150 50  0001 C CNN
	1    8950 6150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR061
U 1 1 60F4CA87
P 9900 6150
F 0 "#PWR061" H 9900 5900 50  0001 C CNN
F 1 "GND" H 9905 5977 50  0000 C CNN
F 2 "" H 9900 6150 50  0001 C CNN
F 3 "" H 9900 6150 50  0001 C CNN
	1    9900 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 6150 9900 6000
Wire Wire Line
	10400 5000 10850 5000
Wire Wire Line
	10400 5100 10850 5100
Wire Wire Line
	10400 5200 10850 5200
$Comp
L power:GND #PWR060
U 1 1 6103053C
P 9250 6150
F 0 "#PWR060" H 9250 5900 50  0001 C CNN
F 1 "GND" H 9255 5977 50  0000 C CNN
F 2 "" H 9250 6150 50  0001 C CNN
F 3 "" H 9250 6150 50  0001 C CNN
	1    9250 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 5800 9250 5800
Wire Wire Line
	9250 5800 9250 6150
Wire Wire Line
	9400 5700 9250 5700
Wire Wire Line
	9250 5700 9250 5800
Connection ~ 9250 5800
Wire Wire Line
	9400 5600 9250 5600
Wire Wire Line
	9250 5600 9250 5700
Connection ~ 9250 5700
$Comp
L power:+3V3 #PWR058
U 1 1 6107E6A7
P 9900 4750
F 0 "#PWR058" H 9900 4600 50  0001 C CNN
F 1 "+3V3" H 9915 4923 50  0000 C CNN
F 2 "" H 9900 4750 50  0001 C CNN
F 3 "" H 9900 4750 50  0001 C CNN
	1    9900 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 4750 9900 4800
Wire Wire Line
	8950 6150 8950 5550
$Comp
L power:+3V3 #PWR057
U 1 1 6116AEA2
P 9300 4750
F 0 "#PWR057" H 9300 4600 50  0001 C CNN
F 1 "+3V3" H 9315 4923 50  0000 C CNN
F 2 "" H 9300 4750 50  0001 C CNN
F 3 "" H 9300 4750 50  0001 C CNN
	1    9300 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 5000 9300 5000
Wire Wire Line
	9300 5000 9300 4750
Text GLabel 9300 5400 0    50   Output ~ 0
INT
Text GLabel 9300 5200 0    50   BiDi ~ 0
SDA
Text GLabel 9300 5100 0    50   Output ~ 0
SCL
Wire Wire Line
	9400 5400 9300 5400
Wire Wire Line
	9300 5200 9400 5200
Wire Wire Line
	9400 5100 9300 5100
Wire Notes Line
	10300 1600 10300 2750
Wire Notes Line
	10300 2750 11150 2750
Wire Notes Line
	11150 2750 11150 1600
Wire Notes Line
	11150 1600 10300 1600
$Comp
L power:+3V3 #PWR055
U 1 1 6125BD2B
P 10400 1850
F 0 "#PWR055" H 10400 1700 50  0001 C CNN
F 1 "+3V3" H 10415 2023 50  0000 C CNN
F 2 "" H 10400 1850 50  0001 C CNN
F 3 "" H 10400 1850 50  0001 C CNN
	1    10400 1850
	1    0    0    -1  
$EndComp
Text GLabel 10900 2550 2    50   BiDi ~ 0
SDA
Text GLabel 10900 2250 2    50   BiDi ~ 0
SCL
$Comp
L Device:R R34
U 1 1 612770B5
P 10650 2250
F 0 "R34" V 10443 2250 50  0000 C CNN
F 1 "4K7" V 10534 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 10580 2250 50  0001 C CNN
F 3 "~" H 10650 2250 50  0001 C CNN
	1    10650 2250
	0    1    1    0   
$EndComp
$Comp
L Device:R R35
U 1 1 612C6271
P 10650 2550
F 0 "R35" V 10443 2550 50  0000 C CNN
F 1 "4K7" V 10534 2550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 10580 2550 50  0001 C CNN
F 3 "~" H 10650 2550 50  0001 C CNN
	1    10650 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	10500 2550 10400 2550
Wire Wire Line
	10400 2550 10400 2250
Wire Wire Line
	10500 2250 10400 2250
Connection ~ 10400 2250
Wire Wire Line
	10400 2250 10400 1850
Wire Wire Line
	10800 2250 10900 2250
Wire Wire Line
	10800 2550 10900 2550
Wire Notes Line
	8700 4450 6600 4450
Wire Notes Line
	6600 4450 6600 6450
Wire Notes Line
	6600 6450 8700 6450
Wire Notes Line
	8700 6450 8700 4450
Text GLabel 8400 5250 2    50   BiDi ~ 0
SDA
Text GLabel 8400 5350 2    50   Output ~ 0
SCL
Wire Wire Line
	8350 5250 8400 5250
Wire Wire Line
	8400 5350 8350 5350
$Comp
L power:GND #PWR065
U 1 1 614CF650
P 7950 6150
F 0 "#PWR065" H 7950 5900 50  0001 C CNN
F 1 "GND" H 7955 5977 50  0000 C CNN
F 2 "" H 7950 6150 50  0001 C CNN
F 3 "" H 7950 6150 50  0001 C CNN
	1    7950 6150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR066
U 1 1 614CF9C7
P 8500 6150
F 0 "#PWR066" H 8500 5900 50  0001 C CNN
F 1 "GND" H 8505 5977 50  0000 C CNN
F 2 "" H 8500 6150 50  0001 C CNN
F 3 "" H 8500 6150 50  0001 C CNN
	1    8500 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 5650 8500 5650
Wire Wire Line
	8500 5650 8500 6150
Wire Wire Line
	8350 5550 8500 5550
Wire Wire Line
	8500 5550 8500 5650
Connection ~ 8500 5650
Wire Wire Line
	7950 5850 7950 6150
$Comp
L power:+3V3 #PWR063
U 1 1 61525AC4
P 7950 4750
F 0 "#PWR063" H 7950 4600 50  0001 C CNN
F 1 "+3V3" H 7965 4923 50  0000 C CNN
F 2 "" H 7950 4750 50  0001 C CNN
F 3 "" H 7950 4750 50  0001 C CNN
	1    7950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 4750 7950 5050
Text Notes 9950 6150 0    50   ~ 0
I2C: 0x20
Text Notes 7950 6000 0    50   ~ 0
I2C: 0x40
$Comp
L Device:C C15
U 1 1 61544958
P 7250 5450
F 0 "C15" H 7300 5550 50  0000 L CNN
F 1 "1uF" H 7300 5300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7288 5300 50  0001 C CNN
F 3 "~" H 7250 5450 50  0001 C CNN
	1    7250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 5200 7250 5300
Wire Wire Line
	7250 5700 7250 5600
Wire Wire Line
	7250 5700 7500 5700
Wire Wire Line
	7500 5700 7500 5550
Wire Wire Line
	7500 5550 7550 5550
Wire Wire Line
	7550 5350 7500 5350
Wire Wire Line
	7500 5350 7500 5200
Wire Wire Line
	7500 5200 7250 5200
$Comp
L Device:R R38
U 1 1 615F7CB2
P 7250 5900
F 0 "R38" H 7180 5854 50  0000 R CNN
F 1 "10R" H 7180 5945 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7180 5900 50  0001 C CNN
F 3 "~" H 7250 5900 50  0001 C CNN
	1    7250 5900
	-1   0    0    1   
$EndComp
$Comp
L Device:R R37
U 1 1 615F8D99
P 7250 5000
F 0 "R37" H 7180 4954 50  0000 R CNN
F 1 "10R" H 7180 5045 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7180 5000 50  0001 C CNN
F 3 "~" H 7250 5000 50  0001 C CNN
	1    7250 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 6150 7250 6050
Wire Wire Line
	7250 5750 7250 5700
Connection ~ 7250 5700
Wire Wire Line
	7250 5200 7250 5150
Connection ~ 7250 5200
Wire Wire Line
	7250 4750 7250 4850
$Comp
L Device:C C14
U 1 1 6167334E
P 6850 5400
F 0 "C14" H 6900 5500 50  0000 L CNN
F 1 "10uF" H 6900 5250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6888 5250 50  0001 C CNN
F 3 "~" H 6850 5400 50  0001 C CNN
	1    6850 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4750 6850 5250
$Comp
L power:+3V3 #PWR062
U 1 1 61673EED
P 6850 4750
F 0 "#PWR062" H 6850 4600 50  0001 C CNN
F 1 "+3V3" H 6865 4923 50  0000 C CNN
F 2 "" H 6850 4750 50  0001 C CNN
F 3 "" H 6850 4750 50  0001 C CNN
	1    6850 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR064
U 1 1 61673EF7
P 6850 6150
F 0 "#PWR064" H 6850 5900 50  0001 C CNN
F 1 "GND" H 6855 5977 50  0000 C CNN
F 2 "" H 6850 6150 50  0001 C CNN
F 3 "" H 6850 6150 50  0001 C CNN
	1    6850 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 6150 6850 5550
Wire Wire Line
	8800 3500 9150 3500
Connection ~ 8800 3500
Wire Wire Line
	8800 3600 8800 3500
Wire Wire Line
	8800 4050 8800 3900
$Comp
L power:GND #PWR044
U 1 1 60F83765
P 8800 4050
F 0 "#PWR044" H 8800 3800 50  0001 C CNN
F 1 "GND" H 8805 3877 50  0000 C CNN
F 2 "" H 8800 4050 50  0001 C CNN
F 3 "" H 8800 4050 50  0001 C CNN
	1    8800 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C9
U 1 1 60F8375F
P 8800 3750
F 0 "C9" H 8850 3850 50  0000 L CNN
F 1 "2200uF/16v" H 8600 3500 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 8838 3600 50  0001 C CNN
F 3 "~" H 8800 3750 50  0001 C CNN
	1    8800 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 3500 8150 3150
Wire Wire Line
	8450 3500 8800 3500
Connection ~ 8450 3500
Wire Wire Line
	8450 3600 8450 3500
Wire Wire Line
	8450 4050 8450 3900
$Comp
L power:GND #PWR043
U 1 1 60C5A3C4
P 8450 4050
F 0 "#PWR043" H 8450 3800 50  0001 C CNN
F 1 "GND" H 8455 3877 50  0000 C CNN
F 2 "" H 8450 4050 50  0001 C CNN
F 3 "" H 8450 4050 50  0001 C CNN
	1    8450 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C8
U 1 1 60C50FD0
P 8450 3750
F 0 "C8" H 8500 3850 50  0000 L CNN
F 1 "2200uF/16v" H 8250 3600 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 8488 3600 50  0001 C CNN
F 3 "~" H 8450 3750 50  0001 C CNN
	1    8450 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR033
U 1 1 60B95E79
P 8150 3150
F 0 "#PWR033" H 8150 3000 50  0001 C CNN
F 1 "+12V" H 8165 3323 50  0000 C CNN
F 2 "" H 8150 3150 50  0001 C CNN
F 3 "" H 8150 3150 50  0001 C CNN
	1    8150 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4050 7000 3950
Wire Wire Line
	7000 3950 7400 3950
Connection ~ 7400 3950
Wire Wire Line
	7400 3950 7400 3700
Connection ~ 8150 3500
Wire Wire Line
	7750 3500 7800 3500
Connection ~ 7750 3500
Wire Wire Line
	7750 3800 7750 3500
Text GLabel 7750 3800 3    50   Output ~ 0
VIN+
Wire Wire Line
	8100 3500 8150 3500
$Comp
L Device:R R36
U 1 1 61785056
P 7950 3500
F 0 "R36" V 7743 3500 50  0000 C CNN
F 1 "0R1" V 7834 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.52x3.35mm_HandSolder" V 7880 3500 50  0001 C CNN
F 3 "~" H 7950 3500 50  0001 C CNN
	1    7950 3500
	0    1    1    0   
$EndComp
$Comp
L Device:Polyfuse F1
U 1 1 60D4A64F
P 7450 3500
F 0 "F1" V 7225 3500 50  0000 C CNN
F 1 "Polyfuse 1.5A/16v" V 7316 3500 50  0000 C CNN
F 2 "Fuse:Fuse_Bourns_MF-RG1000" H 7500 3300 50  0001 L CNN
F 3 "~" H 7450 3500 50  0001 C CNN
	1    7450 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 3500 8450 3500
Wire Wire Line
	7250 3500 7300 3500
Wire Wire Line
	7600 3500 7750 3500
Text GLabel 7250 4750 1    50   Input ~ 0
VIN+
$Comp
L power:+12V #PWR0101
U 1 1 619CB3C2
P 7250 6150
F 0 "#PWR0101" H 7250 6000 50  0001 C CNN
F 1 "+12V" H 7265 6323 50  0000 C CNN
F 2 "" H 7250 6150 50  0001 C CNN
F 3 "" H 7250 6150 50  0001 C CNN
	1    7250 6150
	-1   0    0    1   
$EndComp
$Comp
L Analog_ADC:INA219AxD U14
U 1 1 610F2B75
P 7950 5450
F 0 "U14" H 8200 5800 50  0000 C CNN
F 1 "INA219AxD" H 8150 5050 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 8750 5100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ina219.pdf" H 8300 5350 50  0001 C CNN
	1    7950 5450
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 611BBE01
P 10450 5300
F 0 "TP2" V 10450 5488 50  0000 L CNN
F 1 "TestPoint" V 10495 5488 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 10650 5300 50  0001 C CNN
F 3 "~" H 10650 5300 50  0001 C CNN
	1    10450 5300
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP3
U 1 1 611BCA6F
P 10450 5400
F 0 "TP3" V 10450 5588 50  0000 L CNN
F 1 "TestPoint" V 10495 5588 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 10650 5400 50  0001 C CNN
F 3 "~" H 10650 5400 50  0001 C CNN
	1    10450 5400
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP4
U 1 1 611BCC45
P 10450 5500
F 0 "TP4" V 10450 5688 50  0000 L CNN
F 1 "TestPoint" V 10495 5688 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 10650 5500 50  0001 C CNN
F 3 "~" H 10650 5500 50  0001 C CNN
	1    10450 5500
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP5
U 1 1 611BCDDE
P 10450 5600
F 0 "TP5" V 10450 5788 50  0000 L CNN
F 1 "TestPoint" V 10495 5788 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 10650 5600 50  0001 C CNN
F 3 "~" H 10650 5600 50  0001 C CNN
	1    10450 5600
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP6
U 1 1 611BCFF7
P 10450 5700
F 0 "TP6" V 10450 5888 50  0000 L CNN
F 1 "TestPoint" V 10495 5888 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 10650 5700 50  0001 C CNN
F 3 "~" H 10650 5700 50  0001 C CNN
	1    10450 5700
	0    1    1    0   
$EndComp
Wire Wire Line
	10400 5300 10450 5300
Wire Wire Line
	10450 5400 10400 5400
Wire Wire Line
	10400 5500 10450 5500
Wire Wire Line
	10450 5600 10400 5600
Wire Wire Line
	10400 5700 10450 5700
$EndSCHEMATC
