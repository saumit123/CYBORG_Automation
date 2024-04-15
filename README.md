# RFID based door lock integration with Telegram using ESP32
## Description
This project implements a RFID based door lock system which uses RFID tags and scanner to identify the person and open the door lock,additionally it keeps log and sends a telegram message to a channel using the Telegram API
## Components used
- ESP32
- MFRC522 RFID module
- Electric door lock
- RFID tags 13.6 MHz
## Software/API used
- Telegram API(Bot)
- Postman
- Arduino IDE
## Instructions
1. Power on the ESP32 board and ensure it's connected to the RFID reader and the door lock mechanism.
2. Present a valid RFID card or tag to the reader. If authorized, the door will unlock, and a notification will be sent to the designated Telegram channel.
3. If an unauthorized RFID card or tag is presented, a notification will be sent to the Telegram channel, and the door will remain locked.
4. Monitor the Telegram channel for real-time notifications about access events.
## Configurations
Before running the project, you need to configure the following settings:

1. In the code, update the `WIFI_SSID` and `WIFI_PASSWORD` constants with your WiFi network credentials.
2. Set the `BOT_TOKEN` constant with your Telegram Bot API token.
3. Replace the `CHANNEL_ID` constant with the ID of the Telegram channel where you want to receive notifications.
4. Modify the `authorized_cards` array in the code to include the RFID card or tag IDs that should be granted access.
