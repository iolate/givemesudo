#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define SUDO_PASS "BLANK"

using namespace std;

void SetStdinEcho(bool enable = true) {
	struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void give_me_sudo(string userName) {
	setuid(0);
	string system_cmd = "/usr/sbin/usermod -a -G sudo " + userName;
	//cout << system_cmd << endl;
	system(system_cmd.c_str());
}

int main() {
	char szUserName[64] = {0};
	int nGet = getlogin_r(szUserName, sizeof(szUserName)-1);
	
	string passwd;
	SetStdinEcho(false);
	cout << "GiveMeSudo Password: ";
	getline(cin, passwd);
	SetStdinEcho(true);	
	cout << endl;
	
	if (passwd == SUDO_PASS) {
		cout << "Correct!" << endl;
		give_me_sudo(szUserName);
		cout << "Now you are sudoers!" << endl;
	}else{
		cout << "Wrong password!" << endl;
	}
	
	return 0;
}
