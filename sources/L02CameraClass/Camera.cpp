#include "Camera.h"

CGLCamera::CGLCamera() {
    eye[0]=0;eye[1]=0;eye[2]=1;
    
    view[0]=0;view[1]=0;view[2]=-1;
    
    up[0]=0;up[1]=1;up[2]=0;
    
    right[0]=1;right[1]=0;right[2]=0;
}

void CGLCamera::SetCamera(
                          float ex, float ey, float ez,
                          float tx, float ty, float tz,
                          float ux, float uy, float uz) {
    
    eye[0]=ex; eye[1]=ey; eye[2]=ez;
    setVec(view, tx-ex, ty-ey, tz-ez);
    normalize(view);
    setVec(up, ux, uy, uz);
    crossProduct(view,up,right);
    normalize(right);
    crossProduct(right,view,up);
}

void CGLCamera::ApplyCamera(void) {
    gluLookAt(eye[0],eye[1],eye[2],
              eye[0]+view[0], eye[1]+view[1], eye[2]+view[2],
              up[0], up[1], up[2]);
}

void CGLCamera::MoveForward (float d) {
    eye[0] += view[0]*d;
    eye[1] += view[1]*d;
    eye[2] += view[2]*d;
}
void CGLCamera::MoveUp(float d) {
    eye[0] += up[0]*d;
    eye[1] += up[1]*d;
    eye[2] += up[2]*d;
}

void CGLCamera::MoveRight(float d) {
    eye[0] += right[0]*d;
    eye[1] += right[1]*d;
    eye[2] += right[2]*d;
}

void CGLCamera::RotateHead  (float angle) {
    float temp[3];
    Rotate(up, angle, view, temp);
    normalize(temp);
    setVec(view, temp[0], temp[1], temp[2]);
    crossProduct(view,up,right);
}

void CGLCamera::RotateRoll  (float angle) {
    float temp[3];
    Rotate(view, angle, right, temp);
    normalize(temp);
    setVec(right, temp[0], temp[1], temp[2]);
    crossProduct(right,view,up);
}

void CGLCamera::RotatePitch  (float angle) {
    float temp[3];
    Rotate(right, angle, view, temp);
    normalize(temp);
    setVec(view, temp[0], temp[1], temp[2]);
    crossProduct(right,view,up);
    
}

void CGLCamera::setVec(float *v, float x, float y, float z) {
    v[0]=x; v[1]=y; v[2]=z;
}

void CGLCamera::normalize(float *vec3f) {
    float d=(vec3f[0]*vec3f[0]+vec3f[1]*vec3f[1]+vec3f[2]*vec3f[2]);
    for(int i=0;i<3;i++) vec3f[i]/=d;
}

void CGLCamera::crossProduct(float *v1, float *v2, float *res) {
    res[0] = v1[1]*v2[2]-v1[2]*v2[1];
    res[1] = v1[2]*v2[0]-v1[0]*v2[2];
    res[2] = v1[0]*v2[1]-v1[1]*v2[0];
}

void CGLCamera::Rotate(float *axis, float angleRadian, float *v, float *res) {
    normalize(axis);
    float w = cos(angleRadian/2.0);
    
    float s = sin(angleRadian/2.0);
    float x = s*axis[0];
    float y = s*axis[1];
    float z = s*axis[2];
    
    float m00 = 1-2*y*y-2*z*z;
    float m01 = 2*x*y-2*w*z;
    float m02 = 2*x*z+2*w*y;
    float m10 = 2*x*y+2*w*z;
    float m11 = 1-2*x*x-2*z*z;
    float m12 = 2*y*z-2*w*x;
    float m20 = 2*x*z-2*w*y;
    float m21 = 2*y*z+2*w*x;
    float m22 = 1-2*x*x-2*y*y;
    
    res[0] = m00*v[0]+m01*v[1]+m02*v[2];
    res[1] = m10*v[0]+m11*v[1]+m12*v[2];
    res[2] = m20*v[0]+m21*v[1]+m22*v[2];
}