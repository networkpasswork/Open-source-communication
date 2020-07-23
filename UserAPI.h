#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winhttp.h>
#include <intrin.h>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>
#pragma comment(lib,"Winhttp.lib")
using namespace std;
#define myxorstr(str) (str)
#define myxorstrw(str) (str)

template<int N, int C>
class MXorString
{
private:
	char key;
	char encrypted[N + 1];
public:
	template<int ...Is>
	constexpr __forceinline MXorString(const char *str, std::index_sequence<Is...>) :key(((N * __TIME__[3] * __TIME__[4] * __TIME__[6] * __TIME__[7]) * (C + 1)) & 0xFF), encrypted{ (str[Is] ^ key)... } {}
	constexpr __forceinline const char *decrypt()
	{
		for (int i = 0; i < N; encrypted[i++] ^= key);
		encrypted[N] = '\0';
		return encrypted;
	}
};
template<int N, int C>
class MXorStringW
{
private:
	wchar_t key;
	wchar_t encrypted[N + 1];
public:
	template<int ...Is>
	constexpr __forceinline MXorStringW(const wchar_t *str, std::index_sequence<Is...>) :key(((N * __TIME__[3] * __TIME__[4] * __TIME__[6] * __TIME__[7]) * (C + 1)) & 0xFF), encrypted{ (wchar_t)(str[Is] ^ key)... } {}
	constexpr __forceinline const wchar_t *decrypt()
	{
		for (int i = 0; i < N; encrypted[i++] ^= key);
		encrypted[N] = '\0';
		return encrypted;
	}
};



struct JsonValue
{
	std::string name;
	std::string value;
	bool IsString;
};

struct RetValue
{
private:
	std::vector<JsonValue> &values;
	std::string name;
public:
	RetValue(std::vector<JsonValue> &v, const char *n) :values(v), name(n) {}

	template<class T>
	T as()
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				T v;
				std::stringstream ss;
				ss << iter->value;
				ss >> v;
				return v;
			}
		}
		return {};
	}

	template<class T>
	void operator=(T v)
	{
		std::stringstream ss;
		ss << v;
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				ss >> iter->value;
				iter->IsString = false;
				return;
			}
		}
		if (!name.empty())
		{
			JsonValue NewValue;
			NewValue.name = name;
			ss >> NewValue.value;
			NewValue.IsString = false;
			values.push_back(NewValue);
		}
	}
	void operator=(char *v)
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				iter->value = v;
				iter->IsString = true;
				return;
			}
		}
		if (!name.empty())
		{
			JsonValue NewValue;
			NewValue.name = name;
			NewValue.value = v;
			NewValue.IsString = true;
			values.push_back(NewValue);
		}
	}
	void operator=(const char *v)
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				iter->value = v;
				iter->IsString = true;
				return;
			}
		}
		if (!name.empty())
		{
			JsonValue NewValue;
			NewValue.name = name;
			NewValue.value = v;
			NewValue.IsString = true;
			values.push_back(NewValue);
		}
	}
	void operator=(const std::string &v)
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				iter->value = v;
				iter->IsString = true;
				return;
			}
		}
		if (!name.empty())
		{
			JsonValue NewValue;
			NewValue.name = name;
			NewValue.value = v;
			NewValue.IsString = true;
			values.push_back(NewValue);
		}
	}

	operator bool()
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				bool v = 0;
				std::stringstream ss;
				ss << iter->value;
				ss >> v;
				return v;
			}
		}
		return 0;
	}
	operator short()
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				short v = 0;
				std::stringstream ss;
				ss << iter->value;
				ss >> v;
				return v;
			}
		}
		return 0;
	}
	operator int()
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				int v = 0;
				std::stringstream ss;
				ss << iter->value;
				ss >> v;
				return v;
			}
		}
		return 0;
	}
	operator __int64()
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				__int64 v = 0;
				std::stringstream ss;
				ss << iter->value;
				ss >> v;
				return v;
			}
		}
		return 0;
	}
	operator float()
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				float v = 0;
				std::stringstream ss;
				ss << iter->value;
				ss >> v;
				return v;
			}
		}
		return 0;
	}
	operator double()
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				double v = 0;
				std::stringstream ss;
				ss << iter->value;
				ss >> v;
				return v;
			}
		}
		return 0;
	}
	operator std::string()
	{
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter->name == name)
			{
				return iter->value;
			}
		}
		return std::string();
	}
};

class CJson
{
private:
	std::vector<JsonValue> values;
public:
	bool parse(const std::string &str)
	{
		if (str.empty() || str[0] != '{' || str[str.length() - 1] != '}') { return false; }
		values.clear();

		JsonValue value; value.IsString = false;
		bool Flags = false;

		for (size_t i = 1; i < str.length(); i++)
		{
			if (str[i] == '\"' && !Flags)
			{
				continue;
			}
			else if (str[i] == ':' && !Flags)
			{
				Flags = true;
				continue;
			}
			else if (str[i] == ',' && str[i + 1] == '\"')
			{
				Flags = false;
				values.push_back(value);
				value.name.clear();
				value.value.clear();
				value.IsString = false;
				continue;
			}
			else if (str[i] == '}' && i == (str.length() - 1))
			{
				Flags = false;
				values.push_back(value);
				value.name.clear();
				value.value.clear();
				value.IsString = false;
				return true;
			}
			if (Flags)
			{
				if (str[i] == '"')
				{
					value.IsString = true;
				}
				else
				{
					value.value.push_back(str[i]);
				}
			}
			else
			{
				value.name.push_back(str[i]);
			}
		}
		return false;
	}
	std::string get()
	{
		std::string data;
		data += '{';
		for (auto iter = values.begin(); iter != values.end(); iter++)
		{
			if (iter != values.begin())
			{
				data += ',';
			}
			data += '"' + iter->name + '"' + ':';
			if (iter->IsString)
			{
				data += '"' + iter->value + '"';
			}
			else
			{
				data += iter->value;
			}
		}
		data += '}';
		return data;
	}

	RetValue operator[](const char *name)
	{
		return RetValue(values, name);
	}
};

struct _HDInfo
{
	int status;
	std::string msg;
	CJson data;
};

class UserAPI
{
private:
	std::string appID;
	std::string safeCode;
	std::string customCode;
	std::string token;
private:
	std::string post(CJson &args);
	_HDInfo RetHandler(const std::string &Responsedata);
public:
	static UserAPI *GetInstance();
	std::string GetExpireTime();
public:
	_HDInfo Login(const char *userName, const char *password);
	_HDInfo Trial();
	_HDInfo UnBind(const char *userName, const char *password);
	_HDInfo Register(const char *userName, const char *password, const char *key = NULL, const char *data = NULL);
	_HDInfo Recharge(const char *userName, const char *key);
	_HDInfo ModifyPassword(const char *userName, const char *oldPassword, const char *password);
	_HDInfo Query(int index, const char *param);
	ULONG64 GetRestTime();
	_HDInfo Initialize(const char *appID, const char *safeCode, const char *customCode);
	_HDInfo Heartbeat();
	_HDInfo TelnetFun(const char *fun, const char *param = NULL);
	_HDInfo Set(int index, const char *value = NULL);
	_HDInfo Get();
	_HDInfo Exit();

	_HDInfo CardLogin(const char *key);
	_HDInfo CardUnBind(const char *key);
};