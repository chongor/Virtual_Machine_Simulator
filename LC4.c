/*
 * LC4.c
 */

#include <stdio.h>
#include "LC4.h"

#define INSN_15_12(I) (((I) >> 12) & 0xF)
#define INSN_11_9(I) (((I) >> 9) & 0x7)
#define INSN_11(I) (((I) >> 11) & 0x1)
#define INSN_11_12(I) (((I) >> 12) & 0x3)
#define INSN_5_3(I) (((I) >> 3) & 0x7)
#define INSN_8_7(I) (((I) >> 7) & 0x3)
#define INSN_5(I) (((I) >> 5) & 0x1)
#define INSN_5_4(I) (((I) >> 4) & 0x3)
#define INSN_8(I) (((I) >> 8) & 0x1)
#define INSN_8_6(I) (((I) >> 6) & 0x7)
#define INSN_0x07(I) ((I) & 0x07)

int DecodeNOPBR (unsigned short int INSN, ControlSignals *theControls)
{
       
	unsigned short int insn = INSN_11_9(INSN);
 
	//NOP and BRxxx all have same controls
       	theControls->PCMux_CTL = 0;
       	theControls->rsMux_CTL = 0;
     	theControls->rtMux_CTL = 0;
   	theControls->rdMux_CTL = 0;
       	theControls->regFile_WE = 0;
       	theControls->regInputMux_CTL = 0;
       	theControls->Arith_CTL = 0;
       	theControls->ArithMux_CTL = 0;
       	theControls->LOGIC_CTL = 0;
       	theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
       	theControls->CMP_CTL = 0;
       	theControls->ALUMux_CTL = 0;
       	theControls->NZP_WE = 0;
       	theControls->DATA_WE = 0;
       	theControls->Privilege_CTL = 2;

	switch (insn)
	{
		//NOP
		case 0 :
       			printf("NOP\n");
       			return 0;

		//BRn
		case 4 :
	       		//for debugging
                       	printf("BRn\n");
                        return 0;			

		//BRnz
		case 6 :
                        //for debugging
                       	printf("BRnz\n");
                       	return 0;		

		//BRnp
		case 5 :
			//for debugging
			printf("BRnp\n");
                       	return 0;

		//BRz
		case 2 :
                        //for debugging
                       	printf("BRz\n");
                      	return 0;

		//BRzp
 	        case 3 :
			//for debugging
               		printf("BRzp\n");
         	        return 0;
 
		//BRp
		case 1 :
             	  	//for debugging
        	        printf("BRp\n");
	       		return 0;

		//BRnzp
		case 7 :
                    	//for debugging
                       	printf("BRnzp\n");
                 	return 0;
	}

	//if none of the above cases, error in encoding
	printf("Error decoding NOPBR\n");
	return 1;

}

int DecodeARITH (unsigned short int INSN, ControlSignals *theControls)
{
	unsigned short int insn = INSN_5_3(INSN);
        unsigned short int insn1 = INSN_5(INSN);

        theControls->PCMux_CTL = 1;
        theControls->rsMux_CTL = 0;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 1;
        theControls->regInputMux_CTL = 0;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 0;
        theControls->NZP_WE = 1;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;

	if(insn1 == 1)
	{
		//ADD IMM5
	        theControls->Arith_CTL = 0;
		theControls->ArithMux_CTL = 1;
	        //for debugging
	        printf("ADD IMM5\n");
	        return 0;
	}
	else
	{
		theControls->ArithMux_CTL = 0;
		switch (insn)
		{
			//ADD
			case 0 :
                		theControls->Arith_CTL = 0;
                		//for debugging
               			printf("ADD\n");
                		return 0;
			
			//MUL
			case 1 :
				theControls->Arith_CTL = 1;
                                //for debugging
                                printf("MUL\n");
                                return 0;

			//SUB
			case 2 :
                                theControls->Arith_CTL = 2;
                                //for debugging
                                printf("SUB\n");
                                return 0;

			//DIV
			case 3 :
                                theControls->Arith_CTL = 3;
                                //for debugging
                                printf("DIV\n");
                                return 0;
		}
	}
	
	//if none of the above, error in encoding
	printf("Error in encoding for ARITH\n");
	return 1;
}

