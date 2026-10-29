enum ECharEncoding
{
CE_US_ASCII,
CE_UTF_8,
CE_UTF_16,
CE_ISO_8859_1,
CE_Unkown,
CE_NoSet,
};
class CCharEncoding
{
public:
static ECharEncoding ParseEncoding(char* szEncodingString);
};
class CXMLProlog
{
protected:
ECharEncoding meEncoding;
bool mbStandalone;
float mfVersion;
public:
void Init(void);
void Kill(void);
void SetEncoding(ECharEncoding eEncoding);
void SetStandalone(bool bStandalone);
void SetVersion(float fVersion);
};
void CXMLProlog::Init(void)
{
meEncoding = CE_NoSet;
mbStandalone = true;
mfVersion = -1;
}
void CXMLProlog::Kill(void)
{
meEncoding = CE_NoSet;
mbStandalone = true;
mfVersion = 0;
}
void CXMLProlog::SetEncoding(ECharEncoding eEncoding) { meEncoding = eEncoding; }
void CXMLProlog::SetStandalone(bool bStandalone) { mbStandalone = bStandalone; }
void CXMLProlog::SetVersion(float fVersion) { mfVersion = fVersion; }
