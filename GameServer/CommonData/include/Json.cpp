#include "Json.h"
#include <assert.h>

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
unsigned int BufferStream::ReadUInt(std::string& key)
{

	return DocumentParse(key.c_str()).GetUint();
}

int BufferStream::ReadInt(std::string& key)
{
	return DocumentParse(key.c_str()).GetInt();
}

const char* BufferStream::ReadString(std::string& key)
{
	
	return DocumentParse(key.c_str()).GetString();
}

float BufferStream::ReadFloat(std::string& key)
{
	return DocumentParse(key.c_str()).GetFloat();
}

double BufferStream::ReadDouble(std::string& key)
{
	return DocumentParse(key.c_str()).GetDouble();
}

rapidjson::Value& BufferStream::ReadArray(std::string& key)
{
	rapidjson::Value &array = DocumentParse(key.c_str());
	return array;
}

rapidjson::Value & BufferStream::ReadObject(std::string& key)
{
	rapidjson::Value& object = DocumentParse(key.c_str());
	return object;
}

unsigned int BufferStream::ReadUInt(const char *key)
{

	return DocumentParse(key).GetUint();
}

int BufferStream::ReadInt(const char *key)
{
	return DocumentParse(key).GetInt();
}

const char* BufferStream::ReadString(const char *key)
{

	return DocumentParse(key).GetString();
}

float BufferStream::ReadFloat(const char *key)
{
	return DocumentParse(key).GetFloat();
}

double BufferStream::ReadDouble(const char *key)
{
	return DocumentParse(key).GetDouble();
}

rapidjson::Value& BufferStream::ReadArray(const char *key)
{
	rapidjson::Value &array = DocumentParse(key);
	return array;
}

rapidjson::Value & BufferStream::ReadObject(const char *key)
{
	rapidjson::Value& object = DocumentParse(key);
	return object;
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
		//不清楚这里错误的json都可以通过,打个小补丁
		std::string str = "/" + std::string((char*)buffer);

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