int DecodeCMP (unsigned short int INSN, ControlSignals *theControls)
{
        
	unsigned short int insn = INSN_8_7(INSN);

        theControls->PCMux_CTL = 1;
        theControls->rsMux_CTL = 2;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 0;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 0;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->ALUMux_CTL = 4;
	theControls->CONST_CTL = 0;
	theControls->NZP_WE = 1;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;

	switch (insn)
	{
		//CMP
		case 0 :
			theControls->CMP_CTL = 0;
			printf("CMP\n");
			return 0;
		//CMPU
		case 1 :
		        theControls->CMP_CTL = 1;
                        printf("CMPU\n");
                        return 0;
		//CMPI
		case 2 :
		        theControls->CMP_CTL = 2;
                        printf("CMPI\n");
                        return 0;
		//CMPIU
		case 3 :
		        theControls->CMP_CTL = 3;
	                printf("CMPIU\n");
                        return 0;
	}
	
	//error in encoding
	printf("Error in encoding for CMP\n");
	return 1;
}

int DecodeJSR (unsigned short int INSN, ControlSignals *theControls)
{
        
	unsigned short int insn = INSN_11(INSN);

        theControls->rsMux_CTL = 0;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 0;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 0;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 0;
        theControls->NZP_WE = 0;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;

	switch (insn)
	{
		//JSRR
		case 0 :
		        theControls->PCMux_CTL = 3;
			//for deugging
			printf("JSRR\n");
			return 0;
		//JSR
		case 1 :
		        theControls->PCMux_CTL = 5;
	                //for debugging
                        printf("JSR\n");
                        return 0;
	}

        //for debugging
        printf("Error in encoding for JSR/JSRR\n");
        return 1;
}

int DecodeLOGIC (unsigned short int INSN, ControlSignals *theControls)
{
        unsigned short int insn = INSN_5_3(INSN);
	unsigned short int insn1 = INSN_5(INSN);

        theControls->PCMux_CTL = 1;
        theControls->rsMux_CTL = 0;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 1;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 1;
        theControls->NZP_WE = 1;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;
	
	if (insn1 == 1){
		//AND IMM5
                theControls->ArithMux_CTL = 1;
                theControls->LOGIC_CTL = 0;
                theControls->ALUMux_CTL = 0;
                printf("AND IMM5\n");
                return 0;
	}
	else
	{
		switch (insn)
		{
			//AND
			case 0 :
				theControls->LOGIC_CTL = 0;
				printf("AND\n");
				return 0;
			//NOT
			case 1 :
			        theControls->LOGIC_CTL = 1;
       	                	printf("NOT\n");
       	                	return 0;
			//OR
			case 2 :
			        theControls->LOGIC_CTL = 2;
                	        printf("OR\n");
                	        return 0;
			//XOR
			case 3 :
			        theControls->LOGIC_CTL = 3;
                	        printf("XOR\n");
                	        return 0;
		}
	}	

        //for debugging
        printf("Error in decoding for LOGIC\n");
        return 1;
}

int DecodeLDR (unsigned short int INSN, ControlSignals *theControls)
{
        
        theControls->PCMux_CTL = 1;
        theControls->rsMux_CTL = 0;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 1;
        theControls->regInputMux_CTL = 1;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 2;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 0;
        theControls->NZP_WE = 1;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;

        //for debugging
        printf("LDR\n");
        return 0;
}

int DecodeSTR (unsigned short int INSN, ControlSignals *theControls)
{
        
        theControls->PCMux_CTL = 1;
        theControls->rsMux_CTL = 0;
        theControls->rtMux_CTL = 1;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 0;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 2;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 0;
        theControls->NZP_WE = 0;
        theControls->DATA_WE = 1;
        theControls->Privilege_CTL = 2;

        //for debugging
        printf("STR\n");
        return 0;
}

int DecodeRTI (unsigned short int INSN, ControlSignals *theControls)
{
        
        theControls->PCMux_CTL = 3;
        theControls->rsMux_CTL = 1;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 0;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 0;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 0;
        theControls->NZP_WE = 0;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 0;

        //for debugging
        printf("RTI\n");
        return 0;
}

