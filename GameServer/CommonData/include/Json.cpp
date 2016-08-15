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

void BufferStream::InitData()
{
	WriteObjectFlag = false;
	WriteArrayFlag = false;
	IsDocRead = false;
	m_sBuffer.Clear();
	m_writer.Reset(m_sBuffer);
}	

void BufferStream::InitDocument(std::string& JsonString)
{
	InitDocument(JsonString.c_str());
}

void BufferStream::InitDocument(const char *JsonString)
{
	m_d.Parse(JsonString);
	IsDocRead = true;
}

rapidjson::Value& BufferStream::DocumentParse(const char *str)
{
	assert(str);
	return m_d[str];
}
