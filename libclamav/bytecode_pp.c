#include "bytecode_priv.h"
#include <stdio.h>

static char * str_of_opcode(enum bc_opcode opcode)
{
  switch (opcode) {
  case OP_BC_ADD:
    return "ADD"; 
  case OP_BC_SUB:
    return "SUB";
  case OP_BC_MUL:
    return "MUL";
  case OP_BC_UDIV:
    return "UDIV";
  case OP_BC_SDIV:
    return "SDIV";
  case OP_BC_UREM:
    return "UREM";
  case OP_BC_SREM:
    return "SREM";
  case OP_BC_SHL:
    return "SHL";
  case OP_BC_LSHR:
    return "LSHR";
  case OP_BC_ASHR:
    return "ASHR";
  case OP_BC_AND:
    return "AND";
  case OP_BC_OR:
    return "OR";
  case OP_BC_XOR:
    return "XOR";

  case OP_BC_TRUNC:
    return "TRUNC";
  case OP_BC_SEXT:
    return "SEXT";
  case OP_BC_ZEXT:
    return "ZEXT";

  case OP_BC_BRANCH:
    return "BRANCH";
  case OP_BC_JMP:
    return "JMP";
  case OP_BC_RET:
    return "RET";
  case OP_BC_RET_VOID:
    return "RET_VOID";

  case OP_BC_ICMP_EQ:
    return "ICMP_EQ";
  case OP_BC_ICMP_NE:
    return "ICMP_NE";
  case OP_BC_ICMP_UGT:
    return "ICMP_UGT";
  case OP_BC_ICMP_UGE:
    return "ICMP_UGE";
  case OP_BC_ICMP_ULT:
    return "ICMP_ULT";
  case OP_BC_ICMP_ULE:
    return "ICMP_ULE";
  case OP_BC_ICMP_SGT:
    return "ICMP_SGT";
  case OP_BC_ICMP_SGE:
    return "ICMP_SGE";
  case OP_BC_ICMP_SLE:
    return "ICMP_SLE";
  case OP_BC_ICMP_SLT:
    return "ICMP_SLT";
  case OP_BC_SELECT:
    return "SELECT";
  case OP_BC_CALL_DIRECT:
    return "CALL_DIRECT";
  case OP_BC_CALL_API:
    return "CALL_API";
  case OP_BC_COPY:
    return "COPY";
  case OP_BC_GEP1:
    return "GEP1";
  case OP_BC_GEPZ:
    return "GEPZ";
  case OP_BC_GEPN:
    return "GEPN";
  case OP_BC_STORE:
    return "STORE";
  case OP_BC_LOAD:
    return "LOAD";
  case OP_BC_MEMSET:
    return "MEMSET";
  case OP_BC_MEMCPY:
    return "MEMCPY";
  case OP_BC_MEMMOVE:
    return "MEMMOVE";
  case OP_BC_MEMCMP:
    return "MEMCMP";
  case OP_BC_ISBIGENDIAN:
    return "ISBIGENDIAN";
  case OP_BC_ABORT:
    return "ABORT";
  case OP_BC_BSWAP16:
    return "BSWAP16";
  case OP_BC_BSWAP32:
    return "BSWAP32";
  case OP_BC_BSWAP64:
    return "BSWAP64";
  case OP_BC_PTRDIFF32:
    return "PTRDIFF32";
  case OP_BC_PTRTOINT64:
    return "PTRTOINT64";
  case OP_BC_INVALID:
    return "INVALID"; /* last */
  };

}

char * str_of_inst(struct cli_bc_inst *inst)
{
  char *buf;
  int disas_buf_size = 256;
  buf = calloc(sizeof(char), disas_buf_size);
  char *opcode_str = str_of_opcode(inst->opcode);


  snprintf(buf, disas_buf_size, "%s", opcode_str);


  return buf;
}

int pp_inst(struct cli_bc_inst *inst)
{
  char *inst_str, ret;
  inst_str = str_of_inst(inst);
  ret = fprintf(stdout, "%s\n", inst_str);
  free(inst_str);
  return ret;
}


char * printable_str(char *buf, int len) {
  char *pr;
  pr = calloc(sizeof(char), len * 4 + 2);
  int i;
  unsigned int ptr = 0;
  for (i = 0; i < len; i++) {
    if (buf[i] < 0x7F && buf[i] >= 0x20) {
      pr[ptr++] = buf[i];
    } else {
      ptr += sprintf(pr+ptr, "\\x%02x", buf[i]);
    }
  }
  return pr;
}