int DecodeCONST (unsigned short int INSN, ControlSignals *theControls)
{
        
        theControls->PCMux_CTL = 1;
        theControls->rsMux_CTL = 0;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 1;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 0;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 3;
        theControls->NZP_WE = 1;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;

        //for debugging
        printf("CONST\n");
        return 0;
}

int DecodeSHIFT (unsigned short int INSN, ControlSignals *theControls)
{
        
	unsigned short int insn = INSN_5_4(INSN);

        theControls->PCMux_CTL = 1;
        theControls->rsMux_CTL = 0;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 1;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 0;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 2;
        theControls->NZP_WE = 1;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;

	switch (insn)
	{
		//SLL
		case 0 :
			printf("SLL\n");
			return 0;
		//SRA
		case 1 :
			theControls->SHIFT_CTL = 1;
			printf("SRA\n");
			return 0;
		//SRL
		case 2 :
			theControls->SHIFT_CTL = 2;
			printf("SRL\n");
			return 0;
		//MOD
		case 3 :
			theControls->Arith_CTL = 4;
			theControls->ALUMux_CTL = 0;
			printf("MOD\n");
			return 0;
	}

        //for debugging
        printf("Error in encoding for SHIFT\n");
        return 1;
}

int DecodeJUMP (unsigned short int INSN, ControlSignals *theControls)
{
	
	unsigned short int insn = INSN_11(INSN);        

        theControls->rsMux_CTL = 0;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 0;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL = 0;
        theControls->ArithMux_CTL = 0;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 0;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 0;
        theControls->NZP_WE = 0;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;

	if (insn == 0){
		//JMPR
		theControls->PCMux_CTL = 3;
		printf("JMPR\n");
		return 0;
	}
	else{
		//JMP
		theControls->PCMux_CTL = 2;
		printf("JMP\n");
		return 0;
	}

        //for debugging
        printf("Error in encoding for JUMP\n");
        return 1;
}

int DecodeHICONST (unsigned short int INSN, ControlSignals *theControls)
{
        theControls->PCMux_CTL = 1;
        theControls->rsMux_CTL = 2;
        theControls->rtMux_CTL = 0;
        theControls->rdMux_CTL = 0;
        theControls->regFile_WE = 1;
        theControls->regInputMux_CTL = 0;
        theControls->Arith_CTL =0 ;
        theControls->ArithMux_CTL = 0;
        theControls->LOGIC_CTL = 0;
        theControls->LogicMux_CTL = 0;
        theControls->SHIFT_CTL = 0;
        theControls->CONST_CTL = 1;
        theControls->CMP_CTL = 0;
        theControls->ALUMux_CTL = 3;
        theControls->NZP_WE = 1;
        theControls->DATA_WE = 0;
        theControls->Privilege_CTL = 2;

	//for debugging
	printf("HICONST\n");
	return 0;
}

