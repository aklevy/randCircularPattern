#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetCircleResolution(100);
    ofEnableAlphaBlending();
    //ofSetCurveResolution(100);

    // load image to use it as a texture
    _texImage.load("givre.jpg");

    _winWidth = ofGetWindowWidth();
    _center.x = _winWidth/2;
    _center.y = ofGetWindowHeight()/2;

    _fboDynamic.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA,4);


    _innerCircleRadius = 100;
    _outerCircleRadius = ofGetWindowHeight()/3;
    _distFromCircle = 40;

    _lineWidth = 5.;
    updateCircles();


    _backgroundColor = ofColor(ofRandom(0.,255.),ofRandom(0.,255.),ofRandom(0.,255.));
    _shapeColor = ofColor(ofRandom(0.,255.),ofRandom(0.,255.),ofRandom(0.,255.));

    // drawDynamicImage();
}
//--------------------------------------------------------------

void ofApp::drawShape(shapeType t, int x, int y, float radius){

    if(t == SHAPE_CIRCLE)
        drawCircle(x,y,radius);
    else if(t == SHAPE_TRIANGLE)
    {
        drawTriangle(x,y,radius);
    }
}
//--------------------------------------------------------------

void ofApp::drawTriangle( int x, int y, float radius){
    ofPushStyle();
    float brightness = _shapeColor.getBrightness();
    ofColor darkerShapeColor = _shapeColor;
    darkerShapeColor.setBrightness(brightness*0.5);
    // darkerShapeColor = ofColor::aliceBlue;

    ofSetColor(darkerShapeColor);

    glLineWidth(5);//_lineWidth);
    glBegin(GL_TRIANGLES);
    for(int ii = 0; ii < 3; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / 3;//get the current angle

        float xx = x +radius * cos(theta);//calculate the x component
        float yy = y + radius * sin(theta);//calculate the y component

        glVertex2f((int)xx, (int)yy);//output vertex

    }
    glEnd();
    ofPopStyle();

}

//--------------------------------------------------------------

void ofApp::drawCircle( int x, int y, float radius){
    ofNoFill();
    ofSetLineWidth(_lineWidth);
    ofDrawCircle(x,y,radius);

    float innerFilledCircleRadius = radius * 0.3;
    ofFill();
    ofDrawCircle(x,y,innerFilledCircleRadius);

}
//--------------------------------------------------------------

void ofApp::drawDynamicImage() {

    // draw in fbo
    _fboDynamic.begin();
    ofBackground(_backgroundColor);

    // draw moving circle
    //ofNoFill();
    // ofSetLineWidth(10);//_lineWidth);
    ofSetColor(_shapeColor);
    float shapePos = _innerCircleRadius;// + (_outerCircleRadius - _innerCircleRadius)/_layerNb;
    for(int k = 0; k < _layerNb; k++)
    {
        shape c = _vecCircles[k];
        float rotationSpeed = c._rotationSpeed * _rotateOffset;
        float radius = c._radius;
        if(!_bOverlap)
            shapePos +=  radius;
        else
            shapePos = _innerCircleRadius + (_outerCircleRadius - _innerCircleRadius)/_layerNb + k*(2*radius) ;
        int circleNum = 2 * PI * shapePos / (radius *2.);

        for(int i = 0; i < circleNum; i ++)
        {
            float angle = i * 2 * PI /circleNum + rotationSpeed;
            float x = _center.x + cos(angle) * shapePos ;
            float y =  _center.y + sin(angle) * shapePos ;

            drawShape(c._shapeType,x,y,radius);

            //  ofDrawCircle(x,y,radius);
        }
        if(!_bOverlap)
            shapePos +=  radius;

    }


    _fboDynamic.end();
}
//--------------------------------------------------------------
void ofApp::update(){
    float fps= ofGetFrameRate();
    ofSetWindowTitle(ofToString(fps) );

    if(_bChangeColor)
    {
        _backgroundColor.set(ofRandom(0.,255.),ofRandom(0.,255.),ofRandom(0.,255.));
        _shapeColor.set(ofRandom(0.,255.),ofRandom(0.,255.),ofRandom(0.,255.));

        _bChangeColor = false;
        //_bOverlap = !_bOverlap;
    }
    if(_rotateOffset - _prevRotateOffset > 2.0)
    {
        _prevRotateOffset = _rotateOffset;

        _lineWidth = ofRandom(3.0,7.);

        if(!_bStopGenerating)
            updateCircles();
    }
    drawDynamicImage();
    if(!_bStopRotation)_rotateOffset += 0.01;
}

