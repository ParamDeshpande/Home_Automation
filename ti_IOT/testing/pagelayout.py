import kivy  
    
# base Class of your App inherits from the App class.    
# app:always refers to the instance of your application    
from kivy.app import App  
  
# The PageLayout class is used to create 
# a simple multi-page layout, 
# in a way that allows easy flipping from 
# one page to another using borders. 
from kivy.uix.pagelayout import PageLayout 
from kivy.uix.gridlayout import GridLayout

# creates the button in kivy   
# if not imported shows the error   
from kivy.uix.button import Button 
  
  
# The Utils module provides a selection of general utility 
# functions and classes that may be useful for various applications. 
# These include maths, color, algebraic and platform functions. 
# Here we are usinmg color from the module 
# By get_color_from_hex 
# Transform a hex string color to a kivy Color. 
from kivy.utils import get_color_from_hex 


red = [1,0,0,1]
green = [0,1,0,1]
blue =  [0,0,1,1]
purple = [1,0,1,1]



class PageLayout(PageLayout): 
    """ 
    Define class PageLayout here 
    """
   
    def __init__(self): 
          
        # The super function in Python can be 
        # used to gain access to inherited methods 
        # which is either from a parent or sibling class. 
        super(PageLayout, self).__init__() 
  
        # creating buttons on diffent pages 
  
        # Button 1 or Page 1 
        btn1 = Button(text ='Page 1') 
        # Adding Colour to page 
        # Here we are using colour from 
      
        #btn1.background_color = get_color_from_hex('# FF0000') 
   
        btn2 = Button(text ='Page 2') 
        #btn2.background_color = get_color_from_hex('# 00FF00') 
   
        #btn3 = Button(text ='Page 3') 
        #btn3.background_color = get_color_from_hex('# 0000FF') 
   
  
        # adding button on the screen 
        # by add widget method 
        self.add_widget(btn1) 
  
        self.add_widget(btn2) 
  
        #self.add_widget(btn3) 
   
  
# creating the App class 
class Page_LayoutApp(App): 
    """ 
    App class here 
    """
   
    def build(self): 
        """ 
        build function here 
        """
        layout = GridLayout(cols=2)
        button_lightON = Button(text="Light ON",background_color=red)
        button_lightOFF = Button(text="Light OFF",background_color=green)
        button_fanON =  Button(text="Fan ON",background_color=blue)
        button_fanOFF = Button(text="Fan OFF",background_color=purple)
        button_ledON =  Button(text="LED ON",background_color=red)
        button_ledOFF = Button(text="LED OFF",background_color=green)
        
        layout.add_widget(button_lightON)
        layout.add_widget(button_lightOFF)
        layout.add_widget(button_fanON)
        layout.add_widget(button_fanOFF)
        layout.add_widget(button_ledON)
        layout.add_widget(button_ledOFF)

        return PageLayout() 
   
  
# Run the App 
if __name__ == '__main__': 
    Page_LayoutApp().run() 
