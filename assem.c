#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void opcode_finder(char *opcode_str, int *opcode, int *funct3, int *funct7) {
    *funct3 = 0; *funct7 = 0; // default

    if (strcmp(opcode_str,"add")==0){ *opcode=0b0110011; *funct3=0b000; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"sub")==0){ *opcode=0b0110011; *funct3=0b000; *funct7=0b0100000; }
    else if (strcmp(opcode_str,"sll")==0){ *opcode=0b0110011; *funct3=0b001; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"slt")==0){ *opcode=0b0110011; *funct3=0b010; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"sltu")==0){ *opcode=0b0110011; *funct3=0b011; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"xor")==0){ *opcode=0b0110011; *funct3=0b100; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"srl")==0){ *opcode=0b0110011; *funct3=0b101; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"sra")==0){ *opcode=0b0110011; *funct3=0b101; *funct7=0b0100000; }
    else if (strcmp(opcode_str,"or")==0){ *opcode=0b0110011; *funct3=0b110; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"and")==0){ *opcode=0b0110011; *funct3=0b111; *funct7=0b0000000; }

    /* I-type ALU */
    else if (strcmp(opcode_str,"addi")==0){ *opcode=0b0010011; *funct3=0b000; }
    else if (strcmp(opcode_str,"slti")==0){ *opcode=0b0010011; *funct3=0b010; }
    else if (strcmp(opcode_str,"sltiu")==0){ *opcode=0b0010011; *funct3=0b011; }
    else if (strcmp(opcode_str,"xori")==0){ *opcode=0b0010011; *funct3=0b100; }
    else if (strcmp(opcode_str,"ori")==0){ *opcode=0b0010011; *funct3=0b110; }
    else if (strcmp(opcode_str,"andi")==0){ *opcode=0b0010011; *funct3=0b111; }
    else if (strcmp(opcode_str,"slli")==0){ *opcode=0b0010011; *funct3=0b001; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"srli")==0){ *opcode=0b0010011; *funct3=0b101; *funct7=0b0000000; }
    else if (strcmp(opcode_str,"srai")==0){ *opcode=0b0010011; *funct3=0b101; *funct7=0b0100000; }

    /* Loads */
    else if (strcmp(opcode_str,"lb")==0){ *opcode=0b0000011; *funct3=0b000; }
    else if (strcmp(opcode_str,"lh")==0){ *opcode=0b0000011; *funct3=0b001; }
    else if (strcmp(opcode_str,"lw")==0){ *opcode=0b0000011; *funct3=0b010; }
    else if (strcmp(opcode_str,"lbu")==0){ *opcode=0b0000011; *funct3=0b100; }
    else if (strcmp(opcode_str,"lhu")==0){ *opcode=0b0000011; *funct3=0b101; }

    /* Stores */
    else if (strcmp(opcode_str,"sb")==0){ *opcode=0b0100011; *funct3=0b000; }
    else if (strcmp(opcode_str,"sh")==0){ *opcode=0b0100011; *funct3=0b001; }
    else if (strcmp(opcode_str,"sw")==0){ *opcode=0b0100011; *funct3=0b010; }

    /* Branch */
    else if (strcmp(opcode_str,"beq")==0){ *opcode=0b1100011; *funct3=0b000; }
    else if (strcmp(opcode_str,"bne")==0){ *opcode=0b1100011; *funct3=0b001; }
    else if (strcmp(opcode_str,"blt")==0){ *opcode=0b1100011; *funct3=0b100; }
    else if (strcmp(opcode_str,"bge")==0){ *opcode=0b1100011; *funct3=0b101; }
    else if (strcmp(opcode_str,"bltu")==0){ *opcode=0b1100011; *funct3=0b110; }
    else if (strcmp(opcode_str,"bgeu")==0){ *opcode=0b1100011; *funct3=0b111; }

    /* Jump */
    else if (strcmp(opcode_str,"jal")==0){ *opcode=0b1101111; }
    else if (strcmp(opcode_str,"jalr")==0){ *opcode=0b1100111; *funct3=0b000; }

    /* Upper */
    else if (strcmp(opcode_str,"lui")==0){ *opcode=0b0110111; }
    else if (strcmp(opcode_str,"auipc")==0){ *opcode=0b0010111; }

    else {
        *opcode = 0;
        *funct3 = 0;
        *funct7 = 0;
    }
}

