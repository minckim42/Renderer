#pragma once
#include "../Aniamtor/Animator.hpp"
#include "Controlable.hpp"
#include <Memory>

/*##############################################################################

	World

##############################################################################*/

#define FILE_DRAGON				"../data/dragon/Dragon_Baked_Actions_fbx_7.4_binary.fbx"
#define FILE_GROUND				"../data/ground/ground.obj"
#define FILE_BUILDING_SOLID		"../data/building/sylvan_solid.fbx"
#define FILE_BUILDING_MULLION	"../data/building/sylvan_mullion.fbx"
#define FILE_BUILDING_RAIL		"../data/building/sylvan_rail.fbx"
#define FILE_BUILDING_GROUND	"../data/building/sylvan_ground.fbx"
#define FILE_BUILDING_STIE		"../data/building/sylvan_site.fbx"
#define FILE_BUILDING_FURNITURE	"../data/building/sylvan_furniture.fbx"
#define FILE_BUILDING_GLASS		"../data/building/sylvan_glass.fbx"
#define DISTANCE_SUN			150000000
#define FHD						1920, 1080
#define HD						1280, 720
#define COLOR_SKY				0.71, 0.88, 0.99

class World: public WindowGlfw
{
	/*=========================================
		Type
	=========================================*/
	public:
	typedef std::chrono::system_clock::time_point	TimePoint;
	typedef std::chrono::duration<double>			Duration;
	/*=========================================
		Members
	=========================================*/
	public:
	Controlable			dragon;
	Model::ptr			building;
	TimePoint			time_prev;
	Camera				camera;
	Light				light;
	Shader				shader;
	glm::mat4			mat_identity;


	/*=======================================
		Constructor
	=======================================*/
	public:
	World();

	/*=======================================
		Methods
	=======================================*/
	public:
	bool				work();

};