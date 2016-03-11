#pragma once

#include "ofMain.h"
//#include "ofxControlPanel.h"
#include "ofxXmlSettings.h"
//#include "ofxGui.h"
#include "simpleButtons.h"
#include "ofxColorGradient.h"
//#include "ofxOsc.h"
#include "ofxSimpleSlider.h"
#include "ofxAssimpModelLoader.h"

#include <windows.h>


//#define USE_OSC

#define PORT 12345
#define NUM_MSG_STRINGS 20

#define MAX_COLOR 7
#define MIN_COLOR 2

//#define widthScarf 768//*2
//#define heightScarf 768//*2//5800

#define screenWidthInit 1366
#define screenHeightInit 768

//#define widthPreview 768
#//define heightPreview 768

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void takeStill();

		void keyPressed  (int key);
		void keyReleased (int key);
		string pasteClipBoardText();

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void setupB();
		void drawB();

		ofTrueTypeFont font;
		ofShader shader;
		bool doShader;


		string exportDesignString();
//		ofxControlPanel gui;
//ofxPanel gui;
//ofxFloatSlider red[2];
//ofxFloatSlider green[2];
//ofxFloatSlider blue[2];


		//float red[2];
	//	float green[2];
	//	float blue[2];

//ofxToggle timeFreeze;

ofxSimpleSlider fluidityVal[3];
ofxSimpleSlider timeMotionVal;
ofxSimpleSlider scaleVal;
		ofxSimpleSlider rVal[MAX_COLOR];
		ofxSimpleSlider gVal[MAX_COLOR];
		ofxSimpleSlider bVal[MAX_COLOR];

		int currentState;
		int currentColor;

		int widthScarf;
		int heightScarf;
		/*

		ofxFloatSlider timeMotion;
		ofxFloatSlider fluidity[2];
		ofxIntSlider fluidityI;
	ofxIntSlider scale;
*/

		/*
ofxFloatSlider colorBlendingGradientX;
ofxFloatSlider colorBlendingGradientY;

ofxFloatSlider addBlurSurface1;
ofxFloatSlider addBlurSurface2;

ofxFloatSlider addInnerSurface1;
ofxFloatSlider addInnerSurface2;

ofxFloatSlider moveContrast;
ofxFloatSlider fillThreshold;

*/
//ofxIntSlider r[MAX_COLOR];
//ofxIntSlider g[MAX_COLOR];
//ofxIntSlider b[MAX_COLOR];
/**/
  float red[MAX_COLOR],green[MAX_COLOR],blue[MAX_COLOR];

  vector<string>vars;
  vector<float>floatVars;

int width;
int height;

//float widthThings;
 //   float xThings;

   simpleButtons btColor[MAX_COLOR];
    simpleButtons btPlus;
    simpleButtons btMinus;

	simpleButtons btDesignCat;
	simpleButtons btColorCat;
	simpleButtons btSaveCat;



    int currentColorNum;


	void layoutVar();
	void updateB();
  //  float bWidth;
  //  float bWidth2;
	float margin;
	float marginInner;
	float buttonWidth;
	float buttonWidthSmall;
	ofRectangle gradRect;

int wVid;
int hVid;

void addColor();
void removeColor();

int name;
bool takingStill;
bool saveVideo;

ofFbo FBO;
ofFbo FBO2;
    ofImage gradient;

    ofxColorGradient grad;
ofImage background; //initially I got some weird artifacts without creating a background image large enough for your print it drew part of my screen desktop to the FBO...
ofPixels pix;
ofPixels vidPix;

ofShader shader2;
ofxXmlSettings xml;

float currentTime;
//ofxOscReceiver receiver;
void receiveOSC();

int current_msg_string;
string msg_strings[NUM_MSG_STRINGS];
float timers[NUM_MSG_STRINGS];


int drawX;

ofEasyCam cam;
ofxAssimpModelLoader model;
ofImage image;
ofImage imageBlack;
ofImage imageWhite;

ofImage imageModel;

vector<ofPoint>pts;



};

