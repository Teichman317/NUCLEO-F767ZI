import socket
import time

# --- Settings ---
UDP_IP = "192.168.1.123"   # Replace with the STM32's IP
UDP_PORT = 12345           # Match this in your STM32 setup
INTERVAL = 0.05            # Seconds between sends

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
count = 0
direction = 1

while True:
    data = count.to_bytes(1, byteorder='big')  # 8-bit unsigned
    sock.sendto(data, (UDP_IP, UDP_PORT))
    print(f"Sent: {count}")
    
    count += direction
    if count == 255 or count == 0:
        direction *= -1
    
    time.sleep(INTERVAL)
