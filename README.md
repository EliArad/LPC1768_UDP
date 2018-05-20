# LPC1768_UDP
Example for udp in LPC1768

Please note that LPC1768 uses lwip version 1.41

This version have a bug in long time running, it has a memory leak when 
we try to send async message from controller to host using sendto.

The echo uses the same UDP_PCB in the recv to  send to host back.
if we create a new pcb with addr and port and try to sendto host 
it will crash after several hours.

So only echo back is working , and not async push with a different PCB.
dont know why.
