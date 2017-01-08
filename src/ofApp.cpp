#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetCircleResolution(100);

    _winWidth = ofGetWindowWidth();
    _center.x = _winWidth/2;
    _center.y = ofGetWindowHeight()/2;

    _img.allocate(ofGetWidth(),ofGetHeight(),OF_IMAGE_COLOR_ALPHA);
    _fboStatic.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);
    _fboDynamic.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);


    _innerCircleRadius = 100;
    _outerCircleRadius = _winWidth - 100;
    _distFromCircle = 40;

    _lineWidth = 5.;
    updateCircles();


    _backgroundColor = ofColor(ofRandom(0.,255.),ofRandom(0.,255.),ofRandom(0.,255.));
    _circleColor = ofColor(ofRandom(0.,255.),ofRandom(0.,255.),ofRandom(0.,255.));

    drawStaticImage();
    drawDynamicImage();
}
//--------------------------------------------------------------

void ofApp::drawStaticImage() {
    // update background image containing gradient
    float w = ofGetWidth();
    float h = ofGetHeight();

    // ofBackground(205, 175, 149);
    _backgroundColor.set(ofRandom(0.,255.),ofRandom(0.,255.),ofRandom(0.,255.));
    _circleColor.set(ofRandom(0.,255.),ofRandom(0.,255.),ofRandom(0.,255.));

    ofColor res = _circleColor;
    float dist = 0.;
    float ratio = 0.;

    for (float y=0; y<h; y++) {
        for (float x=0; x<w; x++) {
            dist = ofDist(x,y,_center.x,_center.y);
            //
            if( dist > _outerCircleRadius
                    && dist < _outerCircleRadius + _distFromCircle)
            {
                ratio = ofMap(dist,_outerCircleRadius,_outerCircleRadius +_distFromCircle, 0,1.,true);
                res.lerp(_backgroundColor,ratio);
                _img.setColor(x,y,res);
                res = _circleColor;
            }
            else if( dist < _innerCircleRadius
                     && dist > _distFromCircle)
            {
                ratio = ofMap(dist,_distFromCircle,_innerCircleRadius, 0,1.,true);
                res.lerp(_backgroundColor,1.-ratio);
                _img.setColor(x,y,res);
                res = _circleColor;
            }
            else
            {
                _img.setColor(x,y,ofColor(0,0,0,0));
            }
        }
    }

    _img.update();

    _fboStatic.begin();

    ofBackground(_backgroundColor);

    _img.draw(0,0);

    ofNoFill();
    ofSetLineWidth(1.0);
    ofSetColor(255,239,213);

    // inner circle
    ofDrawCircle(_center,_innerCircleRadius);

    // outer circle
    ofDrawCircle(_center,_outerCircleRadius);

    _fboStatic.end();
}

//--------------------------------------------------------------

void ofApp::drawDynamicImage() {

    // draw in fbo
    _fboDynamic.begin();
    ofBackground(_backgroundColor);

    // draw moving circle
    ofNoFill();
    ofSetLineWidth(_lineWidth);
    ofSetColor(_circleColor);

    float circlePos = _innerCircleRadius;// + (_outerCircleRadius - _innerCircleRadius)/_layerNb;

    for(int k = 0; k < _layerNb; k++)
    {
        circle c = _vecCircles[k];
        float rotationSpeed = c._rotationSpeed * _rotateOffset;
        float radius = c._radius;

        if(!_bOverlap)
            circlePos +=  radius;
        else
            circlePos = _innerCircleRadius + (_outerCircleRadius - _innerCircleRadius)/_layerNb + k*(2*radius) ;
        int circleNum = 2 * PI * circlePos / (radius *2.);

        for(int i = 0; i < circleNum; i ++)
        {
            float angle = i * 2 * PI /circleNum + rotationSpeed;
            float x = _center.x + cos(angle) * circlePos ;
            float y =  _center.y + sin(angle) * circlePos ;
            ofDrawCircle(x,y,radius);
        }
        if(!_bOverlap)
            circlePos +=  radius;

    }


    _fboDynamic.end();
}
//--------------------------------------------------------------
void ofApp::update(){
    float fps= ofGetFrameRate();
    ofSetWindowTitle(ofToString(fps) );

    if(_bChangeColor)
    {
        drawStaticImage();
        _bChangeColor = false;
        //_bOverlap = !_bOverlap;
    }
    if(_rotateOffset - _prevRotateOffset > 2.0)
    {
        _prevRotateOffset = _rotateOffset;

        _lineWidth = ofRandom(3.0,7.);

        updateCircles();
    }
    drawDynamicImage();
    _rotateOffset += 0.01;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(205, 175, 149);
    _fboStatic.draw(0,0);
    _fboDynamic.draw(0,0);
}
//--------------------------------------------------------------

void ofApp::updateCircles() {
    _vecCircles.clear();
    _layerNb = 0;

    int widthFilledByCircles = 0;
    int nbCircles = 0;
    while(widthFilledByCircles < _winWidth)//for(int i = 0; i< _layerNb;i++)
    {
        circle c;
        c._rotationSpeed = nbCircles % 2 ==0 ? -1: 1;
        c._radius = ofRandom(1.,_winWidth/30);
        _vecCircles.push_back(c);

        widthFilledByCircles += c._radius *2;
        nbCircles ++;
    }
    _layerNb = nbCircles;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    _bChangeColor = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    _winWidth = w;
    _center.x = w/2;
    _center.y = h/2;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
