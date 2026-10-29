class CFontCreationParameters
{
public:
bool mbLeftToRightFirst;
int miSpaceWidth;
int miAscent;
int miDescent;
public:
void Init(int iCharWidth, int iCharHeight);
void Init(bool bLeftToRightFirst, int iSpaceWidth, int iAscent, int iDescent);
};
void CFontCreationParameters::Init(int iCharWidth, int iCharHeight)
{
Init(true, iCharWidth, iCharHeight, 0);
}
void CFontCreationParameters::Init(bool bLeftToRightFirst, int iSpaceWidth, int iAscent, int iDescent)
{
miSpaceWidth = iSpaceWidth;
mbLeftToRightFirst = bLeftToRightFirst;
miDescent = iDescent;
miAscent = iAscent;
}
