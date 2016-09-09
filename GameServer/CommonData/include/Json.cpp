#include "Json.h"
#include <assert.h>
#include <stdarg.h>

BufferStream::BufferStream()
{
	InitData();
}

BufferStream::BufferStream(const char* str)
{
	InitDocument(str);
	InitData();
}

BufferStream::BufferStream(std::string& str)
{
	InitDocument(str);
	InitData();
}

BufferStream::~BufferStream()
{

}

/************************************************************************/
/* Writer                                                               */
/************************************************************************/
void BufferStream::Write(std::string key, std::string value)
{
	Write(key.c_str(), value.c_str());
}


void BufferStream::Write(const char *key, const char *value)
{
	m_writer.Key(key);
	m_writer.String(value);
}

void BufferStream::Write(const char *key, int value)
{
	m_writer.Key(key);
	m_writer.Int(value);
}

void BufferStream::Write(const char *key, unsigned int value)
{
	m_writer.Key(key);
	m_writer.Uint(value);
}

void BufferStream::Write(const char *key, double value)
{
	m_writer.Key(key);
	m_writer.Double(value);
}

void BufferStream::Write(const char *key)
{
	m_writer.Key(key);
	m_writer.Null();
}

//template<typename... Types>
//void BufferStream::WriteArray(const char *key, int count, Types ... args)


void BufferStream::WriteObjectStart()
{
	WriteObjectFlag = true;
	m_writer.StartObject();
}

void BufferStream::WriteObjectEnd()
{
	WriteObjectFlag = false;
	m_writer.EndObject();
}

void BufferStream::WriteArrayStart()
{
	WriteArrayFlag = true;
	m_writer.StartArray();
}

void BufferStream::WriteArrayEnd()
{
	WriteArrayFlag = false;
	m_writer.EndArray();
}


/************************************************************************/
/* Reader                                                               */
/************************************************************************/
bool BufferStream::ReadUInt(const char *key, unsigned int &value)
{
	rapidjson::Value &rv = DocumentParse(key);
	if (rv != vEmpty)
	{
		value = rv.GetUint();
		return true;
	}
	else
		return false;
}

bool BufferStream::ReadInt(const char *key, int &value)
{
	rapidjson::Value &rv = DocumentParse(key);
	if (rv != vEmpty)
	{
		value = rv.GetInt();
		return true;
	}
	else
		return false;
}

bool BufferStream::ReadString(const char *key, char *value)
{
	
	rapidjson::Value &rv = DocumentParse(key);
	if (rv != vEmpty)
	{
		memcpy(value, rv.GetString(), rv.GetStringLength());
		return true;
	}
	else
		return false;
}

bool BufferStream::ReadFloat(const char *key, float &value)
{
	rapidjson::Value &rv = DocumentParse(key);
	if (rv != vEmpty)
	{
		value = rv.GetFloat();
		return true;
	}
	else
		return false;
}

bool BufferStream::ReadDouble(const char *key, double &value)
{
	rapidjson::Value &rv = DocumentParse(key);
	if (rv != vEmpty)
	{
		value = rv.GetDouble();
		return true;
	}
	else
		return false;
}

bool BufferStream::ReadArray(const char *key, rapidjson::Value &value)
{
	rapidjson::Value &rv = DocumentParse(key);
	if (rv != vEmpty)
	{
		value = rv;
		return true;
	}
	else
		return false;
}

bool BufferStream::ReadObject(const char *key, rapidjson::Value &value)
{
	rapidjson::Value &rv = DocumentParse(key);
	if (rv != vEmpty)
	{
		value = rv;
		return true;
	}
	else
		return false;
}

/***********************************************************************/
/* Init	                                                               */
/***********************************************************************/

const char* BufferStream::GetJsonString()
{
	if (WriteArrayFlag == true || WriteObjectFlag == true)
		return nullptr;
	if (IsDocRead)
	{
		m_d.Accept(m_writer);
	}
	return m_sBuffer.GetString();
}

