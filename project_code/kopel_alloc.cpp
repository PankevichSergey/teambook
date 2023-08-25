const int MAX_MEM = 1e8;
int mpos = 0;
alignas (long long) char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
	if (mpos & 7) mpos += 8 - (mpos & 7)
	char *res = mem + mpos;
	mpos += n;
	assert(mpos <= MAX_MEM);
	return (void *)res;
}
inline void operator delete ( void * ) { }
