#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned manufacturers_hex[10][3] = 
{
	{ 0x756E6547, 0x49656E69, 0x6C65746E },
	{ 0x68747541, 0x69746E65, 0x444D4163 },
	{ 0x69727943, 0x736E4978, 0x64616574 },
	{ 0x746E6543, 0x48727561, 0x736C7561 },
	{ 0x20536953, 0x20536953, 0x20536953 },
	{ 0x4778654E, 0x72446E65, 0x6E657669 },
	{ 0x756E6547, 0x54656E69, 0x3638784D },
	{ 0x65736952, 0x65736952, 0x65736952 },
	{ 0x20434D55, 0x20434D55, 0x20434D55 },
	{ 0x646F6547, 0x79622065, 0x43534E20 }
};

const char *manufacturers_str[10] = {"Intel", "AMD", "Cyrix", "Centaur", "SiS", "NexGen", "Transmeta",
	"Rise", "UMC", "National Semiconductor"};

const char appnote[] = {"######## Mini CPUID ########\n#### Written by DuXeN0N ####\n\n"};

int has_cpuid()
{
	__asm
	{	
		pushfd         
		pop eax        
		mov ebx, eax   
		xor eax, 200000h
		push eax        
		popfd           
		pushfd          
		pop eax         
		xor eax, ebx    
		je no_cpuid
	}
	return 1;
no_cpuid:
	return 0;
}

#define REG_EAX 0
#define REG_EBX 1
#define REG_ECX 2
#define REG_EDX 3

void get_cpuid(unsigned flag, unsigned *regs)
{
	unsigned r_eax, r_ebx, r_ecx, r_edx;
	__asm
	{
		pushad
		mov eax, flag
		cpuid
		mov r_eax, eax
		mov r_ebx, ebx
		mov r_ecx, ecx
		mov r_edx, edx
		popad
	}
	regs[REG_EAX] = r_eax;
	regs[REG_EBX] = r_ebx;
	regs[REG_ECX] = r_ecx;
	regs[REG_EDX] = r_edx;
}

const char *get_manufacturer()
{
	unsigned regs[4];
	unsigned info[3];
	int i, index = -1;
	get_cpuid(0, regs);
	info[0] = regs[REG_EBX];
	info[1] = regs[REG_EDX];
	info[2] = regs[REG_ECX];
	for (i = 0; i < 10; ++i)
		if (memcmp(info, manufacturers_hex[i], 3 * sizeof(int)) == 0)
		{
			index = i;
			break;
		}
	return manufacturers_str[index];
}

int Has_SSE()
{
	unsigned regs[4];
	get_cpuid(1, regs);
	return ((regs[REG_EDX] & (1 << 25)) > 0);
}

int Has_SSE2()
{
	unsigned regs[4];
	get_cpuid(1, regs);
	return ((regs[REG_EDX] & (1 << 26)) > 0);
}

int Has_SSE3()
{
	unsigned regs[4];
	get_cpuid(1, regs);
	return ((regs[REG_ECX] & 1) > 0);
}

int Has_SSSE3()
{
	unsigned regs[4];
	get_cpuid(1, regs);
	return ((regs[REG_ECX] & (1 << 9)) > 0);
}

int Has_MMX()
{
	unsigned regs[4];
	get_cpuid(1, regs);
	return ((regs[REG_EDX] & (1 << 23)) > 0);
}

int Has_3DNow()
{
	unsigned regs[4];
	get_cpuid(0x80000000, regs);
	if (regs[REG_EAX] < 0x80000000)
		return 0;
	get_cpuid(0x80000001, regs);
	return ((regs[REG_EDX] & (1 << 31)) > 0);
}

int Has_SSE4()
{
	unsigned regs[4];
	int flags[3];
	get_cpuid(1, regs);
	flags[0] = (regs[REG_ECX] & (1 << 19)) > 0;  // SSE 4.1
	flags[1] = (regs[REG_ECX] & (1 << 20)) > 0;  // SSE 4.2
	flags[2] = (regs[REG_ECX] & (1 << 6)) > 0;   // SSE 4A
	return (flags[0] && flags[1] && flags[2]);
}

int main()
{
	printf("%s", appnote);
	if (!has_cpuid())
	{
		printf("CPUID instruction is not supported!\n");
		return 0;
	}
	printf("Manufacturer: %s\n", get_manufacturer());
	printf("Supported instructions:\n");
	if (Has_SSE())
		printf("- SSE\n");
	if (Has_SSE2())
		printf("- SSE2\n");
	if (Has_SSE3())
		printf("- SSE3\n");
	if (Has_SSSE3())
		printf("- SSSE3\n");
	if (Has_SSE4())
		printf("- SSE4 (4.1, 4.2, 4A)\n");
	if (Has_MMX())
		printf("- MMX\n");
	if (Has_3DNow())
		printf("- 3DNow!\n");
	return 0;
}