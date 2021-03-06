// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

#include <chrono>
#include <ctime>

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <enet/enet.h>
#include <iostream>
#include <source/structure/Chunk.h>
#include <source/structure/Structure.h>

#include "qu3e/q3.h"

#include "source/rendering/RenderedStructure.h"

#include "source/cube.h"

#include "source/structure/Dirty.h"
#include "source/ecs/Ecs.h"

#include <thread>

#include "source/rendering/RenderedStructure.h"
#include "source/rendering/DirtyNeedsRendered.h"
#include "source/rendering/DoingRendering.h"
#include "source/rendering/NeedsOpenGLUpdated.h"

inline Ogre::Vector3 to(const q3::q3Vec3& v)
{
	return {v.x, v.y, v.z};
}

inline Ogre::Quaternion to(const q3::q3Quaternion& q)
{
	return {q.w, q.x, q.y, q.z};
}

inline Ogre::Matrix3 to(const q3::q3Mat3& m)
{
	return {m.ex[0], m.ex[1], m.ex[2], m.ey[0], m.ey[1], m.ey[2], m.ez[0], m.ez[1], m.ez[2] };
}

inline Ogre::Quaternion toQuat(const q3::q3Mat3& m)
{
	return { {m.ex[0], m.ey[0], m.ez[0], m.ex[1], m.ey[1], m.ez[1], m.ex[2], m.ey[2], m.ez[2] } };
}

class MyTestApp : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
private:
	static constexpr size_t MAX_KEY = 256;

public:
	inline static MyTestApp* instance = nullptr;
	
	Cosmos::ECSWorld world;
	
	Ogre::SceneNode *node;
	
	bool keys[MAX_KEY] = {false};
	bool keyBuffer[MAX_KEY] = {false};
	bool keysJustDown[MAX_KEY] = {false};
	
	q3::q3Scene scene;
	
	q3::q3Body *mainBody, *planeBody;
	
	MyTestApp();
	
	void setup() override;
	
	bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
	
	bool keyReleased(const OgreBites::KeyboardEvent &evt) override;
	
	void updateInput();
	
	inline bool keyDown(OgreBites::Keycode key)
	{
		return keys[key];
	}
	
	inline bool keyJustDown(OgreBites::Keycode key)
	{
		return keysJustDown[key];
	}
};

void MyTestApp::updateInput()
{
	for (int i = 0; i < MAX_KEY; i++)
	{
		keysJustDown[i] = keyBuffer[i];
		keyBuffer[i] = false;
	}
}

//! [constructor]
MyTestApp::MyTestApp() : OgreBites::ApplicationContext("OgreTutorialApp"),
						 scene(q3::q3Scene(1/60.0f, {0, -10, 0}, 20)),
						 node(nullptr), world(Cosmos::ECSWorld())
{
	instance = this;
}
//! [constructor]

//! [key_handler]
bool MyTestApp::keyPressed(const OgreBites::KeyboardEvent &evt)
{
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	
	if (evt.keysym.sym < MAX_KEY)
	{
		keyBuffer[evt.keysym.sym] = !keyJustDown(evt.keysym.sym);
		
		keys[evt.keysym.sym] = true;
	}
	
	return true;
}

bool MyTestApp::keyReleased(const OgreBites::KeyboardEvent &evt)
{
	if (evt.keysym.sym < MAX_KEY)
		keys[evt.keysym.sym] = false;
	
	return true;
}



