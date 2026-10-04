# trigBoard V8 firmware. See README.md.
#
#   make install            install PlatformIO and the pinned toolchain/libraries
#   make build              compile the firmware
#   make deploy IP=x.x.x.x  upload over WiFi (start OTA in the configurator first)

.PHONY: install build deploy clean

build:
	pio run

install:
	brew list platformio >/dev/null 2>&1 || brew install platformio
	pio pkg install

deploy:
	@if [ -z "$(IP)" ]; then \
		echo "Usage: make deploy IP=<board-ip>"; \
		echo "Get the IP from the configurator status, then press OTA start before deploying."; \
		exit 1; \
	fi
	pio run -t upload --upload-port $(IP)

clean:
	pio run -t clean
