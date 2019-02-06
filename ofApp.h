#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxImGui.h"

#define SIZE 1000000
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void exit();
    
    void recreateSenderUDP();
    void recreateRecieveUDP();
    
    ofxUDPManager udpSender;
    ofxUDPManager udpReciever;
    char sendIp[64];
    char sendArg[SIZE], recieveArg[SIZE];
    vector<string> archiveMsg;
    int sendPort, recievePort;
    bool isBind;
    
    ofxImGui::Gui gui;
    
};
