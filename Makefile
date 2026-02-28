CLI  = arduino-cli
FQBN = arduino:avr:uno
PORT = /dev/ttyACM0

list:
	$(CLI) board list

compile:
	$(CLI) compile --fqbn $(FQBN) . -v

upload:
	$(CLI) upload --fqbn $(FQBN) --port $(PORT) . -v

monitor:
	$(CLI) monitor --fqbn $(FQBN) --port $(PORT) --config baudrate=115200
