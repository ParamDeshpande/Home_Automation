import kivy
import socket
import sys
from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout
from kivy.clock import Clock
import socket_client

red = [1,0,0,1]
green = [0,1,0,1]
blue =  [0,0,1,1]
purple = [0,0.5,1,1]
yellow = [1,1,0,1]
orange = [1,0.5,0,1]

HOST = '192.168.1.150'  # The server's hostname or IP address
PORT = 23        # The port used by the server




class MainApp(App):

    def build(self):
        layout = layout = GridLayout(cols=2)

        # this code writing sucks but as mentioned i am way too lazy to write clean code.

        button_lightON = Button(text="Light ON",background_color=red)
        button_lightOFF = Button(text="Light OFF",background_color=green)
        button_fanON =  Button(text="Fan ON",background_color=yellow)
        button_fanOFF = Button(text="Fan OFF",background_color=blue)
        button_ledON =  Button(text="LED ON",background_color=purple)
        button_ledOFF = Button(text="LED OFF",background_color=orange)
        
        button_lightON.bind(on_press=self.sendLightON)
        button_lightOFF.bind(on_press=self.sendLightOFF)
        button_fanON.bind(on_press=self.sendFanON)
        button_fanOFF.bind(on_press=self.sendFanOFF)
        button_ledON.bind(on_press=self.sendLedON)
        button_ledOFF.bind(on_press=self.sendLedOFF)

        layout.add_widget(button_lightON)
        layout.add_widget(button_lightOFF)
        layout.add_widget(button_fanON)
        layout.add_widget(button_fanOFF)
        layout.add_widget(button_ledON)
        layout.add_widget(button_ledOFF)


        return layout
    
    def __init__(self):
        super().__init__()
        Clock.schedule_once(self.connect, 0)


    def connect(self, _ ):
        port = PORT
        ip = HOST
        username = 'device_x'
        #print("trying to connect")
        if not socket_client.connect(ip, port, username, show_error):
            #print("connection failed")
            return

    def sendLightON(self,instance):
        socket_client.send('lightONq')
    
    def sendLightOFF(self,instance):
        socket_client.send('lightOFFq')
        
    def sendFanON(self,instance):
        socket_client.send('fanONq')
        
    def sendFanOFF(self,instance):
        socket_client.send('fanOFFq')
    
    def sendLedON(self,instance):
        socket_client.send('ledONq')
    
    def sendLedOFF(self,instance):
        socket_client.send('ledOFFq')

def show_error(message):
    Clock.schedule_once(sys.exit, 10)


if __name__ == '__main__':
    app = MainApp()
    app.run()