int DecodeTRAP (unsigned short int INSN, ControlSignals *theControls)
{
	
	theControls->PCMux_CTL = 4;
	theControls->rsMux_CTL = 0;
	theControls->rtMux_CTL = 0;
	theControls->rdMux_CTL = 1;
	theControls->regFile_WE = 1;
	theControls->regInputMux_CTL = 2;
	theControls->Arith_CTL = 0;
	theControls->ArithMux_CTL = 0;
	theControls->LOGIC_CTL = 0;
	theControls->LogicMux_CTL = 0;
	theControls->SHIFT_CTL = 0;
	theControls->CONST_CTL = 0;
	theControls->CMP_CTL = 0;
	theControls->ALUMux_CTL = 0;
	theControls->NZP_WE = 1;
	theControls->DATA_WE = 0;
	theControls->Privilege_CTL = 1;
	
	//for debugging
	printf("TRAP\n");
	return 0;
}
//
// DecodeCurrentInstruction: Decode current instruction and setup associated Control Signals
//
int DecodeCurrentInstruction (unsigned short int INSN, ControlSignals *theControls)
{

	unsigned short int insn = INSN_15_12(INSN);

	//switch for 15:9 encodings
	switch(insn)
	{
		//NOP and BRxxx instructions
		case 0 :			
			return DecodeNOPBR (INSN, theControls);

		//ADD, MUL, SUB, DIV instructions
		case 1 :
			return DecodeARITH (INSN, theControls);

		//CMP instructions
		case 2 :
			return DecodeCMP (INSN, theControls);

		//JSR, JSRR instructions
		case 4 :
			return DecodeJSR (INSN, theControls);

		//AND, NOT, OR, XOR, AND instructions
		case 5 :
			return DecodeLOGIC (INSN, theControls);

		//LDR instruction
		case 6 :
			return DecodeLDR (INSN, theControls);
		
		//STR instruction
		case 7 :
			return DecodeSTR (INSN, theControls);

		//RTI instruction
		case 8 :
			return DecodeRTI (INSN, theControls);

		//CONST instruction
		case 9 :
			return DecodeCONST (INSN, theControls);

		//SLL, SRA, SRL, MOD instructions
		case 10 :
			return DecodeSHIFT (INSN, theControls);

		//JMPR and JMP instructions
		case 12 :
			return DecodeJUMP (INSN, theControls);

		//HICONST instruction
		case 13 :
			return DecodeHICONST (INSN, theControls);

		//TRAP instruction
		case 15 :
			return DecodeTRAP (INSN, theControls);
	}

	//If none of the switches activate, there must be an error with encoding
	printf("Error in encoding");
	return 1;
}
//
// SimulateDatapath: returns 0: Good, Otherwise returns 1 for errors
// 
int SimulateDatapath (ControlSignals *theControls, MachineState *theMachineState, DatapathSignals *theDatapath)
{
	unsigned short int pc = theMachineState->PC;
	unsigned short int mem = theMachineState->memory[pc];

	unsigned short int insn_8_6 = INSN_8_6(mem);
	unsigned short int insn_11_9 = INSN_11_9(mem);
	unsigned short int insn_0x07 = INSN_0x07(mem);

	unsigned short int uimm8 = ((mem) & 0xFF);
	unsigned short int uimm4 = ((mem) & 0xF);
	unsigned short int uimm7 = ((mem) & 0x7F);

	signed short int imm11 = ((mem) & 0x7FF);
	signed short int imm6 = ((mem) & 0x3F);
	signed short int imm5 = ((mem) & 0x1F);
	signed short int imm7 = ((mem) & 0x7F);
	signed short int imm9 = ((mem) & 0x1FF);

	signed short int sext_imm5;
	signed short int sext_imm6;
	signed short int sext_imm7;
	signed short int sext_imm9;
	signed short int sext_imm11;

	signed short int rs;
	unsigned short int rt;
	signed short int sign_rsrt;
	unsigned short int unsign_rsrt;
	signed short int sign_rsimm7;
	unsigned short int unsign_rsuimm7;
	signed short int negative = -1;
	short int i;
	unsigned short int unsign_rs;;
	unsigned short int k;

        if (((imm5) & 0x10) == 0)
		sext_imm5 = imm5;
	else
		sext_imm5 = (0xFFE0 | imm5);

        if (((imm6) & 0x20) == 0)
                sext_imm6 = imm6;
        else
                sext_imm6 = (0xFFC0 | imm6);

        if (((imm7) & 0x40) == 0)
                sext_imm7 = uimm7;
        else
                sext_imm7 = (0xFF80 | uimm7);

        if (((imm9) & 0x100) == 0)
                sext_imm9 = imm9;
        else
                sext_imm9 = (0xFE00 | imm9);

        if (((imm11) & 0x400) == 0)
                sext_imm11 = imm11;
        else
                sext_imm11 = (0xF800 | imm11);


	//for RS
	switch(theControls->rsMux_CTL)
	{
		//I[8:6]
		case 0 :
			theDatapath->RS = insn_8_6;
			break;
		//0x07 = 0000 0111
		case 1 :
			theDatapath->RS = insn_0x07;
                        break;
		//I[11:9]
		case 2 :
			theDatapath->RS = insn_11_9;
                        break;
	}
	
	//for RT
	switch(theControls->rtMux_CTL)
	{
		//I[2:)] = 0x07
		case 0 :
			theDatapath->RT = insn_0x07;
                        break;
		//[11:9]
		case 1 :
			theDatapath->RT = insn_11_9;
                        break;
	}

	switch (theControls->Arith_CTL)
	{
		//ADD
		case 0 :
			switch (theControls->ArithMux_CTL)
			{
				//RT
				case 0 :
					theDatapath->ArithmeticOps = (theMachineState->R[theDatapath->RS] + 
						theMachineState->R[theDatapath->RT]);
                        		break;			
				//SEXT(IMM5)
				case 1 :
					theDatapath->ArithmeticOps = (theMachineState->R[theDatapath->RS] + sext_imm5);
		                        break;
			}
			break;

		//MUL
		case 1 :
                        theDatapath->ArithmeticOps = (theMachineState->R[theDatapath->RS] * 
				theMachineState->R[theDatapath->RT]);
                        break;
		//SUB
		case 2 :
                        theDatapath->ArithmeticOps = (theMachineState->R[theDatapath->RS] - 
				theMachineState->R[theDatapath->RT]);
                        break;
		//DIV
		case 3 :
                        theDatapath->ArithmeticOps = (theMachineState->R[theDatapath->RS] / 
				theMachineState->R[theDatapath->RT]);
                        break;
		//MOD
		case 4 :
	       		theDatapath->ArithmeticOps = (theMachineState->R[theDatapath->RS] % 
				theMachineState->R[theDatapath->RT]);
                        break;
	}
	
	//for LogicalOPS
	switch (theControls->LOGIC_CTL)
	{
		//AND
		case 0 :
			switch (theControls->ArithMux_CTL)
			{
				//RT
				case 0 :
					theDatapath->LogicalOps = ((theMachineState->R[theDatapath->RS]) & 
						(theMachineState->R[theDatapath->RT]));
			                break;
				//SEXT(IMM5)
				case 1 :
					theDatapath->LogicalOps = ((theMachineState->R[theDatapath->RS]) & (sext_imm5));
		                        break;	
			}
			break;

		//NOT (invert top input to logical unit
		case 1 :
                	theDatapath->LogicalOps = (~(theMachineState->R[theDatapath->RS]));
                        break;
		//OR
		case 2 :
                        theDatapath->LogicalOps = ((theMachineState->R[theDatapath->RS]) | 
				(theMachineState->R[theDatapath->RT]));
                        break;
		//XOR
		case 3 :
                	theDatapath->LogicalOps = ((theMachineState->R[theDatapath->RS]) ^ 
				(theMachineState->R[theDatapath->RT]));
                        break;
	}

	//for Shifter
	switch (theControls->SHIFT_CTL)
	{	
		//SLL
		case 0 :
			theDatapath->Shifter = ((theMachineState->R[theDatapath->RS]) << uimm4);		
                        break;
		//SRA
		case 1 :
     			theDatapath->Shifter = (((signed short int) theMachineState->R[theDatapath->RS]) >> uimm4);
                        break;
		//SRL
		case 2 : 
			if (uimm4 > 0) {
				k = theMachineState->R[theDatapath->RS] >> 1;
				k = k & 0x7FFF;		
				theDatapath->Shifter = k >> (uimm4 - 1);
			}
                        break;
	}
	//for Constants
	switch (theControls->CONST_CTL)
	{
		//Constants output = SEXT(IMM9)
		case 0 :
			theDatapath->Constants = sext_imm9;
                        break;
     		//Constants ouput = (RS & xFF) | (UIMM8 << 8)
		case 1 :
			theDatapath->Constants = ((theMachineState->R[theDatapath->RS] & 0xFF) | (uimm8 << 8));
                        break;
	}

        rs = theMachineState->R[theDatapath->RS];
	unsign_rs = theMachineState->R[theDatapath->RS];
        rt = theMachineState->R[theDatapath->RT];
        sign_rsrt = rs - rt;
        unsign_rsrt = theMachineState->R[theDatapath->RS] - theMachineState->R[theDatapath->RT];
        sign_rsimm7 = theMachineState->R[theDatapath->RS] - imm7;
        unsign_rsuimm7 = theMachineState->R[theDatapath->RS] - uimm7;


	//for ALUMux
	switch (theControls->ALUMux_CTL)
	{
		//ALUOutput = Arithmetic output
		case 0 :
			if ((mem & 0x5000) == 0x5000)
				theDatapath->ALUMux = theDatapath->LogicalOps;
			else
				theDatapath->ALUMux = theDatapath->ArithmeticOps;
                        break;
		//ALUOutput = Logical output
		case 1 :
                        theDatapath->ALUMux = theDatapath->LogicalOps;
                        break;
		//ALUOutput = Shifter output
		case 2 :
                        theDatapath->ALUMux = theDatapath->Shifter;
                        break;
		//ALUOutput = Constants output
		case 3 :
                        theDatapath->ALUMux = theDatapath->Constants;
                        break;
		//ALUOutput = Comparator output
		case 4 :
                        theDatapath->ALUMux = theDatapath->Comparator;
                        break;
	}

	if(theControls->NZP_WE == 1) {

		if (theControls->ALUMux_CTL == 3) {
			i = (short int) theDatapath->Constants;

			if (i < 0)
				theDatapath->Comparator = (unsigned short int) negative;
			else if(i == 0)
				theDatapath->Comparator = 0;
			else
				theDatapath->Comparator = +1;	
		}
		else if (theControls->ALUMux_CTL == 4) { 
			//for Comparator
			//since it is unsigned int, store 2 when it's -1
			switch (theControls->CMP_CTL)
			{
				//Out = signed-CC(Rs-Rt) [-1, 0, +1]
				case 0 :
					if (sign_rsrt < 0)
						theDatapath->Comparator = (unsigned short int) negative;
					else if(sign_rsrt == 0)
						theDatapath->Comparator = 0;
					else
						theDatapath->Comparator = +1;	
		                        break;
				//Out = unsigned-CC(Rs-Rt) [-1, 0, +1]
				case 1 :
                       			 if (unsign_rs < rt)
		                                theDatapath->Comparator = (unsigned short int) negative;
               			         else if(unsign_rs == rt)
                               			 theDatapath->Comparator = 0;
		                        else
               			                 theDatapath->Comparator = +1;
		                        break;
				//Out = signed-CC(Rs-SEXT(IMM7)) [-1, 0, +1]
				case 2 :
               			         if (sign_rsimm7 < 0)
                               			 theDatapath->Comparator = (unsigned short int) negative;
		                        else if(sign_rsimm7 == 0)
               			                 theDatapath->Comparator = 0;
		                        else
               			                 theDatapath->Comparator = +1;
		                        break;
				//Out = unsigned-CC(RS-UIMM7) [-1, 0, +1]
				case 3 :
               			         if (unsign_rs < uimm7)
                               			 theDatapath->Comparator = (unsigned short int) negative;
		                        else if(unsign_rs == uimm7)
		                                theDatapath->Comparator = 0;
		                        else
		                                theDatapath->Comparator = +1;
               			         break;
			}
		}
		else if ((theControls->ALUMux_CTL == 1) || ((theControls->ALUMux_CTL == 0) && 
			(theControls->ArithMux_CTL == 1) && (mem & 0x4000))) { 
			i = (short int) theDatapath->LogicalOps;
			if (i < 0) 
				theDatapath->Comparator = (unsigned short int) negative;
			else if (i == 0)
				theDatapath->Comparator = 0;
			else
				theDatapath->Comparator = 1;

		}
		else {
			i = (signed short int) theDatapath->ALUMux;
			if (i < 0) 
				theDatapath->Comparator = (unsigned short int) negative;
			else if (i == 0)
				theDatapath->Comparator = 0;
			else
				theDatapath->Comparator = 1;
		}
	}


	//for regInputMux
	switch (theControls->regInputMux_CTL)
	{
		//Write Input = ALU output
		case 0 :
			theDatapath->regInputMux = theDatapath->ALUMux;
                        break;
		//Write Input = Output of Data Memory
		case 1 :
			theDatapath->regInputMux = mem;
                        break;
		//Write Input = PC + 1
		case 2 :
			theDatapath->regInputMux = pc + 1;
                        break;
	}

	//for PCMux
	switch (theControls->PCMux_CTL)
	{
		//Value of NZP register compared to bits I[11:9] of the current instruction if the test 
		//is satisfied then the output of TEST is 1 and NextPC = BRANCH Target, (PC + 1) + SEXT(IMM9)
		case 0 : 
			switch (insn_11_9)
			{
				//NOP
				case 0 :
					theDatapath->PCMux = pc + 1;
					break;
				//BRn
				case 4 :
                                        if (theDatapath->Comparator == (unsigned short int) negative)
                                                theDatapath->PCMux = pc + 1 + sext_imm9;
                                        else
                                                theDatapath->PCMux = pc + 1;
                                        break;
				//BRnz
				case 6 :
                                        if (theDatapath->Comparator == 1)
                                                theDatapath->PCMux = pc + 1;
                                        else
                                                theDatapath->PCMux = pc + 1 + sext_imm9;
                                        break;
				//BRnp
				case 5 :
                                        if (theDatapath->Comparator == 0)
                                                theDatapath->PCMux = pc + 1;
                                        else
                                                theDatapath->PCMux = pc + 1 + sext_imm9;
                                        break;
				//BRz
				case 2 :
                                        if (theDatapath->Comparator == 0)
                                                theDatapath->PCMux = pc + 1 + sext_imm9;
                                        else
                                                theDatapath->PCMux = pc + 1;
                                        break;
				//BRzp
				case 3 :
                                        if (theDatapath->Comparator == (unsigned short int) negative)
                                                theDatapath->PCMux = pc + 1;
                                        else
                                                theDatapath->PCMux = pc + 1 + sext_imm9;
                                        break;
				//BRp
				case 1 :
					if (theDatapath->Comparator == 1)
                                        	theDatapath->PCMux = pc + 1 + sext_imm9;
					else
                                        	theDatapath->PCMux = pc + 1;
                                        break;
				//BRnzp
				case 7 :
					theDatapath->PCMux = pc + 1 + sext_imm9;
                                        break;
			}	
                        break;			
		//Next PC = PC + 1
		case 1 :
			theDatapath->PCMux = pc + 1; 
                        break;
		//Next PC = (PC + 1) + SEXT(IMM11)
		case 2 :
			theDatapath->PCMux = pc + 1 + sext_imm11; 
                        break;
		//Next PC = RS
		case 3 : 
			// RTI: PC = R7,  JMPR, JSRR: PC = RS
			if((mem & 0xF000) == 0x8000) 	// RTI
				theDatapath->PCMux = theMachineState->R[7];
			else

				theDatapath->PCMux = theMachineState->R[theDatapath->RS];
                        break;
		//Next PC = (0x8000 |  UIMM8)
		case 4 : 
			theDatapath->PCMux = (0x8000 | uimm8);
			theDatapath->Comparator = 1;
                        break;
		//Next PC = (PC & 0x8000) | (IMM11 << 4)
		case 5 :
			theDatapath->PCMux = ((pc & 0x8000) | (imm11 << 4)); 
                        break;
	}
	return 0;
}

