VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cls6567"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
' The following comments were taken from Christian Bauer's document:
'
' The MOS 6567/6569 video controller (VIC-II)
' and its application in the Commodore 64
'
' by Christian Bauer
' <bauec002@goofy.zdv.uni-mainz.de>
'
' 28.Aug.1996
'

' Important Signals:
'----------------------------------------------------------------------------

' The 14 bit video address bus used by the VIC to address 16KB of
' memory. The address bits A0-A5 and A8-A13 are multiplexed in pairs
' (i.e. A0/A8, A1/A9 etc.) on one pin each. The bits A6-A11 are
' (additionally) available on separate lines.
Private Address_Bus As Integer

' A 12 bit wide data bus over which the VIC accesses the memory. The
' lower 8 bits are connected to the main memory and the processor
' data bus, the upper 4 bits are connected to a special 4 bit wide
' static memory (1024 addresses, A0-A9) used for storing color
' information, the Color RAM.
Private Data_Bus As Integer

' This output is wired to the IRQ input on the processor and makes it
' possible for the VIC to trigger interrupts. The VIC has four
' interrupt sources: On reaching a certain raster line (raster
' interrupt), on the collision of two or more sprites, on the
' collision of sprites with graphics data and on a negative edge on
' the light pen input
Private IRQ As Byte

' With this signal, the VIC indicated that the bus is available to
' the processor during the second clock phase (ø2 high). BA is
' normally high as the VIC accesses the bus mostly during the first
' phase. But for the character pointer and sprite data accesses, the
' VIC also needs the bus sometimes during the second phase. In this
' case, BA goes low three cycles before the VIC access. After that,
' AEC remains low during the second phase and the VIC performs the
' accesses. Why three cycles? BA is connected to the RDY line of the
' processor as mentioned, but this line is ignored on write accesses
' (the CPU can only be interrupted on reads), and the 6510 never does
Private BA As Byte

' This pin is wired to the processor signal with the same name (see
' there). It reflects the state of the data and address line drivers
' of the VIC. If AEC is high, they are in tri-state. AEC is normally
' low during the first clock phase (ø2 low) and high during the
' second phase so that the VIC can access the bus during the first
' phase and the 6510 during the second phase. If the VIC also needs
' the bus in the second phase, AEC remains low.
Private AEC As Byte

' This input is intended for connecting a light pen. On a negative
' edge, the current position of the raster beam is latched to the
' registers LPX and LPY. As this pin shares a line with the keyboard
' matrix, it can also be accessed by software.
Private LP As Byte

' This is the feed for the pixel clock of 8.18 MHz (NTSC) or 7.88 MHz
' (PAL) that is generated from the crystal frequency. Eight pixels
' are displayed per bus clock cycle (ø2).
Private PhaseIN As Byte

' From the pixel clock on øIN, the VIC generates the system clock of
' 1.023 MHz (NTSC) or 0.985 MHz (PAL) by dividing øIN by eight. It is
' available on this pin and fed into the processor which in turn
' generated the signal ø2 from it.
Private Phase0 As Byte


' The VIC has 47 read/write registers for the processor to control its
' functions:

