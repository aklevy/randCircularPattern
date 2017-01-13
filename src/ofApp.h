#pragma once

#include "ofMain.h"

enum shapeType{SHAPE_TRIANGLE,SHAPE_CIRCLE,SHAPE_RECTANGLE};

struct shape{
    enum shapeType _shapeType;
    float _radius;
    float _rotationSpeed;
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void drawDynamicImage();

    void update();
    void updateCircles();
    void drawShape(shapeType t, int x, int y, float radius);
    void drawTriangle(int x, int y, float radius);

    void drawCircle(int x, int y, float radius);
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
    ofImage _texImage;
    float _winWidth;
    ofPoint _center;
    ofFbo   _fboDynamic;

    ofColor     _backgroundColor;
    ofColor     _shapeColor;

    float _innerCircleRadius;
    float _outerCircleRadius;
    float _distFromCircle;

    float _rotateOffset = 0;
    float _lineWidth;
    int _layerNb;

    float _prevRotateOffset= 0;
    std::vector<shape> _vecCircles;

    bool    _bChangeColor = false;
    bool    _bDrawSeparation = false;

    bool    _bOverlap = true;
    bool    _bStopRotation = false;
    bool    _bStopGenerating = false;

    int     _countImg = 0;


};
