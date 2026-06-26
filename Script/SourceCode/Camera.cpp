#include "Camera.h"

VECTOR Camera::CAM_POS;
VECTOR Camera::CAM_TARGET;

Camera::Camera()
	:GameObject(Tag::SYSTEM)
{
	position3 = CAM_POS;
	target = CAM_TARGET;
}

Camera::~Camera()
{}

void Camera::Update()
{
	//デバッグ　カメラ確認用
	if (Input::IsKeepKeyDown(KEY_INPUT_1))position3.x += 0.05;
	if (Input::IsKeepKeyDown(KEY_INPUT_2))position3.x -= 0.05;
	if (Input::IsKeepKeyDown(KEY_INPUT_3))position3.y += 0.05;
	if (Input::IsKeepKeyDown(KEY_INPUT_4))position3.y -= 0.05;
	if (Input::IsKeepKeyDown(KEY_INPUT_5))position3.z += 0.05;
	if (Input::IsKeepKeyDown(KEY_INPUT_6))position3.z -= 0.05;
	if (Input::IsKeepKeyDown(KEY_INPUT_7))position3 = CAM_POS;

	SetCameraPositionAndTarget_UpVecY(position3,target);
	SetCameraNearFar(0.1f, 1000.0f);
}
