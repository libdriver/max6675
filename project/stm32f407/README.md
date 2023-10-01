### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MISO/CS  PA5/PA6/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MAX6675

#### 3.1 Command Instruction

1. Show max6675 chip and driver information.

   ```shell
   max6675 (-i | --information)
   ```

2. Show max6675 help.

   ```shell
   max6675 (-h | --help)
   ```

3. Show max6675 pin connections of the current board.

   ```shell
   max6675 (-p | --port)
   ```

4. Run max6675 read test, num is the test times. 

   ```shell
   max6675 (-t read | --test=read) [--times=<num>]
   ```

5. Run max6675 read function, num is the read times. 

   ```shell
   max6675 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
max6675 -i

max6675: chip is Maxim Integrated MAX6675.
max6675: manufacturer is Maxim Integrated.
max6675: interface is SPI.
max6675: driver version is 1.0.
max6675: min supply voltage is 3.0V.
max6675: max supply voltage is 5.5V.
max6675: max current is 1.50mA.
max6675: max temperature is 85.0C.
max6675: min temperature is -20.0C.
```

```shell
max6675 -p

max6675: SCK connected to GPIOA PIN5.
max6675: MISO connected to GPIOA PIN6.
max6675: CS connected to GPIOA PIN4.
```

```shell
max6675 -t read --times=3

max6675: chip is Maxim Integrated MAX6675.
max6675: manufacturer is Maxim Integrated.
max6675: interface is SPI.
max6675: driver version is 1.0.
max6675: min supply voltage is 3.0V.
max6675: max supply voltage is 5.5V.
max6675: max current is 1.50mA.
max6675: max temperature is 85.0C.
max6675: min temperature is -20.0C.
max6675: start read test.
max6675: temperature is 26.50C.
max6675: temperature is 27.00C.
max6675: temperature is 27.00C.
max6675: finish read test.
```

```shell
max6675 -e read --times=3

1/3 27.00C.
2/3 26.75C.
3/3 27.25C.
```

```shell
max6675 -h

Usage:
  max6675 (-i | --information)
  max6675 (-h | --help)
  max6675 (-p | --port)
  max6675 (-t read | --test=read) [--times=<num>]
  max6675 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>        Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
  -p, --port                         Display the pin connections of the current board.
  -t <read>, --test=<read>           Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

