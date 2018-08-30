class network:
        def cable(self): print('I am the cable')
        def router(self): print('I am the router')
        def switch(self): print('I am the switch')
        def wifi(self): print('I am wireless router cable does not matter')
class tokenRing(network):
        def cable(self): print('I am a token ring cable');
        def router(self): print('I am a token ring router')
class ethernet(network):
        def cable(self): print('I am an ethernet cable')
        def router(self): print('I am an ethernet router')
        def wifi(self): print('I am the wifi for ethernet')

def main():
        windows = tokenRing()
        mac = ethernet()

        for obj in (windows,mac):
           obj.cable()
           obj.router()
           obj.wifi()

main()
