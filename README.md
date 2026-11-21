# Description

This repository contains the **LPS2xHH** pressure and temperature sensor driver.

# Dependencies

The driver relies on:

* An external `types.h` header file defining the **standard C types** of the targeted MCU.
* The **embedded utility functions** defined in the [embedded-utils](https://github.com/Ludovic-Lesur/embedded-utils) repository.

Here is the versions compatibility table:

| **lps2xhh-driver** | **embedded-utils** |
|:---:|:---:|
| [sw1.0](https://github.com/Ludovic-Lesur/lps2xhh-driver/releases/tag/sw1.0) | >= [sw7.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw7.0) |

# Compilation flags

| **Flag name** | **Value** | **Description** |
|:---:|:---:|:---:|
| `LPS2XHH_DRIVER_DISABLE_FLAGS_FILE` | `defined` / `undefined` | Disable the `lps2xhh_driver_flags.h` header file inclusion when compilation flags are given in the project settings or by command line. |
| `LPS2XHH_DRIVER_DISABLE` | `defined` / `undefined` | Disable the LPS2xHH driver. |
| `LPS2XHH_DRIVER_I2C_ERROR_BASE_LAST` | `<value>` | Last error base of the low level I2C driver. |
| `LPS2XHH_DRIVER_DELAY_ERROR_BASE_LAST` | `<value>` | Last error base of the low level delay driver. |

# Build

A static library can be compiled by command line with `cmake`.

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="<toolchain_file_path>" \
      -DTOOLCHAIN_PATH="<arm-none-eabi-gcc_path>" \
      -DTYPES_PATH="<types_file_path>" \
      -DEMBEDDED_UTILS_PATH="<embedded-utils_path>" \
      -DLPS2XHH_DRIVER_I2C_ERROR_BASE_LAST=0 \
      -DLPS2XHH_DRIVER_DELAY_ERROR_BASE_LAST=0 \
      -G "Unix Makefiles" ..
make all
```
