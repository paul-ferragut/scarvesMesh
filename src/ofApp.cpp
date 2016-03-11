#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
 	widthScarf = ofGetHeight();
	heightScarf= ofGetHeight();

	//INIT LAYOUT VARIABLE
	layoutVar();

	currentTime = 0;
	//useGui = true;
	vars.push_back(string("Complexity 1"));
	vars.push_back(string("Complexity 2"));
	vars.push_back(string("Complexity 3"));
	vars.push_back(string("Scale"));
	vars.push_back(string("Speed"));


	for (int i = 0; i<MAX_COLOR; i++) {
		vars.push_back(string("Red " + ofToString(i)));
		vars.push_back(string("Green " + ofToString(i)));
		vars.push_back(string("Blue " + ofToString(i)));
	}

	for (int i = 0; i < vars.size(); i++){
		floatVars.push_back(0);
	}



    FBO.allocate(widthScarf,heightScarf,GL_RGB);
	FBO2.allocate(widthScarf,heightScarf,GL_RGB);
    pix.allocate(widthScarf,heightScarf,OF_IMAGE_COLOR);


	// listen on the given port
#ifdef USE_OSC

	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;

#endif


	vidPix.allocate(widthScarf, heightScarf, OF_IMAGE_COLOR);
    name=0;
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(34, 34, 34);
    ofSetVerticalSync(false);
    ofEnableAlphaBlending();

    //gui.loadFromFile("settings.xml");

    //we load a font and tell OF to make outlines so we can draw it as GL shapes rather than textures
    font.loadFont("type/verdana.ttf", 100, true, false, true, 0.4, 72);
    shader.load("shaders/noise");
    shader2.load("shaders/PhotoshopGradientMap");


model.loadModel("scarf3d.obj");
image.load("3scarves.png");
imageBlack.load("1scarves.png");
imageWhite.load("2scarves.png");

imageModel.load("imageTexture.png");

 //   //doShader = true;

  //  gui.setup();
    //gui.setup()
    //gui.addPanel("color",1,false);
    //gui.setWhichPanel(0);


	/*
    gui.add(scale.setup("scale",width,0,600));
	gui.add(timeMotion.setup("time", 0.001f, 0.00001f, 1.01f));
	gui.add(fluidity[0].setup("fluidity1", 2.3f, 0.001f, 5));
	gui.add(fluidity[1].setup("fluidity2", 0.4f, 0.001f, 1));
	gui.add(fluidity[2].setup("fluidity3", 12, 1, 40));
	*/


	/*
	gui.add(colorBlendingGradientX.setup("colorBlendingGradientX", 0, -2, 2));
	gui.add(colorBlendingGradientY.setup("colorBlendingGradientY", 0, -2, 2));
	gui.add(addBlurSurface1.setup("addBlurSurface1", 0, -10, 10));
	gui.add(addBlurSurface2.setup("addBlurSurface2", 0, -10, 10));
	gui.add(addInnerSurface1.setup("addInnerSurface1", 0, -10, 10));
	gui.add(addInnerSurface2.setup("addInnerSurface2", 0, -10, 10));

	gui.add(moveContrast.setup("move contrast", 0, -10, 10));
	gui.add(fillThreshold.setup("fillThreshold", 0, -10, 10));


	gui.add(timeFreeze.setup("freezeTime", false));
	*/


 

	/*
    for(int i=0; i<MAX_COLOR; i++)
    {
        gui.add(r[i].setup("red"+ofToString(i+1),0,0,255));
        gui.add(g[i].setup("green"+ofToString(i+1),0,0,255));
        gui.add(b[i].setup("blue"+ofToString(i+1),0,0,255));
    }
	*/
	

  //  gui.loadFromFile("settings.xml");
    if(xml.load("settingsColor.xml"))
    {
        currentColorNum=MIN_COLOR;//xml.getValue("color", MIN_COLOR);
    }

    //custom gradient design
    grad.setup(256, 256);
    for (int i=0; i<MIN_COLOR; i++)
    {
        ofColor c;
        c.set(rVal[i].getValue(), gVal[i].getValue(), bVal[i].getValue());
        grad.addColor(c);
    }
    setupB();

