# This is to demonstration of how you can use the dsahboard.py as a stand-alone 
# application and how to connect the vehical state to the dashboard.

import dashboard 
import threading
import time ,sys
from PyQt5.QtWidgets import QApplication, QWidget,QVBoxLayout
import sys
import os
import playsound
from gtts import gTTS

audios="warnning you exceed lane"
enable_ACC          ="10001010"
disable_ACC         ="10000101"
#  * ----------------------------
enable_lane_keeping ="10001100"
diable_lane_keeping ="10000011"
#  *-----------------------------
enable_lane_warning ="10001000"
diable_lane_warning ="10001001"
#  *-----------------------------
enable_AEB          ="10000001"
diable_AEB          ="10000000"
#  *-----------------------------
turn_on_buzzer      ="10111111"
turn_off_buzzer     ="10110000"
#-------------------------------
driving_en          ="10111011"  
driving_dis         ="10110111" 
#---------------------------------
turn_right          ="10101010"  
turn_left           ="10110011"         
trigger_action = dashboard.TriggerAction()  # creating dashboard trigger

# the below five method should be called before calling launch_dashboard() method to take effect
# note: this below five are optional
trigger_action.set_dashboard_size(1000,650)#(980, 600)  # aspect ratio 16:9
trigger_action.hide_creator_button(True)
trigger_action.skip_start_screen(False)
trigger_action.skip_loading_screen(True)
trigger_action.set_speedometer_range(180)

def handle_data(data):
    x=data
   #  x=data.decode('utf-8')
    if x== driving_en:
     trigger_action.apply_accelerator()
     
    if x== driving_dis:
        trigger_action.release_accelerator()
        trigger_action.set_speed(0)

    if x == enable_ACC:  # press accelerator
        trigger_action.ACC_on()
    if x ==disable_ACC:  # press break
        trigger_action.ACC_off()
    if x == enable_lane_keeping:  # press horn
        trigger_action.LKA_on()
    if x ==diable_lane_keeping:  # triger left indicator stateQWASEFVPUIH
        trigger_action.LKA_off()
    if x == enable_lane_warning:  # triger right indicator state
        trigger_action.LKW_on()
    if x == diable_lane_warning:
        trigger_action.LKW_off()
    if x ==enable_AEB:
         trigger_action.apply_break()
         trigger_action. release_accelerator()
         trigger_action.set_speedometer_resetter_state(state=True)  

        
    if x == diable_AEB:
         trigger_action.release_break() 
         trigger_action.set_speedometer_resetter_state(state=False)  
 
    if x == turn_right:  # 
        # trigger_action.left_indicator_on_or_off()
        trigger_action.sound_horn()  
        tts=gTTS(text=audios,lang='en',slow=False)
        audioF='audio.mp3'
        tts.save(audioF)
        playsound.playsound(audioF)
        os.remove(audioF)    
    
    if x == turn_left:  # 
        trigger_action.left_indicator_on_or_off()

            
    if x == turn_on_buzzer:
        trigger_action.sound_horn()  
        tts=gTTS(text=audios,lang='en',slow=False)
        audioF='audio.mp3'
        tts.save(audioF)
        playsound.playsound(audioF)
        os.remove(audioF)
    if x == turn_off_buzzer:
        trigger_action.off_horn()                     
    if (x[0]=='1')and (x[1]=='1') :#battery voltage 
        # trigger_action.set_speed(int(x))
        print("battery")
    if x[0]=='0':#set speed
        print(x)
        decimal_value = int(x, 2)
        print("speed equal =",decimal_value)

        trigger_action.set_speed(decimal_value)          
        trigger_action.set_speedometer_resetter_state(state=False)  
  
def read_and_delete_first_line(file_path):
    while True:

        try:
            # Read the first line from the file
            with open(file_path, 'r') as file:
                first_line = file.readline().strip()
            
            # Print the first line
            # print("First Line:", first_line)
            
            # Open the file in write mode to delete the first line
            with open(file_path, 'r') as file:
                lines = file.readlines()

            # Open the file again in write mode to overwrite it without the first line
            with open(file_path, 'w') as file:
                file.writelines(lines[1:])
            handle_data(first_line)    
            time.sleep(1);    

            
        except Exception as e:
            continue
            # print("An error occurred:", str(e))

    # Provide the path to your text file


    
file_path = r"C:\Users\mohamed\Desktop\adas&fota_graduation_project\server_django\myproject\data.txt"

thread=threading.Thread(target=read_and_delete_first_line,args=(file_path,))
thread.start()

# to show dashboard note: this should be called at end of our code
trigger_action.set_speedometer_range(100)
trigger_action.launch_dashboard()  
print("finished")

        


# /* enable  ACC B1000 1010
#  * disable ACC B1000 0101
#  * ----------------------------
#  * enable lane keeping B1000 1100
#  * diable lane keeping B1000 0011
#  *-----------------------------
#  *enable lane warinig  B1000 1000
#  *diable lane waringi  B1000 1001
#  *-----------------------------
#  *enable AEB B1000 0001
#  *diable AEB B1000 0000
#  *-----------------------------
#  *turn on buzzer B1011 1111
#  *turn off buzzerB1011 0000 
#  *----------------------------
#  *batteryvoltage B11XX XXXX
#  *speed          B0XXX XXXX
#  *
#  *
# # #  */
# 10001010
# 10001100
# 10001010
# 10000011
# 10001010
# 10000101
# 10001010
# 10001100
# 10001010
# 10000011
# 10001000
# 10001001
# 10000001
# 10000000
# 10111111
# 10110000