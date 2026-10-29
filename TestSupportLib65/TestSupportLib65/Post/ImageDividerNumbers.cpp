class CImageDividerNumbers
{
friend class CImageDivider;
public:
int iCelWidth;
int iCelHeight;
int iColumnCount;
int iRowCount;
int iLeftOffset;
int iTopOffset;
int iWidthSpacing;
int iHeightSpacing;
public:
void InitGeneral(int iCelWidth, int iCelHeight, int iColumnCount, int iRowCount, int iLeftOffset, int iTopOffset, int iWidthSpacing, int iHeightSpacing);
void InitFromCelSize(int iCelWidth, int iCelHeight, int iLeftOffset = 0, int iTopOffset = 0, int iWidthSpacing = 0, int iHeightSpacing = 0);
void InitFromRowsColumns(int iColumnCount, int iRowCount, int iLeftOffset = 0, int iTopOffset = 0, int iWidthSpacing = 0, int iHeightSpacing = 0);
void InitFromSingle(int iLeftOffset = 0, int iTopOffset = 0, int iRightOffset = 0, int iBottomOffset = 0);
protected:
void Calculate(int iImageWidth, int iImageHeight);
};
void CImageDividerNumbers::InitGeneral(int iCelWidth, int iCelHeight, int iColumnCount, int iRowCount, int iLeftOffset, int iTopOffset, int iWidthSpacing, int iHeightSpacing)
{
this->iCelWidth = iCelWidth;
this->iCelHeight = iCelHeight;
this->iColumnCount = iColumnCount;
this->iRowCount = iRowCount;
this->iLeftOffset = iLeftOffset;
this->iTopOffset = iTopOffset;
this->iWidthSpacing = iWidthSpacing;
this->iHeightSpacing = iHeightSpacing;
}
void CImageDividerNumbers::InitFromCelSize(int iCelWidth, int iCelHeight, int iLeftOffset, int iTopOffset, int iWidthSpacing, int iHeightSpacing)
{
InitGeneral(iCelWidth, iCelHeight, -1, -1, iLeftOffset, iTopOffset, iWidthSpacing, iHeightSpacing);
}
void CImageDividerNumbers::InitFromRowsColumns(int iColumnCount, int iRowCount, int iLeftOffset, int iTopOffset, int iWidthSpacing, int iHeightSpacing)
{
InitGeneral(-1, -1, iColumnCount, iRowCount, iLeftOffset, iTopOffset, iWidthSpacing, iHeightSpacing);
}
void CImageDividerNumbers::InitFromSingle(int iLeftOffset, int iTopOffset, int iRightOffset, int iBottomOffset)
{
InitGeneral(-1, -1, 1, 1, iLeftOffset, iTopOffset, iRightOffset, iBottomOffset);
}
void CImageDividerNumbers::Calculate(int iImageWidth, int iImageHeight)
{
int iTotalWidth;
int iTotalHeight;
int iRemainder;
if ((iColumnCount == -1) && (iCelWidth == -1))
{
iCelWidth = iImageWidth - iLeftOffset - iWidthSpacing;
iColumnCount = 1;
}
else
{
if (iColumnCount == -1)
{
iTotalWidth = iCelWidth + iWidthSpacing;
iColumnCount = (iImageWidth - iLeftOffset) / iTotalWidth;
iRemainder = (iImageWidth - iLeftOffset) % iTotalWidth;
if (iRemainder >= iCelWidth)
{
iColumnCount++;
}
}
else if (iCelWidth == -1)
{
iCelWidth = (iImageWidth - iLeftOffset - iWidthSpacing * (iColumnCount-1)) / iColumnCount;
}
}
if ((iRowCount == -1) && (iCelHeight == -1))
{
iCelHeight = iImageHeight;
iRowCount = 1;
}
else
{
if (iRowCount == -1)
{
iTotalHeight = iCelHeight + iHeightSpacing;
iRowCount = (iImageHeight - iTopOffset) / iTotalHeight;
iRemainder = (iImageHeight - iTopOffset) % iTotalHeight;
if (iRemainder >= iCelHeight)
{
iRowCount++;
}
}
if (iCelHeight == -1)
{
iCelHeight = (iImageHeight - iTopOffset - iHeightSpacing * (iRowCount-1)) / iRowCount;
}
}
}