//! [setup]
void MyTestApp::setup(void)
{
	// do not forget to call the base first
	OgreBites::ApplicationContext::setup();
	
	// register for input events
	addInputListener(this);
	
	// get a pointer to the already created root
	Ogre::Root *root = getRoot();
	Ogre::SceneManager *scnMgr = root->createSceneManager();
	
	// register our scene with the RTSS
	Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);
	
	scnMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox", 300);
	
	// without light we would just get a black screen
	Ogre::Light *light = scnMgr->createLight("MainLight");
	Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(0, 10, 2);
	lightNode->attachObject(light);
	
	// also need to tell where we are
	Ogre::SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 0, 0);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	
	// create the camera
	Ogre::Camera *cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(0.01); // specific to this sample
	cam->setFarClipDistance(1000);
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	
	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);
	
	// ADD PHYSICS STUFF
	{
		using namespace q3;
		
		q3::q3BodyDef bdef;
		bdef.position = q3::q3Vec3(0, 10, -20);
		bdef.bodyType = q3::eDynamicBody;
		
		
		q3::q3BodyDef plane;
		plane.position = q3::q3Vec3(2.5f, -10, -20);
		plane.bodyType = q3::eStaticBody;
		
		mainBody = scene.CreateBody(bdef);
		planeBody = scene.CreateBody(plane);
		
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
	}
	
	using namespace Cosmos;
	using namespace Cosmos::Rendering;
	
	Entity* ent = world.createEntity();
	
	auto* structure = new Structure(2, 2, 2, ent);
	
	ent->addComponent(structure);
	ent->addComponent(new RenderedStructure(*scnMgr, *structure));
	
	for(int z = 0; z < structure->blocksLength(); z++)
	{
		for(int y = 0; y < structure->blocksHeight(); y++)
		{
			for(int x = 0; x < structure->blocksWidth(); x++)
			{
				ent->addComponent(new DirtyNeedsRendered(x, y, z));
			}
		}
	}
	
	world.addMutSystem(new MutSystem(
			new HasQuery(DirtyNeedsRendered::STATIC_ID(), new HasQuery(RenderedStructure::STATIC_ID())),
			[](ECSWorld& world, MutQueryIterator itr)
			{
				for(Entity* structureEntity : itr)
				{
					auto* rs = (RenderedStructure*) structureEntity->getFirstComponentMut(RenderedStructure::STATIC_ID());
					
					for(Component* comp : structureEntity->getComponents(DirtyNeedsRendered::STATIC_ID()))
					{
						auto* needsRendered = (DirtyNeedsRendered*)comp;
						
						rs->addPlaceToUpdateNext(needsRendered->chunkX(), needsRendered->chunkY(), needsRendered->chunkZ());
					}
					
					structureEntity->removeAllComponentsWithID(DirtyNeedsRendered::STATIC_ID());
					
					structureEntity->addComponent(new DoingRendering(new std::thread([rs, structureEntity]()
					{
						rs->updateNoGL();
						
						structureEntity->removeAllComponentsWithID(DoingRendering::STATIC_ID());
						
						structureEntity->addComponent(new NeedsOpenGLUpdated());
					})));
				}
			}));
	
	world.addMutSystem(new MutSystem(
			new HasQuery(NeedsOpenGLUpdated::STATIC_ID()),
			[](ECSWorld& world, MutQueryIterator itr)
			{
				for(Entity* entity : itr)
				{
					auto* rs = (RenderedStructure*) entity->getFirstComponentMut(RenderedStructure::STATIC_ID());
					
					rs->updateGL();
					
					if (!rs->isAddedToScene())
					{
						MyTestApp::instance->node = rs->addToScene();
					}
					
					entity->removeAllComponentsWithID(NeedsOpenGLUpdated::STATIC_ID());
				}
			}, true));
	
	world.addMutSystem(new MutSystem(
			new HasQuery(Dirty::STATIC_ID(), new HasQuery(RenderedStructure::STATIC_ID(), new HasQuery(Structure::STATIC_ID()))),
			[](ECSWorld& world, MutQueryIterator itr)
			{
				for(Entity* structureEntity : itr)
				{
					auto* rs = (RenderedStructure*) structureEntity->getFirstComponentMut(RenderedStructure::STATIC_ID());
					
					std::thread([rs]()
					{
						rs->updateNoGL();
					});
				}
			}));
	
	world.addMutSystem(new MutSystem(
			new HasQuery(Dirty::STATIC_ID()),
			[](ECSWorld& world, MutQueryIterator itr)
			{
				for(Entity* ent : itr)
				{
					ent->removeAllComponentsWithID(Dirty::STATIC_ID());
				}
			}));
	
	
	// finally something to render
	
//	rs.updateNoGL();
//	rs.updateGL();
//
//	node = rs.addToScene();
//
//	if(!node)
//	{
//		throw ":(";
//	}

