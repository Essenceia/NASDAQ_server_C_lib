# Fake ITCH Nasdaq Server C library

Objective :

- read NASDAQ ITCH log and create fake MoldUDP64 packet to send over UDP

- keep track of sent ITCH packets within the session window

- respond to re-request requests with a new MoldUDP64 packet containg the replay
     