int reg_str_to_num(char *reg) {
    return atoi(reg + 1); // skip 'x'
}

void write_instruction(FILE *outfptr, int opcode_val, int fn3_val, int fn7_val,
                       int rd_val, int rs1_val, int rs2_val, int imm_val) {

    unsigned int instr = 0;

    switch(opcode_val) {
        case 0b0110011: // R-type
            instr = (fn7_val << 25) | (rs2_val << 20) | (rs1_val << 15) |
                    (fn3_val << 12) | (rd_val << 7) | opcode_val;
            break;

        case 0b0010011: // I-type
        case 0b0000011: // Loads
        case 0b1100111: // jalr
            instr = (imm_val << 20) | (rs1_val << 15) |
                    (fn3_val << 12) | (rd_val << 7) | opcode_val;
            break;

        case 0b0100011: // S-type
            instr = ((imm_val >> 5) << 25) | (rs2_val << 20) | (rs1_val << 15) |
                    (fn3_val << 12) | ((imm_val & 0x1F) << 7) | opcode_val;
            break;

        case 0b1100011: // B-type
            instr = (((imm_val >> 12) & 0x1) << 31) |
                    (((imm_val >> 5) & 0x3F) << 25) |
                    (rs2_val << 20) | (rs1_val << 15) |
                    (fn3_val << 12) |
                    (((imm_val >> 1) & 0xF) << 8) |
                    (((imm_val >> 11) & 0x1) << 7) |
                    opcode_val;
            break;

        case 0b1101111: // J-type (jal)
            instr = (((imm_val >> 20) & 0x1) << 31) |
                    (((imm_val >> 1) & 0x3FF) << 21) |
                    (((imm_val >> 11) & 0x1) << 20) |
                    (((imm_val >> 12) & 0xFF) << 12) |
                    (rd_val << 7) |
                    opcode_val;
            break;

        case 0b0110111: // LUI
        case 0b0010111: // AUIPC
            instr = (imm_val << 12) | (rd_val << 7) | opcode_val;
            break;
    }

    fprintf(outfptr, "%08x\n", instr);
}

int main() {

    FILE* fptr = fopen("code.txt", "r");
    if (!fptr) { printf("Cannot open input file.\n"); return 1; }

    FILE* outfptr = fopen("machine_code.txt", "w");
    if (!outfptr) { printf("Cannot open output file.\n"); return 1; }

    char line[100];
    while (fgets(line, sizeof(line), fptr)) {

        char opcode[20], rd[10], rs1[10], rs2[10], imm[20];
        int i = 0, j = 0;

        while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n') opcode[j++] = line[i++];
        opcode[j] = '\0';
        while (line[i] == ' ') i++;

        j = 0;
        while (line[i] != ',' && line[i] != '\0') rd[j++] = line[i++];
        rd[j] = '\0'; i++; while(line[i]==' ') i++;

        j = 0;
        while (line[i] != ',' && line[i] != '\0') rs1[j++] = line[i++];
        rs1[j] = '\0'; i++; while(line[i]==' ') i++;

        j = 0;
        while (line[i] != ',' && line[i] != '\0' && line[i] != '\n') rs2[j++] = line[i++];
        rs2[j] = '\0'; i++; while(line[i]==' ') i++;

        j = 0;
        while (line[i] != '\n' && line[i] != '\0') imm[j++] = line[i++];
        imm[j] = '\0';

        int opcode_val, fn3_val, fn7_val;
        opcode_finder(opcode, &opcode_val, &fn3_val, &fn7_val);

        int rd_val = reg_str_to_num(rd);
        int rs1_val = reg_str_to_num(rs1);
        int rs2_val = reg_str_to_num(rs2);
        int imm_val = imm[0] ? atoi(imm) : 0;

        write_instruction(outfptr, opcode_val, fn3_val, fn7_val, rd_val, rs1_val, rs2_val, imm_val);
    }

    fclose(fptr);
    fclose(outfptr);
    return 0;
}