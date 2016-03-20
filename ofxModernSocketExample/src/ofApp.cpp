#include "ofMain.h"
#include "ofxModernOscReceiver.h"

class ofApp : public ofBaseApp {
    ofxModernOscReceiver receiver;
public:
    void setup() {
        ofSetColor(255, 255, 255);
        ofSetBackgroundColor(0, 0, 0);
        
        receiver.setup(9005);
        receiver.addCallback("/test", [](ofxModernOscMessage &mess) { ofLogNotice("ofApp") << mess; });
    }
    void update() {}
    void draw() {
        ofDrawBitmapString(ofToString(ofGetFrameNum()), 20, 20);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 40);
    }
    
    void exit() {}
    
    void keyPressed(int key) {}
    void keyReleased(int key) {}
    void mouseMoved(int x, int y) {}
    void mouseDragged(int x, int y, int button) {}
    void mousePressed(int x, int y, int button) {}
    void mouseReleased(int x, int y, int button) {}
    void mouseEntered(int x, int y) {}
    void mouseExited(int x, int y) {}
    void windowResized(int w, int h) {}
    void dragEvent(ofDragInfo dragInfo) {}
    void gotMessage(ofMessage msg) {}
};

int main() {
    ofSetupOpenGL(100, 100, OF_WINDOW);
    ofRunApp(new ofApp);
}
