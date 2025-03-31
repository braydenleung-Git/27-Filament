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

print("Stepper motor control (I2C)")
print("Press Enter to toggle ON/OFF. Type 'q' to quit.")

motor_on = False

while True:
    user_input = input(">>> ")

    if user_input.lower() == 'q':
        if motor_on:
            send_stepper_state(0x00)
        print("Exiting.")
        break

    motor_on = not motor_on

    if motor_on:
        print("Stepper motor: ON")
        send_stepper_state(0x01)
    else:
        print("Stepper motor: OFF")
        send_stepper_state(0x00)
        time.sleep(0.1)  # Ensure motor has stopped
        steps = read_step_count()
        print(f"Total steps: {steps}")
