all:
	g++ TeamspeakStatus.cpp -o TeamspeakStatus -lwiringPi

install:
	TeamspeakStatus tts
	install TeamspeakStatus /usr/bin/TeamspeakStatus
	install tts /usr/bin/tts


