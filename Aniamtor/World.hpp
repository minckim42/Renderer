// #include "Controlable.hpp"
// #include "AssimpLoader.hpp"
// #include "Shader.hpp"
// #include "Camera.hpp"
// #include <Memory>

// /*##############################################################################

// 	World

// ##############################################################################*/

// class World
// {
// 	/*=========================================
// 		Type
// 	=========================================*/
// 	public:
// 	typedef std::chrono::system_clock::time_point	TimePoint;
// 	typedef std::chrono::duration<double>			Duration;
// 	/*=========================================
// 		Members
// 	=========================================*/
// 	public:
// 	Object::ptr		dragon;
// 	Object::ptr		building;
// 	TimePoint		time_prev;
// 	Camera			camera;


// 	/*=======================================
// 		Constructor
// 	=======================================*/
// 	public:
// 	World();

// 	/*=======================================
// 		Methods
// 	=======================================*/
// 	public:
// 	void			draw();
// 	void			key_process();
// 	void			update_camera();

// };