#pragma once
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <map>
#include <stb_image.h>
#include "Material.hpp"
#include "Model.hpp"

/*##############################################################################

	obj Loader

##############################################################################*/

typedef std::unordered_map<std::string, Material>	MaterialContainer;

class ObjLoader
{
	struct GroupTmp
	{
		std::vector<glm::vec3>		positions;
		std::vector<glm::vec3>		normals;
		std::vector<glm::vec2>		tex_coords;
		std::vector<unsigned int>	indices;
		Material*					material;
		std::string					name;
	};

	/*=========================================
		Types
	=========================================*/

	public:


	/*=========================================
		Members
	=========================================*/

	private:
	std::string				directory;
	std::string				line;
	std::string				key;
	std::string				value;
	std::ifstream			ifs;
	std::stringstream		ss;

	std::list<GroupTmp>		list_tmp;
	Model&					model;
	MaterialContainer&		materials;

	std::map<std::string, void (ObjLoader::*)()>	obj_key_map;

	/*=========================================
		Constructor
	=========================================*/

	public:
	ObjLoader(const std::string& path, Model& model, MaterialContainer& materials);
	
	virtual			~ObjLoader()=default;

	/*=========================================
		Methods
	=========================================*/

	private:
	void			init_obj_key_map();
	void			reset_stream();
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
	private:
	std::string			directory;
	std::string			line;
	std::string			key;
	std::string			value;
	std::ifstream		ifs;
	std::stringstream	ss;

	MaterialContainer&		materials;
	Material*				back;
	
	std::map<std::string, void (MtlLoader::*)()>	mtl_key_map;

	/*=========================================
		Constructor
	=========================================*/

	public:
	MtlLoader(const std::string& path, MaterialContainer& materials);

	virtual			~MtlLoader()=default;

	/*=========================================
		Methods
	=========================================*/

	private:
	void			init_mtl_key_map();
	void			parse_newmtl();
	void			reset_stream();
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

/*##############################################################################

	None Member

##############################################################################*/

unsigned int		image_loader(const std::string& path);
void				obj_loader(const std::string& path, Model& model, MaterialContainer& materials);