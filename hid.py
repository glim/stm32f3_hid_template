import usb.core,usb.util,struct
class PicStim(object):
    _packet_size = 64
    _in_endpoint = 0x01
    _out_endpoint = 0x81
    
    def __init__(self,idVendor=0x0483,idProduct=0x5710,packetSize=64):
        self._packet_size = packetSize
        try:
            self.dev = usb.core.find(idVendor=idVendor, idProduct=idProduct)
        except:
            self.dev = usb.core.find(idVendor=idVendor, idProduct=idProduct)                
        
        if (self.dev.is_kernel_driver_active(0)):
            self.dev.detach_kernel_driver(0)
        
        self.dev.set_configuration(1)
            
    def write(self,packet=None):
        if packet is not None:
            try:
                if len(packet) > 0 and len(packet) < self._packet_size:
                    return self.dev.write(self._in_endpoint,packet,timeout=100)
            except:
                p = [0 for i in range(self._packet_size)]
                p[0] = packet
                return self.dev.write(self._in_endpoint,p,timeout=100)
            
    def read(self,size=0,timeout=1000):
        if size == 0:
            size = self._packet_size
        return self.dev.read(self._out_endpoint,size,timeout=timeout)
    
    def toggle_led(self,led):
        p = [i for i in range(self._packet_size)]
        p[0] = led
        self.write(p)
        return self.read(self._packet_size)