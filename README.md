# pico_pio_touch_c

This repository serves as an migration of the jtouch library into a C codebase, as opposed to the original uMicropython codebase found in the [AncientJames/jtouch](https://github.com/AncientJames/jtouch) repository. It provides the necessary modifications and adaptations to make the library compatible with C programming language.

How it works:
We will use the PIO interface of the PICO. To get to know more about PIO, visit [documentation](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf). This code employs a PIO program to ascertain the capacitance of a finger. Initially, the pin is configured as an output and pulled to a low state. Subsequently, it transitions to an input state with the internal pull-up enabled, allowing the PIO to measure the duration until it transitions to a high state. Minute discrepancies in this timing occur depending on the proximity of a finger. By iterating this test thousands of times within a loop, these subtle variations are magnified.


## Build

1. **Clone the Repository**: 
   - Check out the repository to your local machine.

2. **Install Docker**: 
   - Refer to the [Docker Installation Guide](https://docs.docker.com/desktop/install/mac-install/) for instructions.
   - Note: it is not enough to copy the docker image to the application folder, you have to run it and follow the installation instructions!

3. **Open Terminal at the firmware codebase directory**: 
   - Launch a terminal window if you have not done yet, and change directory to the root of the codebase on your computer.

4. **Build Docker Image**: 
   - Execute `docker build -t pico .`.

5. **Run the container**: 
   - Execute `docker run --rm --privileged -it -v /dev:/dev -v $PWD:/project -w /project/ pico sh -c "bash"`.

6. **Run the building script from the container**: 
   - Run the build script for building the FW `./build.sh`.


## Upload program 
To transfer your compiled program, utilize the UF2 bootloader included with the Pico.

Ensure that the USB cable is disconnected from your Pico. Press and hold the BOOTSEL button while connecting the USB cable to your Pico. Release the BOOTSEL button after the USB cable is connected.

Your computer should recognize the Pico as a storage device labeled RPI-RP2.

Navigate to your build directory and locate the file main.uf2. Unfortunately, copying files directly from VS Code is not supported; you'll need to use a file explorer window. Copy the main.uf2 file and paste it into the root directory of the RPI-RP2 drive.

