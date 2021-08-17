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
	struct GroupTmp
	{
		std::vector<glm::vec3>		positions;
		std::vector<glm::vec3>		normals;
		std::vector<glm::vec3>		tex_coords;
		std::vector<unsigned int>	indices;
		std::string					name;
	};

	/*=========================================
		Members
	=========================================*/

	public:
	std::string			directory;
	std::string			line;
	std::string			key;
	std::string			value;
	std::ifstream		ifs;
	std::stringstream	ss;

	std::map<std::string, void (ObjLoader::*)()>	obj_key_map;
	std::list<GroupTmp>								tmp;
	std::vector<std::shared_ptr<Group>>&			container;
	std::unordered_map<std::string, Material>&		materials;

	/*=========================================
		Constructor
	=========================================*/

	public:
	ObjLoader(
		const std::string& path, 
		std::vector<std::shared_ptr<Group>>& container, 
		std::unordered_map<std::string, Material>& materials
	);
	
	virtual			~ObjLoader()=default;

	/*=========================================
		Methods
	=========================================*/

	public:
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
	std::string			directory;
	std::string			line;
	std::string			key;
	std::string			value;
	std::ifstream		ifs;
	std::stringstream	ss;

	std::map<std::string, void (MtlLoader::*)()>	mtl_key_map;
	std::unordered_map<std::string, Material>&		container;
	Material*										back;

	/*=========================================
		Constructor
	=========================================*/

	public:
	MtlLoader(const std::string& path, std::unordered_map<std::string, Material>& container);

	virtual			~MtlLoader()=default;

	/*=========================================
		Methods
	=========================================*/

	public:
	void			init_mtl_key_map();
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

/*##############################################################################

	None Member

##############################################################################*/

void				put_coord(std::istream& is, std::vector<glm::vec3>& container);
void				put_coord(std::istream& is, std::vector<glm::vec2>& container);
void				put_coord(std::istream& is, glm::vec3& target);
void				put_coord(std::istream& is, glm::vec2& target);
unsigned int		image_loader(const std::string& path);