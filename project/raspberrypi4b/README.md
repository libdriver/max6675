### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MISO/CS GPIO11/GPIO9/GPIO8.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(max6675 REQUIRED)
```


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
./max6675 -i

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
./max6675 -p

max6675: SCK connected to GPIO11(BCM).
max6675: MISO connected to GPIO9(BCM).
max6675: CS connected to GPIO8(BCM).
```

```shell
./max6675 -t read --times=3

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
max6675: temperature is 26.50C.
max6675: temperature is 26.25C.
max6675: finish read test.
```

```shell
./max6675 -e read --times=3

1/3 26.50C.
2/3 26.50C.
3/3 26.50C.
```

```shell
./max6675 -h

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