//	useGui = true;

	//string pointString = "769.2, 345.8 761.2, 571.1 761.1, 571.8 761.1, 572.5 761, 573.2 760.9, 573.9 760.7, 574.6 760.5, 575.2 760.3, 575.8 756.5, 585 753.1, 594.3 750, 603.7 747.2, 613.2 744.7, 622.7 742.5, 632.3 735.4, 668.2 731.3, 684.3 726.3, 700.1 720.5, 715.6 713.8, 730.6 706.4, 745.4 698.1, 759.8 689, 773.9 628.8, 859.2 613.3, 882.4 598.3, 905.8 591, 917.7 584.1, 929.8 577.5, 942.1 571.3, 954.6 569, 958.7 566.5, 962.5 563.7, 966.1 560.7, 969.5 557.5, 972.7 554.2, 975.7 547.4, 981.7 546.1, 982.7 544.9, 983.1 543.8, 983.1 542.9, 982.7 542, 982 541.3, 981.1 540.5, 980 523.6, 952.9 520.2, 947.8 516.6, 942.9 512.9, 938.1 507.2, 931.2 380.9, 788.6 373.7, 779.8 366.9, 770.8 360.4, 761.6 354.1, 752.1 348.1, 742.5 342.4, 732.8 331.4, 713 326.6, 703.7 317.4, 684.7 287.6, 618.9 280.1, 600.9 266, 564.7 222.1, 442.9 216.6, 426.6 212.2, 412 208.2, 397.3 204.5, 382.5 197.5, 349.8 194.1, 331.8 191, 313.9 188.2, 295.8 187.7, 290 187.6, 284.2 188.1, 278.5 189.2, 272.9 190.8, 267.4 192.9, 262 195.7, 256.6 199, 251.4 203.6, 245.1 208.5, 239.1 213.6, 233.3 234.4, 210.4 242.5, 200.7 245.7, 197.1 249, 193.5 252.4, 190.1 256, 186.8 259.7, 183.7 263.6, 180.7 267.6, 178 268.5, 177.4 269.4, 176.6 270.2, 175.9 270.9, 175.1 271.7, 174.2 273.1, 172.4 288.7, 151.8 291.3, 148.6 293.9, 145.4 295.6, 143.7 297.4, 142.2 299.3, 140.7 305.3, 136.6 307.2, 135.1 309.1, 133.6 314.5, 128.5 325.1, 118.2 330.4, 112.9 331.4, 111.7 332.4, 110.5 333.3, 109.3 336.1, 105.5 337.1, 104.3 338.1, 103.2 346.9, 93.6 355.9, 84.3 356.4, 83.9 357, 83.5 357.6, 83.2 358.2, 82.8 360.2, 82 360.9, 81.7 361.2, 82.4 362.2, 84.5 362.5, 85.2 362.8, 85.9 363, 86.6 363.1, 87.3 363.8, 110.6 364.2, 118.3 364.4, 119.8 364.6, 121.4 364.8, 122.9 365.1, 124.4 365.5, 125.9 366, 127.4 366.6, 128.8 367.3, 130.1 434.5, 250.2 440.6, 260 447, 269.6 453.7, 279 467.6, 297.4 482, 315.5 483.1, 316.8 484, 317.8 484.9, 318.3 485.6, 318.5 486.4, 318.3 487.1, 317.7 488, 316.7 488.9, 315.3 513.3, 277.4 537, 239.2 559.7, 200.4 581.3, 160.9 584, 155.7 586.5, 150.4 600.5, 118 601.8, 114.6 602.7, 111.1 603.3, 107.5 603.7, 103.9 603.9, 100.3 603.9, 89.5 604, 88.5 604.1, 87.5 604.3, 86.5 604.6, 85.5 605.5, 82.6 605.8, 81.6 610.6, 85.1 612.2, 86.3 612.5, 86.6 612.7, 86.8 613, 87.1 613.2, 87.4 613.5, 87.7 613.6, 88.1 613.8, 88.4 614, 88.7 615.4, 91.8 617.1, 94.4 619.2, 96.6 621.5, 98.6 624, 100.3 626.7, 101.9 632.3, 105 638.3, 108.5 650, 115.6 678.8, 134.3 679, 134.4 679.2, 134.5 679.4, 134.7 679.6, 134.9 679.8, 135.1 711.1, 169.6 716.7, 176.4 721.7, 183.5 726.3, 190.8 730.5, 198.4 734.4, 206.1 738, 214 741.3, 222 766.2, 287 766.7, 288.5 767.1, 290.1 767.4, 291.6 767.7, 293.3 767.9, 294.9 768, 296.5 768.1, 298.1 768.2, 345.7 769.2, 345.8";
	string pointString = "1030.2, 580.6 1029.9, 578.2 1029.6, 576 1029.2, 574.1 1028.7, 572.5 1028, 570.8 1027.1, 568.5 1026, 565.4 1024.8, 561.3 1023.5, 556.1 1022.1, 549.6 1020.6, 541.7 1019, 532.2 1016.6, 523.1 1010.2, 500.6 1005.9, 486.5 1001, 471.8 995.7, 457.3 990.2, 443.9 985.4, 432.8 982, 424.2 979.7, 417.7 978.2, 412.9 977.3, 409.4 976.3, 404.4 975.7, 402.1 974.4, 399.1 972.3, 395.1 969.5, 390.4 966.2, 385.3 962.5, 380.1 958.6, 375 954.7, 370.4 951, 366.5 946.7, 362.6 940.9, 358 933.9, 352.8 925.8, 347.2 916.8, 341.4 907.1, 335.5 896.8, 329.6 886.1, 324 876.7, 319.4 869.9, 316.2 865.2, 314.3 862.3, 313.3 861, 313 860.4, 313.1 860.3, 313.4 860.4, 313.5 860.2, 313.5 859.6, 313.3 858.7, 313 857.5, 312.6 856.1, 312.1 854.5, 311.5 852.8, 310.7 851, 309.8 849.1, 308.4 847.1, 306.5 845, 304.2 843, 301.7 838.2, 295.2 837.3, 294 836.7, 293.4 836.2, 293 835.8, 292.8 835.5, 292.8 835.3, 292.9 835.2, 293 835.2, 293.1 835, 295.4 834.6, 301.1 834.4, 304.7 834.3, 308.4 834.3, 312 834.6, 318.8 834.6, 322.8 834.4, 327.2 834.1, 332 833.6, 337 832.9, 342 832, 347 830.9, 351.8 818.7, 381.8 805.7, 418 799.8, 433 793.2, 448.6 786.1, 463.9 778.6, 477.9 741.3, 543.1 697.5, 609.1 681.1, 586 674.2, 575.7 667.3, 565 661, 554.5 644.1, 522 622.4, 478.1 616.5, 465.1 612.5, 455.3 562.6, 342.1 560, 335.8 558.6, 332.1 555.4, 321.7 554.1, 317 552.9, 311.9 552, 306.5 551.5, 301 551.6, 295.6 549.7, 288 547.3, 290.9 544.6, 294.1 541.1, 298.1 539.2, 300.4 537.3, 302.9 535.4, 305.6 511.2, 342.3 505, 347.6 499.6, 352.6 497, 355.2 492.5, 360 488.1, 364.5 482.1, 370.3 481.8, 370.6 435, 419.3 431.6, 423.2 427.5, 428.5 422.4, 434.8 419.7, 438 417, 441.1 414, 444 411.5, 446.4 408.2, 449.8 403.3, 455.3 391, 470.1 384.6, 478.1 378.8, 485.7 374, 492.3 370.8, 497.3 370.4, 498.2 369.4, 500.8 368, 504.8 366.5, 510 365.1, 516.1 364, 522.9 363.4, 530.2 363.6, 537.8 370.5, 605 383, 679.8 384.3, 686 423.2, 843.6 445.1, 924.6 462.9, 984.6 464.5, 989.5 469.2, 1002.2 479.4, 1027.1 481, 1030.8 483.3, 1035.3 513, 1087.9 515.4, 1091.9 559.9, 1157.1 563.6, 1162 673.4, 1301.1 684.7, 1316.1 690.4, 1324.4 691.9, 1326.4 695.6, 1331.4 697.8, 1334.6 700.1, 1338.1 702.3, 1341.6 704.2, 1345 705.8, 1348.3 708.5, 1354.2 710.4, 1358.7 711.5, 1361.6 718.8, 1374.2 718.8, 1374.1 718.9, 1373.9 719.2, 1373.5 719.8, 1373 720.8, 1372.2 722.3, 1371.2 724.4, 1370 730.3, 1366.7 733.3, 1364.8 736.2, 1362.9 738.9, 1361.1 741.2, 1359.4 743.1, 1358 744.5, 1356.9 745.3, 1356.2 746.2, 1355.4 747.7, 1353.8 749.7, 1351.4 752.2, 1348.2 755.1, 1344.2 758.4, 1339.4 761.9, 1333.8 778.1, 1306.1 782.5, 1298.8 787.1, 1291.6 791.8, 1284.6 796.6, 1277.9 801.4, 1271.6 806.2, 1264.3 812.1, 1255.8 820.1, 1244.6 830.1, 1231.2 842, 1216 855.7, 1199.5 871, 1182 902, 1143.3 914.1, 1127.4 925.4, 1111.8 934.7, 1098 940.7, 1087.3 951.2, 1069.5 958.4, 1047.6 960.4, 1042 973.8, 1001.5 979.5, 979.3 982.1, 970.3 984.8, 961.5 987.5, 953.8 990, 948 993, 939.1 996.1, 930.6 997.9, 926.1 1001.5, 917.8 1002.8, 914.4 1003.8, 911.5 1004.5, 909 1005, 906.9 1006.2, 900.2 1006.4, 898.3 1006.6, 896.2 1006.7, 894 1006.7, 891.7 1006.7, 889.3 1006.6, 886.9 1006.4, 884.5 1006.1, 882.3 1005.6, 878.8 1005.4, 877.2 1005.2, 875.5 1005.1, 873.5 1005.1, 871 1005.2, 867.9 1014.7, 743.4 1030.7, 599.4 1031.1, 591.2 1030.8, 588.5";
		vector<string>parsedString;
	parsedString= ofSplitString(pointString, " ");
	for (int i = 0;i < parsedString.size();i+=2) {
		ofPoint ptTemp(ofToFloat(parsedString[i]), ofToFloat(parsedString[i + 1]));
		pts.push_back(ptTemp);
	}





	//cout << "size" << parsedString.size();
	//for (int i = 0;i < parsedString.size();i++) {

	//	vector<string>parsedString2;
	//	parsedString2 = ofSplitString(parsedString[i], ",");
	//	cout << "size" << parsedString.size();
	//	ofPoint ptTemp(ofToFloat(parsedString2[0]), ofToFloat(parsedString2[1]));
	//	pts.push_back(ptTemp);
	//}



}
void ofApp::layoutVar() {
	margin = ofGetHeight() * 0.04;
	marginInner = margin / 2;
	buttonWidth = ((ofGetWidth() - widthScarf) *0.5) *0.2;
	buttonWidthSmall = buttonWidth*0.3;
	gradRect.set(margin, margin*3 +buttonWidth, ((ofGetWidth() - (widthScarf)) / 2) - margin * 2, margin*0.8);
}
//--------------------------------------------------------------
void ofApp::update()
{

	//RESPONSIVE LAYOUT VARIABLE
	layoutVar();
	updateB();

#ifdef USE_OSC
	receiveOSC();
#endif 


    for(int i=0; i<grad.getNumColors(); i++)
    {
        ofColor c;
        c.set(rVal[i].getValue(), gVal[i].getValue(),bVal[i].getValue());
        grad.replaceColorAtIndex(i, c);
    }


    if(saveVideo)
    {
        string fileName;
        fileName = "img/screen-"+ofToString(ofGetFrameNum())+".png";

        FBO.readToPixels(vidPix);
        vidPix.resize(wVid,hVid);
        ofSaveImage(vidPix, fileName, OF_IMAGE_QUALITY_BEST);
    }
	currentTime += 0.001;
	//drawX = (ofGetWidth() - (widthScarf)) / 2;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0, 0, 0);

	ofPixels pix = grad.getRef(256, 256);

	ofTexture tex;
	ofSetColor(255, 255, 255,255);

	//ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	tex.allocate(pix);	
	
	//ofEnableAlphaBlending();
	ofFill();
	//cam.begin();//	
	float ratio;
	ratio = 1000.0 / 1400.0;
	ofPushMatrix();
	ofScale(ratio, ratio);
	shader.begin();

	shader.setUniform1f("fluidity1", fluidityVal[0].getValue());
	shader.setUniform1f("fluidity2", fluidityVal[1].getValue());
	shader.setUniform1i("fluidity3", fluidityVal[2].getValue());
	shader.setUniform1f("scaleWidth", scaleVal.getValue());
	shader.setUniform1f("scaleHeight", scaleVal.getValue());
	shader.setUniform1f("time", currentTime);//ofGetFrameNum() *timeMotionVal.getValue());
	shader.setUniformTexture("gradient", tex, 1);
//	shader.setUniform1f("colorThreshold", colorThreshold);
	shader.setUniform1f("gradientWidth", 256.0);
	//ofDrawRectangle(0, 0, widthScarf, heightScarf);

	ofSetColor(255, 255, 255);
	

	ofBeginShape();
	for (int i = 0;i < pts.size();i++) {
		ofVertex(pts[i]);
	}
	ofEndShape();
//
	//
	//model.drawFaces();
	//imageModel.draw(0,0);
	shader.end();
	//cam.end();

	ofPopMatrix();

	ofFill();
	ofSetColor(255, 255, 255, 255);
	ofEnableAlphaBlending();

	//ofEnableBlendMode(OF_BLENDMODE_ADD);

	ofSetColor(255, 255, 255, 195);
	imageBlack.draw(0, 0, 1000, 1000);

	//ofDisableBlendMode();

	ofSetColor(255, 255, 255, 120);
	imageWhite.draw(0, 0, 1000, 1000);
	ofSetColor(255, 255, 255, 255);
	image.draw(0, 0, 1000, 1000);

	drawB();

}
void ofApp::takeStill()
{

	string fileName;
	fileName = "img/screen-" + ofToString(ofGetHours()) + "-" + ofToString(ofGetMinutes()) + "-" + ofToString(ofGetSeconds()) + ".png";
	cout << "name" << fileName << endl;
	FBO2.readToPixels(pix);
	ofSaveImage(pix, fileName, OF_IMAGE_QUALITY_BEST);

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{


    if( key == ' ' )
    {
        takeStill();
    }

	if (key == 'f')
	{
		ofToggleFullscreen();
	}

    if( key == 's' )
    {
        string fileName;
	//	gui.saveToFile(ofGetTimestampString()+".xml");
       // fileName = "img/screen-"+ofToString(ofGetHours())+"-"+ofToString(ofGetMinutes())+"-"+ofToString(ofGetSeconds())+".png";
       
		fileName = ofGetTimestampString()+ ".png";
		FBO.readToPixels(pix);
        ofSaveImage(pix, fileName, OF_IMAGE_QUALITY_BEST);
    }


	if (key == 'l')
	{


		string openF;
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .knct in data folder");
		if (openFileResult.bSuccess) {
			ofLogVerbose("File Selected");
			openF= openFileResult.getName();
			ofLogVerbose("Reader Initiated");
		//	gui.loadFromFile(openF);//+".xml"
		}
		else {
			ofLogVerbose("User hit cancel");
			//startPlay = false;
		}
		
	}

	if (key == 'g'){
		//useGui=!useGui;
	}

	if (key == OF_KEY_LEFT){
		drawX-=10;

	}

	if (key == OF_KEY_RIGHT){
		drawX+=10;

	}
	

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

 
}
//--------------------------------------------------------------
void ofApp::exit()
{
 //   gui.saveToFile("settings.xml");

    for (int i=0; i<currentColorNum; i++)
    {
        //r[i]->saveSettings("settingsColor"+ofToString(i)+".xml");
        //  delete guiColorG[i];
    }

    xml.setValue("color", currentColorNum);
    xml.save("settingsColor.xml");
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	if (currentState == 0) {
		for (int i = 0; i<MAX_COLOR; i++)
	{
		if (currentColor == i) {
			rVal[i].mouseMoved(x, y);
			gVal[i].mouseMoved(x, y);
			bVal[i].mouseMoved(x, y);
		}
	}
	}
	else if (currentState == 1) {
		fluidityVal[0].mouseMoved(x, y);
	fluidityVal[1].mouseMoved(x, y);
	fluidityVal[2].mouseMoved(x, y);
	timeMotionVal.mouseMoved(x, y);
	scaleVal.mouseMoved(x, y);
	}




}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if (currentState == 0) {

	}
	else if (currentState == 1) {

	}
	for (int i = 0; i<MAX_COLOR; i++)
	{
		if (currentColor == i) {
			rVal[i].mouseDragged(x, y);
			gVal[i].mouseDragged(x, y);
			bVal[i].mouseDragged(x, y);
		}
	}


	fluidityVal[0].mouseDragged(x, y);
	fluidityVal[1].mouseDragged(x, y);
	fluidityVal[2].mouseDragged(x, y);
	timeMotionVal.mouseDragged(x, y);
	scaleVal.mouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (currentState == 0) {
	for (int i = 0; i<MAX_COLOR; i++)
	{
		if (currentColor == i) {
			rVal[i].mousePressed(x, y);
			gVal[i].mousePressed(x, y);
			bVal[i].mousePressed(x, y);
		}
	}

	}
	else if (currentState == 1) {
	fluidityVal[0].mousePressed(x, y);
	fluidityVal[1].mousePressed(x, y);
	fluidityVal[2].mousePressed(x, y);
	timeMotionVal.mousePressed(x, y);
	scaleVal.mousePressed(x, y);
	}



}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	if (currentState == 0) {



		for (int i = 0; i < currentColorNum; i++)
		{


			bool ok = btColor[i].updateSimpleButtons(x, y, x, y);
			if (ok == true)
			{
				//   guiColorG[i]->setVisible(true);
				btColor[i].buttonState = true;
				for (int j = 0; j < currentColorNum; j++)
				{
					cout << "i" << i << " j" << j << endl;
					if (i != j)
					{
						cout << "valid i" << i << " j" << j << endl;
						btColor[j].buttonState = false;
						//              guiColorG[j]->setVisible(false);
					}
				}
				currentColor = i;
			}

		}



			if (btPlus.updateSimpleButtons(x, y, x, y))
			{
				addColor();
			}
			if (btMinus.updateSimpleButtons(x, y, x, y))
			{
				removeColor();
			}
	for (int i = 0; i<MAX_COLOR; i++)
	{
		if (currentColor == i) {
			rVal[i].mouseReleased(x, y);
			gVal[i].mouseReleased(x, y);
			bVal[i].mouseReleased(x, y);
		}
	}

	}

	else if (currentState == 1) {
	fluidityVal[0].mouseReleased(x, y);
	fluidityVal[1].mouseReleased(x, y);
	fluidityVal[2].mouseReleased(x, y);
	timeMotionVal.mouseReleased(x, y);
	scaleVal.mouseReleased(x, y);
	}
	if (btColorCat.updateSimpleButtons(x, y, x, y))
	{
		currentState = 0;
		btDesignCat.buttonState = false;
		btSaveCat.buttonState = false;
	}
	if (btDesignCat.updateSimpleButtons(x, y, x, y))
	{
		currentState = 1;
		btColorCat.buttonState = false;
		btSaveCat.buttonState = false;
	}

	if(btSaveCat.updateSimpleButtons(x, y, x, y))
	{
		currentState = 2;
		btColorCat.buttonState = false;
		btDesignCat.buttonState = false;
	}







}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

