#define TIXML_USE_STL
#define _CRT_SECURE_NO_WARNINGS

#include "../tinyxml/tinyxml.h"
#include "configuration.h"
#include <windows.h>
#include <gl/gl.h>

Configuration *Configuration::_instance = 0;

Configuration *Configuration::GetInstance()
{
	if (!_instance) _instance = new Configuration();
	return _instance;
}

char *Configuration::ReadFile(const char*filename)
{
	FILE *file = fopen(filename, "rb");
	if (!file) return 0;
	fseek(file, 0, SEEK_END);
	int len = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* buffer = new char[len + 1]; buffer[len] = 0;
	fread(buffer, len, 1, file);
	fclose(file);
	return buffer;
}

void Configuration::ReadReplacers(TiXmlElement *child)
{
	Vendor v = VENDOR_ALL;
	const char *vstr = child->Attribute("Vendor");
	if (vstr)
	{
		string s = vstr;
		for (unsigned i = 0; i < s.size(); i++) if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 'a' - 'A';
		if (s.find("ATI") != string::npos) v = VENDOR_ATI;
		if (s.find("NVIDIA") != string::npos) v = VENDOR_NVIDIA;
	}
	if (child->ValueStr() == "StringReplacer")
	{
		const char *src = child->Attribute("Src"), *dst = child->Attribute("Dst");
		if (src && dst)
			_replacers.push_back(Replacer(src, dst, v));
	}
	else if (child->ValueStr() == "FileReplacer")
	{
		const char *src = child->Attribute("Src"), *dst = child->Attribute("Dst");
		if (src && dst)
		{
			src = ReadFile(src);
			dst = ReadFile(dst);
			if (src && dst)
				_replacers.push_back(Replacer(src, dst, v));
			if (src) delete[] src;
			if (dst) delete[] dst;
		}
	}
}


Configuration::Configuration()
{
	vendor = VENDOR_UNKNOWN;

	char buffer[1000];
	int n = GetModuleFileName(0, buffer, 1000);
	char *exename = buffer;
	for (int i = 0; i < n; i++)
	if (buffer[i] == '\\') exename = buffer + i + 1;

	TiXmlDocument doc("gShaderReplacer.xml");
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		TiXmlElement *root = doc.RootElement();
		int i = 0;
		_dumpAllShaders = (root->QueryIntAttribute("DumpAllShaders", &i) == TIXML_SUCCESS) ? (i ? true : false) : 0;
		_dumpErrorShaders = (root->QueryIntAttribute("DumpErrorShaders", &i) == TIXML_SUCCESS) ? (i ? true : false) : 0;

		TiXmlElement *child = root->FirstChildElement();
		while (child)
		{
			if (child->ValueStr() == "Application")
			{
				bool match = false;
				const char* name = child->Attribute("Name");
				if (name && _strcmpi(exename, name) == 0) match = true;
				for (int j = 0; j < 10; j++)
				{
					const string *s = child->Attribute(string("Name") + char(j + 0x30));
					if (s && _strcmpi(exename, s->c_str()) == 0) match = true;
				}
				if (match)
				{
					TiXmlElement *child2 = child->FirstChildElement();
					while (child2)
					{
						ReadReplacers(child2);
						child2 = child2->NextSiblingElement();
					}
				}
			}
			ReadReplacers(child);
			child = child->NextSiblingElement();
		}
	}
	_buffer = new char[BUFFERSIZE];
	_bufferpos = 0;
}


const char* Configuration::ReplaceShader(int count, const char *const*srcs, const int *lengths)
{
	if (vendor == VENDOR_UNKNOWN)
	{
		vendor = VENDOR_OTHER;
		extern const char* myglGetString(int in);
		const char *vendorstr = myglGetString(GL_VENDOR);
		if (vendorstr)
		{
			string s(vendorstr);
			for (unsigned i = 0; i < s.size(); i++) if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 'a' - 'A';
			if (s.find("ATI") != string::npos) vendor = VENDOR_ATI;
			if (s.find("NVIDIA") != string::npos) vendor = VENDOR_NVIDIA;
		}
	}

	string txt("");
	for (int i = 0; i < count; i++)
	{
		if (lengths == 0 || lengths[i] < 1)
			txt.append(srcs[i]);
		else
			txt.append(srcs[i], lengths[i]);
	}

	for (unsigned i = 0; i < _replacers.size(); i++)
	{
		Replacer &r = _replacers[i];
		if (!(r.vendor == VENDOR_ALL || r.vendor == vendor))
			continue;
		size_t pos = 0;
		int count = 0;
		while ((pos = txt.find(r.src, pos)) != string::npos && count++ < 1000)
		{
			txt.replace(pos, r.src.size(), r.dst);
			pos += r.dst.size();
		}
	}

	int len = txt.size() + 1;
	if (_bufferpos + len >= BUFFERSIZE)
		_bufferpos = 0;
	char *ret = &_buffer[_bufferpos];
	strncpy_s(ret, BUFFERSIZE - _bufferpos, txt.c_str(), len);
	_bufferpos += len;
	return ret;
}
