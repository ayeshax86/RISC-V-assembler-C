// Written by: ayeshax86 on gitHub

/*

R,I,S,B,U,J

addi x1, x2, x3
R = opcode rd rs1 rs2

I = opcode rd rs1 imm

S = rd imm(rs1)

B = rs1 rs2 imm

U = rd imm in hex

J = rd imm

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// parse, encode, combine each inst

int fn_R(char *line, int *rs1_ptr, int *rs2_ptr) {
    char rd_str[10], rs1_str[10], rs2_str[10];
    int i = 0, j = 0;

    // Parse rd
    while (line[i] != ',' && line[i] != '\0') rd_str[j++] = line[i++];
    rd_str[j] = '\0'; i++; while(line[i] == ' ') i++;

    // Parse rs1
    j = 0;
    while (line[i] != ',' && line[i] != '\0') rs1_str[j++] = line[i++];
    rs1_str[j] = '\0'; i++; while(line[i] == ' ') i++;

    // Parse rs2
    j = 0;
    while (line[i] != ',' && line[i] != '\0') rs2_str[j++] = line[i++];
    rs2_str[j] = '\0';

    // Convert registers from strings to numbers
    *rs1_ptr = atoi(rs1_str + 1);   // skip 'x'
    *rs2_ptr = atoi(rs2_str + 1);   // skip 'x'
    int rd = atoi(rd_str + 1);      // skip 'x'

    return rd;  // return rd, pointers already updated
}


// I-type: e.g., addi x3, x4, 5
int fn_I(char *line, int *rs1_ptr, int *imm_ptr) {
    char rd_str[10], rs1_str[10], imm_str[20];
    int i = 0, j = 0;

    // Parse rd
    while (line[i] != ',' && line[i] != '\0') rd_str[j++] = line[i++];
    rd_str[j] = '\0'; i++; while (line[i] == ' ') i++;

    // Parse rs1
    j = 0;
    while (line[i] != ',' && line[i] != '\0') rs1_str[j++] = line[i++];
    rs1_str[j] = '\0'; i++; while (line[i] == ' ') i++;

    // Parse immediate
    j = 0;
    while (line[i] != '\0' && line[i] != '\n') imm_str[j++] = line[i++];
    imm_str[j] = '\0';

    // Convert registers and immediate
    *rs1_ptr = atoi(rs1_str + 1);          // skip 'x'
    *imm_ptr = atoi(imm_str);
    return atoi(rd_str + 1);               // return rd
}


// S-type: e.g., lw x3, 34(x2)
int fn_S(char *line, int *rs1_ptr, int *imm_ptr, int *rs2_ptr) {
    char rs2_str[10], imm_str[20], rs1_str[10];
    int i = 0, j = 0;

    // Parse rs2
    while (line[i] != ',' && line[i] != '\0') rs2_str[j++] = line[i++];
    rs2_str[j] = '\0'; i++; while (line[i] == ' ') i++;

    // Parse offset(base) like 34(x2)
    j = 0;
    while (line[i] != '(' && line[i] != '\0') imm_str[j++] = line[i++];
    imm_str[j] = '\0'; i++;  // skip '('

    // Parse base register
    j = 0;
    while (line[i] != ')' && line[i] != '\0') rs1_str[j++] = line[i++];
    rs1_str[j] = '\0';

    // Convert registers and immediate
    *rs1_ptr = atoi(rs1_str + 1);
    *rs2_ptr = atoi(rs2_str + 1);
    *imm_ptr = atoi(imm_str);

    return 0; // S-type does not have rd
}


// B-type: e.g., beq x3, x1, 16
void fn_B(char *line, int *rs1_ptr, int *rs2_ptr, int *imm_ptr) {
    char rs1_str[10], rs2_str[10], imm_str[20];
    int i = 0, j = 0;

    // Parse rs1
    while (line[i] != ',' && line[i] != '\0') rs1_str[j++] = line[i++];
    rs1_str[j] = '\0'; i++; while (line[i] == ' ') i++;

    // Parse rs2
    j = 0;
    while (line[i] != ',' && line[i] != '\0') rs2_str[j++] = line[i++];
    rs2_str[j] = '\0'; i++; while (line[i] == ' ') i++;

    // Parse immediate
    j = 0;
    while (line[i] != '\0' && line[i] != '\n') imm_str[j++] = line[i++];
    imm_str[j] = '\0';

    // Convert registers and immediate
    *rs1_ptr = atoi(rs1_str + 1);  // skip 'x'
    *rs2_ptr = atoi(rs2_str + 1);  // skip 'x'
    *imm_ptr = atoi(imm_str);

    //return 0;  // B-type does not have rd
}


// U-type: e.g., lui x1, 0x12345
int fn_U(char *line, int *imm_ptr) {
    char rd_str[10], imm_str[20];
    int i = 0, j = 0;

    // Parse rd
    while (line[i] != ',' && line[i] != '\0') rd_str[j++] = line[i++];
    rd_str[j] = '\0'; i++; while (line[i] == ' ') i++;

    // Parse immediate
    j = 0;
    while (line[i] != '\0' && line[i] != '\n') imm_str[j++] = line[i++];
    imm_str[j] = '\0';

    *imm_ptr = strtol(imm_str, NULL, 0); // allows hex or decimal
    return atoi(rd_str + 1);             // return rd
}


// J-type: e.g., jal x1, 32
int fn_J(char *line, int *imm_ptr) {
    char rd_str[10], imm_str[20];
    int i = 0, j = 0;

    // Parse rd
    while (line[i] != ',' && line[i] != '\0') rd_str[j++] = line[i++];
    rd_str[j] = '\0'; i++; while (line[i] == ' ') i++;

    // Parse immediate
    j = 0;
    while (line[i] != '\0' && line[i] != '\n') imm_str[j++] = line[i++];
    imm_str[j] = '\0';

    *imm_ptr = atoi(imm_str);
    return atoi(rd_str + 1); // return rd
}




int main () {

    FILE* fptr = fopen ("code.txt", "r");
    if (!fptr) { 
        printf ("Cannot open file.\n");
        return 1;
    }

    FILE* fout = fopen("output.hex", "w");
    if (!fout) { 
        printf ("Cannot open file.\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), fptr)) {

        char opcode_str[20];
        int i = 0, j = 0;

        while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n') opcode_str[j++] = line[i++];
        opcode_str[j] = '\0';
        while (line[i] == ' ') i++;
    

        int opcode, funct3, funct7;
        int rd;
        int rs1=0, rs2=0, imm=0;

        char inst_type = 'R';
        int machine_code = 0;

// important: just pass the address of rs1 directly. if you make a pointer in main you can use the same 
// pointer to set multiple values in multiple functions which is a good thing to remember :)

if (strcmp(opcode_str,"add")==0){ opcode=0b0110011; funct3=0b000; funct7=0b0000000; 
    rd = fn_R(line, &rs1, &rs2); 
    inst_type = 'R';
}
else if (strcmp(opcode_str,"sub")==0){ opcode=0b0110011; funct3=0b000; funct7=0b0100000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}
else if (strcmp(opcode_str,"sll")==0){ opcode=0b0110011; funct3=0b001; funct7=0b0000000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}
else if (strcmp(opcode_str,"slt")==0){ opcode=0b0110011; funct3=0b010; funct7=0b0000000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}
else if (strcmp(opcode_str,"sltu")==0){ opcode=0b0110011; funct3=0b011; funct7=0b0000000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}
else if (strcmp(opcode_str,"xor")==0){ opcode=0b0110011; funct3=0b100; funct7=0b0000000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}
else if (strcmp(opcode_str,"srl")==0){ opcode=0b0110011; funct3=0b101; funct7=0b0000000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}
else if (strcmp(opcode_str,"sra")==0){ opcode=0b0110011; funct3=0b101; funct7=0b0100000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}
else if (strcmp(opcode_str,"or")==0){ opcode=0b0110011; funct3=0b110; funct7=0b0000000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}
else if (strcmp(opcode_str,"and")==0){ opcode=0b0110011; funct3=0b111; funct7=0b0000000;
    rd = fn_R(line, &rs1, &rs2);
    inst_type = 'R';
}

/* I-type ALU */
else if (strcmp(opcode_str,"addi")==0){ opcode=0b0010011; funct3=0b000;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"slti")==0){ opcode=0b0010011; funct3=0b010;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"sltiu")==0){ opcode=0b0010011; funct3=0b011;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"xori")==0){ opcode=0b0010011; funct3=0b100;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"ori")==0){ opcode=0b0010011; funct3=0b110;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"andi")==0){ opcode=0b0010011; funct3=0b111;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"slli")==0){ opcode=0b0010011; funct3=0b001; funct7=0b0000000;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"srli")==0){ opcode=0b0010011; funct3=0b101; funct7=0b0000000;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"srai")==0){ opcode=0b0010011; funct3=0b101; funct7=0b0100000;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}

