#ifndef __CAMERA_H__YMK
#define __CAMERA_H__YMK

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <math.h>

class CGLCamera {
    float eye[3];
    float view[3];
    float up[3];
    float right[3];
    
public:
    CGLCamera();
    void SetCamera(
                   float ex, float ey, float ez,
                   float tx, float ty, float tz,
                   float ux, float uy, float uz);
    
    void ApplyCamera(void);
    
    void MoveForward(float d);
    void MoveUp(float d);
    void MoveRight(float d);
    void RotateHead  (float angle);
    void RotateRoll  (float angle);
    void RotatePitch (float angle);
    
    void setVec(float *v, float x, float y, float z);
    void normalize(float *vec3f);
    void crossProduct(float *v1, float *v2, float *res);
    void Rotate(float *axis, float angleRadian, float *v, float *res);
};

#endif