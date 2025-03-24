import serial
import struct

if __name__ == "__main__":
    ser = serial.Serial(port = "COM7", baudrate=115200)
    theta = 360  & 0xFF
    R = int(0 / 35 * 127) & 0xFF
    command = 0x00
    check_sum = (theta + R + command + 1) & 0xFF
    data = struct.pack("8B", *[0x53, 0x5A, 0x48, 0x59, command, theta, R, check_sum])
    ser.write(data)


