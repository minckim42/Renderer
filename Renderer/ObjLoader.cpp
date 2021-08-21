#include "ObjLoader.hpp"
#include <iostream>
using namespace std;
using namespace glm;

void				put_coord(std::istream& is, std::vector<glm::vec3>& container);
void				put_coord(std::istream& is, std::vector<glm::vec2>& container);
void				put_coord(std::istream& is, glm::vec3& target);
void				put_coord(std::istream& is, glm::vec2& target);

/*##############################################################################

	obj Loader

##############################################################################*/

ObjLoader::ObjLoader(const string& path, Model& model, MaterialContainer& materials):
	model(model),
	materials(materials),
	ifs(path)
{
	if (!ifs)
		throw string("Failed to open file: ") + path;

	directory = path.substr(0, path.find_last_of('/'));

	init_obj_key_map();

	while (ifs.good())
	{
		getline(ifs, line);
		ss.str(line);
		ss >> key;
		if (key.empty() || obj_key_map.find(key) == obj_key_map.end())
		{
			if (!key.empty())
				cout << "obj loader: Unknown key: [" << key << "]\n";
			reset_stream();
			continue;
		}
		(this->*obj_key_map[key])();
		reset_stream();
	}

	for (GroupTmp& tmp: list_tmp)
	{
		model.add_child(Mesh(tmp.positions, tmp.normals, tmp.tex_coords, tmp.indices, tmp.material));
	}
}

//------------------------------------------------------------------------------

void		ObjLoader::init_obj_key_map()
{
	obj_key_map["g"] = &ObjLoader::parse_g;
	obj_key_map["o"] = &ObjLoader::parse_g;
	obj_key_map["v"] = &ObjLoader::parse_v;
	obj_key_map["vt"] = &ObjLoader::parse_vt;
	obj_key_map["vn"] = &ObjLoader::parse_vn;
	obj_key_map["f"] = &ObjLoader::parse_f;
	obj_key_map["usemtl"] = &ObjLoader::parse_usemtl;
	obj_key_map["mtllib"] = &ObjLoader::parse_mtllib;
	obj_key_map["#"] = &ObjLoader::parse_comment;
}

//------------------------------------------------------------------------------

void			ObjLoader::reset_stream()
{
	line.clear();
	key.clear();
	value.clear();
	ss.str("");
	ss.clear();
}

//------------------------------------------------------------------------------

void			ObjLoader::parse_g()
{
	ss >> value;
	list_tmp.emplace_back();
	list_tmp.back().name = value;
}

//------------------------------------------------------------------------------

void			ObjLoader::parse_v()
{
	put_coord(ss, list_tmp.back().positions);
}

//------------------------------------------------------------------------------

void			ObjLoader::parse_vt()
{
	put_coord(ss, list_tmp.back().tex_coords);
}

//------------------------------------------------------------------------------

void			ObjLoader::parse_vn()
{
	put_coord(ss, list_tmp.back().normals);
}

//------------------------------------------------------------------------------

void			ObjLoader::parse_f()
{
	unsigned int	idx[3];
	string			base;
	for (int i = 0 ; i < 3 ; i++)
	{
		ss >> base;
		stringstream	base_stream(base);
		base_stream >> idx[i];
		base.clear();
		list_tmp.back().indices.emplace_back(idx[i] - 1);
	}
}

//------------------------------------------------------------------------------

void			ObjLoader::parse_usemtl()
{
	ss >> value;
	if (materials.find(value) == materials.end())
	{
		cout << "Material not fount: " << value << endl;
	}
	list_tmp.back().material = &materials[value];
}

//------------------------------------------------------------------------------

void			ObjLoader::parse_mtllib()
{
	ss >> value;
	MtlLoader	loader(directory + '/' + value, materials);
}

//------------------------------------------------------------------------------

void			ObjLoader::parse_comment()
{}

/*##############################################################################

	mtl Loader

##############################################################################*/

MtlLoader::MtlLoader(const string& path, std::unordered_map<std::string, Material>& materials):
	ifs(path),
	materials(materials)
{
	if (!ifs)
		throw string("Failed to open file: ") + path;

	directory = path.substr(0, path.find_last_of('/'));
	
	init_mtl_key_map();

	while (ifs.good())
	{
		getline(ifs, line);
		ss.str(line);
		ss >> key;
		if (key.empty() || mtl_key_map.find(key) == mtl_key_map.end())
		{
			if (!key.empty())
				cout << "mtl loader: Unknown key: [" << key << "]\n";
			key.clear();
			continue;
		}
		(this->*mtl_key_map[key])();
		line.clear();
		key.clear();
		value.clear();
		ss.str("");
		ss.clear();
	}
}

