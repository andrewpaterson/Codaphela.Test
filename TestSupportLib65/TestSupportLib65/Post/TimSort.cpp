extern int errno;
typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef long long max_align_t;
extern "C"
{
void* malloc(size_t uiBytes);
void* calloc(size_t uiCount, size_t uiBytes);
void* realloc(void* pv, size_t uiBytes);
void free(void* pv);
int abs(int i);
long labs(long i);
int atoi(const char* sz);
long atol(const char* sz);
long strtol(const char* sz, char** pszEnd, int iBase);
unsigned long strtoul(const char* sz, char** pszEnd, int iBase);
long long strtoll(const char* sz, char** pszEnd, int iBase);
unsigned long long strtoull(const char* sz, char** pszEnd, int iBase);
double strtod(const char* sz, char** pszEnd);
float strtof(const char* sz, char** pszEnd);
long double strtold(const char* sz, char** pszEnd);
double atof(const char* sz);
int rand(void);
void srand(unsigned int uiSeed);
void qsort(void* pvBase, size_t uiCount, size_t uiBytes, int (*fCompare)(const void*, const void*));
void abort(void);
int atexit(void (*fFunction)(void));
void exit(int iStatus);
void _Exit(int iStatus);
}
extern "C"
{
void* memcpy(void* pvDest, const void* pvSource, size_t uiBytes);
void* memmove(void* pvDest, const void* pvSource, size_t uiBytes);
void* memset(void* pvDest, int iValue, size_t uiBytes);
int memcmp(const void* pv1, const void* pv2, size_t uiBytes);
void* memchr(const void* pv, int iValue, size_t uiBytes);
size_t strlen(const char* sz);
char* strcpy(char* szDest, const char* szSource);
char* strncpy(char* szDest, const char* szSource, size_t uiChars);
char* strcat(char* szDest, const char* szSource);
char* strncat(char* szDest, const char* szSource, size_t uiChars);
int strcmp(const char* sz1, const char* sz2);
int strncmp(const char* sz1, const char* sz2, size_t uiChars);
char* strchr(const char* sz, int c);
char* strrchr(const char* sz, int c);
char* strstr(const char* sz, const char* szFind);
}
typedef signed char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int_least8_t;
typedef short int_least16_t;
typedef long int_least32_t;
typedef long long int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned long uint_least32_t;
typedef unsigned long long uint_least64_t;
typedef int int_fast8_t;
typedef int int_fast16_t;
typedef long int_fast32_t;
typedef long long int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long uint_fast32_t;
typedef unsigned long long uint_fast64_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t uint8;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef int64_t int64 ;
typedef uint64_t uint64 ;
typedef int64 int128 ;
typedef uint64 uint128 ;
typedef char char8;
typedef wchar_t char16;
typedef float float32;
typedef double float64 ;
typedef long double float128;
typedef unsigned int uint;
typedef size_t size;
typedef uintptr_t ptr;
typedef ptrdiff_t ptrdiff;
typedef size lsize;
typedef int64 longint;
typedef uint64 ulongint;
typedef int (*DataCompare)(const void* pvLeft, const void* pvRight);
void TimSort(DataCompare fCompare, void* pvArray, lsize uiStride, lsize uiNumElements);
int timsort(void* base, lsize nel, lsize width, int (*compar) (const void*, const void*));
void TimSort(DataCompare fCompare, void* pvArray, lsize uiStride, lsize uiNumElements)
{
timsort(pvArray, uiNumElements, uiStride, fCompare);
}
typedef int (*comparator) (const void* x, const void* y);
struct timsort_run {
void* base;
lsize len;
};
struct timsort {
void* a;
lsize a_length;
comparator c;
lsize minGallop;
void* tmp;
lsize tmp_length;
lsize stackSize;
lsize stackLen;
struct timsort_run run[85];
};
static int timsort_init(struct timsort* ts, void* a, lsize len,
comparator c,
lsize width);
static void timsort_deinit(struct timsort* ts);
static lsize minRunLength(lsize n);
static void pushRun(struct timsort* ts, void* runBase, lsize runLen);
static void* ensureCapacity(struct timsort* ts, lsize minCapacity,
lsize width);
static int timsort_init(struct timsort* ts, void* a, lsize len,
comparator c,
lsize width)
{
int err = 0;
((void)0);
((void)0);
((void)0);
((void)0);
ts->minGallop = 7;
ts->stackSize = 0;
ts->a = a;
ts->a_length = len;
ts->c = c;
ts->tmp_length = (len < 2 * 256 ?
len >> 1 : 256);
if (ts->tmp_length) {
ts->tmp = malloc(ts->tmp_length * width);
err |= ts->tmp == 0L;
}
else {
ts->tmp = 0L;
}
ts->stackLen = 85;
if (!err) {
return 0;
}
else {
timsort_deinit(ts);
return (-1);
}
}
static void timsort_deinit(struct timsort* ts)
{
free(ts->tmp);
}
static lsize minRunLength(lsize n)
{
lsize r = 0;
while (n >= 32) {
r |= (n & 1);
n >>= 1;
}
return n + r;
}
static void pushRun(struct timsort* ts, void* runBase, lsize runLen)
{
((void)0);
ts->run[ts->stackSize].base = runBase;
ts->run[ts->stackSize].len = runLen;
ts->stackSize++;
}
static void* ensureCapacity(struct timsort* ts, lsize minCapacity,
lsize width)
{
if (ts->tmp_length < minCapacity) {
lsize newSize = minCapacity;
newSize |= newSize >> 1;
newSize |= newSize >> 2;
newSize |= newSize >> 4;
newSize |= newSize >> 8;
newSize |= newSize >> 16;
newSize++;
newSize = ((newSize) <= (ts->a_length >> 1) ? (newSize) : (ts->a_length >> 1));
if (newSize == 0) {
newSize = minCapacity;
}
free(ts->tmp);
ts->tmp_length = newSize;
ts->tmp = malloc(ts->tmp_length * width);
}
return ts->tmp;
}
static void binarySort_4 (void* a, lsize hi, lsize start,
comparator compare, lsize width);
static lsize countRunAndMakeAscending_4 (void* a, lsize hi,
comparator compare,
lsize width);
static void reverseRange_4 (void* a, lsize hi, lsize width);
static int mergeCollapse_4 (struct timsort* ts, lsize width);
static int mergeForceCollapse_4 (struct timsort* ts, lsize width);
static int mergeAt_4 (struct timsort* ts, lsize i, lsize width);
static lsize gallopLeft_4 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width);
static lsize gallopRight_4 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width);
static int mergeLo_4 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width);
static int mergeHi_4 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width);
static int timsort_4 (void* a, lsize nel, lsize width, comparator c)
{
int err = 0;
struct timsort ts;
lsize minRun;
if (nel < 2 || !width)
return err;
if (nel < 32) {
lsize initRunLen =
countRunAndMakeAscending_4 (a, nel, (c), width);
binarySort_4 (a, nel, initRunLen, (c), width);
return err;
}
if ((err = timsort_init(&ts, a, nel, (c), width)))
return err;
minRun = minRunLength(nel);
do {
lsize runLen =
countRunAndMakeAscending_4 (a, nel, (c), width);
if (runLen < minRun) {
lsize force = nel <= minRun ? nel : minRun;
binarySort_4 (a, force, runLen, (c), width);
runLen = force;
}
pushRun(&ts, a, runLen);
if ((err = mergeCollapse_4 (&ts, width)))
goto out;
a = ((char *)(a) + (runLen) * 4);
nel -= runLen;
}
while (nel != 0);
if ((err = mergeForceCollapse_4 (&ts, width)))
goto out;
out:
timsort_deinit(&ts);
return err;
}
static void binarySort_4 (void* a, lsize hi, lsize start,
comparator compare, lsize width) {
void *pivot = __builtin_alloca(4);
char* startp;
if (start == 0)
start++;
startp = ((char *)(a) + (start) * 4);
for (; start < hi; start++, startp = (char*)((void *)((char *)(startp) + 4))) {
char* leftp = (char*)a;
lsize right = start;
lsize n;
while (0 < right) {
lsize mid = right >> 1;
void* midp = ((char *)(leftp) + (mid) * 4);
if ((compare((startp), (midp))) < 0) {
right = mid;
}
else {
leftp = (char*)((void *)((char *)(midp) + 4));
right -= (mid + 1);
}
}
n = startp - leftp;
memcpy(pivot, startp, 4);
memmove((char*)((void *)((char *)(leftp) + 4)), leftp, n);
memcpy(leftp, pivot, 4);
}
;
(void)width;
}
static lsize countRunAndMakeAscending_4 (void* a, lsize hi,
comparator compare, lsize width)
{
lsize runHi = 1;
char* cur;
char* next;
if (runHi == hi)
return 1;
cur = (char*)((void *)((char *)(a) + 4));
next = (char*)((void *)((char *)(cur) + 4));
runHi++;
if ((compare((cur), (a))) < 0) {
while (runHi < hi && (compare((next), (cur))) < 0) {
runHi++;
cur = next;
next = (char*)((void *)((char *)(next) + 4));
}
reverseRange_4 (a, runHi, width);
}
else {
while (runHi < hi && (compare((next), (cur))) >= 0) {
runHi++;
cur = next;
next = (char*)((void *)((char *)(next) + 4));
}
}
(void)width;
return runHi;
}
static void reverseRange_4 (void* a, lsize hi, lsize width) {
void *t = __builtin_alloca(4);
char* front = (char*)a;
char* back = ((char *)(a) + (hi - 1) * 4);
while (front < back) {
memcpy(t, front, 4);
memcpy(front, back, 4);
memcpy(back, t, 4);
front = (char*)((void *)((char *)(front) + 4));
back = (char*)((void *)((char *)(back) - 4));
}
;
(void)width;
}
static int mergeCollapse_4 (struct timsort* ts, lsize width) {
int err = 0;
while (ts->stackSize > 1) {
lsize n = ts->stackSize - 2;
struct timsort_run* run = ts->run;
if ((n > 0 && run[n - 1].len <= run[n].len + run[n + 1].len)
|| (n > 1 && run[n - 2].len <= run[n].len + run[n - 1].len)) {
if (run[n - 1].len < run[n + 1].len)
n--;
}
else if (run[n].len > run[n + 1].len) {
break;
}
err = mergeAt_4 (ts, n, width);
if (err)
break;
}
return err;
}
static int mergeForceCollapse_4 (struct timsort* ts, lsize width) {
int err = 0;
while (ts->stackSize > 1) {
lsize n = ts->stackSize - 2;
if (n > 0 && ts->run[n - 1].len < ts->run[n + 1].len)
n--;
err = mergeAt_4 (ts, n, width);
if (err)
break;
}
return err;
}
static int mergeAt_4 (struct timsort* ts, lsize i, lsize width) {
void* base1 = ts->run[i].base;
lsize len1 = ts->run[i].len;
void* base2 = ts->run[i + 1].base;
lsize len2 = ts->run[i + 1].len;
lsize k;
ts->run[i].len = len1 + len2;
if (i == ts->stackSize - 3) {
ts->run[i + 1] = ts->run[i + 2];
}
ts->stackSize--;
k = gallopRight_4 (base2, base1, len1, 0, (ts->c), width);
base1 = ((char *)(base1) + (k) * 4);
len1 -= k;
if (len1 == 0)
return 0;
len2 =
gallopLeft_4 (((char *)(base1) + (len1 - 1) * 4), base2, len2, len2 - 1,
(ts->c), width);
if (len2 == 0)
return 0;
if (len1 <= len2)
return mergeLo_4 (ts, base1, len1, base2, len2, width);
else
return mergeHi_4 (ts, base1, len1, base2, len2, width);
}
static lsize gallopLeft_4 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width) {
char* hintp = ((char *)(base) + (hint) * 4);
ptrdiff_t lastOfs = 0;
ptrdiff_t ofs = 1;
if ((compare((key), (hintp))) > 0) {
ptrdiff_t maxOfs = len - hint;
while (ofs < maxOfs
&& (compare((key), (((char *)(hintp) + (ofs) * 4)))) > 0) {
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
lastOfs += hint + 1;
ofs += hint;
}
else {
const ptrdiff_t maxOfs = hint + 1;
lsize tmp;
while (ofs < maxOfs && (compare((key), (((char *)(hintp) + (-ofs) * 4)))) <= 0)
{
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
tmp = lastOfs;
lastOfs = hint + 1 - ofs;
ofs = hint - tmp;
}
while (lastOfs < ofs) {
lsize m = (lastOfs & ofs) + ((lastOfs ^ ofs) >> 1);
if ((compare((key), (((char *)(base) + (m) * 4)))) > 0)
lastOfs = m + 1;
else
ofs = m;
}
(void)width;
return ofs;
}
static lsize gallopRight_4 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width) {
char* hintp = ((char *)(base) + (hint) * 4);
ptrdiff_t ofs = 1;
ptrdiff_t lastOfs = 0;
if ((compare((key), (hintp))) < 0) {
ptrdiff_t maxOfs = hint + 1;
lsize tmp;
while (ofs < maxOfs
&& (compare((key), (((char *)(hintp) + (-ofs) * 4)))) < 0) {
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
tmp = lastOfs;
lastOfs = hint + 1 - ofs;
ofs = hint - tmp;
}
else {
ptrdiff_t maxOfs = len - hint;
while (ofs < maxOfs && (compare((key), (((char *)(hintp) + (ofs) * 4)))) >= 0)
{
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
lastOfs += hint + 1;
ofs += hint;
}
while (lastOfs < ofs) {
lsize m = (lastOfs & ofs) + ((lastOfs ^ ofs) >> 1);
if ((compare((key), (((char *)(base) + (m) * 4)))) < 0)
ofs = m;
else
lastOfs = m + 1;
}
(void)width;
return ofs;
}
static int mergeLo_4 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width) {
void* tmp = ensureCapacity(ts, len1, width);
char* cursor1;
char* cursor2;
char* dest;
comparator compare;
lsize minGallop;
if (!tmp)
return (-1);
memcpy(tmp, base1, ((len1) * 4));
cursor1 = (char*)tmp;
cursor2 = (char*)base2;
dest = (char*)base1;
memcpy(dest, cursor2, 4);
dest = (char*)((void *)((char *)(dest) + 4));
cursor2 = (char*)((void *)((char *)(cursor2) + 4));
if (--len2 == 0) {
memcpy(dest, cursor1, ((len1) * 4));
return 0;
}
if (len1 == 1) {
memmove(dest, cursor2, ((len2) * 4));
memcpy(((char *)(dest) + (len2) * 4), cursor1, 4);
return 0;
}
compare = ts->c;
minGallop = ts->minGallop;
while (1) {
lsize count1 = 0;
lsize count2 = 0;
do {
if ((compare((cursor2), (cursor1))) < 0) {
memcpy(dest, cursor2, 4);
dest = (char*)((void *)((char *)(dest) + 4));
cursor2 = (char*)((void *)((char *)(cursor2) + 4));
count2++;
count1 = 0;
if (--len2 == 0)
goto outer;
if (count2 >= minGallop)
break;
}
else {
memcpy(dest, cursor1, 4);
dest = (char*)((void *)((char *)(dest) + 4));
cursor1 = (char*)((void *)((char *)(cursor1) + 4));
count1++;
count2 = 0;
if (--len1 == 1)
goto outer;
if (count1 >= minGallop)
break;
}
}
while (true);
do {
count1 =
gallopRight_4 (cursor2, cursor1, len1, 0,
(compare), width);
if (count1 != 0) {
memcpy(dest, cursor1, ((count1) * 4));
dest = ((char *)(dest) + (count1) * 4);
cursor1 = ((char *)(cursor1) + (count1) * 4);
len1 -= count1;
if (len1 <= 1)
goto outer;
}
memcpy(dest, cursor2, 4);
dest = (char*)((void *)((char *)(dest) + 4));
cursor2 = (char*)((void *)((char *)(cursor2) + 4));
if (--len2 == 0)
goto outer;
count2 =
gallopLeft_4 (cursor1, cursor2, len2, 0,
(compare), width);
if (count2 != 0) {
memmove(dest, cursor2, ((count2) * 4));
dest = ((char *)(dest) + (count2) * 4);
cursor2 = ((char *)(cursor2) + (count2) * 4);
len2 -= count2;
if (len2 == 0)
goto outer;
}
memcpy(dest, cursor1, 4);
dest = (char*)((void *)((char *)(dest) + 4));
cursor1 = (char*)((void *)((char *)(cursor1) + 4));
if (--len1 == 1)
goto outer;
if (minGallop > 0)
minGallop--;
}
while (count1 >= 7 || count2 >= 7);
minGallop += 2;
}
outer:
ts->minGallop = minGallop < 1 ? 1 : minGallop;
if (len1 == 1) {
memmove(dest, cursor2, ((len2) * 4));
memcpy(((char *)(dest) + (len2) * 4), cursor1, 4);
}
else if (len1 == 0) {
errno = 22;
return (-1);
}
else {
memcpy(dest, cursor1, ((len1) * 4));
}
return 0;
}
static int mergeHi_4 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width) {
void* tmp = ensureCapacity(ts, len2, width);
char* cursor1;
char* cursor2;
char* dest;
comparator compare;
ptrdiff_t minGallop;
if (!tmp)
return (-1);
memcpy(tmp, base2, ((len2) * 4));
cursor1 = ((char *)(base1) + (len1 - 1) * 4);
cursor2 = ((char *)(tmp) + (len2 - 1) * 4);
dest = ((char *)(base2) + (len2 - 1) * 4);
memcpy(dest, cursor1, 4);
dest = (char*)((void *)((char *)(dest) - 4));
cursor1 = (char*)((void *)((char *)(cursor1) - 4));
if (--len1 == 0) {
memcpy(((char *)(dest) + (-((ptrdiff_t)((len2 - 1)))) * 4), tmp, ((len2) * 4));
return 0;
}
if (len2 == 1) {
dest = ((char *)(dest) + (-((ptrdiff_t)len1)) * 4);
cursor1 = ((char *)(cursor1) + (-((ptrdiff_t)len1)) * 4);
memmove(((char *)(dest) + (1) * 4), ((char *)(cursor1) + (1) * 4), ((len1) * 4));
memcpy(dest, cursor2, 4);
return 0;
}
compare = ts->c;
minGallop = ts->minGallop;
while (1) {
ptrdiff_t count1 = 0;
ptrdiff_t count2 = 0;
do {
if ((compare((cursor2), (cursor1))) < 0) {
memcpy(dest, cursor1, 4);
dest = (char*)((void *)((char *)(dest) - 4));
cursor1 = (char*)((void *)((char *)(cursor1) - 4));
count1++;
count2 = 0;
if (--len1 == 0)
goto outer;
}
else {
memcpy(dest, cursor2, 4);
dest = (char*)((void *)((char *)(dest) - 4));
cursor2 = (char*)((void *)((char *)(cursor2) - 4));
count2++;
count1 = 0;
if (--len2 == 1)
goto outer;
}
}
while ((count1 | count2) < minGallop);
do {
count1 =
len1 - gallopRight_4 (cursor2, base1,
len1, len1 - 1,
(compare),
width);
if (count1 != 0) {
dest = ((char *)(dest) + (-count1) * 4);
cursor1 = ((char *)(cursor1) + (-count1) * 4);
len1 -= count1;
memmove((char*)((void *)((char *)(dest) + 4)), (char*)((void *)((char *)(cursor1) + 4)),
((count1) * 4));
if (len1 == 0)
goto outer;
}
memcpy(dest, cursor2, 4);
dest = (char*)((void *)((char *)(dest) - 4));
cursor2 = (char*)((void *)((char *)(cursor2) - 4));
if (--len2 == 1)
goto outer;
count2 =
len2 - gallopLeft_4 (cursor1, tmp, len2,
len2 - 1, (compare),
width);
if (count2 != 0) {
dest = ((char *)(dest) + (-count2) * 4);
cursor2 = ((char *)(cursor2) + (-count2) * 4);
len2 -= count2;
memcpy((char*)((void *)((char *)(dest) + 4)), (char*)((void *)((char *)(cursor2) + 4)), ((count2) * 4));
if (len2 <= 1)
goto outer;
}
memcpy(dest, cursor1, 4);
dest = (char*)((void *)((char *)(dest) - 4));
cursor1 = (char*)((void *)((char *)(cursor1) - 4));
if (--len1 == 0)
goto outer;
if (minGallop > 0)
minGallop--;
}
while (count1 >= 7 || count2 >= 7);
minGallop += 2;
}
outer:
ts->minGallop = minGallop < 1 ? 1 : minGallop;
if (len2 == 1)
{
dest = ((char *)(dest) + (-((ptrdiff_t)len1)) * 4);
cursor1 = ((char *)(cursor1) + (-((ptrdiff_t)len1)) * 4);
memmove((char*)((void *)((char *)(dest) + 4)), (char*)((void *)((char *)(cursor1) + 4)), ((len1) * 4));
memcpy(dest, cursor2, 4);
}
else if (len2 == 0)
{
errno = 22;
return (-1);
}
else
{
memcpy(((char *)(dest) + (-((ptrdiff_t)(len2 - 1))) * 4), tmp, ((len2) * 4));
}
return 0;
}
static void binarySort_8 (void* a, lsize hi, lsize start,
comparator compare, lsize width);
static lsize countRunAndMakeAscending_8 (void* a, lsize hi,
comparator compare,
lsize width);
static void reverseRange_8 (void* a, lsize hi, lsize width);
static int mergeCollapse_8 (struct timsort* ts, lsize width);
static int mergeForceCollapse_8 (struct timsort* ts, lsize width);
static int mergeAt_8 (struct timsort* ts, lsize i, lsize width);
static lsize gallopLeft_8 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width);
static lsize gallopRight_8 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width);
static int mergeLo_8 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width);
static int mergeHi_8 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width);
static int timsort_8 (void* a, lsize nel, lsize width, comparator c)
{
int err = 0;
struct timsort ts;
lsize minRun;
if (nel < 2 || !width)
return err;
if (nel < 32) {
lsize initRunLen =
countRunAndMakeAscending_8 (a, nel, (c), width);
binarySort_8 (a, nel, initRunLen, (c), width);
return err;
}
if ((err = timsort_init(&ts, a, nel, (c), width)))
return err;
minRun = minRunLength(nel);
do {
lsize runLen =
countRunAndMakeAscending_8 (a, nel, (c), width);
if (runLen < minRun) {
lsize force = nel <= minRun ? nel : minRun;
binarySort_8 (a, force, runLen, (c), width);
runLen = force;
}
pushRun(&ts, a, runLen);
if ((err = mergeCollapse_8 (&ts, width)))
goto out;
a = ((char *)(a) + (runLen) * 8);
nel -= runLen;
}
while (nel != 0);
if ((err = mergeForceCollapse_8 (&ts, width)))
goto out;
out:
timsort_deinit(&ts);
return err;
}
static void binarySort_8 (void* a, lsize hi, lsize start,
comparator compare, lsize width) {
void *pivot = __builtin_alloca(8);
char* startp;
if (start == 0)
start++;
startp = ((char *)(a) + (start) * 8);
for (; start < hi; start++, startp = (char*)((void *)((char *)(startp) + 8))) {
char* leftp = (char*)a;
lsize right = start;
lsize n;
while (0 < right) {
lsize mid = right >> 1;
void* midp = ((char *)(leftp) + (mid) * 8);
if ((compare((startp), (midp))) < 0) {
right = mid;
}
else {
leftp = (char*)((void *)((char *)(midp) + 8));
right -= (mid + 1);
}
}
n = startp - leftp;
memcpy(pivot, startp, 8);
memmove((char*)((void *)((char *)(leftp) + 8)), leftp, n);
memcpy(leftp, pivot, 8);
}
;
(void)width;
}
static lsize countRunAndMakeAscending_8 (void* a, lsize hi,
comparator compare, lsize width)
{
lsize runHi = 1;
char* cur;
char* next;
if (runHi == hi)
return 1;
cur = (char*)((void *)((char *)(a) + 8));
next = (char*)((void *)((char *)(cur) + 8));
runHi++;
if ((compare((cur), (a))) < 0) {
while (runHi < hi && (compare((next), (cur))) < 0) {
runHi++;
cur = next;
next = (char*)((void *)((char *)(next) + 8));
}
reverseRange_8 (a, runHi, width);
}
else {
while (runHi < hi && (compare((next), (cur))) >= 0) {
runHi++;
cur = next;
next = (char*)((void *)((char *)(next) + 8));
}
}
(void)width;
return runHi;
}
static void reverseRange_8 (void* a, lsize hi, lsize width) {
void *t = __builtin_alloca(8);
char* front = (char*)a;
char* back = ((char *)(a) + (hi - 1) * 8);
while (front < back) {
memcpy(t, front, 8);
memcpy(front, back, 8);
memcpy(back, t, 8);
front = (char*)((void *)((char *)(front) + 8));
back = (char*)((void *)((char *)(back) - 8));
}
;
(void)width;
}
static int mergeCollapse_8 (struct timsort* ts, lsize width) {
int err = 0;
while (ts->stackSize > 1) {
lsize n = ts->stackSize - 2;
struct timsort_run* run = ts->run;
if ((n > 0 && run[n - 1].len <= run[n].len + run[n + 1].len)
|| (n > 1 && run[n - 2].len <= run[n].len + run[n - 1].len)) {
if (run[n - 1].len < run[n + 1].len)
n--;
}
else if (run[n].len > run[n + 1].len) {
break;
}
err = mergeAt_8 (ts, n, width);
if (err)
break;
}
return err;
}
static int mergeForceCollapse_8 (struct timsort* ts, lsize width) {
int err = 0;
while (ts->stackSize > 1) {
lsize n = ts->stackSize - 2;
if (n > 0 && ts->run[n - 1].len < ts->run[n + 1].len)
n--;
err = mergeAt_8 (ts, n, width);
if (err)
break;
}
return err;
}
static int mergeAt_8 (struct timsort* ts, lsize i, lsize width) {
void* base1 = ts->run[i].base;
lsize len1 = ts->run[i].len;
void* base2 = ts->run[i + 1].base;
lsize len2 = ts->run[i + 1].len;
lsize k;
ts->run[i].len = len1 + len2;
if (i == ts->stackSize - 3) {
ts->run[i + 1] = ts->run[i + 2];
}
ts->stackSize--;
k = gallopRight_8 (base2, base1, len1, 0, (ts->c), width);
base1 = ((char *)(base1) + (k) * 8);
len1 -= k;
if (len1 == 0)
return 0;
len2 =
gallopLeft_8 (((char *)(base1) + (len1 - 1) * 8), base2, len2, len2 - 1,
(ts->c), width);
if (len2 == 0)
return 0;
if (len1 <= len2)
return mergeLo_8 (ts, base1, len1, base2, len2, width);
else
return mergeHi_8 (ts, base1, len1, base2, len2, width);
}
static lsize gallopLeft_8 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width) {
char* hintp = ((char *)(base) + (hint) * 8);
ptrdiff_t lastOfs = 0;
ptrdiff_t ofs = 1;
if ((compare((key), (hintp))) > 0) {
ptrdiff_t maxOfs = len - hint;
while (ofs < maxOfs
&& (compare((key), (((char *)(hintp) + (ofs) * 8)))) > 0) {
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
lastOfs += hint + 1;
ofs += hint;
}
else {
const ptrdiff_t maxOfs = hint + 1;
lsize tmp;
while (ofs < maxOfs && (compare((key), (((char *)(hintp) + (-ofs) * 8)))) <= 0)
{
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
tmp = lastOfs;
lastOfs = hint + 1 - ofs;
ofs = hint - tmp;
}
while (lastOfs < ofs) {
lsize m = (lastOfs & ofs) + ((lastOfs ^ ofs) >> 1);
if ((compare((key), (((char *)(base) + (m) * 8)))) > 0)
lastOfs = m + 1;
else
ofs = m;
}
(void)width;
return ofs;
}
static lsize gallopRight_8 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width) {
char* hintp = ((char *)(base) + (hint) * 8);
ptrdiff_t ofs = 1;
ptrdiff_t lastOfs = 0;
if ((compare((key), (hintp))) < 0) {
ptrdiff_t maxOfs = hint + 1;
lsize tmp;
while (ofs < maxOfs
&& (compare((key), (((char *)(hintp) + (-ofs) * 8)))) < 0) {
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
tmp = lastOfs;
lastOfs = hint + 1 - ofs;
ofs = hint - tmp;
}
else {
ptrdiff_t maxOfs = len - hint;
while (ofs < maxOfs && (compare((key), (((char *)(hintp) + (ofs) * 8)))) >= 0)
{
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
lastOfs += hint + 1;
ofs += hint;
}
while (lastOfs < ofs) {
lsize m = (lastOfs & ofs) + ((lastOfs ^ ofs) >> 1);
if ((compare((key), (((char *)(base) + (m) * 8)))) < 0)
ofs = m;
else
lastOfs = m + 1;
}
(void)width;
return ofs;
}
static int mergeLo_8 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width) {
void* tmp = ensureCapacity(ts, len1, width);
char* cursor1;
char* cursor2;
char* dest;
comparator compare;
lsize minGallop;
if (!tmp)
return (-1);
memcpy(tmp, base1, ((len1) * 8));
cursor1 = (char*)tmp;
cursor2 = (char*)base2;
dest = (char*)base1;
memcpy(dest, cursor2, 8);
dest = (char*)((void *)((char *)(dest) + 8));
cursor2 = (char*)((void *)((char *)(cursor2) + 8));
if (--len2 == 0) {
memcpy(dest, cursor1, ((len1) * 8));
return 0;
}
if (len1 == 1) {
memmove(dest, cursor2, ((len2) * 8));
memcpy(((char *)(dest) + (len2) * 8), cursor1, 8);
return 0;
}
compare = ts->c;
minGallop = ts->minGallop;
while (1) {
lsize count1 = 0;
lsize count2 = 0;
do {
if ((compare((cursor2), (cursor1))) < 0) {
memcpy(dest, cursor2, 8);
dest = (char*)((void *)((char *)(dest) + 8));
cursor2 = (char*)((void *)((char *)(cursor2) + 8));
count2++;
count1 = 0;
if (--len2 == 0)
goto outer;
if (count2 >= minGallop)
break;
}
else {
memcpy(dest, cursor1, 8);
dest = (char*)((void *)((char *)(dest) + 8));
cursor1 = (char*)((void *)((char *)(cursor1) + 8));
count1++;
count2 = 0;
if (--len1 == 1)
goto outer;
if (count1 >= minGallop)
break;
}
}
while (true);
do {
count1 =
gallopRight_8 (cursor2, cursor1, len1, 0,
(compare), width);
if (count1 != 0) {
memcpy(dest, cursor1, ((count1) * 8));
dest = ((char *)(dest) + (count1) * 8);
cursor1 = ((char *)(cursor1) + (count1) * 8);
len1 -= count1;
if (len1 <= 1)
goto outer;
}
memcpy(dest, cursor2, 8);
dest = (char*)((void *)((char *)(dest) + 8));
cursor2 = (char*)((void *)((char *)(cursor2) + 8));
if (--len2 == 0)
goto outer;
count2 =
gallopLeft_8 (cursor1, cursor2, len2, 0,
(compare), width);
if (count2 != 0) {
memmove(dest, cursor2, ((count2) * 8));
dest = ((char *)(dest) + (count2) * 8);
cursor2 = ((char *)(cursor2) + (count2) * 8);
len2 -= count2;
if (len2 == 0)
goto outer;
}
memcpy(dest, cursor1, 8);
dest = (char*)((void *)((char *)(dest) + 8));
cursor1 = (char*)((void *)((char *)(cursor1) + 8));
if (--len1 == 1)
goto outer;
if (minGallop > 0)
minGallop--;
}
while (count1 >= 7 || count2 >= 7);
minGallop += 2;
}
outer:
ts->minGallop = minGallop < 1 ? 1 : minGallop;
if (len1 == 1) {
memmove(dest, cursor2, ((len2) * 8));
memcpy(((char *)(dest) + (len2) * 8), cursor1, 8);
}
else if (len1 == 0) {
errno = 22;
return (-1);
}
else {
memcpy(dest, cursor1, ((len1) * 8));
}
return 0;
}
static int mergeHi_8 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width) {
void* tmp = ensureCapacity(ts, len2, width);
char* cursor1;
char* cursor2;
char* dest;
comparator compare;
ptrdiff_t minGallop;
if (!tmp)
return (-1);
memcpy(tmp, base2, ((len2) * 8));
cursor1 = ((char *)(base1) + (len1 - 1) * 8);
cursor2 = ((char *)(tmp) + (len2 - 1) * 8);
dest = ((char *)(base2) + (len2 - 1) * 8);
memcpy(dest, cursor1, 8);
dest = (char*)((void *)((char *)(dest) - 8));
cursor1 = (char*)((void *)((char *)(cursor1) - 8));
if (--len1 == 0) {
memcpy(((char *)(dest) + (-((ptrdiff_t)((len2 - 1)))) * 8), tmp, ((len2) * 8));
return 0;
}
if (len2 == 1) {
dest = ((char *)(dest) + (-((ptrdiff_t)len1)) * 8);
cursor1 = ((char *)(cursor1) + (-((ptrdiff_t)len1)) * 8);
memmove(((char *)(dest) + (1) * 8), ((char *)(cursor1) + (1) * 8), ((len1) * 8));
memcpy(dest, cursor2, 8);
return 0;
}
compare = ts->c;
minGallop = ts->minGallop;
while (1) {
ptrdiff_t count1 = 0;
ptrdiff_t count2 = 0;
do {
if ((compare((cursor2), (cursor1))) < 0) {
memcpy(dest, cursor1, 8);
dest = (char*)((void *)((char *)(dest) - 8));
cursor1 = (char*)((void *)((char *)(cursor1) - 8));
count1++;
count2 = 0;
if (--len1 == 0)
goto outer;
}
else {
memcpy(dest, cursor2, 8);
dest = (char*)((void *)((char *)(dest) - 8));
cursor2 = (char*)((void *)((char *)(cursor2) - 8));
count2++;
count1 = 0;
if (--len2 == 1)
goto outer;
}
}
while ((count1 | count2) < minGallop);
do {
count1 =
len1 - gallopRight_8 (cursor2, base1,
len1, len1 - 1,
(compare),
width);
if (count1 != 0) {
dest = ((char *)(dest) + (-count1) * 8);
cursor1 = ((char *)(cursor1) + (-count1) * 8);
len1 -= count1;
memmove((char*)((void *)((char *)(dest) + 8)), (char*)((void *)((char *)(cursor1) + 8)),
((count1) * 8));
if (len1 == 0)
goto outer;
}
memcpy(dest, cursor2, 8);
dest = (char*)((void *)((char *)(dest) - 8));
cursor2 = (char*)((void *)((char *)(cursor2) - 8));
if (--len2 == 1)
goto outer;
count2 =
len2 - gallopLeft_8 (cursor1, tmp, len2,
len2 - 1, (compare),
width);
if (count2 != 0) {
dest = ((char *)(dest) + (-count2) * 8);
cursor2 = ((char *)(cursor2) + (-count2) * 8);
len2 -= count2;
memcpy((char*)((void *)((char *)(dest) + 8)), (char*)((void *)((char *)(cursor2) + 8)), ((count2) * 8));
if (len2 <= 1)
goto outer;
}
memcpy(dest, cursor1, 8);
dest = (char*)((void *)((char *)(dest) - 8));
cursor1 = (char*)((void *)((char *)(cursor1) - 8));
if (--len1 == 0)
goto outer;
if (minGallop > 0)
minGallop--;
}
while (count1 >= 7 || count2 >= 7);
minGallop += 2;
}
outer:
ts->minGallop = minGallop < 1 ? 1 : minGallop;
if (len2 == 1)
{
dest = ((char *)(dest) + (-((ptrdiff_t)len1)) * 8);
cursor1 = ((char *)(cursor1) + (-((ptrdiff_t)len1)) * 8);
memmove((char*)((void *)((char *)(dest) + 8)), (char*)((void *)((char *)(cursor1) + 8)), ((len1) * 8));
memcpy(dest, cursor2, 8);
}
else if (len2 == 0)
{
errno = 22;
return (-1);
}
else
{
memcpy(((char *)(dest) + (-((ptrdiff_t)(len2 - 1))) * 8), tmp, ((len2) * 8));
}
return 0;
}
static void binarySort_16 (void* a, lsize hi, lsize start,
comparator compare, lsize width);
static lsize countRunAndMakeAscending_16 (void* a, lsize hi,
comparator compare,
lsize width);
static void reverseRange_16 (void* a, lsize hi, lsize width);
static int mergeCollapse_16 (struct timsort* ts, lsize width);
static int mergeForceCollapse_16 (struct timsort* ts, lsize width);
static int mergeAt_16 (struct timsort* ts, lsize i, lsize width);
static lsize gallopLeft_16 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width);
static lsize gallopRight_16 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width);
static int mergeLo_16 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width);
static int mergeHi_16 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width);
static int timsort_16 (void* a, lsize nel, lsize width, comparator c)
{
int err = 0;
struct timsort ts;
lsize minRun;
if (nel < 2 || !width)
return err;
if (nel < 32) {
lsize initRunLen =
countRunAndMakeAscending_16 (a, nel, (c), width);
binarySort_16 (a, nel, initRunLen, (c), width);
return err;
}
if ((err = timsort_init(&ts, a, nel, (c), width)))
return err;
minRun = minRunLength(nel);
do {
lsize runLen =
countRunAndMakeAscending_16 (a, nel, (c), width);
if (runLen < minRun) {
lsize force = nel <= minRun ? nel : minRun;
binarySort_16 (a, force, runLen, (c), width);
runLen = force;
}
pushRun(&ts, a, runLen);
if ((err = mergeCollapse_16 (&ts, width)))
goto out;
a = ((char *)(a) + (runLen) * 16);
nel -= runLen;
}
while (nel != 0);
if ((err = mergeForceCollapse_16 (&ts, width)))
goto out;
out:
timsort_deinit(&ts);
return err;
}
static void binarySort_16 (void* a, lsize hi, lsize start,
comparator compare, lsize width) {
void *pivot = __builtin_alloca(16);
char* startp;
if (start == 0)
start++;
startp = ((char *)(a) + (start) * 16);
for (; start < hi; start++, startp = (char*)((void *)((char *)(startp) + 16))) {
char* leftp = (char*)a;
lsize right = start;
lsize n;
while (0 < right) {
lsize mid = right >> 1;
void* midp = ((char *)(leftp) + (mid) * 16);
if ((compare((startp), (midp))) < 0) {
right = mid;
}
else {
leftp = (char*)((void *)((char *)(midp) + 16));
right -= (mid + 1);
}
}
n = startp - leftp;
memcpy(pivot, startp, 16);
memmove((char*)((void *)((char *)(leftp) + 16)), leftp, n);
memcpy(leftp, pivot, 16);
}
;
(void)width;
}
static lsize countRunAndMakeAscending_16 (void* a, lsize hi,
comparator compare, lsize width)
{
lsize runHi = 1;
char* cur;
char* next;
if (runHi == hi)
return 1;
cur = (char*)((void *)((char *)(a) + 16));
next = (char*)((void *)((char *)(cur) + 16));
runHi++;
if ((compare((cur), (a))) < 0) {
while (runHi < hi && (compare((next), (cur))) < 0) {
runHi++;
cur = next;
next = (char*)((void *)((char *)(next) + 16));
}
reverseRange_16 (a, runHi, width);
}
else {
while (runHi < hi && (compare((next), (cur))) >= 0) {
runHi++;
cur = next;
next = (char*)((void *)((char *)(next) + 16));
}
}
(void)width;
return runHi;
}
static void reverseRange_16 (void* a, lsize hi, lsize width) {
void *t = __builtin_alloca(16);
char* front = (char*)a;
char* back = ((char *)(a) + (hi - 1) * 16);
while (front < back) {
memcpy(t, front, 16);
memcpy(front, back, 16);
memcpy(back, t, 16);
front = (char*)((void *)((char *)(front) + 16));
back = (char*)((void *)((char *)(back) - 16));
}
;
(void)width;
}
static int mergeCollapse_16 (struct timsort* ts, lsize width) {
int err = 0;
while (ts->stackSize > 1) {
lsize n = ts->stackSize - 2;
struct timsort_run* run = ts->run;
if ((n > 0 && run[n - 1].len <= run[n].len + run[n + 1].len)
|| (n > 1 && run[n - 2].len <= run[n].len + run[n - 1].len)) {
if (run[n - 1].len < run[n + 1].len)
n--;
}
else if (run[n].len > run[n + 1].len) {
break;
}
err = mergeAt_16 (ts, n, width);
if (err)
break;
}
return err;
}
static int mergeForceCollapse_16 (struct timsort* ts, lsize width) {
int err = 0;
while (ts->stackSize > 1) {
lsize n = ts->stackSize - 2;
if (n > 0 && ts->run[n - 1].len < ts->run[n + 1].len)
n--;
err = mergeAt_16 (ts, n, width);
if (err)
break;
}
return err;
}
static int mergeAt_16 (struct timsort* ts, lsize i, lsize width) {
void* base1 = ts->run[i].base;
lsize len1 = ts->run[i].len;
void* base2 = ts->run[i + 1].base;
lsize len2 = ts->run[i + 1].len;
lsize k;
ts->run[i].len = len1 + len2;
if (i == ts->stackSize - 3) {
ts->run[i + 1] = ts->run[i + 2];
}
ts->stackSize--;
k = gallopRight_16 (base2, base1, len1, 0, (ts->c), width);
base1 = ((char *)(base1) + (k) * 16);
len1 -= k;
if (len1 == 0)
return 0;
len2 =
gallopLeft_16 (((char *)(base1) + (len1 - 1) * 16), base2, len2, len2 - 1,
(ts->c), width);
if (len2 == 0)
return 0;
if (len1 <= len2)
return mergeLo_16 (ts, base1, len1, base2, len2, width);
else
return mergeHi_16 (ts, base1, len1, base2, len2, width);
}
static lsize gallopLeft_16 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width) {
char* hintp = ((char *)(base) + (hint) * 16);
ptrdiff_t lastOfs = 0;
ptrdiff_t ofs = 1;
if ((compare((key), (hintp))) > 0) {
ptrdiff_t maxOfs = len - hint;
while (ofs < maxOfs
&& (compare((key), (((char *)(hintp) + (ofs) * 16)))) > 0) {
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
lastOfs += hint + 1;
ofs += hint;
}
else {
const ptrdiff_t maxOfs = hint + 1;
lsize tmp;
while (ofs < maxOfs && (compare((key), (((char *)(hintp) + (-ofs) * 16)))) <= 0)
{
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
tmp = lastOfs;
lastOfs = hint + 1 - ofs;
ofs = hint - tmp;
}
while (lastOfs < ofs) {
lsize m = (lastOfs & ofs) + ((lastOfs ^ ofs) >> 1);
if ((compare((key), (((char *)(base) + (m) * 16)))) > 0)
lastOfs = m + 1;
else
ofs = m;
}
(void)width;
return ofs;
}
static lsize gallopRight_16 (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width) {
char* hintp = ((char *)(base) + (hint) * 16);
ptrdiff_t ofs = 1;
ptrdiff_t lastOfs = 0;
if ((compare((key), (hintp))) < 0) {
ptrdiff_t maxOfs = hint + 1;
lsize tmp;
while (ofs < maxOfs
&& (compare((key), (((char *)(hintp) + (-ofs) * 16)))) < 0) {
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
tmp = lastOfs;
lastOfs = hint + 1 - ofs;
ofs = hint - tmp;
}
else {
ptrdiff_t maxOfs = len - hint;
while (ofs < maxOfs && (compare((key), (((char *)(hintp) + (ofs) * 16)))) >= 0)
{
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
lastOfs += hint + 1;
ofs += hint;
}
while (lastOfs < ofs) {
lsize m = (lastOfs & ofs) + ((lastOfs ^ ofs) >> 1);
if ((compare((key), (((char *)(base) + (m) * 16)))) < 0)
ofs = m;
else
lastOfs = m + 1;
}
(void)width;
return ofs;
}
static int mergeLo_16 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width) {
void* tmp = ensureCapacity(ts, len1, width);
char* cursor1;
char* cursor2;
char* dest;
comparator compare;
lsize minGallop;
if (!tmp)
return (-1);
memcpy(tmp, base1, ((len1) * 16));
cursor1 = (char*)tmp;
cursor2 = (char*)base2;
dest = (char*)base1;
memcpy(dest, cursor2, 16);
dest = (char*)((void *)((char *)(dest) + 16));
cursor2 = (char*)((void *)((char *)(cursor2) + 16));
if (--len2 == 0) {
memcpy(dest, cursor1, ((len1) * 16));
return 0;
}
if (len1 == 1) {
memmove(dest, cursor2, ((len2) * 16));
memcpy(((char *)(dest) + (len2) * 16), cursor1, 16);
return 0;
}
compare = ts->c;
minGallop = ts->minGallop;
while (1) {
lsize count1 = 0;
lsize count2 = 0;
do {
if ((compare((cursor2), (cursor1))) < 0) {
memcpy(dest, cursor2, 16);
dest = (char*)((void *)((char *)(dest) + 16));
cursor2 = (char*)((void *)((char *)(cursor2) + 16));
count2++;
count1 = 0;
if (--len2 == 0)
goto outer;
if (count2 >= minGallop)
break;
}
else {
memcpy(dest, cursor1, 16);
dest = (char*)((void *)((char *)(dest) + 16));
cursor1 = (char*)((void *)((char *)(cursor1) + 16));
count1++;
count2 = 0;
if (--len1 == 1)
goto outer;
if (count1 >= minGallop)
break;
}
}
while (true);
do {
count1 =
gallopRight_16 (cursor2, cursor1, len1, 0,
(compare), width);
if (count1 != 0) {
memcpy(dest, cursor1, ((count1) * 16));
dest = ((char *)(dest) + (count1) * 16);
cursor1 = ((char *)(cursor1) + (count1) * 16);
len1 -= count1;
if (len1 <= 1)
goto outer;
}
memcpy(dest, cursor2, 16);
dest = (char*)((void *)((char *)(dest) + 16));
cursor2 = (char*)((void *)((char *)(cursor2) + 16));
if (--len2 == 0)
goto outer;
count2 =
gallopLeft_16 (cursor1, cursor2, len2, 0,
(compare), width);
if (count2 != 0) {
memmove(dest, cursor2, ((count2) * 16));
dest = ((char *)(dest) + (count2) * 16);
cursor2 = ((char *)(cursor2) + (count2) * 16);
len2 -= count2;
if (len2 == 0)
goto outer;
}
memcpy(dest, cursor1, 16);
dest = (char*)((void *)((char *)(dest) + 16));
cursor1 = (char*)((void *)((char *)(cursor1) + 16));
if (--len1 == 1)
goto outer;
if (minGallop > 0)
minGallop--;
}
while (count1 >= 7 || count2 >= 7);
minGallop += 2;
}
outer:
ts->minGallop = minGallop < 1 ? 1 : minGallop;
if (len1 == 1) {
memmove(dest, cursor2, ((len2) * 16));
memcpy(((char *)(dest) + (len2) * 16), cursor1, 16);
}
else if (len1 == 0) {
errno = 22;
return (-1);
}
else {
memcpy(dest, cursor1, ((len1) * 16));
}
return 0;
}
static int mergeHi_16 (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width) {
void* tmp = ensureCapacity(ts, len2, width);
char* cursor1;
char* cursor2;
char* dest;
comparator compare;
ptrdiff_t minGallop;
if (!tmp)
return (-1);
memcpy(tmp, base2, ((len2) * 16));
cursor1 = ((char *)(base1) + (len1 - 1) * 16);
cursor2 = ((char *)(tmp) + (len2 - 1) * 16);
dest = ((char *)(base2) + (len2 - 1) * 16);
memcpy(dest, cursor1, 16);
dest = (char*)((void *)((char *)(dest) - 16));
cursor1 = (char*)((void *)((char *)(cursor1) - 16));
if (--len1 == 0) {
memcpy(((char *)(dest) + (-((ptrdiff_t)((len2 - 1)))) * 16), tmp, ((len2) * 16));
return 0;
}
if (len2 == 1) {
dest = ((char *)(dest) + (-((ptrdiff_t)len1)) * 16);
cursor1 = ((char *)(cursor1) + (-((ptrdiff_t)len1)) * 16);
memmove(((char *)(dest) + (1) * 16), ((char *)(cursor1) + (1) * 16), ((len1) * 16));
memcpy(dest, cursor2, 16);
return 0;
}
compare = ts->c;
minGallop = ts->minGallop;
while (1) {
ptrdiff_t count1 = 0;
ptrdiff_t count2 = 0;
do {
if ((compare((cursor2), (cursor1))) < 0) {
memcpy(dest, cursor1, 16);
dest = (char*)((void *)((char *)(dest) - 16));
cursor1 = (char*)((void *)((char *)(cursor1) - 16));
count1++;
count2 = 0;
if (--len1 == 0)
goto outer;
}
else {
memcpy(dest, cursor2, 16);
dest = (char*)((void *)((char *)(dest) - 16));
cursor2 = (char*)((void *)((char *)(cursor2) - 16));
count2++;
count1 = 0;
if (--len2 == 1)
goto outer;
}
}
while ((count1 | count2) < minGallop);
do {
count1 =
len1 - gallopRight_16 (cursor2, base1,
len1, len1 - 1,
(compare),
width);
if (count1 != 0) {
dest = ((char *)(dest) + (-count1) * 16);
cursor1 = ((char *)(cursor1) + (-count1) * 16);
len1 -= count1;
memmove((char*)((void *)((char *)(dest) + 16)), (char*)((void *)((char *)(cursor1) + 16)),
((count1) * 16));
if (len1 == 0)
goto outer;
}
memcpy(dest, cursor2, 16);
dest = (char*)((void *)((char *)(dest) - 16));
cursor2 = (char*)((void *)((char *)(cursor2) - 16));
if (--len2 == 1)
goto outer;
count2 =
len2 - gallopLeft_16 (cursor1, tmp, len2,
len2 - 1, (compare),
width);
if (count2 != 0) {
dest = ((char *)(dest) + (-count2) * 16);
cursor2 = ((char *)(cursor2) + (-count2) * 16);
len2 -= count2;
memcpy((char*)((void *)((char *)(dest) + 16)), (char*)((void *)((char *)(cursor2) + 16)), ((count2) * 16));
if (len2 <= 1)
goto outer;
}
memcpy(dest, cursor1, 16);
dest = (char*)((void *)((char *)(dest) - 16));
cursor1 = (char*)((void *)((char *)(cursor1) - 16));
if (--len1 == 0)
goto outer;
if (minGallop > 0)
minGallop--;
}
while (count1 >= 7 || count2 >= 7);
minGallop += 2;
}
outer:
ts->minGallop = minGallop < 1 ? 1 : minGallop;
if (len2 == 1)
{
dest = ((char *)(dest) + (-((ptrdiff_t)len1)) * 16);
cursor1 = ((char *)(cursor1) + (-((ptrdiff_t)len1)) * 16);
memmove((char*)((void *)((char *)(dest) + 16)), (char*)((void *)((char *)(cursor1) + 16)), ((len1) * 16));
memcpy(dest, cursor2, 16);
}
else if (len2 == 0)
{
errno = 22;
return (-1);
}
else
{
memcpy(((char *)(dest) + (-((ptrdiff_t)(len2 - 1))) * 16), tmp, ((len2) * 16));
}
return 0;
}
static void binarySort_width (void* a, lsize hi, lsize start,
comparator compare, lsize width);
static lsize countRunAndMakeAscending_width (void* a, lsize hi,
comparator compare,
lsize width);
static void reverseRange_width (void* a, lsize hi, lsize width);
static int mergeCollapse_width (struct timsort* ts, lsize width);
static int mergeForceCollapse_width (struct timsort* ts, lsize width);
static int mergeAt_width (struct timsort* ts, lsize i, lsize width);
static lsize gallopLeft_width (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width);
static lsize gallopRight_width (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width);
static int mergeLo_width (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width);
static int mergeHi_width (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width);
static int timsort_width (void* a, lsize nel, lsize width, comparator c)
{
int err = 0;
struct timsort ts;
lsize minRun;
if (nel < 2 || !width)
return err;
if (nel < 32) {
lsize initRunLen =
countRunAndMakeAscending_width (a, nel, (c), width);
binarySort_width (a, nel, initRunLen, (c), width);
return err;
}
if ((err = timsort_init(&ts, a, nel, (c), width)))
return err;
minRun = minRunLength(nel);
do {
lsize runLen =
countRunAndMakeAscending_width (a, nel, (c), width);
if (runLen < minRun) {
lsize force = nel <= minRun ? nel : minRun;
binarySort_width (a, force, runLen, (c), width);
runLen = force;
}
pushRun(&ts, a, runLen);
if ((err = mergeCollapse_width (&ts, width)))
goto out;
a = ((char *)(a) + (runLen) * width);
nel -= runLen;
}
while (nel != 0);
if ((err = mergeForceCollapse_width (&ts, width)))
goto out;
out:
timsort_deinit(&ts);
return err;
}
static void binarySort_width (void* a, lsize hi, lsize start,
comparator compare, lsize width) {
void *pivot = __builtin_alloca(width);
char* startp;
if (start == 0)
start++;
startp = ((char *)(a) + (start) * width);
for (; start < hi; start++, startp = (char*)((void *)((char *)(startp) + width))) {
char* leftp = (char*)a;
lsize right = start;
lsize n;
while (0 < right) {
lsize mid = right >> 1;
void* midp = ((char *)(leftp) + (mid) * width);
if ((compare((startp), (midp))) < 0) {
right = mid;
}
else {
leftp = (char*)((void *)((char *)(midp) + width));
right -= (mid + 1);
}
}
n = startp - leftp;
memcpy(pivot, startp, width);
memmove((char*)((void *)((char *)(leftp) + width)), leftp, n);
memcpy(leftp, pivot, width);
}
;
(void)width;
}
static lsize countRunAndMakeAscending_width (void* a, lsize hi,
comparator compare, lsize width)
{
lsize runHi = 1;
char* cur;
char* next;
if (runHi == hi)
return 1;
cur = (char*)((void *)((char *)(a) + width));
next = (char*)((void *)((char *)(cur) + width));
runHi++;
if ((compare((cur), (a))) < 0) {
while (runHi < hi && (compare((next), (cur))) < 0) {
runHi++;
cur = next;
next = (char*)((void *)((char *)(next) + width));
}
reverseRange_width (a, runHi, width);
}
else {
while (runHi < hi && (compare((next), (cur))) >= 0) {
runHi++;
cur = next;
next = (char*)((void *)((char *)(next) + width));
}
}
(void)width;
return runHi;
}
static void reverseRange_width (void* a, lsize hi, lsize width) {
void *t = __builtin_alloca(width);
char* front = (char*)a;
char* back = ((char *)(a) + (hi - 1) * width);
while (front < back) {
memcpy(t, front, width);
memcpy(front, back, width);
memcpy(back, t, width);
front = (char*)((void *)((char *)(front) + width));
back = (char*)((void *)((char *)(back) - width));
}
;
(void)width;
}
static int mergeCollapse_width (struct timsort* ts, lsize width) {
int err = 0;
while (ts->stackSize > 1) {
lsize n = ts->stackSize - 2;
struct timsort_run* run = ts->run;
if ((n > 0 && run[n - 1].len <= run[n].len + run[n + 1].len)
|| (n > 1 && run[n - 2].len <= run[n].len + run[n - 1].len)) {
if (run[n - 1].len < run[n + 1].len)
n--;
}
else if (run[n].len > run[n + 1].len) {
break;
}
err = mergeAt_width (ts, n, width);
if (err)
break;
}
return err;
}
static int mergeForceCollapse_width (struct timsort* ts, lsize width) {
int err = 0;
while (ts->stackSize > 1) {
lsize n = ts->stackSize - 2;
if (n > 0 && ts->run[n - 1].len < ts->run[n + 1].len)
n--;
err = mergeAt_width (ts, n, width);
if (err)
break;
}
return err;
}
static int mergeAt_width (struct timsort* ts, lsize i, lsize width) {
void* base1 = ts->run[i].base;
lsize len1 = ts->run[i].len;
void* base2 = ts->run[i + 1].base;
lsize len2 = ts->run[i + 1].len;
lsize k;
ts->run[i].len = len1 + len2;
if (i == ts->stackSize - 3) {
ts->run[i + 1] = ts->run[i + 2];
}
ts->stackSize--;
k = gallopRight_width (base2, base1, len1, 0, (ts->c), width);
base1 = ((char *)(base1) + (k) * width);
len1 -= k;
if (len1 == 0)
return 0;
len2 =
gallopLeft_width (((char *)(base1) + (len1 - 1) * width), base2, len2, len2 - 1,
(ts->c), width);
if (len2 == 0)
return 0;
if (len1 <= len2)
return mergeLo_width (ts, base1, len1, base2, len2, width);
else
return mergeHi_width (ts, base1, len1, base2, len2, width);
}
static lsize gallopLeft_width (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width) {
char* hintp = ((char *)(base) + (hint) * width);
ptrdiff_t lastOfs = 0;
ptrdiff_t ofs = 1;
if ((compare((key), (hintp))) > 0) {
ptrdiff_t maxOfs = len - hint;
while (ofs < maxOfs
&& (compare((key), (((char *)(hintp) + (ofs) * width)))) > 0) {
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
lastOfs += hint + 1;
ofs += hint;
}
else {
const ptrdiff_t maxOfs = hint + 1;
lsize tmp;
while (ofs < maxOfs && (compare((key), (((char *)(hintp) + (-ofs) * width)))) <= 0)
{
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
tmp = lastOfs;
lastOfs = hint + 1 - ofs;
ofs = hint - tmp;
}
while (lastOfs < ofs) {
lsize m = (lastOfs & ofs) + ((lastOfs ^ ofs) >> 1);
if ((compare((key), (((char *)(base) + (m) * width)))) > 0)
lastOfs = m + 1;
else
ofs = m;
}
(void)width;
return ofs;
}
static lsize gallopRight_width (void* key, void* base, lsize len,
lsize hint, comparator compare,
lsize width) {
char* hintp = ((char *)(base) + (hint) * width);
ptrdiff_t ofs = 1;
ptrdiff_t lastOfs = 0;
if ((compare((key), (hintp))) < 0) {
ptrdiff_t maxOfs = hint + 1;
lsize tmp;
while (ofs < maxOfs
&& (compare((key), (((char *)(hintp) + (-ofs) * width)))) < 0) {
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
tmp = lastOfs;
lastOfs = hint + 1 - ofs;
ofs = hint - tmp;
}
else {
ptrdiff_t maxOfs = len - hint;
while (ofs < maxOfs && (compare((key), (((char *)(hintp) + (ofs) * width)))) >= 0)
{
lastOfs = ofs;
ofs = (ofs << 1) + 1;
}
if (ofs > maxOfs)
ofs = maxOfs;
lastOfs += hint + 1;
ofs += hint;
}
while (lastOfs < ofs) {
lsize m = (lastOfs & ofs) + ((lastOfs ^ ofs) >> 1);
if ((compare((key), (((char *)(base) + (m) * width)))) < 0)
ofs = m;
else
lastOfs = m + 1;
}
(void)width;
return ofs;
}
static int mergeLo_width (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width) {
void* tmp = ensureCapacity(ts, len1, width);
char* cursor1;
char* cursor2;
char* dest;
comparator compare;
lsize minGallop;
if (!tmp)
return (-1);
memcpy(tmp, base1, ((len1) * width));
cursor1 = (char*)tmp;
cursor2 = (char*)base2;
dest = (char*)base1;
memcpy(dest, cursor2, width);
dest = (char*)((void *)((char *)(dest) + width));
cursor2 = (char*)((void *)((char *)(cursor2) + width));
if (--len2 == 0) {
memcpy(dest, cursor1, ((len1) * width));
return 0;
}
if (len1 == 1) {
memmove(dest, cursor2, ((len2) * width));
memcpy(((char *)(dest) + (len2) * width), cursor1, width);
return 0;
}
compare = ts->c;
minGallop = ts->minGallop;
while (1) {
lsize count1 = 0;
lsize count2 = 0;
do {
if ((compare((cursor2), (cursor1))) < 0) {
memcpy(dest, cursor2, width);
dest = (char*)((void *)((char *)(dest) + width));
cursor2 = (char*)((void *)((char *)(cursor2) + width));
count2++;
count1 = 0;
if (--len2 == 0)
goto outer;
if (count2 >= minGallop)
break;
}
else {
memcpy(dest, cursor1, width);
dest = (char*)((void *)((char *)(dest) + width));
cursor1 = (char*)((void *)((char *)(cursor1) + width));
count1++;
count2 = 0;
if (--len1 == 1)
goto outer;
if (count1 >= minGallop)
break;
}
}
while (true);
do {
count1 =
gallopRight_width (cursor2, cursor1, len1, 0,
(compare), width);
if (count1 != 0) {
memcpy(dest, cursor1, ((count1) * width));
dest = ((char *)(dest) + (count1) * width);
cursor1 = ((char *)(cursor1) + (count1) * width);
len1 -= count1;
if (len1 <= 1)
goto outer;
}
memcpy(dest, cursor2, width);
dest = (char*)((void *)((char *)(dest) + width));
cursor2 = (char*)((void *)((char *)(cursor2) + width));
if (--len2 == 0)
goto outer;
count2 =
gallopLeft_width (cursor1, cursor2, len2, 0,
(compare), width);
if (count2 != 0) {
memmove(dest, cursor2, ((count2) * width));
dest = ((char *)(dest) + (count2) * width);
cursor2 = ((char *)(cursor2) + (count2) * width);
len2 -= count2;
if (len2 == 0)
goto outer;
}
memcpy(dest, cursor1, width);
dest = (char*)((void *)((char *)(dest) + width));
cursor1 = (char*)((void *)((char *)(cursor1) + width));
if (--len1 == 1)
goto outer;
if (minGallop > 0)
minGallop--;
}
while (count1 >= 7 || count2 >= 7);
minGallop += 2;
}
outer:
ts->minGallop = minGallop < 1 ? 1 : minGallop;
if (len1 == 1) {
memmove(dest, cursor2, ((len2) * width));
memcpy(((char *)(dest) + (len2) * width), cursor1, width);
}
else if (len1 == 0) {
errno = 22;
return (-1);
}
else {
memcpy(dest, cursor1, ((len1) * width));
}
return 0;
}
static int mergeHi_width (struct timsort* ts, void* base1, lsize len1,
void* base2, lsize len2, lsize width) {
void* tmp = ensureCapacity(ts, len2, width);
char* cursor1;
char* cursor2;
char* dest;
comparator compare;
ptrdiff_t minGallop;
if (!tmp)
return (-1);
memcpy(tmp, base2, ((len2) * width));
cursor1 = ((char *)(base1) + (len1 - 1) * width);
cursor2 = ((char *)(tmp) + (len2 - 1) * width);
dest = ((char *)(base2) + (len2 - 1) * width);
memcpy(dest, cursor1, width);
dest = (char*)((void *)((char *)(dest) - width));
cursor1 = (char*)((void *)((char *)(cursor1) - width));
if (--len1 == 0) {
memcpy(((char *)(dest) + (-((ptrdiff_t)((len2 - 1)))) * width), tmp, ((len2) * width));
return 0;
}
if (len2 == 1) {
dest = ((char *)(dest) + (-((ptrdiff_t)len1)) * width);
cursor1 = ((char *)(cursor1) + (-((ptrdiff_t)len1)) * width);
memmove(((char *)(dest) + (1) * width), ((char *)(cursor1) + (1) * width), ((len1) * width));
memcpy(dest, cursor2, width);
return 0;
}
compare = ts->c;
minGallop = ts->minGallop;
while (1) {
ptrdiff_t count1 = 0;
ptrdiff_t count2 = 0;
do {
if ((compare((cursor2), (cursor1))) < 0) {
memcpy(dest, cursor1, width);
dest = (char*)((void *)((char *)(dest) - width));
cursor1 = (char*)((void *)((char *)(cursor1) - width));
count1++;
count2 = 0;
if (--len1 == 0)
goto outer;
}
else {
memcpy(dest, cursor2, width);
dest = (char*)((void *)((char *)(dest) - width));
cursor2 = (char*)((void *)((char *)(cursor2) - width));
count2++;
count1 = 0;
if (--len2 == 1)
goto outer;
}
}
while ((count1 | count2) < minGallop);
do {
count1 =
len1 - gallopRight_width (cursor2, base1,
len1, len1 - 1,
(compare),
width);
if (count1 != 0) {
dest = ((char *)(dest) + (-count1) * width);
cursor1 = ((char *)(cursor1) + (-count1) * width);
len1 -= count1;
memmove((char*)((void *)((char *)(dest) + width)), (char*)((void *)((char *)(cursor1) + width)),
((count1) * width));
if (len1 == 0)
goto outer;
}
memcpy(dest, cursor2, width);
dest = (char*)((void *)((char *)(dest) - width));
cursor2 = (char*)((void *)((char *)(cursor2) - width));
if (--len2 == 1)
goto outer;
count2 =
len2 - gallopLeft_width (cursor1, tmp, len2,
len2 - 1, (compare),
width);
if (count2 != 0) {
dest = ((char *)(dest) + (-count2) * width);
cursor2 = ((char *)(cursor2) + (-count2) * width);
len2 -= count2;
memcpy((char*)((void *)((char *)(dest) + width)), (char*)((void *)((char *)(cursor2) + width)), ((count2) * width));
if (len2 <= 1)
goto outer;
}
memcpy(dest, cursor1, width);
dest = (char*)((void *)((char *)(dest) - width));
cursor1 = (char*)((void *)((char *)(cursor1) - width));
if (--len1 == 0)
goto outer;
if (minGallop > 0)
minGallop--;
}
while (count1 >= 7 || count2 >= 7);
minGallop += 2;
}
outer:
ts->minGallop = minGallop < 1 ? 1 : minGallop;
if (len2 == 1)
{
dest = ((char *)(dest) + (-((ptrdiff_t)len1)) * width);
cursor1 = ((char *)(cursor1) + (-((ptrdiff_t)len1)) * width);
memmove((char*)((void *)((char *)(dest) + width)), (char*)((void *)((char *)(cursor1) + width)), ((len1) * width));
memcpy(dest, cursor2, width);
}
else if (len2 == 0)
{
errno = 22;
return (-1);
}
else
{
memcpy(((char *)(dest) + (-((ptrdiff_t)(len2 - 1))) * width), tmp, ((len2) * width));
}
return 0;
}
int timsort(void* a, lsize nel, lsize width, comparator c)
{
switch (width) {
case 4:
return timsort_4(a, nel, width, (c));
case 8:
return timsort_8(a, nel, width, (c));
case 16:
return timsort_16(a, nel, width, (c));
default:
return timsort_width(a, nel, width, (c));
}
}