void ofApp::setupB()
{



    for (int i=0; i<currentColorNum; i++)
    {
		ofRectangle btColRect(gradRect.x + gradRect.height + (((gradRect.width - gradRect.height * 2) / (currentColorNum - 1))*i) - (buttonWidthSmall / 2),gradRect.y - buttonWidthSmall, buttonWidthSmall, buttonWidthSmall);
		btColor[i].setupSimpleButtons(btColRect, "icons/frame-w.png");
    }

	ofRectangle btP(gradRect.x, gradRect.y, gradRect.height, gradRect.height);
	ofRectangle btM(gradRect.x + gradRect.width - gradRect.height, gradRect.y, gradRect.height, gradRect.height);
	ofRectangle btDC(margin, margin, buttonWidth, buttonWidth);
	ofRectangle btCC(margin + buttonWidth + margin / 2, margin, buttonWidth, buttonWidth);
	ofRectangle btSC(margin + (buttonWidth + margin / 2)*2, margin, buttonWidth, buttonWidth);

	btPlus.setupSimpleButtons(btP, "icons/plus.png");
	btMinus.setupSimpleButtons(btM, "icons/minus.png");
	btDesignCat.setupSimpleButtons(btDC, "icons/icons-02w.png");
	btColorCat.setupSimpleButtons(btCC, "icons/icons-01w.png");
	btSaveCat.setupSimpleButtons(btSC, "icons/download-01.png");



	float heightSlider=btDC.height/2;
	float marginSlider= heightSlider *1.5;
	float gapSlider = heightSlider + marginSlider;
	float ySlider = btDC.y + btDC.height + margin;
	float widthSlider = gradRect.width;

	fluidityVal[0].setup(btDC.x, ySlider, widthSlider, heightSlider, 0.001f, 5, 2.3f, false, true);
	fluidityVal[0].setLabelString("fluidity 1");

	fluidityVal[1].setup(btDC.x, ySlider+gapSlider, widthSlider, heightSlider, 0.001f, 1, 0.4f, false, true);
	fluidityVal[1].setLabelString("fluidity 2");

	fluidityVal[2].setup(btDC.x, ySlider +( gapSlider*2), widthSlider, heightSlider, 1, 40, 12, false, true);
	fluidityVal[2].setLabelString("fluidity 3");

	timeMotionVal.setup(btDC.x, ySlider + (gapSlider * 3), widthSlider, heightSlider, 0.0f, 0.002,0.0012f, false, true);
	timeMotionVal.setLabelString("Speed");

	scaleVal.setup(btDC.x, ySlider + (gapSlider * 4), widthSlider, heightSlider, 0, 600, 10, false, true);
	scaleVal.setLabelString("Scale");


	float heightSliderColor = btP.y + btP.height + margin;
	for (int i = 0; i<MAX_COLOR; i++)
	{
	rVal[i].setup(btP.x, heightSliderColor , widthSlider, heightSlider,0, 255, 0, false, true);
	rVal[i].setLabelString("red" + ofToString(i + 1));
	gVal[i].setup(btP.x, heightSliderColor + gapSlider, widthSlider, heightSlider,0, 255, 0, false, true);
	gVal[i].setLabelString("green" + ofToString(i + 1));
	bVal[i].setup(btP.x, heightSliderColor + gapSlider*2, widthSlider, heightSlider,0, 255, 0, false, true);
	bVal[i].setLabelString("blue" + ofToString(i + 1));
	}
}
//--------------------------------------------------------------
void ofApp::updateB() {


	//THIS IS STUPID HOW TO IMPROVE?
	for (int i = 0; i<currentColorNum; i++)
	{
		ofRectangle btColRect(gradRect.x + gradRect.height + (((gradRect.width - gradRect.height * 2) / (currentColorNum - 1))*i) - (buttonWidthSmall / 2), gradRect.y - buttonWidthSmall, buttonWidthSmall, buttonWidthSmall);
		btColor[i].updateSimpleButtonsPosHover(btColRect, mouseX, mouseY);
	}

	ofRectangle btP(gradRect.x, gradRect.y, gradRect.height, gradRect.height);
	ofRectangle btM(gradRect.x + gradRect.width - gradRect.height, gradRect.y, gradRect.height, gradRect.height);
	ofRectangle btDC(margin, margin, buttonWidth, buttonWidth);
	ofRectangle btCC(margin+ buttonWidth + margin/2, margin, buttonWidth, buttonWidth);
	ofRectangle btSC(margin + (buttonWidth + margin / 2) * 2, margin, buttonWidth, buttonWidth);

	btPlus.updateSimpleButtonsPosHover(btP, mouseX, mouseY);
	btMinus.updateSimpleButtonsPosHover(btM, mouseX, mouseY);
	btDesignCat.updateSimpleButtonsPosHover(btDC,  mouseX, mouseY);
	btColorCat.updateSimpleButtonsPosHover(btCC, mouseX, mouseY);	
	btSaveCat.updateSimpleButtonsPosHover(btSC, mouseX, mouseY);
	
	
	float heightSlider = btDC.height / 2;
	float marginSlider = heightSlider * 1.5;
	float gapSlider = heightSlider + marginSlider;
	float ySlider = btDC.y + btDC.height + margin;
	float widthSlider = gradRect.width;

	fluidityVal[0].updateLayout(ofRectangle(btP.x, ySlider, widthSlider, heightSlider));
	fluidityVal[1].updateLayout(ofRectangle(btP.x, ySlider + gapSlider, widthSlider, heightSlider));
	fluidityVal[2].updateLayout(ofRectangle(btP.x, ySlider + (gapSlider * 2), widthSlider, heightSlider));
	timeMotionVal.updateLayout(ofRectangle(btP.x, ySlider + (gapSlider * 3), widthSlider, heightSlider));
	scaleVal.updateLayout(ofRectangle(btP.x, ySlider + (gapSlider * 4), widthSlider, heightSlider));


	float heightSliderColor = btP.y + btP.height + margin;
	for (int i = 0; i<MAX_COLOR; i++)
	{
		if (currentColor == i) {
			rVal[i].updateLayout(ofRectangle(btP.x, heightSliderColor, widthSlider, heightSlider));
			gVal[i].updateLayout(ofRectangle(btP.x, heightSliderColor + gapSlider, widthSlider, heightSlider));
			bVal[i].updateLayout(ofRectangle(btP.x, heightSliderColor + gapSlider * 2, widthSlider, heightSlider));
		}
	}

}
//--------------------------------------------------------------
void ofApp::drawB()
{

   // int screenWidth=widthPreview;
   // ofSetColor(0, 0, 0,150);
    // ofRect(UIrect);
	btColorCat.drawSimpleButtons();
	btDesignCat.drawSimpleButtons();
	btSaveCat.drawSimpleButtons();



	if (currentState == 1) {
		fluidityVal[0].draw();
		fluidityVal[1].draw();
		fluidityVal[2].draw();
		timeMotionVal.draw();
		scaleVal.draw();
	
	}
	else if (currentState == 0) {

	grad.drawDebug(gradRect.x+ gradRect.height,gradRect.y,gradRect.width-(gradRect.height*2),gradRect.height);//+(margin*2)

    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(115, 115, 115, 255);
	ofRect(gradRect);
    // ofSetLineWidth(7);
    ofRect(btPlus.simpleButtonsRect);
    ofRect(btMinus.simpleButtonsRect);
    //ofSetLineWidth(1);
    ofFill();
    btMinus.drawSimpleButtons();
    btPlus.drawSimpleButtons();

    bool checkVisible=false;
	ofFill();
    for (int i=0; i<currentColorNum; i++)
    {
        float q=1.0/(currentColorNum-1)*(float)i;
        ofSetColor(grad.getColorAtPercent(q));//(1.0/(MAX_COLOR-1))*(float)i)
		ofRectangle colInBt(btColor[i].getDimension());
		colInBt.height*=0.85;
		ofRect(colInBt);
        btColor[i].drawSimpleButtons();
        //checkVisible=guiColorG[i]->isVisible();
    }

	for (int i = 0; i<MAX_COLOR; i++)
	{
		if (currentColor == i) {
				rVal[i].draw();
				gVal[i].draw();
				bVal[i].draw();
			}
		}
	}





    //textColor.draw(bWidth, 6*(g.screenHeight/10));
}