//------------------------------------------------------------------------------

void		MtlLoader::init_mtl_key_map()
{
	mtl_key_map["newmtl"] = &MtlLoader::parse_newmtl;
	mtl_key_map["Ka"] = &MtlLoader::parse_ka;
	mtl_key_map["Kd"] = &MtlLoader::parse_kd;
	mtl_key_map["Ks"] = &MtlLoader::parse_ks;
	mtl_key_map["Tf"] = &MtlLoader::parse_tf;
	mtl_key_map["Tr"] = &MtlLoader::parse_tr;
	mtl_key_map["d"] = &MtlLoader::parse_d;
	mtl_key_map["Ns"] = &MtlLoader::parse_ns;
	mtl_key_map["Ni"] = &MtlLoader::parse_ni;
	mtl_key_map["map_Ka"] = &MtlLoader::parse_map_ka;
	mtl_key_map["map_Kd"] = &MtlLoader::parse_map_kd;
	mtl_key_map["map_Ks"] = &MtlLoader::parse_map_ks;
	mtl_key_map["map_Bump"] = &MtlLoader::parse_map_bump;
	mtl_key_map["bump"] = &MtlLoader::parse_bump;
	mtl_key_map["illum"] = &MtlLoader::parse_illum;
	mtl_key_map["#"] = &MtlLoader::parse_comment;
}

//------------------------------------------------------------------------------

void			MtlLoader::reset_stream()
{
	line.clear();
	key.clear();
	value.clear();
	ss.str("");
	ss.clear();
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_newmtl()
{
	ss >> value;
	if (materials.find(value) != materials.end())
		return;
	materials[value] = Material(value);
	back = &materials[value];
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_ka()
{
	put_coord(ss, back->param.ka);
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_kd()
{
	put_coord(ss, back->param.kd);
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_ks()
{
	put_coord(ss, back->param.ks);
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_tf()
{
	put_coord(ss, back->param.tf);
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_tr()
{
	ss >> back->param.d;
	back->param.d = 1 - back->param.d;
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_d()
{
	ss >> back->param.d;
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_ns()
{
	ss >> back->param.ns;
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_ni()
{
	ss >> back->param.ni;
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_map_ka()
{
	ss >> value;
	back->map_ka = image_loader(directory + '/' + value);
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_map_kd()
{
	ss >> value;
	back->map_kd = image_loader(directory + '/' + value);
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_map_ks()
{
	ss >> value;
	back->map_ks = image_loader(directory + '/' + value);
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_map_bump()
{
	ss >> value;
	back->map_bump = image_loader(directory + '/' + value);
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_bump()
{
	parse_map_bump();
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_illum()
{
	ss >>  back->illum;
}

//------------------------------------------------------------------------------

void			MtlLoader::parse_comment()
{}

//------------------------------------------------------------------------------


/*##############################################################################

	None Member

##############################################################################*/

void				put_coord(istream& is, vector<vec3>& container)
{
	vec3	v;
	is >> v[0] >> v[1] >> v[2];
	container.emplace_back(v[0], -v[2], v[1]);
}

//------------------------------------------------------------------------------

void				put_coord(istream& is, vector<vec2>& container)
{
	vec2	v;
	is >> v[0] >> v[1];
	container.emplace_back(v);
}

//------------------------------------------------------------------------------

void				put_coord(std::istream& is, glm::vec3& target)
{
	is >> target[0] >> target[1] >> target[2];
}

//------------------------------------------------------------------------------

void				put_coord(std::istream& is, glm::vec2& target)
{
	is >> target[0] >> target[1];
}

//------------------------------------------------------------------------------

unsigned int		image_loader(const std::string& path)
{
	unsigned int	image_id;

	glGenTextures(1, &image_id);
	glBindTexture(GL_TEXTURE_2D, image_id);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	stbi_set_flip_vertically_on_load(true);

	int				width, height, nr_channel;
	unsigned char*	data = stbi_load(path.c_str(), &width, &height, &nr_channel, 0);

	if (!data)
	{
		throw string("Failed to load image file: ") + path;
	}
	unsigned int	format[5] = {0, GL_RED, 0, GL_RGB, GL_RGBA};
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		format[nr_channel], 
		width, 
		height, 
		0, 
		format[nr_channel], 
		GL_UNSIGNED_BYTE, 
		data
	);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return image_id;
}

void			obj_loader(const string& path, Model& model, MaterialContainer& materials)
{
	ObjLoader	tmp(path, model, materials);
}