//	man->begin("Examples/OgreLogo", Ogre::RenderOperation::OT_TRIANGLE_LIST);
//
//
//	cube.addBottom(*man,
//				   cube.addTop(*man,
//							   cube.addRight(*man,
//											 cube.addLeft(*man,
//														  cube.addBack(*man,
//																	   cube.addFront(*man, 0))))));
//
//	man->end();
	
	Ogre::ManualObject *man2 = scnMgr->createManualObject("test_obj_2");
	
	man2->begin("Examples/OgreLogo", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	
	Cube cube;
	
	cube.addBottom(*man2,
				   cube.addTop(*man2,
							   cube.addRight(*man2,
											 cube.addLeft(*man2,
														  cube.addBack(*man2,
																	   cube.addFront(*man2, 0, 5, 5, 5), 5, 5, 5), 5, 5, 5), 5, 5, 5), 5, 5, 5), 5, 5, 5);
	man2->end();
	
	scnMgr->getRootSceneNode()->createChildSceneNode(to(planeBody->GetTransform().position),
													 toQuat(planeBody->GetTransform().rotation))->attachObject(man2);
//    node->attachObject(ent);
}

//! [setup]


//int main()
//{
//
//
//	for(int i = 0; i < 200; i++)
//	{
//		scene.Step();
//
//		printf("%f\n", mainBody->GetWorldPoint({}).y);
//	}
//
//	scene.Shutdown();
//}

//#define TESTING

#ifdef TESTING

#include "tests/TestECS.h"

int main()
{
	testMain();
}

#else

int main232323()
{
	using namespace Cosmos;
	
	ECSWorld world;
	
	Entity* structEnt = world.createEntity();
	Entity* e2 = world.createEntity();
	
	e2->addComponent(new Chunk());
	
	structEnt->addComponent(new Chunk());
	
	structEnt->addComponent(new Structure(10, 10, 10, structEnt));
	
	world.addSystem(new ConstSystem(new HasQuery(Chunk::STATIC_ID()), [](const ECSWorld& world, ConstQueryIterator itr)
	{
		printf("SYSTEM RAN\n");
		
		for(const Entity* ent : itr)
		{
			printf("FOUND AN ENTITY\n");
		}
	
//		auto x = entity.getComponents(Chunk::STATIC_ID());
//		printf("%u count\n", (unsigned int) x.size());
//		printf("Found chunks!!\n");
	}));
	
	world.addMutSystem(new MutSystem (new HasQuery(Chunk::STATIC_ID()), [](ECSWorld& world, MutQueryIterator itr)
	{
		for(Entity* x : itr)
		{
			printf("MUT FOUND AN ENTITY\n");
		}
	}));
	
	for(int i = 0; i < 10; i++)
	{
		world.runSystems();
	}
	
	world.destroyEntity(structEnt);
}
#endif


//! [main]
int main(int argc, char *argv[])
{
	MyTestApp app;
	app.initApp();
	
	float ry = 0;
	
	auto last = std::chrono::system_clock::now();
	
	
	while (!app.getRoot()->endRenderingQueued())
	{
		auto now = std::chrono::system_clock::now();
		
		if(now - last < std::chrono::milliseconds(16))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(16) - (now - last));
		}
		
		last = now;
		
		app.pollEvents();
		app.getRoot()->renderOneFrame();
		
		app.world.runSystems();
		
		app.scene.Step();
		
		if(app.node && app.mainBody)
		{
			app.node->setPosition(to(app.mainBody->GetTransform().position));
			app.node->setOrientation(toQuat(app.mainBody->GetTransform().rotation));
		}
//		if (app.keyJustDown('w'))
//		{
////			app.node->setPosition(app.node->getPosition() + Ogre::Vector3(0, 0, 0.1));
//			ry += 0.1;
//			Ogre::Quaternion orien;
//			orien.FromAngleAxis(Ogre::Radian(ry), {1, 0, 0});
//			app.node->setOrientation(orien);
//		}
		
		
		app.updateInput();
	}
	
	app.scene.Shutdown();
	app.closeApp();
	return 0;
}
//! [main]

int main33()
{
	ENetHost* client;
	
	// NULL = client host
	client = enet_host_create(NULL, 1, 8, 0, 0);
	
	if(!client)
	{
		std::cerr << "Unable to create enet client host." << std::endl;
		return EXIT_FAILURE;
	}
	
	
	enet_host_destroy(client);
	
	return 0;
}