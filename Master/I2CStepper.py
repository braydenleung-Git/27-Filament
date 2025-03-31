from smbus import SMBus
import struct
import time

addr = 0x08
bus = SMBus(1)

def send_stepper_state(state):
    # Always send [0x02, <state>]
    bus.write_i2c_block_data(addr, 0x02, [state])

def read_step_count():
    data = bus.read_i2c_block_data(addr, 0, 4)
    return struct.unpack('<L', bytes(data))[0]

# Start motor
send_stepper_state(0x01)
time.sleep(5)

# Stop motor
send_stepper_state(0x00)

# Read steps
steps = read_step_count()
print("Steps taken:", steps)
