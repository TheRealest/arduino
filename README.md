# Réal's Arduino Repo

This is a collection of code for my Arduino projects.

## `make` commands

The FQBN and port are harcoded in the Makefil to make for some easier syntax for common actions.

- `make compile <sketch_name>`: Compile a sketch
- `make upload <sketch_name>`: Upload a sketch
- `make monitor`: Open the serial monitor
- `make run <sketch_name>`: Do all three in order

## Using `arduino-cli` directly

Install it with `brew install arduino-cli`. Getting started info here: https://arduino.github.io/arduino-cli/1.0/getting-started/

Helpful usage:

- `arduino-cli sketch new <sketch_name>`: Create a new sketch
- `arduino-cli board list`: List all connected boards
- `arduino-cli compile --fqbn <fqbn> <sketch_dir>`: Compile a sketch
- `arduino-cli upload -p <port> --fqbn <fqbn> <sketch_dir>`: Upload a sketch

## Config file

Located at `~/Library/Arduino15/arduino-cli.yaml` (run `arduino-cli config init` to create). See [config docs](https://arduino.github.io/arduino-cli/1.0/configuration/) for more info. `arduino-cli config dump` will show the current config.
