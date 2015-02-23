#include <iostream>
#include <string>

#include <cinttypes>
#include <cstring>

using namespace std;

struct cpuinfo_1
{
	// eax
	uint32_t stepping : 4;
	uint32_t base_model : 4;
	uint32_t base_family : 4;
	uint32_t reserved_1 : 4;
	uint32_t ext_model : 4;
	uint32_t ext_family : 8;
	uint32_t reserved_2 : 4;
	
	// ebx
	uint32_t brand_id : 8;
	uint32_t clfush : 8;
	uint32_t processor_count : 8;
	uint32_t local_apic_id : 8;
	
	// ecx & edx
	uint32_t feature_flags[2];
};
static_assert(sizeof(cpuinfo_1) == 16, "cpuinfo_1 must have the size of four registers.");

// feature_flags[0]
#define FF_SSE3			(1 << 0)
#define FF_PCLMULQDQ 	(1 << 1)
#define FF_MONITOR		(1 << 3)
#define FF_SSSE3		(1 << 9)
#define FF_FMA			(1 << 12)
#define FF_CMPXCHG16B	(1 << 13)
#define FF_SSE41		(1 << 19)
#define FF_SSE42		(1 << 20)
#define FF_POPCNT		(1 << 23)
#define FF_AES			(1 << 25)
#define FF_XSAVE		(1 << 26)
#define FF_OSXSAVE		(1 << 27)
#define FF_AVX			(1 << 28)
#define FF_F16C			(1 << 29)
#define FF_RAZ			(1 << 31)

// feature_flags[1]
#define FF_FPU			(1 << 0)
#define FF_VME			(1 << 1)
#define FF_DE			(1 << 2)
#define FF_PSE			(1 << 3)
#define FF_TSC			(1 << 4)
#define FF_MSR			(1 << 5)
#define FF_PAE			(1 << 6)
#define FF_MCE			(1 << 7)
#define FF_CMPXCHG8B	(1 << 8)
#define FF_APIC			(1 << 9)
#define FF_SysEnterSysExit	(1 << 11)
#define FF_MTRR			(1 << 12)
#define FF_PGE			(1 << 13)
#define FF_MCA			(1 << 14)
#define FF_CMOV			(1 << 15)
#define FF_PAT			(1 << 16)
#define FF_PSE36		(1 << 17)
#define FF_CLFSH		(1 << 19)
#define FF_MMX			(1 << 23)
#define FF_FXSR			(1 << 24)
#define FF_SSE			(1 << 25)
#define FF_SSE2			(1 << 26)
#define FF_HTT			(1 << 28)

struct cpuinfo
{
    union
    {
        uint8_t raw[16];
        uint32_t registers[4];
        cpuinfo_1 info1;
    };
};

enum
{
    R_EAX = 0,
    R_EBX,
    R_ECX,
    R_EDX
};

#define BASE_CPUID (0)
#define EXT_CPUID  (1 << 31)
void cpuid(uint32_t level, cpuinfo & info)
{
    asm(
        "cpuid"
        : "=a"(info.registers[R_EAX]), "=b"(info.registers[R_EBX]), "=c"(info.registers[R_ECX]), "=d"(info.registers[R_EDX])
        : "a"(level)
        :
    );
}

int main()
{
	char const * yesno[] = { "no", "yes" };
	
    cpuinfo info;

    cpuid(0, info);
    uint32_t max_cpuid = info.registers[R_EAX];
    cout << "Maximum CPUID level:    " << max_cpuid << endl;

    string vendorid;
    vendorid.append((char*)&(info.registers[R_EBX]), 4);
    vendorid.append((char*)&(info.registers[R_EDX]), 4);
    vendorid.append((char*)&(info.registers[R_ECX]), 4);
    cout << "CPU Vendor:             " << vendorid << endl;
    
    cpuid(1, info);
    bool has_hyperthreading = info.info1.feature_flags[1] & FF_HTT;
    cout << "Has hyperthreading:     " << yesno[has_hyperthreading] << endl;
    if (has_hyperthreading)
	{
		cout << "CPU cores:              " << info.info1.processor_count << endl;
	}
	
#define HAS_FEATURE(ff, bit) ((bool)(info.info1.feature_flags[(ff)] & (bit)))
	cout << "Has MMX:                " << yesno[HAS_FEATURE(1, FF_MMX)] << endl;
	cout << "Has SSE:                " << yesno[HAS_FEATURE(1, FF_SSE)] << endl;
	cout << "Has SSE 2:              " << yesno[HAS_FEATURE(1, FF_SSE2)] << endl;
	cout << "Has SSE 3:              " << yesno[HAS_FEATURE(0, FF_SSE3)] << endl;
	cout << "Has Supplemental SSE 3: " << yesno[HAS_FEATURE(0, FF_SSSE3)] << endl;
	cout << "Has SSE 4.1:            " << yesno[HAS_FEATURE(0, FF_SSE41)] << endl;
	cout << "Has SSE 4.2:            " << yesno[HAS_FEATURE(0, FF_SSE42)] << endl;
#undef HAS_FEATURE

	char processor_name[48];
	cpuid(EXT_CPUID | 2, info);
	memcpy(processor_name, info.raw, 16);
	cpuid(EXT_CPUID | 3, info);
	memcpy(processor_name + 16, info.raw, 16);
	cpuid(EXT_CPUID | 4, info);
	memcpy(processor_name + 32, info.raw, 16);
	
	cout << "Proccessor name:        " << processor_name << endl;

    return 0;
}
