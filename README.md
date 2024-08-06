# Réal's Arduino Repo

This is a collection of code for my Arduino projects.

## Using `arduino-cli`

Install it with `brew install arduino-cli`. Getting started info here: https://arduino.github.io/arduino-cli/1.0/getting-started/

Helpful usage:

- `arduino-cli sketch new <sketch_name>`: Create a new sketch
- `arduino-cli board list`: List all connected boards
- `arduino-cli compile --fqbn <fqbn> <sketch_dir>`: Compile a sketch
- `arduino-cli upload -p <port> --fqbn <fqbn> <sketch_dir>`: Upload a sketch

## Config file

Located at `~/Library/Arduino15/arduino-cli.yaml` (run `arduino-cli config init` to create). See [config docs](https://arduino.github.io/arduino-cli/1.0/configuration/) for more info. `arduino-cli config dump` will show the current config.
