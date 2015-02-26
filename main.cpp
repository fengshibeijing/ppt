#include "./include/sharpnow.hpp"
#include <iostream>
#include <Windows.h>
#pragma comment(lib,"user32.lib")

sharpnow::SDK sdk;
class Ppt
{
private:

public:
	void Left()	{
		keybd_event(33,0,0,0);
		keybd_event(33,KEYEVENTF_KEYUP,0,0);
	}
	void right(){
		keybd_event(34,0,0,0);
		keybd_event(34,KEYEVENTF_KEYUP,0,0);

	}

};
int main(int argc, char** argv){
	Ppt p;
	// 加载动态链接库
	if (!sdk.LoadInPath("../lib")) return -1;

	std::cout << "等待设备连接 ... " << std::endl;
	bool connected[] = { false, false };
	while (true){
		for (int device = 0; device < 2; ++device){
			if (sdk.RetrieveFrame(device))	{
				// 检测是否为新连接设备
				if (!connected[device])	{
					//std::cout << "检测到微动 " << device << " 连接" << std::endl;
					//std::cout << "伸出单指可控制屏幕光标移动" << std::endl;
					connected[device] = true;
				}
				// 确认收到最新数据
				const sharpnow::Frame* frame = sdk.GetFrameInfo();
				if (!frame->updated) continue;

				const sharpnow::Hand* hand=sdk.GetHandFocus();
				const sharpnow::Finger* finger = sdk.GetFingerFocus();
				if (finger)	{
					float x=finger->position.x;
					if (finger->velocity.x>=0.8&&finger->position==100) {p.Left();std::cout<<1;}
					if (finger->velocity.x<=-0.058&&finger->position==-100)p.right();						

				}


			}

			else{
				// 检测设备断开
				if (connected[device])	{
					std::cout << "检测到微动 " << device << " 断开" << std::endl;
					connected[device] = false;
				}
				continue;
			}
		}
		::Sleep(1);
	}

	return 0;
	system("pause");

}