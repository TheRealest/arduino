.PHONY: run
run:
	make compile $(filter-out $@,$(MAKECMDGOALS)) && make upload $(filter-out $@,$(MAKECMDGOALS)) && make monitor

.PHONY: compile
compile:
	arduino-cli compile --fqbn arduino:avr:uno $(filter-out $@,$(MAKECMDGOALS))

.PHONY: upload
upload:
	arduino-cli upload -p /dev/cu.usbserial-110 --fqbn arduino:avr:uno $(filter-out $@,$(MAKECMDGOALS))

.PHONY: monitor
monitor:
	arduino-cli monitor -p /dev/cu.usbserial-110 --fqbn arduino:avr:uno

# This empty rule is necessary to handle arguments passed to make
%:
  @:
