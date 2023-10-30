# RP2040 Console Mode PoC

This implements [Elecia Whites console mode](https://github.com/eleciawhite/reusable/tree/master/source) on the RPi Pico.

All in the `./src/lib/console` is ~~totally stolen~~heavily influenced from the implementation [here](https://wokwi.com/projects/324879108372693587).

## Configuring the environment

This was built and depends on the [RPi Pico SDK V1.5.1](https://github.com/raspberrypi/pico-sdk)

Its location must be set as an environment, e.g.:

```shell
export PICO_SDK_PATH="your_local_path"
```

The project is configured for the Adafruit Feather RP2040.
To change this, please change the follwing line `./CMakeLists.txt` in the projects root directory.

```cmake
set(PICO_BOARD "adafruit_feather_rp2040")
```
And `PICO_BOARD=adafruit_feather_rp2040` in `./build.sh`

Add a `./build` folder and run `cmake ..` from inside it.

## Building and flashing

Run `./build.sh`

If you are using [picotool](https://github.com/raspberrypi/picotool) you can simmple flash in two steps:

1. Bring the board into BOOTSEL mode by holding the similar called button while resetting
2. Write the built `.uf2` onto the board with the following command:
    ```shell
    "PATH_TO_PICOTOOL/picotool load .build/debug/src/console_poc.uf2
    ```

