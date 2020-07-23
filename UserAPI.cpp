#include "UserAPI.h"

typedef struct
{
	unsigned int count[2];
	unsigned int state[4];
	unsigned char buffer[64];
}MD5_CTX;

#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) \
          { \
          a += F(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define GG(a,b,c,d,x,s,ac) \
          { \
          a += G(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define HH(a,b,c,d,x,s,ac) \
          { \
          a += H(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define II(a,b,c,d,x,s,ac) \
          { \
          a += I(b,c,d) + x + ac; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }                                            

void MD5Init(MD5_CTX *context)
{
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xEFCDAB89;
	context->state[2] = 0x98BADCFE;
	context->state[3] = 0x10325476;
}
void MD5Encode(unsigned char *output, unsigned int *input, unsigned int len)
{
	unsigned int i = 0, j = 0;
	while (j < len)
	{
		output[j] = input[i] & 0xFF;
		output[j + 1] = (input[i] >> 8) & 0xFF;
		output[j + 2] = (input[i] >> 16) & 0xFF;
		output[j + 3] = (input[i] >> 24) & 0xFF;
		i++;
		j += 4;
	}
}
void MD5Decode(unsigned int *output, unsigned char *input, unsigned int len)
{
	unsigned int i = 0, j = 0;
	while (j < len)
	{
		output[i] = (input[j]) |
			(input[j + 1] << 8) |
			(input[j + 2] << 16) |
			(input[j + 3] << 24);
		i++;
		j += 4;
	}
}
void MD5Transform(unsigned int state[4], unsigned char block[64])
{
	unsigned int a = state[0];
	unsigned int b = state[1];
	unsigned int c = state[2];
	unsigned int d = state[3];
	unsigned int x[64];
	MD5Decode(x, block, 64);
	FF(a, b, c, d, x[0], 7, 0xd76aa478); /* 1 */
	FF(d, a, b, c, x[1], 12, 0xe8c7b756); /* 2 */
	FF(c, d, a, b, x[2], 17, 0x242070db); /* 3 */
	FF(b, c, d, a, x[3], 22, 0xc1bdceee); /* 4 */
	FF(a, b, c, d, x[4], 7, 0xf57c0faf); /* 5 */
	FF(d, a, b, c, x[5], 12, 0x4787c62a); /* 6 */
	FF(c, d, a, b, x[6], 17, 0xa8304613); /* 7 */
	FF(b, c, d, a, x[7], 22, 0xfd469501); /* 8 */
	FF(a, b, c, d, x[8], 7, 0x698098d8); /* 9 */
	FF(d, a, b, c, x[9], 12, 0x8b44f7af); /* 10 */
	FF(c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
	FF(b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
	FF(a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
	FF(d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
	FF(c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
	FF(b, c, d, a, x[15], 22, 0x49b40821); /* 16 */

	/* Round 2 */
	GG(a, b, c, d, x[1], 5, 0xf61e2562); /* 17 */
	GG(d, a, b, c, x[6], 9, 0xc040b340); /* 18 */
	GG(c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
	GG(b, c, d, a, x[0], 20, 0xe9b6c7aa); /* 20 */
	GG(a, b, c, d, x[5], 5, 0xd62f105d); /* 21 */
	GG(d, a, b, c, x[10], 9, 0x2441453); /* 22 */
	GG(c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
	GG(b, c, d, a, x[4], 20, 0xe7d3fbc8); /* 24 */
	GG(a, b, c, d, x[9], 5, 0x21e1cde6); /* 25 */
	GG(d, a, b, c, x[14], 9, 0xc33707d6); /* 26 */
	GG(c, d, a, b, x[3], 14, 0xf4d50d87); /* 27 */
	GG(b, c, d, a, x[8], 20, 0x455a14ed); /* 28 */
	GG(a, b, c, d, x[13], 5, 0xa9e3e905); /* 29 */
	GG(d, a, b, c, x[2], 9, 0xfcefa3f8); /* 30 */
	GG(c, d, a, b, x[7], 14, 0x676f02d9); /* 31 */
	GG(b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */

	/* Round 3 */
	HH(a, b, c, d, x[5], 4, 0xfffa3942); /* 33 */
	HH(d, a, b, c, x[8], 11, 0x8771f681); /* 34 */
	HH(c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
	HH(b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
	HH(a, b, c, d, x[1], 4, 0xa4beea44); /* 37 */
	HH(d, a, b, c, x[4], 11, 0x4bdecfa9); /* 38 */
	HH(c, d, a, b, x[7], 16, 0xf6bb4b60); /* 39 */
	HH(b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
	HH(a, b, c, d, x[13], 4, 0x289b7ec6); /* 41 */
	HH(d, a, b, c, x[0], 11, 0xeaa127fa); /* 42 */
	HH(c, d, a, b, x[3], 16, 0xd4ef3085); /* 43 */
	HH(b, c, d, a, x[6], 23, 0x4881d05); /* 44 */
	HH(a, b, c, d, x[9], 4, 0xd9d4d039); /* 45 */
	HH(d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
	HH(c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
	HH(b, c, d, a, x[2], 23, 0xc4ac5665); /* 48 */

	/* Round 4 */
	II(a, b, c, d, x[0], 6, 0xf4292244); /* 49 */
	II(d, a, b, c, x[7], 10, 0x432aff97); /* 50 */
	II(c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
	II(b, c, d, a, x[5], 21, 0xfc93a039); /* 52 */
	II(a, b, c, d, x[12], 6, 0x655b59c3); /* 53 */
	II(d, a, b, c, x[3], 10, 0x8f0ccc92); /* 54 */
	II(c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
	II(b, c, d, a, x[1], 21, 0x85845dd1); /* 56 */
	II(a, b, c, d, x[8], 6, 0x6fa87e4f); /* 57 */
	II(d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
	II(c, d, a, b, x[6], 15, 0xa3014314); /* 59 */
	II(b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
	II(a, b, c, d, x[4], 6, 0xf7537e82); /* 61 */
	II(d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
	II(c, d, a, b, x[2], 15, 0x2ad7d2bb); /* 63 */
	II(b, c, d, a, x[9], 21, 0xeb86d391); /* 64 */
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}
void MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputlen)
{
	unsigned int i = 0, index = 0, partlen = 0;
	index = (context->count[0] >> 3) & 0x3F;
	partlen = 64 - index;
	context->count[0] += inputlen << 3;
	if (context->count[0] < (inputlen << 3))
		context->count[1]++;
	context->count[1] += inputlen >> 29;

	if (inputlen >= partlen)
	{
		memcpy(&context->buffer[index], input, partlen);
		MD5Transform(context->state, context->buffer);
		for (i = partlen; i + 64 <= inputlen; i += 64)
			MD5Transform(context->state, &input[i]);
		index = 0;
	}
	else
	{
		i = 0;
	}
	memcpy(&context->buffer[index], &input[i], inputlen - i);
}
void MD5Final(MD5_CTX *context, unsigned char digest[16])
{
	unsigned char PADDING[] = { 0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	unsigned int index = 0, padlen = 0;
	unsigned char bits[8];
	index = (context->count[0] >> 3) & 0x3F;
	padlen = (index < 56) ? (56 - index) : (120 - index);
	MD5Encode(bits, context->count, 8);
	MD5Update(context, PADDING, padlen);
	MD5Update(context, bits, 8);
	MD5Encode(digest, context->state, 16);
}

std::string RC4Enc(const std::string &data, const std::string &key)
{
	if (data.empty() || key.empty()) { return std::string(); }

	unsigned char m[256];
	unsigned char k[256];

	for (int i = 0; i < 256; m[i++] = i);

	if (!key.empty())
	{
		for (int i = 0, j = 0; i < 256; i++)
		{
			k[i] = key[j++];
			if (j >= (int)key.length()) { j = 0; }
		}

		for (int i = 0, j = 0; i < 256; i++)
		{
			j = (j + m[i] + k[i]) & 0xFF;
			unsigned char temp = m[i];
			m[i] = m[j];
			m[j] = temp;
		}
	}

	std::string encrypted;
	const char *table = myxorstrw("0123456789ABCDEF");
	for (int i = 0, j = 0, x = 0; x < (int)data.length(); x++)
	{
		i = (i + 1) & 0xFF;
		j = (j + m[i]) & 0xFF;
		unsigned char temp = m[i];
		m[i] = m[j];
		m[j] = temp;
		temp = data[x] ^ m[(m[i] + m[j]) & 0xFF];
		encrypted += table[temp >> 4];
		encrypted += table[temp & 0xF];
	}
	return encrypted;
}
std::string RC4Dec(const std::string &data, const std::string &key)
{
	if (data.empty() || key.empty()) { return std::string(); }

	unsigned char m[256];
	unsigned char k[256];

	for (int i = 0; i < 256; m[i++] = i);

	if (!key.empty())
	{
		for (int i = 0, j = 0; i < 256; i++)
		{
			k[i] = key[j++];
			if (j >= (int)key.length()) { j = 0; }
		}

		for (int i = 0, j = 0; i < 256; i++)
		{
			j = (j + m[i] + k[i]) & 0xFF;
			unsigned char temp = m[i];
			m[i] = m[j];
			m[j] = temp;
		}
	}

	std::string decrypted;
	for (int i = 0, j = 0, x = 0; x < (int)data.length() / 2; x++)
	{
		i = (i + 1) & 0xFF;
		j = (j + m[i]) & 0xFF;
		unsigned char temp = m[i];
		m[i] = m[j];
		m[j] = temp;

		temp = 0;
		int idx = x * 2;
		if (data[idx] >= '0' && data[idx] <= '9')
			temp |= (data[idx] - '0') << 4;
		else if (data[idx] >= 'A' && data[idx] <= 'F')
			temp |= (data[idx] - 55) << 4;
		if (data[idx + 1] >= '0' && data[idx + 1] <= '9')
			temp |= data[idx + 1] - '0';
		else if (data[idx + 1] >= 'A' && data[idx + 1] <= 'F')
			temp |= data[idx + 1] - 55;

		decrypted += temp ^ m[(m[i] + m[j]) & 0xFF];
	}
	return decrypted;
}

UserAPI *UserAPI::GetInstance()
{
	static UserAPI *p;
	if (!p)
	{
		p = new UserAPI();
	}
	return p;
}

std::string UserAPI::post(CJson &json)
{
	HINTERNET hSession = 0, hConnect = 0, hRequest = 0;
	std::string Buffer;

	if (WinHttpCheckPlatform())
	{
		hSession = WinHttpOpen(myxorstrw(L"Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1)"), WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, NULL);
		if (hSession)
		{
			WinHttpSetTimeouts(hSession, 3000, 3000, 3000, 3000);

			hConnect = WinHttpConnect(hSession, myxorstrw(L"1.5yyz.com"), 80, NULL);
			if (hConnect)
			{
				hRequest = WinHttpOpenRequest(hConnect, myxorstrw(L"POST"), myxorstrw(L"/UserApi?"), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, NULL);
				if (hRequest)
				{
					int cpu_name[12];
					__cpuid(cpu_name, 0x80000002);
					__cpuid(cpu_name + 4, 0x80000003);
					__cpuid(cpu_name + 8, 0x80000004);
					json[myxorstrw("machineCode")] = (char*)cpu_name;

					std::string Enced = RC4Enc(json.get(), safeCode);

					std::string timestamp = std::to_string((time_t)(time(NULL) * 1000));

					std::string sign;
					sign += appID;
					sign += safeCode;
					sign += timestamp;
					sign += Enced;

					BYTE decrypt[16];
					MD5_CTX md5;
					MD5Init(&md5);
					MD5Update(&md5, (PBYTE)sign.c_str(), (DWORD)sign.length());
					MD5Final(&md5, decrypt);

					sign.clear();
					const char *table = myxorstrw("0123456789abcdef");
					for (int i = 0; i < 16; i++)
					{
						sign += table[decrypt[i] >> 4];
						sign += table[decrypt[i] & 0xF];
					}

					std::string data;
					data += myxorstrw("appid=") + appID;
					data += myxorstrw("&timestamp=") + timestamp;
					data += myxorstrw("&data=") + Enced;
					data += myxorstrw("&sign=") + sign;
					if (!token.empty())
					{
						data += myxorstrw("&token=") + token;
					}

					WinHttpAddRequestHeaders(hRequest, myxorstrw(L"Accept: */*"), -1, WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);
					WinHttpAddRequestHeaders(hRequest, myxorstrw(L"Referer: http://c1.5yyz.com/UserApi?"), -1, WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);
					WinHttpAddRequestHeaders(hRequest, myxorstrw(L"Accept-Language: zh-cn"), -1, WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);
					WinHttpAddRequestHeaders(hRequest, myxorstrw(L"Content-Type: application/x-www-form-urlencoded; charset=GBK"), -1, WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);
					WinHttpAddRequestHeaders(hRequest, myxorstrw(L"Cache-Control: no-cache"), -1, WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);

					if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, -1, (LPVOID)data.c_str(), (DWORD)data.length(), (DWORD)data.length(), NULL))
					{
						if (WinHttpReceiveResponse(hRequest, NULL))
						{
							char temp[1024];
							DWORD NumOfRead = 0;
							while (WinHttpReadData(hRequest, temp, sizeof(temp), &NumOfRead) && NumOfRead)
							{
								Buffer.append(temp, NumOfRead);
							}
							if (!Buffer.empty())
							{
								int len = MultiByteToWideChar(CP_UTF8, NULL, Buffer.c_str(), -1, NULL, NULL);
								if (len > 0)
								{
									wchar_t *wbuf = new wchar_t[len];
									if (wbuf)
									{
										MultiByteToWideChar(CP_UTF8, NULL, Buffer.c_str(), -1, wbuf, len);
										len = WideCharToMultiByte(CP_ACP, NULL, wbuf, -1, NULL, NULL, NULL, NULL);
										if (len > 0)
										{
											char *buf = new char[len];
											if (buf)
											{
												WideCharToMultiByte(CP_ACP, NULL, wbuf, -1, buf, len, NULL, NULL);
												Buffer = buf;
												delete[] buf;
											}
										}
										delete[] wbuf;
									}
								}
							}
						}
					}
				}
			}
		}
		if (hSession) { WinHttpCloseHandle(hSession); }
		if (hConnect) { WinHttpCloseHandle(hConnect); }
		if (hRequest) { WinHttpCloseHandle(hRequest); }
	}
	return Buffer;
}
_HDInfo UserAPI::RetHandler(const std::string &Responsedata)
{
	
	_HDInfo HDInfo;
	if (HDInfo.data.parse(Responsedata))
	{
		HDInfo.status = HDInfo.data[myxorstr("status")];
		std::string msgs = HDInfo.data[myxorstrw("msg")];
		HDInfo.msg = msgs;
		HDInfo.data.parse(RC4Dec(HDInfo.data[myxorstr("data")], customCode));
	}
	return HDInfo;
}
ULONG64  UserAPI::GetRestTime()
{
	__int64 expireTime = 0;
	_HDInfo Info = Get();
	if (Info.status == 1)
	{
		if ((int)Info.data[myxorstrw("code")] == 1)
		{
			expireTime = (__int64)Info.data[myxorstrw("expireTime")] / 1000;
		}
	}
	return expireTime;
}
std::string UserAPI::GetExpireTime()
{
	_HDInfo Info = Get();
	if (Info.status == 1)
	{
		if ((int)Info.data[myxorstrw("code")] == 1)
		{
			__int64 expireTime = (__int64)Info.data[myxorstrw("expireTime")] / 1000;
			int day = (int)(expireTime / 86400);
			int hour = (expireTime % 86400) / 3600;
			int min = ((expireTime % 86400) % 3600) / 60;
			int sec = (((expireTime % 86400) % 3600) % 60);

			std::string str;
			str += std::to_string(day) + myxorstrw("Ìì");
			str += std::to_string(hour) + myxorstrw("Ê±");
			str += std::to_string(min) + myxorstrw("·Ö");
			str += std::to_string(sec) + myxorstrw("Ãë");
			return str;
		}
	}
	return std::string();
}

_HDInfo UserAPI::Login(const char *userName, const char *password)
{
	CJson args;
	args[myxorstrw("api")] = 1;
	args[myxorstrw("userName")] = userName;
	args[myxorstrw("password")] = password;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::Trial()
{
	CJson args;
	args[myxorstrw("api")] = 2;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::UnBind(const char *userName, const char *password)
{
	CJson args;
	args[myxorstrw("api")] = 3;
	args[myxorstrw("userName")] = userName;
	args[myxorstrw("password")] = password;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::Register(const char *userName, const char *password, const char *key, const char *data)
{
	CJson args;
	args[myxorstrw("api")] = 4;
	args[myxorstrw("userName")] = userName;
	args[myxorstrw("password")] = password;
	if (key)
	{
		args[myxorstrw("key")] = key;
	}
	if (data)
	{
		args[myxorstrw("data")] = data;
	}

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::Recharge(const char *userName, const char *key)
{
	CJson args;
	args[myxorstrw("api")] = 5;
	args[myxorstrw("userName")] = userName;
	args[myxorstrw("key")] = key;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::ModifyPassword(const char *userName, const char *oldPassword, const char *password)
{
	CJson args;
	args[myxorstrw("api")] = 6;
	args[myxorstrw("userName")] = userName;
	args[myxorstrw("oldPassword")] = oldPassword;
	args[myxorstrw("password")] = password;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::Query(int index, const char *param)
{
	CJson args;
	args[myxorstrw("api")] = 7;
	args[myxorstrw("index")] = index;
	args[myxorstrw("param")] = param;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}

_HDInfo UserAPI::Initialize(const char *appID, const char *safeCode, const char *customCode)
{
	this->appID = appID;
	this->safeCode = safeCode;
	this->customCode = customCode;

	CJson args;
	args[myxorstrw("api")] = 10;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	CJson jso;
	if (jso.parse(Responsedata))
	{		
		std::string to = jso[myxorstrw("token")];//token
		token = to;
	}

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::Heartbeat()
{
	CJson args;
	args[myxorstrw("api")] = 12;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::TelnetFun(const char *fun, const char *param)
{
	CJson args;
	args[myxorstrw("api")] = 13;
	args[myxorstrw("fun")] = fun;
	if (param)
	{
		args[myxorstrw("param")] = param;
	}

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::Set(int index, const char *value)
{
	CJson args;
	args[myxorstrw("api")] = 14;
	args[myxorstrw("index")] = index;
	if (value)
	{
		args[myxorstrw("value")] = value;
	}

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::Get()
{
	CJson args;
	args[myxorstrw("api")] = 15;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::Exit()
{
	CJson args;
	args[myxorstrw("api")] = 16;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}

_HDInfo UserAPI::CardLogin(const char *key)
{
	CJson args;
	args[myxorstrw("api")] = 20;
	args[myxorstrw("key")] = key;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}
_HDInfo UserAPI::CardUnBind(const char *key)
{
	CJson args;
	args[myxorstrw("api")] = 21;
	args[myxorstrw("key")] = key;

	std::string Responsedata = post(args);
	if (Responsedata.empty()) { return _HDInfo(); }

	return RetHandler(Responsedata);
}