//
// UpdateMachineState: Update the Virtual Machine
// Returns 1, 2, 3 for Exceptions
// 1: Attempting to execute a data section address as code
// 2: Attempting to read or write a code section address as data
// 3: Attempting to access an address or instruction in the OS section of memory
//    when the processor is in user mode.
//
int UpdateMachineState (ControlSignals *theControls, MachineState *theMachineState, DatapathSignals *theDatapath)
{
	// CHECK FOR ERRORS HERE:
	// (1)Attempting to execute a data section address as code
	// (2)Attempting to read or write a code section address as data
	// (3)Attempting to access an address or instruction in the OS section of memory 
	//    when the processor is in user mode

	//stuff from datapathsignals
	//unsigned short int rs = theDatapath->RS;
	unsigned short int rs = theMachineState->R[theDatapath->RS];
	//unsigned short int rt = theDatapath->RT;
	unsigned short int rt = theMachineState->R[theDatapath->RT];
	unsigned short int arithmeticops = theDatapath->ArithmeticOps;
	unsigned short int logicalops = theDatapath->LogicalOps;
	unsigned short int shifter = theDatapath->Shifter;
	unsigned short int constants = theDatapath->Constants;
	short int comparator = (signed short int) theDatapath->Comparator;
	unsigned short int alumux = theDatapath->ALUMux;
	unsigned short int reginputmux = theDatapath->regInputMux;
	unsigned short int pcmux = theDatapath->PCMux;

	//stuff from controlsignals
	unsigned char privilege = theControls->Privilege_CTL;
	unsigned char data = theControls->DATA_WE;	


	//stuff from MachineState
	unsigned short int pc = theMachineState->PC;
	unsigned short int mem = theMachineState->memory[pc];

	// unsigned short int rd = INSN_11_9(mem);
	unsigned short int rd;
	unsigned short int imm6 = (mem & 0x3F);
	signed short int sext_imm6;
	short int negative = -1;
	unsigned short int addr;

	//for RD
	switch(theControls->rdMux_CTL)
	{
		//I[2:)] = 0x07
		case 1 :
			rd = 7;
                        break;
		//[11:9]
		case 0 :
			rd = INSN_11_9(mem);
                        break;
	}

        if (((imm6) & 0x20) == 0)
                sext_imm6 = imm6;
        else
                sext_imm6 = (0xFFC0 | imm6);

	theMachineState->PC = pcmux;	

	if (pcmux == 0x80FF)
	{
		printf("Update Machine State: PC = 0x80FF, exit command\n");
		return 0;
	}

	// Privilege: setup USer Mode or OS Mode
	//Error type 1: Execute a data data section as code
	if (pcmux >= 0 && pcmux <= 0x3FFF)
		theMachineState->PSR &= 0x7FFF;
	else if (pcmux >= 0x8000 && pcmux <= 0x9FFF)
		theMachineState->PSR |= 0x8000;
	else
		return 1;


	//handles arithmetic, compare, logic, shift, and constants
	if (theControls->regFile_WE == 1)
	{
		theMachineState->R[rd] = reginputmux;
	}

	//for JSR, JSRR, or TRAP
	if ((theControls->PCMux_CTL == 3 && theControls->rsMux_CTL != 1 && (mem & 0xF800) != 0xC000) || 
			theControls->PCMux_CTL == 5)	
	{
		theMachineState->R[7] = pc + 1;
	}

	//for STR
	if (theControls->DATA_WE == 1)
	{
		addr = rs + sext_imm6;

		// Error Type 3: User Mode to access OS data memory
		if (((theMachineState->PSR & 0x8000) == 0) && (addr >= 0xA000))
			return 3;
		
		// Eror Type: cannot write to code setion
		if ((rs + sext_imm6) <= 0x3FFF || ((rs + sext_imm6) >= 0x8000 && (rs + sext_imm6) <= 0x9FFF))
			return 2;
		else
			theMachineState->memory[rs + sext_imm6] = rt;
	}

	//for LDR
	if (theControls->ArithMux_CTL == 2 && theControls->DATA_WE == 0)
	{
                //error type 2
                //cannot load from code section
		if (((rs + sext_imm6) <= 0x3FFF) || (((rs + sext_imm6) >=0x8000) && ((rs + sext_imm6) <= 0x9FFF)))
			return 2;

		addr = rs + sext_imm6;

		// Error Type 3: User Mode to access OS data memory
		if (((theMachineState->PSR & 0x8000) == 0) && (addr >= 0xA000))
			return 3;

		theMachineState->R[rd] = theMachineState->memory[rs + sext_imm6];
		if(theMachineState->R[rd] < 0)
			theDatapath->Comparator = (unsigned short int) negative;
		else if (theMachineState->R[rd] == 0)
			theDatapath->Comparator = 0;
		else
			theDatapath->Comparator = 1;
	}
	comparator = (short int) theDatapath->Comparator;

	if (theControls->NZP_WE == 1)
	{
		theMachineState->PSR &= 0xFFF8;
		switch (comparator)
		{
			//PSR bit[2] = N
			case -1 :
				theMachineState->PSR = ((theMachineState->PSR) | 0x0004);
				break;
			//PSR bit[1] = Z
			case 0 :
				theMachineState->PSR = ((theMachineState->PSR) | 0x0002);
				break;
			//PSR bit[0] = P
			case 1 :
				theMachineState->PSR = ((theMachineState->PSR) | 0x0001);
				break;
		}	
	}


	//return 0 if no error encountered
	return 0;

}

//
// Reset Machine State
//
void Reset (MachineState *theMachineState)
{
	int i;
	MachineState *theMachine;

	printf("Reset LC4 machine ..... \n");

	theMachineState->PC = 0x8200;
	
	for (i = 0; i < 8; i++)
	{
		theMachineState->R[i] = 0;
	}
	
	theMachineState->PSR = 0x8002;		

	for (i = 0; i < 65536; i++)
	{
		theMachineState->memory[i] = 0x0000;
	}
}