void BufferStream::PrintJsonString()
{
	std::cout << "Json字符串:" << GetJsonString() << std::endl;
}

bool BufferStream::IsJsonString(void *buffer)
{
	if (m_d.HasParseError())
	{
		fprintf(stderr, "Schema file '%s' is not a valid JSON\n", (char*)buffer);
		fprintf(stderr, "Error(offset %u): %s\n",
			static_cast<unsigned>(m_d.GetErrorOffset()),
			GetParseError_En(m_d.GetParseError()));
		return false;
	}

	rapidjson::SchemaDocument sd(m_d);

	//将用户的json信息转换为SAX事件转发给验证器
	rapidjson::SchemaValidator validator(sd);
	rapidjson::Reader reader;
	rapidjson::StringStream sb((char*)buffer);
	if (!reader.Parse(sb, validator) && reader.GetParseErrorCode() != rapidjson::kParseErrorTermination)
	{
		fprintf(stderr, "Input is not a valid JSON\n");
		fprintf(stderr, "Error(offset %u): %s\n",
			static_cast<unsigned>(reader.GetErrorOffset()),
			GetParseError_En(reader.GetParseErrorCode()));
		return false;
	}

 	// Check the validation result
   	if (validator.IsValid())
   	{
		//这里通过查找特殊成员page来判断包是否json
		std::string str("/Page");
		rapidjson::Value *value = rapidjson::Pointer(str.c_str()).Get(m_d);
		if (value != nullptr)
		{
			printf("Input JSON is valid.\n");
			return true;
		}
		else
		{
			printf("Input JSON is invalid.\n");
			return false;
		}
   	}
   	else
   	{
   		printf("Input JSON is invalid.\n");
   		rapidjson::StringBuffer sb;
   		validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);
   		fprintf(stderr, "Invalid schema: %s\n", sb.GetString());
   		fprintf(stderr, "Invalid keyword: %s\n", validator.GetInvalidSchemaKeyword());
   		sb.Clear();
   		validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
   		fprintf(stderr, "Invalid document: %s\n", sb.GetString());
   		return false;
   	}

}

void BufferStream::InitData()
{
	WriteObjectFlag = false;
	WriteArrayFlag = false;
	IsDocRead = false;
	m_sBuffer.Clear();
	m_writer.Reset(m_sBuffer);
}	

bool BufferStream::InitDocument(std::string& JsonString)
{
	return InitDocument(JsonString.c_str());
}

bool BufferStream::InitDocument(const char *JsonString)
{
	m_d.Parse(JsonString);
	if (IsJsonString((void*)JsonString))
	{
		IsDocRead = true;
		return true;
	}
	return false;
}

rapidjson::Value& BufferStream::DocumentParse(const char *str)
{
	assert(str);
	rapidjson::ParseErrorCode code = m_d.GetParseError();
	if (!code)
	{
		if (m_d.HasMember(str))
			return m_d[str];
	}
	
	return vEmpty;
}

#ifdef DEBUG
void writeTest()
{
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value root(rapidjson::kObjectType);
	root.AddMember("name", "哥伦布啊", allocator);
	root.AddMember("gold", 1234, allocator);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	root.Accept(writer);
	std::string reststring = buffer.GetString();
	std::cout << reststring << std::endl;
	getchar();
}

void test()
{
	BufferStream ss;
	ss.InitDocument("{\"project\":\"rapidjson\",\"stars\":10}");
	std::cout << ss.GetJsonString() << std::endl;
	// 	BufferStream ss;
	// 	ss.InitDocument("{\"UpdateInfo\":[{\"url\":\"aaaa.ipa\",\"platform\":\"ios\"}]}");
	// 	rapidjson::Value& v = ss.ReadArray("UpdateInfo");

	//BufferStream ss;
	//ss.WriteObjectStart();
	//ss.Write("123", "val");
	//ss.WriteObjectEnd();
	//std::cout << ss.GetJsonString() << std::endl;
	getchar();
}
#endif