/* Loads */
else if (strcmp(opcode_str,"lb")==0){ opcode=0b0000011; funct3=0b000;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"lh")==0){ opcode=0b0000011; funct3=0b001;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"lw")==0){ opcode=0b0000011; funct3=0b010;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"lbu")==0){ opcode=0b0000011; funct3=0b100;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}
else if (strcmp(opcode_str,"lhu")==0){ opcode=0b0000011; funct3=0b101;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}

/* Stores */
else if (strcmp(opcode_str,"sb")==0){ opcode=0b0100011; funct3=0b000;
    rd = fn_S(line, &rs1, &imm);
    inst_type = 'S';
}
else if (strcmp(opcode_str,"sh")==0){ opcode=0b0100011; funct3=0b001;
    rd = fn_S(line, &rs1, &imm);
    inst_type = 'S';
}
else if (strcmp(opcode_str,"sw")==0){ opcode=0b0100011; funct3=0b010;
    rd = fn_S(line, &rs1, &imm);
    inst_type = 'S';
}

/* Branch */
else if (strcmp(opcode_str,"beq")==0){ opcode=0b1100011; funct3=0b000;
    fn_B(line, &rs1, &rs2, &imm);
    inst_type = 'B';
}
else if (strcmp(opcode_str,"bne")==0){ opcode=0b1100011; funct3=0b001;
    fn_B(line, &rs1, &rs2, &imm);
    inst_type = 'B';
}
else if (strcmp(opcode_str,"blt")==0){ opcode=0b1100011; funct3=0b100;
    fn_B(line, &rs1, &rs2, &imm);
    inst_type = 'B';
}
else if (strcmp(opcode_str,"bge")==0){ opcode=0b1100011; funct3=0b101;
    fn_B(line, &rs1, &rs2, &imm);
    inst_type = 'B';
}
else if (strcmp(opcode_str,"bltu")==0){ opcode=0b1100011; funct3=0b110;
    fn_B(line, &rs1, &rs2, &imm);
    inst_type = 'B';
}
else if (strcmp(opcode_str,"bgeu")==0){ opcode=0b1100011; funct3=0b111;
    fn_B(line, &rs1, &rs2, &imm);
    inst_type = 'B';
}

