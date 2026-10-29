bool IsWhitespace(char c, bool bIncludeNewLines = true);
bool IsWhitespace(char c, bool bIncludeNewLines)
{
if (bIncludeNewLines)
{
if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'))
{
return true;
}
return false;
}
else
{
if ((c == ' ') || (c == '\t'))
{
return true;
}
return false;
}
}
