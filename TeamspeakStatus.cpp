#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool running = true;

void Speak(string message) {
	string run = "tts ";
    run += message;
    system(run.c_str());
}

void Init() {
	system("gpio export 17 out");
	system("gpio export 18 out");
	system("gpio export 22 out");
	system("gpio export 23 out");
	system("gpio export 24 out");
}

void alloff() {
	system("gpio -g write 17 0");
	system("gpio -g write 18 0");
	system("gpio -g write 22 0");
	system("gpio -g write 23 0");
	system("gpio -g write 24 0");
}

void syncLeds(int amount) {
	alloff();
	if(amount >= 1) {
		system("gpio -g write 17 1");
	}
	if(amount >= 2) {
		system("gpio -g write 18 1");
	}
	if(amount >= 3) {
		system("gpio -g write 22 1");
	}
	if(amount >= 4) {
		system("gpio -g write 23 1");
	}
	if(amount >= 5) {
		system("gpio -g write 24 1");
	}
}

int main(int argc, char* argv[]) {
    FILE *cmd = NULL;
	printf("Teamspeak Listener 1.0\n");
	char user[200];
	user[0] = '\0';
	int olduser = 0;
	
    while(running) { //loop until running=false
		cmd = popen("curl http://192.168.1.5/status/check_users.php","r");
		fscanf(cmd,"%s",user);
		fclose(cmd);
		string userstring(user);
		int useri = atoi(userstring.c_str());
		if (useri >= 0 && useri != olduser) {
			printf("\033[32m%s users are online\033[0m\n", user);
			if (useri < olduser) {
				Speak("User offline");
			} else { 
				Speak("User online");
			}
			syncLeds(useri);
			olduser = useri;
		}
    }
	return 0;
}