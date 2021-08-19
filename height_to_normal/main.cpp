#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <fstream>

using namespace			std;
using namespace			glm;
typedef unsigned char	uint8;

class Image
{

public:
	int				width;
	int				height;
	int				format;
	uint8* data;

	Image(const string& path) : data(0)
	{
		open_file(path);
	}

	~Image()
	{
		if (data)
			stbi_image_free(data);
	}


	void	open_file(const string& path)
	{
		data = stbi_load(path.c_str(), &width, &height, &format, 0);
		if (!data)
			throw string("Failed to open file") + path;
	}

	inline
	uint8*	get_xy(int x, int y)
	{
		return data + (y * width + x) * format;
	}
};

class Height_map
{
public:
	int		width;
	int		height;
	float* data;

	Height_map(Image& img) : data(0)
	{
		set_data(img);
	}

	~Height_map()
	{
		if (data)
			delete[] data;
	}

	inline
	float&	get_xy(int x, int y)
	{
		return data[y * width + x];
	}

	float	color_to_height(uint8* pixel, int format)
	{
		float	h = 0;
		for (int i = 0; i < format; i++)
		{
			h += pixel[i];
		}
		return h / (format * 256);
	}

	void	set_data(Image& img)
	{
		width = img.width;
		height = img.height;
		data = new float[width * height];
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				get_xy(x, y) = color_to_height(img.get_xy(x, height - y - 1), img.format);
			}
		}
	}
};

class Normal_map
{
public:
	int		width;
	int		height;
	vec3* data;

	Normal_map(Height_map& hmap) : data(0)
	{
		set_data(hmap);
	}

	~Normal_map()
	{
		if (data)
			delete[] data;
	}

	inline
	vec3&		get_xy(int x, int y)
	{
		return data[y * width + x];
	}

	void		set_data(Height_map& hmap)
	{
		width = hmap.width;
		height = hmap.height;
		data = new vec3[width * height];
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				get_xy(x, y) = vec3(y, x, hmap.get_xy(x, y));
			}
		}

		for (int y = 0; y < height - 1; y++)
		{
			for (int x = 0; x < width - 1; x++)
			{
				vec3	u = get_xy(x, y + 1) - get_xy(x, y);
				vec3	v = get_xy(x + 1, y) - get_xy(x, y);

				get_xy(x, y) = normalize(cross(u, v));
			}
		}

		for (int x = 0; x < width; x++)
		{
			get_xy(x, height - 1) = vec3(0, 0, 1);
		}

		for (int y = 0; y < height; y++)
		{
			get_xy(width - 1, y) = vec3(0, 0, 1);
		}
	}

	void		to_bmp(const string& name)
	{
		uint8* output = new uint8[width * height * 3];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				uint8* p = output + (y * width + x) * 3;
				p[2] = (get_xy(x, y)[0] + 1) * 127.5;
				p[1] = (get_xy(x, y)[1] + 1) * 127.5;
				p[0] = (get_xy(x, y)[2] + 1) * 127.5;
				// p[0] = 0xff;
				// p[1] = 0x00;
				// p[2] = 0x00;
			}
		}

		ofstream		os(name, ios::out | ios::binary);

		char			header[512];
		int				header_size = 40;
		int				data_offset = 14 + header_size;
		int				img_size = width * height * 3;
		int				file_size = data_offset + img_size;
		int				color_plane = 1;
		int				bit_per_pixel = 24;
		int				n_color = 1 << 24;

		memset(header, 0, 512);

		memcpy(header, "BM", 2);
		memcpy(header + 2, &file_size, 4);
		memcpy(header + 10, &data_offset, 4);
		memcpy(header + 14, &header_size, 4);
		memcpy(header + 18, &width, 4);
		memcpy(header + 22, &height, 4);
		memcpy(header + 26, &color_plane, 2);
		memcpy(header + 28, &bit_per_pixel, 2);
		memcpy(header + 34, &img_size, 2);
		memcpy(header + 46, &n_color, 4);


		os.write(header, data_offset);
		os.write((char*)output, img_size);
		cout << img_size << endl;
		os.close();
		delete[] output;
	}

private:

};

int			main(int argc, char** argv)
{
	Image		img("../Renderer/box/img_height.png");
	Height_map	hmap(img);
	Normal_map	nmap(hmap);
	nmap.to_bmp("../Renderer/box/img_normal.bmp");


	//string		path = "img_normal.bmp";
	//ifstream	ifs(path, ios::binary);

	//if (ifs.is_open() == false)
	//	throw string("Failed to open file");
	//char	buffer[18];

	//ifs.read(buffer, 18);
	//unsigned int	file_size = *reinterpret_cast<int*>(buffer + 2);
	//unsigned int	data_offset = *reinterpret_cast<int*>(buffer + 10);
	//unsigned int	header_size = *reinterpret_cast<int*>(buffer + 14);

	//char* header = new char[data_offset - 18];
	//ifs.read(header, data_offset - 18);

	//unsigned int	width;
	//unsigned int	height;
	//unsigned int	pixel_size;
	//unsigned int	data_size;
	//if (header_size == 40)
	//{
	//	width = *reinterpret_cast<int*>(header);
	//	height = *reinterpret_cast<int*>(header + 4);
	//	pixel_size = *reinterpret_cast<int*>(header + 10) / 8;
	//	data_size = *reinterpret_cast<int*>(header + 16);
	//}
	//else
	//{
	//	throw string("Invalid header size");
	//}
	//delete[] header;

	//cout << file_size << endl;
	//cout << data_offset << endl;
	//cout << header_size << endl;

}