/* Jump */
else if (strcmp(opcode_str,"jal")==0){ opcode=0b1101111;
    rd = fn_J(line, &imm);
    inst_type = 'J';
}
else if (strcmp(opcode_str,"jalr")==0){ opcode=0b1100111; funct3=0b000;
    rd = fn_I(line, &rs1, &imm);
    inst_type = 'I';
}

/* Upper */
else if (strcmp(opcode_str,"lui")==0){ opcode=0b0110111;
    rd = fn_U(line, &imm);
    inst_type = 'U';
}
else if (strcmp(opcode_str,"auipc")==0){ opcode=0b0010111;
    rd = fn_U(line, &imm);
    inst_type = 'U';
}

else {
    opcode = 0;
    funct3 = 0;
    funct7 = 0;
    inst_type = 'R';
}
 

switch (inst_type) {

    case 'R':
    machine_code = (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
    break;

    case 'I':
    machine_code = (imm << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
    break;

    case 'S':
    machine_code = ((imm >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) 
    | ((imm & 0x1F) << 7) | opcode;
    break;

    case 'B':
    machine_code = (((imm >> 12) & 0x1) << 31) 
    | (((imm >> 5) & 0x3F) << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) 
    | (((imm >> 1) & 0xF) << 8) | (((imm >> 11) & 0x1) << 7) | opcode;
    break;

    case 'U':
    machine_code = (imm << 12) | (rd << 7) | opcode;
    break;

    case 'J':
    machine_code = (((imm >> 20) & 0x1) << 31) | (((imm >> 1) & 0x3FF) << 21) 
    | (((imm >> 11) & 0x1) << 20) | ((imm >> 12) & 0xFF) << 12 | (rd << 7) | opcode;
    break;

    default:
    machine_code = 0;
    break;
}


// write to file
fprintf(fout, "%08x\n", machine_code);

    } // while end - 1 inst

fclose(fout);
fclose(fptr);

} // end main

