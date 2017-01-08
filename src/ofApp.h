#pragma once

#include "ofMain.h"

struct circle{
    float _radius;
    float _rotationSpeed;
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void drawDynamicImage();

    void update();
    void updateCircles();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    float _winWidth;
    ofPoint _center;
    ofImage _img;
    ofFbo   _fboDynamic;

    float _innerCircleRadius;
    float _outerCircleRadius;
    float _distFromCircle;

    float _rotateOffset = 0;
    float _lineWidth;
    int _layerNb;

    float _prevRotateOffset= 0;
    std::vector<circle> _vecCircles;

    bool    _bChangeColor = false;
    bool    _bOverlap = true;
    ofColor     _backgroundColor;
    ofColor     _circleColor;
};