//--------------------------------------------------------------
void ofApp::draw(){
    _fboDynamic.draw(0,0);
    // ofNoFill();
    // ofDrawCircle(_center,100);
    /*  ofBackground(0);
    ofSetColor(255);
    float x = _center.x;
    float y = _center.y;
    float radius = 100;
    int resolution = 100;
    ofEnableAntiAliasing();
    glLineWidth(15);//_lineWidth);
    //glPointSize(10);
    // glEnable(GL_POINT_SMOOTH);
    glBegin(GL_LINE_LOOP);//POINT);
    glEnable( GL_LINE_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
//    glBegin(GL_POINTS);
//    glEnable(GL_POINT_SMOOTH);
    for(int ii = 0; ii < resolution; ii++)
    {
        float theta = 2.0f * PI * float(ii) / float(resolution);//get the current angle

        float xx = x +radius * cosf(theta);//calculate the x component
        float yy = y + radius * sinf(theta);//calculate the y component

        glVertex2f((int)xx, (int)yy);//output vertex

    }


    glEnd();
    /*   ofBackground(0);
    glEnable(GL_DEPTH_TEST);

        //Tells OpenGL not to draw backfaces
        //Backfaces are defined by vertex drawing order
        //By default couter-clockwise drawing order specifies front faces
        //Note: The circle is drawn counter-clockwise
        //Note: It is not necessary to enable this for a simple 2D circle
        //but is good practice
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

    int M_IN_DEGREE = 370;
    int N_IN_DEGREE = 100;
    int nCount = 1;
    float stVertexArray[2*360];
    float radius = 100;
    stVertexArray[0] = _center.x;
    stVertexArray[1] = _center.y;
    int resolution = 50;
   // for( int nR =N_IN_DEGREE; nR < M_IN_DEGREE; nR++ )
    for(int ii = 0; ii < resolution; ii++)
    {
        float theta = 2.0f * PI * float(ii) / float(resolution);//get the current angle
//    {
        float fX = sin(theta) ;
        float fY = cos(theta );
        stVertexArray[nCount*2] = radius * fX + _center.x;
        stVertexArray[nCount*2 + 1] = radius * fY+ _center.y;
        nCount++;
    }
   // ofSetColor(255);
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, stVertexArray );
    glDrawArrays( GL_LINE_LOOP, 0, nCount );
*/
    //ofBackground(205, 175, 149);

    //drawDynamicImage();
    // _fboDynamic.draw(0,0);
}
//--------------------------------------------------------------

void ofApp::updateCircles() {
    _vecCircles.clear();
    _layerNb = 0;

    int widthFilledByCircles = 0;
    int nbCircles = 0;
    float maxRadius = _winWidth/30;
    while(widthFilledByCircles < (_outerCircleRadius - maxRadius))//for(int i = 0; i< _layerNb;i++)
    {
        shape c;
        c._rotationSpeed = nbCircles % 2 ==0 ? -1: 1;
        c._radius = ofRandom(1.,maxRadius);
        c._shapeType = ofRandom(1.,3) >1.5? SHAPE_CIRCLE : SHAPE_TRIANGLE;

        _vecCircles.push_back(c);

        widthFilledByCircles += c._radius *2;
        nbCircles ++;
    }
    _layerNb = nbCircles;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c')
        _bChangeColor = true;
    else if(key == 'd')
        _bDrawSeparation = !_bDrawSeparation;
    else if(key == ' ')
        _bStopGenerating = !_bStopGenerating;
    else if(key == 's')
    {
        // save screen to image
        ofImage img;
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());

        // check if an image with the same exists or not
        // if it exists, change name until a new file can be created without overwriting an old img
        string nameImg = "OF_randCircularPattern_"+ofToString(_countImg)+".png";
        ofFile f(nameImg);
        while(f.exists())
        {
            _countImg++;
            f.close();
            nameImg = "OF_randCircularPattern_"+ofToString(_countImg)+".png";
            f.open(nameImg);
        }
        //  ofSaveImage(p,nameImg);
        img.save(nameImg);
        //_countImg ++;
    }
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
    _bStopRotation = !_bStopRotation;
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
