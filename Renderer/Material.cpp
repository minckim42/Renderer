#include "Material.hpp"

using namespace std;
using namespace glm;

/*##############################################################################

	Material

##############################################################################*/

Material::Material(const string& name):
param({ 
	{1, 1, 1},	// ka
	{1, 1, 1},	// kd
	{1, 1, 1},	// ks
	{1, 1, 1},	// tf
	1.0f, 		// d
	60.0f, 		// ns
	1.0f 		// ni
}),
map_ka(0),
map_ks(0),
map_kd(0),
map_bump(0),
illum(0),
name(name)
{}