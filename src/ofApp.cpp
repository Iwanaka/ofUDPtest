#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofSetWindowTitle("Udp Test");
    
    strcpy(sendArg, "");
    strcpy(sendIp, "127.0.0.1");
    sendPort = 7400;
    recievePort = 7400;
    
    isBind = false;
    
    recreateSenderUDP();
    recreateRecieveUDP();
 
    gui.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    char msg[SIZE];
    udpReciever.Receive(msg, SIZE);
    if(strlen(msg) > 0) {
        strcpy(recieveArg, msg);
        
        string m = ofToString(recieveArg);
        archiveMsg.push_back(m);
        
        if(5 < archiveMsg.size()) archiveMsg.erase(archiveMsg.begin());
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    gui.begin();
    {
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiSetCond_Always);
        ImGui::SetNextWindowSize(ImVec2(380, 280), ImGuiSetCond_Always);
        
        ImGui::Begin("Udp Test");
        {
            
            ImGui::InputText("arg", sendArg, SIZE);
            
            if(ImGui::InputText("send ip", sendIp, 64)){
                recreateSenderUDP();
            };
            
            if(ImGui::InputInt(" send port", &sendPort)){
                if(sendPort < 0) sendPort = 0;
                if(sendPort >= 65535) sendPort = 65535;
                recreateSenderUDP();
            };
            
            if(ImGui::InputInt(" recieve port", &recievePort)){
                if(recievePort < 0) recievePort = 0;
                if(recievePort >= 65535) recievePort = 65535;
                recreateRecieveUDP();
            };
            
            if(ImGui::Button("send")){
                udpSender.Send(sendArg, sendPort);
            };
            
            ImGui::Text("recieve message");
            ImGui::PushItemWidth(380);
            //ImGui::TextWrapped("%s", recieveArg);
            
            for(int i =0 ;i<archiveMsg.size();i++){
                
                ImGui::TextWrapped("    %s",archiveMsg[i].c_str());
                
            }
            
            ImGui::PopItemWidth();
            
            
        }
        ImGui::End();
        
    }
    gui.end();
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    if(isBind) udpReciever.Close();
    
}

//--------------------------------------------------------------
void ofApp::recreateSenderUDP(){
    
    udpSender.Close();
    
    udpSender.Create();
    udpSender.Connect(sendIp, sendPort);
    udpSender.SetNonBlocking(true);
}

//--------------------------------------------------------------
void ofApp::recreateRecieveUDP(){
    
    udpReciever.Close();
    
    udpReciever.Create();
    isBind =  udpReciever.Bind(recievePort);
    udpReciever.SetNonBlocking(true);
    
}
