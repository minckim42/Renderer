#pragma once
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <map>
#include "Material.hpp"
#include "Group.hpp"

/*##############################################################################

	obj Loader

##############################################################################*/

class ObjLoader
{
	/*=========================================
		Members
	=========================================*/

	public:
	std::string		directory;
	std::string		line;
	std::string		key;
	std::string		value;
	std::ifstream	ifs;

	std::map<std::string, void (ObjLoader::*)()>	obj_key_map;
	std::vector<std::shared_ptr<Group>>				group;

	/*=========================================
		Constructor
	=========================================*/

	ObjLoader()=default;
	ObjLoader(const std::string& path);
	virtual			~ObjLoader()=default;

	/*=========================================
		Methods
	=========================================*/

	void			init_obj_key_map();
	void			parse_g();
	void			parse_v();
	void			parse_vt();
	void			parse_vn();
	void			parse_f();
	void			parse_usemtl();
	void			parse_mtllib();
	void			parse_comment();
};

/*##############################################################################

	mtl Loader

##############################################################################*/

class MtlLoader
{


	public:
	std::string		directory;
	std::string		line;
	std::string		key;
	std::string		value;
	std::ifstream	ifs;

	std::map<std::string, void (MtlLoader::*)()>	mtl_key_map;
	std::unordered_map<std::string, Material>		material;

	/*=========================================
		Methods
	=========================================*/

	void			init_mtl_key_map();
	void			parse_none();
	void			parse_newmtl();
	void			parse_ka();
	void			parse_kd();
	void			parse_ks();
	void			parse_tf();
	void			parse_tr();
	void			parse_d();
	void			parse_ns();
	void			parse_ni();
	void			parse_map_ka();
	void			parse_map_kd();
	void			parse_map_ks();
	void			parse_map_bump();
	void			parse_bump();
	void			parse_illum();
	void			parse_comment();
};