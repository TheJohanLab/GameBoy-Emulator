#pragma once
#include <iostream>
#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction1BitOperation : public Instruction
{
	public:
		Instruction1BitOperation(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction1BitOperation() = default;
		
		static void BIT_0cB(CPU& cpu);		//0xCB40 BIT 0,B
		static void BIT_0cC(CPU& cpu);		//0xCB41 BIT 0,C
		static void BIT_0cD(CPU& cpu);		//0xCB42 BIT 0,D
		static void BIT_0cE(CPU& cpu);		//0xCB43 BIT 0,E
		static void BIT_0cH(CPU& cpu);		//0xCB44 BIT 0,H
		static void BIT_0cL(CPU& cpu);		//0xCB45 BIT 0,L
		static void BIT_0cpHLq(CPU& cpu);	//0xCB46 BIT 0,(HL)
		static void BIT_0cA(CPU& cpu);		//0xCB47 BIT 0,A
		static void BIT_1cB(CPU& cpu);		//0xCB48 BIT 1,B
		static void BIT_1cC(CPU& cpu);		//0xCB49 BIT 1,C
		static void BIT_1cD(CPU& cpu);		//0xCB4A BIT 1,D
		static void BIT_1cE(CPU& cpu);		//0xCB4B BIT 1,E
		static void BIT_1cH(CPU& cpu);		//0xCB4C BIT 1,H
		static void BIT_1cL(CPU& cpu);		//0xCB4D BIT 1,L
		static void BIT_1cpHLq(CPU& cpu);	//0xCB4E BIT 1,(HL)
		static void BIT_1cA(CPU& cpu);		//0xCB4F BIT 1,A

		static void BIT_2cB(CPU& cpu);		//0xCB50 BIT 2,B
		static void BIT_2cC(CPU& cpu);		//0xCB51 BIT 2,C
		static void BIT_2cD(CPU& cpu);		//0xCB52 BIT 2,D
		static void BIT_2cE(CPU& cpu);		//0xCB53 BIT 2,E
		static void BIT_2cH(CPU& cpu);		//0xCB54 BIT 2,H
		static void BIT_2cL(CPU& cpu);		//0xCB55 BIT 2,L
		static void BIT_2cpHLq(CPU& cpu);	//0xCB56 BIT 2,(HL)
		static void BIT_2cA(CPU& cpu);		//0xCB57 BIT 2,A
		static void BIT_3cB(CPU& cpu);		//0xCB58 BIT 3,B
		static void BIT_3cC(CPU& cpu);		//0xCB59 BIT 3,C
		static void BIT_3cD(CPU& cpu);		//0xCB5A BIT 3,D
		static void BIT_3cE(CPU& cpu);		//0xCB5B BIT 3,E
		static void BIT_3cH(CPU& cpu);		//0xCB5C BIT 3,H
		static void BIT_3cL(CPU& cpu);		//0xCB5D BIT 3,L
		static void BIT_3cpHLq(CPU& cpu);	//0xCB5E BIT 3,(HL)
		static void BIT_3cA(CPU& cpu);		//0xCB5F BIT 3,A

		static void BIT_4cB(CPU& cpu);		//0xCB60 BIT 4,B
		static void BIT_4cC(CPU& cpu);		//0xCB61 BIT 4,C
		static void BIT_4cD(CPU& cpu);		//0xCB62 BIT 4,D
		static void BIT_4cE(CPU& cpu);		//0xCB63 BIT 4,E
		static void BIT_4cH(CPU& cpu);		//0xCB64 BIT 4,H
		static void BIT_4cL(CPU& cpu);		//0xCB65 BIT 4,L
		static void BIT_4cpHLq(CPU& cpu);	//0xCB66 BIT 4,(HL)
		static void BIT_4cA(CPU& cpu);		//0xCB67 BIT 4,A
		static void BIT_5cB(CPU& cpu);		//0xCB68 BIT 5,B
		static void BIT_5cC(CPU& cpu);		//0xCB69 BIT 5,C
		static void BIT_5cD(CPU& cpu);		//0xCB6A BIT 5,D
		static void BIT_5cE(CPU& cpu);		//0xCB6B BIT 5,E
		static void BIT_5cH(CPU& cpu);		//0xCB6C BIT 5,H
		static void BIT_5cL(CPU& cpu);		//0xCB6D BIT 5,L
		static void BIT_5cpHLq(CPU& cpu);	//0xCB6E BIT 5,(HL)
		static void BIT_5cA(CPU& cpu);		//0xCB6F BIT 5,A

		static void BIT_6cB(CPU& cpu);		//0xCB70 BIT 6,B
		static void BIT_6cC(CPU& cpu);		//0xCB71 BIT 6,C
		static void BIT_6cD(CPU& cpu);		//0xCB72 BIT 6,D
		static void BIT_6cE(CPU& cpu);		//0xCB73 BIT 6,E
		static void BIT_6cH(CPU& cpu);		//0xCB74 BIT 6,H
		static void BIT_6cL(CPU& cpu);		//0xCB75 BIT 6,L
		static void BIT_6cpHLq(CPU& cpu);	//0xCB76 BIT 6,(HL)
		static void BIT_6cA(CPU& cpu);		//0xCB77 BIT 6,A
		static void BIT_7cB(CPU& cpu);		//0xCB78 BIT 7,B
		static void BIT_7cC(CPU& cpu);		//0xCB79 BIT 7,C
		static void BIT_7cD(CPU& cpu);		//0xCB7A BIT 7,D
		static void BIT_7cE(CPU& cpu);		//0xCB7B BIT 7,E
		static void BIT_7cH(CPU& cpu);		//0xCB7C BIT 7,H
		static void BIT_7cL(CPU& cpu);		//0xCB7D BIT 7,L
		static void BIT_7cpHLq(CPU& cpu);	//0xCB7E BIT 7,(HL)
		static void BIT_7cA(CPU& cpu);		//0xCB7F BIT 7,A

		static void RES_0cB(CPU& cpu);		//0xCB40 RES 0,B
		static void RES_0cC(CPU& cpu);		//0xCB41 RES 0,C
		static void RES_0cD(CPU& cpu);		//0xCB42 RES 0,D
		static void RES_0cE(CPU& cpu);		//0xCB43 RES 0,E
		static void RES_0cH(CPU& cpu);		//0xCB44 RES 0,H
		static void RES_0cL(CPU& cpu);		//0xCB45 RES 0,L
		static void RES_0cpHLq(CPU& cpu);	//0xCB46 RES 0,(HL)
		static void RES_0cA(CPU& cpu);		//0xCB47 RES 0,A
		static void RES_1cB(CPU& cpu);		//0xCB48 RES 1,B
		static void RES_1cC(CPU& cpu);		//0xCB49 RES 1,C
		static void RES_1cD(CPU& cpu);		//0xCB4A RES 1,D
		static void RES_1cE(CPU& cpu);		//0xCB4B RES 1,E
		static void RES_1cH(CPU& cpu);		//0xCB4C RES 1,H
		static void RES_1cL(CPU& cpu);		//0xCB4D RES 1,L
		static void RES_1cpHLq(CPU& cpu);	//0xCB4E RES 1,(HL)
		static void RES_1cA(CPU& cpu);		//0xCB4F RES 1,A

		static void RES_2cB(CPU& cpu);		//0xCB50 RES 2,B
		static void RES_2cC(CPU& cpu);		//0xCB51 RES 2,C
		static void RES_2cD(CPU& cpu);		//0xCB52 RES 2,D
		static void RES_2cE(CPU& cpu);		//0xCB53 RES 2,E
		static void RES_2cH(CPU& cpu);		//0xCB54 RES 2,H
		static void RES_2cL(CPU& cpu);		//0xCB55 RES 2,L
		static void RES_2cpHLq(CPU& cpu);	//0xCB56 RES 2,(HL)
		static void RES_2cA(CPU& cpu);		//0xCB57 RES 2,A
		static void RES_3cB(CPU& cpu);		//0xCB58 RES 3,B
		static void RES_3cC(CPU& cpu);		//0xCB59 RES 3,C
		static void RES_3cD(CPU& cpu);		//0xCB5A RES 3,D
		static void RES_3cE(CPU& cpu);		//0xCB5B RES 3,E
		static void RES_3cH(CPU& cpu);		//0xCB5C RES 3,H
		static void RES_3cL(CPU& cpu);		//0xCB5D RES 3,L
		static void RES_3cpHLq(CPU& cpu);	//0xCB5E RES 3,(HL)
		static void RES_3cA(CPU& cpu);		//0xCB5F RES 3,A

		static void RES_4cB(CPU& cpu);		//0xCB60 RES 4,B
		static void RES_4cC(CPU& cpu);		//0xCB61 RES 4,C
		static void RES_4cD(CPU& cpu);		//0xCB62 RES 4,D
		static void RES_4cE(CPU& cpu);		//0xCB63 RES 4,E
		static void RES_4cH(CPU& cpu);		//0xCB64 RES 4,H
		static void RES_4cL(CPU& cpu);		//0xCB65 RES 4,L
		static void RES_4cpHLq(CPU& cpu);	//0xCB66 RES 4,(HL)
		static void RES_4cA(CPU& cpu);		//0xCB67 RES 4,A
		static void RES_5cB(CPU& cpu);		//0xCB68 RES 5,B
		static void RES_5cC(CPU& cpu);		//0xCB69 RES 5,C
		static void RES_5cD(CPU& cpu);		//0xCB6A RES 5,D
		static void RES_5cE(CPU& cpu);		//0xCB6B RES 5,E
		static void RES_5cH(CPU& cpu);		//0xCB6C RES 5,H
		static void RES_5cL(CPU& cpu);		//0xCB6D RES 5,L
		static void RES_5cpHLq(CPU& cpu);	//0xCB6E RES 5,(HL)
		static void RES_5cA(CPU& cpu);		//0xCB6F RES 5,A

		static void RES_6cB(CPU& cpu);		//0xCB70 RES 6,B
		static void RES_6cC(CPU& cpu);		//0xCB71 RES 6,C
		static void RES_6cD(CPU& cpu);		//0xCB72 RES 6,D
		static void RES_6cE(CPU& cpu);		//0xCB73 RES 6,E
		static void RES_6cH(CPU& cpu);		//0xCB74 RES 6,H
		static void RES_6cL(CPU& cpu);		//0xCB75 RES 6,L
		static void RES_6cpHLq(CPU& cpu);	//0xCB76 RES 6,(HL)
		static void RES_6cA(CPU& cpu);		//0xCB77 RES 6,A
		static void RES_7cB(CPU& cpu);		//0xCB78 RES 7,B
		static void RES_7cC(CPU& cpu);		//0xCB79 RES 7,C
		static void RES_7cD(CPU& cpu);		//0xCB7A RES 7,D
		static void RES_7cE(CPU& cpu);		//0xCB7B RES 7,E
		static void RES_7cH(CPU& cpu);		//0xCB7C RES 7,H
		static void RES_7cL(CPU& cpu);		//0xCB7D RES 7,L
		static void RES_7cpHLq(CPU& cpu);	//0xCB7E RES 7,(HL)
		static void RES_7cA(CPU& cpu);		//0xCB7F RES 7,A

		static void SET_0cB(CPU& cpu);		//0xCB40 SET 0,B
		static void SET_0cC(CPU& cpu);		//0xCB41 SET 0,C
		static void SET_0cD(CPU& cpu);		//0xCB42 SET 0,D
		static void SET_0cE(CPU& cpu);		//0xCB43 SET 0,E
		static void SET_0cH(CPU& cpu);		//0xCB44 SET 0,H
		static void SET_0cL(CPU& cpu);		//0xCB45 SET 0,L
		static void SET_0cpHLq(CPU& cpu);	//0xCB46 SET 0,(HL)
		static void SET_0cA(CPU& cpu);		//0xCB47 SET 0,A
		static void SET_1cB(CPU& cpu);		//0xCB48 SET 1,B
		static void SET_1cC(CPU& cpu);		//0xCB49 SET 1,C
		static void SET_1cD(CPU& cpu);		//0xCB4A SET 1,D
		static void SET_1cE(CPU& cpu);		//0xCB4B SET 1,E
		static void SET_1cH(CPU& cpu);		//0xCB4C SET 1,H
		static void SET_1cL(CPU& cpu);		//0xCB4D SET 1,L
		static void SET_1cpHLq(CPU& cpu);	//0xCB4E SET 1,(HL)
		static void SET_1cA(CPU& cpu);		//0xCB4F SET 1,A

		static void SET_2cB(CPU& cpu);		//0xCB50 SET 2,B
		static void SET_2cC(CPU& cpu);		//0xCB51 SET 2,C
		static void SET_2cD(CPU& cpu);		//0xCB52 SET 2,D
		static void SET_2cE(CPU& cpu);		//0xCB53 SET 2,E
		static void SET_2cH(CPU& cpu);		//0xCB54 SET 2,H
		static void SET_2cL(CPU& cpu);		//0xCB55 SET 2,L
		static void SET_2cpHLq(CPU& cpu);	//0xCB56 SET 2,(HL)
		static void SET_2cA(CPU& cpu);		//0xCB57 SET 2,A
		static void SET_3cB(CPU& cpu);		//0xCB58 SET 3,B
		static void SET_3cC(CPU& cpu);		//0xCB59 SET 3,C
		static void SET_3cD(CPU& cpu);		//0xCB5A SET 3,D
		static void SET_3cE(CPU& cpu);		//0xCB5B SET 3,E
		static void SET_3cH(CPU& cpu);		//0xCB5C SET 3,H
		static void SET_3cL(CPU& cpu);		//0xCB5D SET 3,L
		static void SET_3cpHLq(CPU& cpu);	//0xCB5E SET 3,(HL)
		static void SET_3cA(CPU& cpu);		//0xCB5F SET 3,A

		static void SET_4cB(CPU& cpu);		//0xCB60 SET 4,B
		static void SET_4cC(CPU& cpu);		//0xCB61 SET 4,C
		static void SET_4cD(CPU& cpu);		//0xCB62 SET 4,D
		static void SET_4cE(CPU& cpu);		//0xCB63 SET 4,E
		static void SET_4cH(CPU& cpu);		//0xCB64 SET 4,H
		static void SET_4cL(CPU& cpu);		//0xCB65 SET 4,L
		static void SET_4cpHLq(CPU& cpu);	//0xCB66 SET 4,(HL)
		static void SET_4cA(CPU& cpu);		//0xCB67 SET 4,A
		static void SET_5cB(CPU& cpu);		//0xCB68 SET 5,B
		static void SET_5cC(CPU& cpu);		//0xCB69 SET 5,C
		static void SET_5cD(CPU& cpu);		//0xCB6A SET 5,D
		static void SET_5cE(CPU& cpu);		//0xCB6B SET 5,E
		static void SET_5cH(CPU& cpu);		//0xCB6C SET 5,H
		static void SET_5cL(CPU& cpu);		//0xCB6D SET 5,L
		static void SET_5cpHLq(CPU& cpu);	//0xCB6E SET 5,(HL)
		static void SET_5cA(CPU& cpu);		//0xCB6F SET 5,A

		static void SET_6cB(CPU& cpu);		//0xCB70 SET 6,B
		static void SET_6cC(CPU& cpu);		//0xCB71 SET 6,C
		static void SET_6cD(CPU& cpu);		//0xCB72 SET 6,D
		static void SET_6cE(CPU& cpu);		//0xCB73 SET 6,E
		static void SET_6cH(CPU& cpu);		//0xCB74 SET 6,H
		static void SET_6cL(CPU& cpu);		//0xCB75 SET 6,L
		static void SET_6cpHLq(CPU& cpu);	//0xCB76 SET 6,(HL)
		static void SET_6cA(CPU& cpu);		//0xCB77 SET 6,A
		static void SET_7cB(CPU& cpu);		//0xCB78 SET 7,B
		static void SET_7cC(CPU& cpu);		//0xCB79 SET 7,C
		static void SET_7cD(CPU& cpu);		//0xCB7A SET 7,D
		static void SET_7cE(CPU& cpu);		//0xCB7B SET 7,E
		static void SET_7cH(CPU& cpu);		//0xCB7C SET 7,H
		static void SET_7cL(CPU& cpu);		//0xCB7D SET 7,L
		static void SET_7cpHLq(CPU& cpu);	//0xCB7E SET 7,(HL)
		static void SET_7cA(CPU& cpu);		//0xCB7F SET 7,A

	private:

		static void BIT_bcr(u8& registry, flags& flagRegistry, u8 bit);
		static void RES_bcr(u8& registry, flags& flagRegistry, u8 bit);
		static void SET_bcr(u8& registry, flags& flagRegistry, u8 bit);
};

