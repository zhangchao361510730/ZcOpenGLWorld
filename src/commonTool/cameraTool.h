#ifndef cameraTool_H_
#define cameraTool_H_


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class cameraTool
{
private:
    /* data */
public:
    cameraTool(/* args */);
    ~cameraTool();
};




#endif