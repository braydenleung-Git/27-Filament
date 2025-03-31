#  Raspberry Pi Master for Arduino Slave
#  i2c_master_pi.py
#  Connects to Arduino via I2C

#  DroneBot Workshop 2019
#  https://dronebotworkshop.com

from smbus import SMBus
import time

addr = 0x8
bus = SMBus(1)

def send_command(cmd_id, value):
    bus.write_i2c_block_data(addr, cmd_id, [value])
    print(f"Sent command {cmd_id:#04x} with value {value}")

    # Wait for Arduino to report status = 1
    while True:
        time.sleep(0.1)
        response = bus.read_i2c_block_data(addr, 0, 2)
        status, result = response
        if status == 1:
            print(f"Arduino done. Result: {result}")
            break

# Example usage
send_command(0x01, 1)  # Turn LED ON
send_command(0x02, 5)  # Blink LED 5 times
send_command(0x01, 0)  # Turn LED OFF



