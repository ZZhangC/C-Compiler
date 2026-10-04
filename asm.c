#include "defs.h"
#include "data.h"
#include "decl.h"

static int freeReg[4];
static char *regList[4] = { "%r8", "%r9", "%r10", "%r11" };

// Set all registers as available
void setAllRegFree(void) {
	freeReg[0] = freeReg[1] = freeReg[2] = freeReg[3] = 1;
}

// Allocate a free register
static int allocReg(void) {
	for (int i = 0; i < 4; i++) {
		if (freeReg[i]) {
			freeReg[i] = 0;
			return i;
		}
	}
	fprintf(stderr, "Run out of registers\n");
	exit(1);
}

static void setRegFree(int reg) {
	if (freeReg[reg] != 0) {
		fprintf(stderr, "Error trying to free register %d\n", reg);
		exit(1);
	}
	freeReg[reg] = 1;
}

void genASMPreamble() {
	setAllRegFree();
	fputs(
		"\t.text\n"
		".LC0:\n"
		"\t.string\t\"%d\\n\"\n"
		"printint:\n"
		"\tpushq\t%rbp\n"
		"\tmovq\t%rsp, %rbp\n"
		"\tsubq\t$16, %rsp\n"
		"\tmovl\t%edi, -4(%rbp)\n"
		"\tmovl\t-4(%rbp), %eax\n"
		"\tmovl\t%eax, %esi\n"
		"\tleaq	.LC0(%rip), %rdi\n"
		"\tmovl	$0, %eax\n"
		"\tcall	printf@PLT\n"
		"\tnop\n"
		"\tleave\n"
		"\tret\n"
		"\n"
		"\t.globl\tmain\n"
		"\t.type\tmain, @function\n"
		"main:\n"
		"\tpushq\t%rbp\n"
		"\tmovq	%rsp, %rbp\n",
		outFile);
}

void genASMPostamble() {
	fputs(
		"\tmovl	$0, %eax\n"
		"\tpopq	%rbp\n"
		"\tret\n",
		outFile);
}

int genASMLoad(int value) {
	int r = allocReg();

	fprintf(outFile, "\tmovq\t$%d, %s\n", value, regList[r]);
	return r;
}

int genASMAdd(int r1, int r2) {
	fprintf(outFile, "\taddq\t%s, %s\n", regList[r1], regList[r2]);
	setRegFree(r1);
	return r2;
}

int genASMSub(int r1, int r2) {
	fprintf(outFile, "\tsubq\t%s, %s\n", regList[r2], regList[r1]);
	setRegFree(r2);
	return r1;
}

int genASMMul(int r1, int r2) {
	fprintf(outFile, "\timulq\t%s, %s\n", regList[r1], regList[r2]);
	setRegFree(r1);
	return r2;
}

int genASMDiv(int r1, int r2) {
	fprintf(outFile, "\tmovq\t%s, %%rax\n", regList[r1]);
	fprintf(outFile, "\tcqo\n");
	fprintf(outFile, "\tidivq\t%s\n", regList[r2]);
	fprintf(outFile, "\tmovq\t%rax, %s\n", regList[r1]);
	setRegFree(r2);
	return r1;
}

void genASMPrintInt(int r) {
	fprintf(outFile, "\tmovq\t%s, %%rdi\n", regList[r]);
	fprintf(outFile, "\tcall\tprintint\n");
	setRegFree(r);
}

int genASMLoadGlob(char *ident) {
	int r = allocReg();
	fprintf(outFile, "\tmovq\t%s(\%%rip), %s\n", ident, regList[r]);
	return r;
}

int genASMStorGlob(int r, char *ident) {
	fprintf(outFile, "\tmovq\t%s, %s(\%%rip)\n", regList[r], ident);
	return r;
}

void genASMGlobSym(char *sym) {
	fprintf(outFile, "\t.comm\t%s,8,8\n", sym);
}
