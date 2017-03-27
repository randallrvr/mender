//******************************************************************************
//read.h************************************************************************
//******************************************************************************

#pragma once

// Third party includes
#include "tinydir.h"

// Standard Library Includes
#include <vector>
#include <string>

namespace render
{
namespace file
{
	static std::vector<std::string> listDir(const char *path = ".", const char *ext = "")
	{
		std::vector<std::string> files;

		const char *localPath = (strlen(path) > 0) ? path : "./";
		tinydir_dir dir;
		size_t i;
		if(tinydir_open_sorted(&dir, localPath) == -1)
		{
			perror("Error opening file");
			return files;
		}

		bool checkExt = (strlen(ext) > 0);
		for (i = 0; i < dir.n_files; i++)
		{
			tinydir_file file;
			if (tinydir_readfile_n(&dir, &file, i) == -1)
			{
				perror("Error getting file");
				return files;
			}

			std::string filename = (file.is_dir) ? "/" : "";
			filename += file.name;
			if(checkExt)
			{
				if(strcmp(file.extension, ext) == 0)
					files.push_back(filename);
			}
			else
				files.push_back(filename);
		}
		return files;
	}

	static bool dirExists(const char *dir)
	{
		tinydir_file file;

		if(tinydir_file_open(&file, dir) != -1)
			return file.is_dir;
		return false;
	}

};	// End namespace render
};	// End namespace file