string ofApp::pasteClipBoardText()
{
    string clipBoardText = "";
    if (OpenClipboard(NULL))
    {
        HANDLE hClipboardData = GetClipboardData(CF_TEXT);
        if(IsClipboardFormatAvailable(CF_TEXT))
        {
            char *pchData = (char*)GlobalLock(hClipboardData);
            clipBoardText.assign(pchData);
            GlobalUnlock(hClipboardData);
            CloseClipboard();
        }
    }
    return clipBoardText;
}


void ofApp::addColor(){
	if (currentColorNum<MAX_COLOR)
	{
		cout << "NEW COLOR" << endl;
		ofColor col = grad.getColorAtPercent(1);

		//TO CHANGE
	//	r[currentColorNum] = col.r;
	//	g[currentColorNum] = col.g;
	//	b[currentColorNum] = col.b;

		
		rVal[currentColorNum].setPercent(ofMap(col.r, 0,255, 0, 100));
		gVal[currentColorNum].setPercent(ofMap(col.g, 0,255, 0, 100));
		bVal[currentColorNum].setPercent(ofMap(col.b, 0,255, 0, 100));
		

		//

		grad.addColor(grad.getColorAtPercent(1));
		currentColorNum++;
		btPlus.buttonState = false;
	
		//float widthThings2 = widthThings - bWidth;
		for (int i = 0; i<currentColorNum; i++)
		{

			btColor[i].setupSimpleButtons(gradRect.x+gradRect.height + (((gradRect.width-gradRect.height*2) / (currentColorNum - 1))*i) - (buttonWidthSmall / 2),
				gradRect.y - buttonWidthSmall, buttonWidthSmall, buttonWidthSmall, "icons/frame-w.png", 0, 0);
		}
		

	}

}

