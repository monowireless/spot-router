# -*- coding: utf-8-unix -*-
# Python 3.11

import logging
from websocket_server import WebsocketServer

def new_client(client, server):
    server.send_message_to_all("This is ground control to TWELITE SPOT")

def new_message(client, server, message):
    print("Received an message:")
    print(message)

server = WebsocketServer(host="YOUR IP ADDRESS", port=8080, loglevel=logging.INFO)
server.set_fn_new_client(new_client)
server.set_fn_message_received(new_message)
server.run_forever()
