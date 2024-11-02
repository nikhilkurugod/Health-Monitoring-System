# Health Monitoring System

# Circuit Diagram

![image](https://github.com/user-attachments/assets/338e380f-c780-4ea2-bf4d-f52aba1703ce)

Circuit Diagram with Pulse sensor connection

![image](https://github.com/user-attachments/assets/b8950926-17b6-4e3a-a762-060c5e9d5d41)

Circuit Diagram with Temperature sensor connection

# Working

• Raspberry pi3 is used as medium that interacts with both sensors and output         
device (App). 

• The temperature sensor does not require ADC, however it requires resistor connected 
across Vcc and sensor output.

• The temperature sensor output is connected to one of the GPIO pins of Raspberry pi, 
for communication it uses only one wired interface. 

• Pulse sensor communicates through ADC(MCP3008), the data pin is connected to 
channel 0 of MCP3008. 

• The analog output from Pulse sensor is converted into digital through ADC and 
interfaced with Raspberry pi.  

• ADC(MCP3008) uses SAR(Successive approximation) technique to get accurate 
pulse readings. 

• Raspberry pi communicates with mobile application by using MQTT client. 

• A MQTT broker connects Raspberry pi to the cloud and cloud to mobile. 

• The sensor output is sent to cloud through a channel and the mobile app receives the 
data from subscribing the channel that contains the sensor output. 

• To collect the data for ML code is written to include the data into a csv file created 
locally. 

• The csv file is used for various applications of ML.