void ofApp::removeColor(){
	if (currentColorNum>MIN_COLOR)
	{
		//cout << "REMOVED COLOR" << endl;
		grad.deleteColor();
		currentColorNum--;
		btMinus.buttonState = false;
		/*float widthThings2 = widthThings - bWidth;*/
		for (int i = 0; i<currentColorNum; i++)
		{
			btColor[i].setupSimpleButtons(gradRect.x + gradRect.height + (((gradRect.width - gradRect.height * 2) / (currentColorNum - 1))*i) - (buttonWidthSmall / 2),
				gradRect.y - buttonWidthSmall, buttonWidthSmall, buttonWidthSmall, "icons/frame-w.png", 0, 0);
		}
		
	}
}

string ofApp::exportDesignString() {
	string designSt = "";

	//float widthThings2 = widthThings - bWidth;



	designSt += ofToString(fluidityVal[0].getValue());
	designSt += ";";
	designSt += ofToString(fluidityVal[1].getValue());
	designSt += ";";
	designSt += ofToString(fluidityVal[2].getValue());
	designSt += ";";
	designSt += ofToString(scaleVal.getValue());
	designSt += ";";
	designSt += ofToString(ofGetFrameNum() *timeMotionVal.getValue());
	designSt += ";";


	for (int i = 0; i<currentColorNum; i++)
	{

		designSt += ofToString(rVal[currentColorNum].getValue());
		designSt += ";";
		designSt += ofToString(gVal[currentColorNum].getValue());
		designSt += ";";
		designSt += ofToString(bVal[currentColorNum].getValue());
		designSt += ";";

	}





	return designSt;
}



