    #ifndef CAMERA_H
#define CAMERA_H

#include "MyVector3.h"
#include "LightRay.h"
#include "MatrixOperations.h"
#include "Constants.h"

class Camera {
public:
	Camera() {
		screenWidth = constWidth;
		screenHeight = constHeight;
	}
public:
	float3 pos;
	int screenWidth;
	int screenHeight;
	int screenDistance;
	float3 screenVector;
private:
	float3 rightVector;
	float3 upVector;
	float3 leftDownPos;

public:
	Ray GetRay(const float w, const float h) const
	{
		Ray ray;
		ray.pos = rightVector*w + upVector*h + leftDownPos;
		ray.dir = ray.pos - pos;
		ray.dir.Normalize();
		return ray;
	}
		
	void Init() 
	{
		pos -= screenVector.Normalize()*screenDistance;
        float3 startVector = float3(-1,0,0);
		float angleX,angleZ, angleY;
        angleX = 0;
        angleZ = 0;
        angleY = 0;
		float angle[3];

        angleZ = GetAngle(startVector,screenVector,2);
        RotateZ(startVector,angleZ);

        /*angleY = GetAngle(startVector,screenVector,1);
        RotateZ(startVector,angleY);

        angleX= GetAngle(startVector,screenVector,0);
        RotateX(startVector,angleX);*/

        //angle[3] = GetAngle(startVector,screenVector,1);

        angle[0] = angleX;
        angle[1] = angleY;
        angle[2] = angleZ;

		float3 vecLeftUp = GetStandartScreenVector(0, screenHeight);
		float3 vecLeftDown = GetStandartScreenVector(0,0);
		float3 vecRightUp = GetStandartScreenVector(screenWidth,screenHeight);
		float3 vecRightDown = GetStandartScreenVector(screenWidth,0);
		
        Rotate(vecLeftUp, angle);
        Rotate(vecLeftDown, angle);
        Rotate(vecRightUp, angle);
        Rotate(vecRightDown, angle);

        /*if (fabs(vecLeftDown[2] - vecLeftUp[2]) < 0.1)
        {
            float3 temp = vecLeftDown;
            vecLeftDown = vecLeftUp;
            vecLeftUp = temp;
            temp = vecRightUp;
            vecRightUp = vecRightDown;
            vecRightDown = temp;
        }*/

		leftDownPos = pos + vecLeftDown;
		rightVector = (vecRightUp - vecLeftUp) / screenWidth;
		upVector = (vecLeftUp - vecLeftDown) / screenHeight;
	}

private:

	float3 GetStandartCenterPosition() {
        return float3(0,(int)((screenWidth-1)/2) , (int)((screenHeight-1)/2));
	}

	float3 GetStandartScreenVector(const int x, const int y) 
	{
		float3 myPos = GetStandartCenterPosition();
		float3 result;
        result.values[0] =  -screenDistance;
        result.values[1] = x - myPos[1];
        result.values[2] = y - myPos[2];
		return result;
	}

};

#endif
