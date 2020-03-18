# Description

Simple GTK UI application that generates diceware based passwords based on a few options.

# Installation

Download the code and run the following commands from the `diceware_generator` folder:

    mkdir build
    cd build
    cmake ..
    sudo make install

You can then run the generator using `DicewareGenerator`.

# Uninstallation

The following steps will uninstall the application:

    cd build
    cmake ..
    sudo make uninstall

Note that uninstall requires you to have run install since it uses the files generated during the install process.
