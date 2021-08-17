#include "ObjLoader.hpp"
#include <iostream>
using namespace std;

/*##############################################################################

	obj Loader

##############################################################################*/

void		ObjLoader::init_obj_key_map()
{
	obj_key_map["g"] = &ObjLoader::parse_g;
	obj_key_map["v"] = &ObjLoader::parse_v;
	obj_key_map["vt"] = &ObjLoader::parse_vt;
	obj_key_map["vn"] = &ObjLoader::parse_vn;
	obj_key_map["f"] = &ObjLoader::parse_f;
	obj_key_map["usemtl"] = &ObjLoader::parse_usemtl;
	obj_key_map["mtllib"] = &ObjLoader::parse_mtllib;
	obj_key_map["#"] = &ObjLoader::parse_comment;
}


ObjLoader::ObjLoader(const string& path):
	ifs(path)
{
	if (!ifs)
		throw string("Failed to open file: ") + path;

	directory = path.substr(0, path.find_last_of('/'));
	
	while (ifs.good())
	{
		getline(ifs, line);
		stringstream	ss(line);
		ss >> key;
		if (obj_key_map.find(key) == obj_key_map.end())
		{
			cout << "obj loader: Unknown key: " << key << endl;
		}
		(this->*obj_key_map[key])();

	}
}

void			ObjLoader::parse_g()
{}
void			ObjLoader::parse_v()
{}
void			ObjLoader::parse_vt()
{}
void			ObjLoader::parse_vn()
{}
void			ObjLoader::parse_f()
{}
void			ObjLoader::parse_usemtl()
{}
void			ObjLoader::parse_mtllib()
{}
void			ObjLoader::parse_comment()
{}

/*##############################################################################

	mtl Loader

##############################################################################*/

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
	mtl_key_map["map_bump"] = &MtlLoader::parse_map_bump;
	mtl_key_map["bump"] = &MtlLoader::parse_bump;
	mtl_key_map["illum"] = &MtlLoader::parse_illum;
	mtl_key_map["#"] = &MtlLoader::parse_comment;
}

void			MtlLoader::parse_none()
{}
void			MtlLoader::parse_newmtl()
{}
void			MtlLoader::parse_ka()
{}
void			MtlLoader::parse_kd()
{}
void			MtlLoader::parse_ks()
{}
void			MtlLoader::parse_tf()
{}
void			MtlLoader::parse_tr()
{}
void			MtlLoader::parse_d()
{}
void			MtlLoader::parse_ns()
{}
void			MtlLoader::parse_ni()
{}
void			MtlLoader::parse_map_ka()
{}
void			MtlLoader::parse_map_kd()
{}
void			MtlLoader::parse_map_ks()
{}
void			MtlLoader::parse_map_bump()
{}
void			MtlLoader::parse_bump()
{}
void			MtlLoader::parse_illum()
{}
void			MtlLoader::parse_comment()
{}