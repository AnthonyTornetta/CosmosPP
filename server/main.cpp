//
// Created by cornchip on 4/28/22.
//

#include <iostream>

#include <qu3e/q3.h>
#include <chrono>
#include <thread>

int main()
{
	using namespace q3;
	
	q3Scene scene(1 / 60.0f);
	
	q3::q3BodyDef bdef;
	bdef.position = q3::q3Vec3(0, 10, -20);
	bdef.bodyType = q3::eDynamicBody;
	
	q3::q3BodyDef plane;
	plane.position = q3::q3Vec3(2.5, -10, -20);
	plane.bodyType = q3::eStaticBody;
	
	q3Body *mainBody = scene.CreateBody(bdef);
	q3Body *planeBody = scene.CreateBody(plane);
	
	q3::q3BoxDef boxDef;
	q3Transform trans;
	trans.position.Set(0, 0, 0);
	trans.rotation.Set(1, 0, 0, 0, 1, 0, 0, 0, 1);
	boxDef.Set(trans, {1, 1, 1});
	boxDef.SetRestitution(0.1);
	mainBody->AddBox(boxDef);
	
	q3Transform trans2;
	trans2.position.Set(0, 0, 0);
	trans2.rotation.Set(1, 0, 0, 0, 1, 0, 0, 0, 1);
	q3::q3BoxDef planeBox;
	planeBox.Set(trans2, {5, 5, 5});
	planeBox.SetRestitution(0.1);
	planeBody->AddBox(planeBox);
	
	auto last = std::chrono::system_clock::now();
	
	while (true)
	{
		auto now = std::chrono::system_clock::now();
		
		if (now - last < std::chrono::milliseconds(16))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(16) - (now - last));
		}
		
		scene.Step();
		
		std::cout << mainBody->GetTransform().position.x << ", " << mainBody->GetTransform().position.y << ", "
				  << mainBody->GetTransform().position.z << '\n';
		
		last = now;
	}
}