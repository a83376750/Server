#include <iostream>
#include <string>

#include "../ThirdLibrary/rapidjson/allocators.h"
#include "../ThirdLibrary/rapidjson/writer.h"
#include "../ThirdLibrary/rapidjson/stringbuffer.h"
#include "../ThirdLibrary/rapidjson/document.h"

namespace rapidjson
{
	void rapidjsonTest()
	{
		const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
		std::cout << "Before:" << json << std::endl;
		Document d;
		d.Parse(json);

		Value& s = d["stars"];
		s.SetInt(s.GetInt() + 1);
		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);
		std::cout << "After:" << buffer.GetString() << std::endl;

		Value& project = d["project"];
		std::string str = project.GetString();
		std::cout << "Project:" << str << std::endl;
	}




}