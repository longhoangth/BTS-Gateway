
runPub: buildPub
	./mqtt_pub

buildPub:	
	g++ mqtt_pub.cpp -o mqtt_pub -lmosquitto -ljsoncpp

runSub: buildSub
	./mqtt_sub

buildSub:
	g++ mqtt_sub.cpp -o mqtt_sub -lmosquitto -ljsoncpp