void ofApp::receiveOSC() {

	/*
	while (receiver.hasWaitingMessages()) {
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);


		string a = m.getAddress();

		if (a == "/iPad/add") {

			addColor();
		}

		if (a == "/iPad/remove") {
			removeColor();
			//return;
		}

		if (a == "/iPad/save") {
			string mail = m.getArgAsString(0);

			string fileName;
			fileName = "img/screen-" + ofToString(ofGetHours()) + "-" + ofToString(ofGetMinutes()) + "-" + ofToString(ofGetSeconds()) + "-" + mail + ".png";

			FBO2.readToPixels(pix);
			ofSaveImage(pix, fileName, OF_IMAGE_QUALITY_BEST);
		}


		float v = m.getArgAsFloat(0);
		for (int i = 0; i < vars.size(); i++) {

			if (a == "/iPad/" + vars[i]) {
				floatVars[i] = v;

				switch (i) {
				case 0:
					//		fluidityVal[0] = ofMap(floatVars[0], 0.0, 1.0, 0.001f, 5);
					break;
				case 1:
					//		fluidity[1] = ofMap(floatVars[1], 0.0, 1.0, 0.001f, 1);
					break;
				case 2:
					//		fluidity[2] = ofMap(floatVars[2], 0.0, 1.0, 1, 40);
					break;
				case 3:
					//			scale = ofMap(floatVars[3], 0.0, 1.0, 1, 40000);
					break;
				case 4:
					//			timeMotion = ofMap(floatVars[4], 0.0, 1.0, 0.00001f, 0.6f);
					break;
				
				case 5:
					r[0] = v;
					break;
				case 6:
					g[0] = v;
					break;
				case 7:
					b[0] = v;
					break;
				case 8:
					r[1] = v;
					break;
				case 9:
					g[1] = v;
					break;
				case 10:
					b[1] = v;
					break;
				case 11:
					r[2] = v;
					break;
				case 12:
					g[2] = v;
					break;
				case 13:
					b[2] = v;
					break;
				case 14:
					r[3] = v;
					break;
				case 15:
					g[3] = v;
					break;
				case 16:
					b[3] = v;
					break;
				case 17:
					r[4] = v;
					break;
				case 18:
					g[4] = v;
					break;
				case 19:
					b[4] = v;
					break;
				case 20:
					r[5] = v;
					break;
				case 21:
					g[5] = v;
					break;
				case 22:
					b[5] = v;
					break;
				case 23:
					r[6] = v;
					break;
				case 24:
					g[6] = v;
					break;
				case 25:
					b[6] = v;
					break;
					
				}
			}


		}

	}*/
}