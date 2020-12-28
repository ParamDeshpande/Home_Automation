import kivy
import socket

from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout

red = [1,0,0,1]
green = [0,1,0,1]
blue =  [0,0,1,1]
purple = [1,0,1,1]


HOST = '192.168.0.109'  # The server's hostname or IP address
PORT = 23        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'Hello, world')
    data = s.recv(1024)

print('Received', repr(data))


class MainApp(App):

    def build(self):

        # this code writing sucks but as mentioned i am way too lazy to write clean code.

        button_lightON = Button(text="Light ON",background_color=red)
       
        button_lightON.bind(on_press=self.sendLightON)
        

        layout.add_widget(button_lightON)
        

        return layout

    def sendLightON(self,instance):
        print("light on")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            s.sendall(b'lightON')

   
    class Devices(App):
        def __init__(self, name ):
            self.name = name

        def build(self):
            layout = GridLayout(cols=1)




if __name__ == '__main__':
    app = MainApp()
    app.run()