#include <iostream>
#include <string>
#include <vector>

#include "ChatMessage.h"

using namespace std;

ChatMessage* chat = NULL;
string username = "";

int main(int argc, char* argv[]) {

    if(argc != 9) {
        cout << "Usage:\n  " << argv[0]
        << "\n-ip <ip address of chat server>"
        << "\n-pn <port number of chat server>"
        << "\n-c <name of chatroom you want to enter>"
        << "\n-uname <username to use>\n\n";
        return 1;
    }

    // prep argument vector
    vector<string> arg_vec;
    for(int i = 0; i < argc; i++)
        arg_vec.push_back(argv[i]);

    auto getFlag = [](vector<string>& v, const string& target) {
        for(int i = 1; i < (v.size()-1); i++) {
            if(target == v.at(i))
                return v.at(i+1);
        }

        cout << "ERROR GETTING FLAG: " << target << endl;
        exit(1);
    };

    // retrieve certain flags
    auto ip_address    = getFlag(arg_vec, "-ip");
    auto port_number   = getFlag(arg_vec, "-pn");
    auto chatroom_name = getFlag(arg_vec, "-c");
    username = getFlag(arg_vec, "-uname");

    // asynchronous recieve of messages
    chat = new ChatMessage(new CPJL(ip_address, stoi(port_number)), chatroom_name, 
        [](void) -> void {
            if(chat->sender != username)
                // we care about our own name
                cout << chat->sender << " : " << chat->msg << endl;
        });

    auto msg_loop = CPJL_Message::loop();

    auto send_chat = new ChatMessage(new CPJL(ip_address, stoi(port_number)), chatroom_name);

    for(;;) {
        string send_txt;
        getline(cin, send_txt);

        send_chat->sender = username;
        send_chat->msg = send_txt;
        send_chat->putMessage();
    }

    return 0;
}