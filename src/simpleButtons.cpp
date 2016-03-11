#include "simpleButtons.h"
#include "ofMain.h"


simpleButtons::simpleButtons()
{

}
//--------------------------------------------------------------
void simpleButtons::setupSimpleButtons(int x,int y, int w,int h, string imgLocation,int linkModel, int indexNum){
    
    //Define Bounding box
    simpleButtonsRect.x=x;
    simpleButtonsRect.y=y;
    simpleButtonsRect.width=w;
    simpleButtonsRect.height=h;
    
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255,255);
    
    buttonImage.loadImage(imgLocation);
    buttonImage.setImageType(OF_IMAGE_COLOR_ALPHA);
    
   // imgSize.width=buttonImage.getWidth();
   // imgSize.height=buttonImage.getHeight();
    
    mylinkModel=linkModel;
    indexLink=indexNum;
    
}


//--------------------------------------------------------------
void simpleButtons::setupSimpleButtons(ofRectangle btRect, string imgLocation) {

	//Define Bounding box
	simpleButtonsRect=btRect;

	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 255);

	buttonImage.loadImage(imgLocation);
	buttonImage.setImageType(OF_IMAGE_COLOR_ALPHA);

	//imgSize.width = buttonImage.getWidth();
	//imgSize.height = buttonImage.getHeight();

}


//--------------------------------------------------------------
void simpleButtons::setupSimpleButtons(int x,int y, int w,int h, int linkModel, int indexNum){
    
    //Define Bounding box
    simpleButtonsRect.x=x;
    simpleButtonsRect.y=y;
    simpleButtonsRect.width=w;
    simpleButtonsRect.height=h;
    
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255,255);
    
    mylinkModel=linkModel;
    indexLink=indexNum;
    
}
//--------------------------------------------------------------
void simpleButtons::updateSimpleButtonsPosHover(ofRectangle btRect, int mouseX, int mouseY) {

	simpleButtonsRect = btRect;

	if ((mouseX > simpleButtonsRect.x && mouseX<simpleButtonsRect.x + simpleButtonsRect.width && mouseY>simpleButtonsRect.y && mouseY < simpleButtonsRect.y + simpleButtonsRect.height)) {
		hover = true;
	}
	else {
		hover = false;
	}

}

//--------------------------------------------------------------
bool simpleButtons::updateSimpleButtons(int tapX, int tapY,int prevTapX, int prevTapY){

   // cout<<"x"<<tapX<<"y"<<tapY<<"rect x"<<simpleButtonsRect.x<<"rect y"<<simpleButtonsRect.y<<"allx"<<simpleButtonsRect.x+simpleButtonsRect.width<<"ally"<<simpleButtonsRect.y+simpleButtonsRect.height<<endl;
    buttonState=false;
 //   cout<<"button"<<simpleButtonsRect<<endl;
    if (
        (tapX>simpleButtonsRect.x && tapX<simpleButtonsRect.x+simpleButtonsRect.width && tapY>simpleButtonsRect.y && tapY<simpleButtonsRect.y+simpleButtonsRect.height)
        
        &&
        
      (  prevTapX>simpleButtonsRect.x && prevTapX<simpleButtonsRect.x+simpleButtonsRect.width && prevTapY>simpleButtonsRect.y && prevTapY<simpleButtonsRect.y+simpleButtonsRect.height)
        )
    {
            
        //cout<<"button true"<<endl;
        buttonState=true;
        return(buttonState);
    }
    else
    {return(buttonState);

    }
}
//--------------------------------------------------------------
void simpleButtons::drawSimpleButtons(){
    
int hoverColor = 0;
if (hover)hoverColor = 50;
	


    if(buttonState==false){
        ofSetColor(115-hoverColor, 115 - hoverColor, 115 - hoverColor, 255);
    buttonImage.draw(simpleButtonsRect.x, simpleButtonsRect.y, simpleButtonsRect.width,simpleButtonsRect.height);
    }
    
    else // TO DO FUNCTION
    {
        ofSetColor(255 - hoverColor, 255 - hoverColor, 255 - hoverColor, 255);
        buttonImage.draw(simpleButtonsRect.x, simpleButtonsRect.y, simpleButtonsRect.width,simpleButtonsRect.height);
    }
    //ofSetColor(0, 0, 0,255);
    //    
}

ofRectangle simpleButtons::getDimension()
{
   // ofRectangle dimensions;

    return simpleButtonsRect;
}
