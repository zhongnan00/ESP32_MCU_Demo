import paho.mqtt.client as mqtt
import zmq
from random import randrange


context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5556")

# while True:
#     zipcode = randrange(1, 100000)
#     temperature = randrange(-80, 135)
#     relhumidity = randrange(10, 60)

#     socket.send_string(f"{zipcode} {temperature} {relhumidity}")


# Callback when a message is received
def on_message(client, userdata, msg):
    print(f"Received message from topic {msg.topic}: {msg.payload.decode()}")
    socket.send_string(f"{msg.payload.decode()}")

# MQTT setup
broker = "192.168.1.104"  # Replace with your MQTT broker address
port = 1883
topic = "/esp32/pub"

client = mqtt.Client()
client.on_message = on_message

# Connect to the broker and subscribe to the topic
client.connect(broker, port, 60)
client.subscribe(topic)

print(f"Subscribed to topic: {topic}")

# Start the MQTT loop
client.loop_forever()