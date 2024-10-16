sudo chmod 777 /dev/ttyUSB*

echo "Build"
make -j4

echo "run"
echo ""

./Modbus