' #| Adr.  |Bit7|Bit6|Bit5|Bit4|Bit3|Bit2|Bit1|Bit0| Function
'--+-------+----+----+----+----+----+----+----+----+------------------------
' 0| $d000 |                  M0X                  | X coordinate sprite 0
'--+-------+---------------------------------------+------------------------
' 1| $d001 |                  M0Y                  | Y coordinate sprite 0
'--+-------+---------------------------------------+------------------------
' 2| $d002 |                  M1X                  | X coordinate sprite 1
'--+-------+---------------------------------------+------------------------
' 3| $d003 |                  M1Y                  | Y coordinate sprite 1
'--+-------+---------------------------------------+------------------------
' 4| $d004 |                  M2X                  | X coordinate sprite 2
'--+-------+---------------------------------------+------------------------
' 5| $d005 |                  M2Y                  | Y coordinate sprite 2
'--+-------+---------------------------------------+------------------------
' 6| $d006 |                  M3X                  | X coordinate sprite 3
'--+-------+---------------------------------------+------------------------
' 7| $d007 |                  M3Y                  | Y coordinate sprite 3
'--+-------+---------------------------------------+------------------------
' 8| $d008 |                  M4X                  | X coordinate sprite 4
'--+-------+---------------------------------------+------------------------
' 9| $d009 |                  M4Y                  | Y coordinate sprite 4
'--+-------+---------------------------------------+------------------------
'10| $d00a |                  M5X                  | X coordinate sprite 5
'--+-------+---------------------------------------+------------------------
'11| $d00b |                  M5Y                  | Y coordinate sprite 5
'--+-------+---------------------------------------+------------------------
'12| $d00c |                  M6X                  | X coordinate sprite 6
'--+-------+---------------------------------------+------------------------
'13| $d00d |                  M6Y                  | Y coordinate sprite 6
'--+-------+---------------------------------------+------------------------
'14| $d00e |                  M7X                  | X coordinate sprite 7
'--+-------+---------------------------------------+------------------------
'15| $d00f |                  M7Y                  | Y coordinate sprite 7
'--+-------+----+----+----+----+----+----+----+----+------------------------
'16| $d010 |M7X8|M6X8|M5X8|M4X8|M3X8|M2X8|M1X8|M0X8| MSBs of X coordinates
'--+-------+----+----+----+----+----+----+----+----+------------------------
'17| $d011 |RST8| ECM| BMM| DEN|RSEL|    YSCROLL   | Control register 1
'--+-------+----+----+----+----+----+--------------+------------------------
'18| $d012 |                 RASTER                | Raster counter
'--+-------+---------------------------------------+------------------------
'19| $d013 |                  LPX                  | Light pen X
'--+-------+---------------------------------------+------------------------
'20| $d014 |                  LPY                  | Light pen Y
'--+-------+----+----+----+----+----+----+----+----+------------------------
'21| $d015 | M7E| M6E| M5E| M4E| M3E| M2E| M1E| M0E| Sprite enabled
'--+-------+----+----+----+----+----+----+----+----+------------------------
'22| $d016 |  - |  - | RES| MCM|CSEL|    XSCROLL   | Control register 2
'--+-------+----+----+----+----+----+----+----+----+------------------------
'23| $d017 |M7YE|M6YE|M5YE|M4YE|M3YE|M2YE|M1YE|M0YE| Sprite Y expansion
'--+-------+----+----+----+----+----+----+----+----+------------------------
'24| $d018 |VM13|VM12|VM11|VM10|CB13|CB12|CB11|  - | Memory pointers
'--+-------+----+----+----+----+----+----+----+----+------------------------
'25| $d019 | IRQ|  - |  - |  - | ILP|IMMC|IMBC|IRST| Interrupt register
'--+-------+----+----+----+----+----+----+----+----+------------------------
'26| $d01a |  - |  - |  - |  - | ELP|EMMC|EMBC|ERST| Interrupt enabled
'--+-------+----+----+----+----+----+----+----+----+------------------------
'27| $d01b |M7DP|M6DP|M5DP|M4DP|M3DP|M2DP|M1DP|M0DP| Sprite data priority
'--+-------+----+----+----+----+----+----+----+----+------------------------
'28| $d01c |M7MC|M6MC|M5MC|M4MC|M3MC|M2MC|M1MC|M0MC| Sprite multicolor
'--+-------+----+----+----+----+----+----+----+----+------------------------
'29| $d01d |M7XE|M6XE|M5XE|M4XE|M3XE|M2XE|M1XE|M0XE| Sprite X expansion
'--+-------+----+----+----+----+----+----+----+----+------------------------
'30| $d01e | M7M| M6M| M5M| M4M| M3M| M2M| M1M| M0M| Sprite-sprite collision
'--+-------+----+----+----+----+----+----+----+----+------------------------
'31| $d01f | M7D| M6D| M5D| M4D| M3D| M2D| M1D| M0D| Sprite-data collision
'--+-------+----+----+----+----+----+----+----+----+------------------------
'32| $d020 |  - |  - |  - |  - |         EC        | Border color
'--+-------+----+----+----+----+-------------------+------------------------
'33| $d021 |  - |  - |  - |  - |        B0C        | Background color 0
'--+-------+----+----+----+----+-------------------+------------------------
'34| $d022 |  - |  - |  - |  - |        B1C        | Background color 1
'--+-------+----+----+----+----+-------------------+------------------------
'35| $d023 |  - |  - |  - |  - |        B2C        | Background color 2
'--+-------+----+----+----+----+-------------------+------------------------
'36| $d024 |  - |  - |  - |  - |        B3C        | Background color 3
'--+-------+----+----+----+----+-------------------+------------------------
'37| $d025 |  - |  - |  - |  - |        MM0        | Sprite multicolor 0
'--+-------+----+----+----+----+-------------------+------------------------
'38| $d026 |  - |  - |  - |  - |        MM1        | Sprite multicolor 1
'--+-------+----+----+----+----+-------------------+------------------------
'39| $d027 |  - |  - |  - |  - |        M0C        | Color sprite 0
'--+-------+----+----+----+----+-------------------+------------------------
'40| $d028 |  - |  - |  - |  - |        M1C        | Color sprite 1
'--+-------+----+----+----+----+-------------------+------------------------
'41| $d029 |  - |  - |  - |  - |        M2C        | Color sprite 2
'--+-------+----+----+----+----+-------------------+------------------------
'42| $d02a |  - |  - |  - |  - |        M3C        | Color sprite 3
'--+-------+----+----+----+----+-------------------+------------------------
'43| $d02b |  - |  - |  - |  - |        M4C        | Color sprite 4
'--+-------+----+----+----+----+-------------------+------------------------
'44| $d02c |  - |  - |  - |  - |        M5C        | Color sprite 5
'--+-------+----+----+----+----+-------------------+------------------------
'45| $d02d |  - |  - |  - |  - |        M6C        | Color sprite 6
'--+-------+----+----+----+----+-------------------+------------------------
'46| $d02e |  - |  - |  - |  - |        M7C        | Color sprite 7
'--+-------+----+----+----+----+-------------------+------------------------

