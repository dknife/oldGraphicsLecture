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
    // location of camera
    float eye[3];       // camera의 위치
    
    // three important vectors (axes)
    float view[3];     // 시선 벡터
    float up[3];        // 상향 벡터
    float right[3];     // 카메라의 우측 방향 벡터 ( view X up )
    
public:
    CGLCamera();
    
    void SetCamera(     // gluLookAt 처럼 카메라 설정 가능
                   float ex, float ey, float ez,
                   float tx, float ty, float tz,
                   float ux, float uy, float uz);  // view, up, right 계산되어 저장
    
    void ApplyCamera(void);   // 현재 카메라 상태를 오픈지엘로 넘김
    
    void MoveForward(float d);  // MoveBackward??? MoveForward(-alpha)
    void MoveUp(float d);
    void MoveRight(float d);  // 3-DoF으로 이동 가능
    
    void RotateHead  (float angle); // up 벡터를 축으로 angle 회전
    void RotateRoll  (float angle);  // view 벡터를 축으로 angle 회전
    void RotatePitch (float angle); //  right 벡터를 축으로 angle 회전
    
    
    // 보조적인 벡터 연산
private:
    void setVec(float *v, float x, float y, float z);  // v에 (x,y,z) 설정
    void normalize(float *vec3f);  // 특정 벡터 vec3f를 정규화
    void crossProduct(float *v1, float *v2, float *res); // 외적 계산
    
    void Rotate(float *axis, float angleRadian, float *v, float *res); 
    // v를 axis중심으로 angleRadian만큼 회전하여 res에 저장
};

#endif