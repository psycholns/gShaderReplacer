#pragma once
#include <string>
#include <vector>

using namespace std;


enum Vendor { VENDOR_UNKNOWN = 0, VENDOR_ATI, VENDOR_NVIDIA, VENDOR_OTHER, VENDOR_ALL };
struct Replacer
{
	Replacer(string s, string d, Vendor v) : src(s), dst(d), vendor(v)	 {}
	string src, dst;
	Vendor vendor;
};

class TiXmlElement;

class Configuration
{
public:
	static Configuration *GetInstance();

	const char* ReplaceShader(int count, const char *const*srcs, const int *lengths);
	bool _dumpAllShaders, _dumpErrorShaders;

private:
	Configuration();
	static Configuration *_instance;

	vector<Replacer> _replacers;

	char *ReadFile(const char*filename);
	void Configuration::ReadReplacers(TiXmlElement *child);

	static const int BUFFERSIZE = 300000;
	char* _buffer;
	int _bufferpos;
	Vendor vendor;
};
