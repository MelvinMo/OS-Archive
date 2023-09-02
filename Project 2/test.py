import os
import random
path = "/dev/iutnode"
fd = os.open(path, os.O_RDWR)

k=os.fork()
	
for i in range(10**6):
 rand = random.randint(1,99)
 msg = f"e,{rand},0,1"
 os.write(fd, msg.encode())
if k==0:
 os._exit(0)
if k!=0:
 os.wait()
data = os.read(fd,1000)
print(data.decode())
os.close(fd)

