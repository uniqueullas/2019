The code is written for AIT college project, called HEALTH MONITORING SYSTEM
   ECE dept Final year project
   board used is NODE MCU version 2.3
   micro contoller NodeMCU 1.0(ESP-12E MOdule)
   Upload speed 115200
   80 Mhz CPU frequency
   auto bootloader 
   code uploaded to https://github.com/uniqueullas/Node-MCU-2019/blob/master/health_monitoring.ino
   
   *Download the file using zip option
   *Extract the library fles
   *Update the library files on arduino library folder
   *Open software freshly
   *Copy the code
   *Compaile
   *Selcect the board
   *Upload and on serial log you will able to see

AIT _ Health Monitoring Sysyem Logs
Entering loop....!
Function :emergency initialized
Function :temparature initialized
Function :ecg initialized
Function :bpm initialized
Function :displai initialized
*******Running on loop*******
Function calling-temparature
...
Temperature for the device 1 (index 0) is: 30
...
Function calling-ecg
...
Function calling-bpm
...
Function calling-displai
...
TMP:30   BPM:0


Problem Statement: The weather monitoring system has a limitation of connectivity and remotely working complexity. The weather monitoring system has placed in very particular areas and all the data is uploaded manually to in information sources. The 1st type of weather monitoring will be done through satellite and the other one will be using all types of sensor which will be deployed on land. To deploy these monitoring centres most many is invested and power will be the major constraint. So the problem here is, powering the sensing unit and deployment of them. 		
Hence we are with the solution which will give power for sensor because of self-sustaining power management system using solar, deployment of this weather monitoring system will be much easier, no man power used once after deployed, better connectivity because of nodal network concepts, uploading all data to cloud automatically continuously and uninterested. 
Because of this we can monitor the data 24/7 and no data will be missed out, hence weather monitoring will be easier and we can upload the data cloud which enables sharing data continuously. Research and data analytics will be endless because of the huge data availability. The proposed system can be improved with more features like the data from the satellite and fetched data from the ground can be clubbed together for more accurate results. 
Contribution to society: The proposed system has been selected with the contribution to society. As the problem statement explains the weather monitoring system has some limitations and we with this proposed system trying to overcome the problem. The contribution to society is, weather monitoring and weather forecasting become easier, and lots of data will be acquired to study and analyse the nature.  The quality of air what we breathe can be measured, and we can take some actions in order to countdown the pollution. The private campus like colleges, companies (production lines) and any large boundary areas can adopt this proposed system and have a track of waste products releasing to atmosphere. Waste management system can be altered and make suitable corrections in the campus. The major challenge in this project is to bridge the communication of sensing nodes through Wi-Fi, and collect all data in centre node which is data centre without internet.    
	
Literature survey on IoT: IoT Internet of Things, this enables the communication between the user and the sensing nodes, when all the data is uploaded to cloud (the big data storage) circulation of data will be easier. In the whole world 1 communication protocol which is commonly used is internet. These days it’s hard to see a computer without connecting to internet. Because the data storage is the main constraint and all sorts of data is available in one of the server (data storage) at least, if we have connection to that why we store the same data again in our PC. IoT is one of the fastest growing areas in embedded system. The application is so much so that every electronic product will end up with IOT. For example home automation, surveillance camera all over city, vehicles, data storage and many more things. Many industries are making private clouds which will be accessible all over the world with single internet connection.
\\\add_articles_here  
Project Description: The purposed system is a self-sustained weather monitoring system. We use solar panel to generate power and this will be given to power management system, which regulates required voltages. We use ESP8266 as a controller, which is the major need in our project. We choose ESP8266 because it has in built Wi-Fi with some GPIO. Here we create 2 sensor nodes which will be enabled with sensor like temperature, humidity, pressure, altitude, carbon presence. These 2 sensor node will be connected to the data hub all these will be connected through Wi-Fi which need not to be connected to internet, so here we see that every sensing node need not to be having internet connectivity this work can be done through private network which will be created by us. The data storage unit which will be receiving sensed data from sensory nodes should have internet connection and all the data which it receives will through out to cloud. 
Here we are using 2 sensory nodes and 1 data centre unit and the connectivity is through Wi-Fi 801.11 Standard. 
//////add these in lecture survey too write about the wifi standard, topology, bridging  and add links below  for reference  
Wi-Fi standard: https://www.netspotapp.com/explaining-wifi-standards.html
Star topology: https://en.wikipedia.org/wiki/Star_network 
Wi-Fi Bridging :https://www.lifewire.com/wireless-bridging-explained-816563///////////////
This allows many devices to connect to the same network. For prototyping we have the bellow architecture. We use Star topology which connects all sensory nodes to the centre hub called data centre. This profile is called the Bridging through Wi-Fi devices. 

Software: Blynk which is available cloud space, Arduino IDE which is used to code the ESP8266, Diptrace to design schematics and PCB, Cisco packet tracer to simulate Star topology. 
Hardware: Copper clad board for PCB, ESP8266 as a controller and Wi-Fi module, temperature, humidity, altitude, pressure, carbon sensor, SD card module and SD card for temporary data storage in data centre.
Protocols used: 
I2c //// add some pictures theory also https://i2c.info/ : To communicate sensor and ESP8266
Wi-Fi Bridging /// add some pictures theory also https://www.lifewire.com/wireless-bridging-explained-816563 : To communicate node to node. (start topology)
TCP/IP /// add some pictures theory also https://community.blynk.cc/t/blynks-communication-protocol-method/4749/2 : To communicate hardware to cloud which we use library of Blynk 

Planning  
Sl no	Project work time line	Work 
01		Simulate start topology
02		Collecting of similar articles 
03		Understand the protocols and examples
04		Getting all the hardware ready 
05		Integrating the sensor and controllers
06		Examples to upload data to cloud 
07		Upload sensing data to cloud 
08		Bridging between nodes 
09		Add a temporary memory using SD card if needed only 
10		Simple, compact the code lines 
11		Simulate verify all things are working and documenting the result
12		Solar power units manually 
13		Design the schematic and verify
14		Design PCB layout , decide of outer caseing
15		PCB post printing verification , Design verification test 
16		Integrate all things together and verify.
17		Deploy nodes in side the campus and start collecting data
18		Final report, documentation, presentation 

Data sheets and info about hardware:
BMP180: https://www.bosch-sensortec.com/bst/products/all_products/bmp180
