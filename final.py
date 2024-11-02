#this is the end code for the data collection and output of the sensors
# import pulse
import temp


tempread=temp.read_temp_c
# pulseread=pulse.bpm

# #for bpm
# if pulseread==0:
#     readp="No heartbeat found"


# #for temp
# if tempread==0:
#     readt="No temperature detected"

print("temperature in celcius"+ tempread)



