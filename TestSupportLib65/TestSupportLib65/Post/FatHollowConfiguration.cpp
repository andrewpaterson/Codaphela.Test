extern bool gbForceFatHollows;
void ForceFatHollows(void);
void UnforceFatHollows(void);
bool gbForceFatHollows = false;
void ForceFatHollows(void)
{
gbForceFatHollows = true;
}
void UnforceFatHollows(void)
{
gbForceFatHollows = false;
}
