start mosquitto : .\mosquitto -c "mosquitto.conf" -v
kill mosquitto : sc stop mosquitto 
check publishes : mosquitto_sub -h ''ip'' -t "#" -