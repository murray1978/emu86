#ifndef __BC_H__
#define __BC_H__

/*
  The great cpuloop, not realy a loop, but, because im pissed about the 
  lookup table not working, here is the really great big case structure,
  bound to add hundreds of bytes to my code
*/

void cpuloop( unsigned int opcode ){
	switch(opcode){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			add86();
                        break;
		case 6:
			push86();
			break;
		case 7:
			pop86();
			break;
		case 14:
                        push86();
			break;
		case 15:
                        pop86();
			break;
		case 16:
		case 17:
		case 18:
                case 19:
                case 20:
                case 21:
                        adc86();
			break;
                case 23:
                case 31:
                    pop86();
                    break;
                case 22:
                case 30:
                case 80:
                case 81:
                case 82:
                case 83:
                case 84:
                case 85:
                case 86:
                case 87:
                case 255:
                  push86();
                  break;
                case 88:
                case 89:
                case 90:
                case 91:
                case 92:
                case 93:
                case 94:
                case 95:
                    pop86();
                    break;
                case 128:
                case 129:
                case 130:
                case 131:
                  add86();
                  break;
                case 134:
                case 135:
                  xchg86();
                  break;
                case 136:
                case 137:
                case 138:
                case 139:
                case 140:
                  mov86();
                  break;
                case 141:
                  lea86();
                  break;
                case 142:
                  mov86();
                  break;
                case 143:
                  pop86();
                  break;
                case 144:
                case 145:
                case 146:
                case 147:
                case 148:
                case 149:
                case 150:
                case 151:
                  xchg86();
                  break;
                case 156:
                  pushf86();
                  break;
                case 157:
                  popf86();
                   break;
                case 158:
                  sahf86();
                  break;
                case 159:
                  lahf86();
                  break;
                case 160:
                case 161:
                case 162:
                case 163:
                case 176:
                case 177:
                case 178:
                case 179:
                case 180:
                case 181:
                case 182:
                case 183:
                case 184:
                case 185:
                case 186:
                case 187:
                case 188:
                case 189:
                case 190:
                case 191:
                case 198:
                case 199:
                  mov86();
                  break;
                case 196:
                  les86();
                  break;
                case 197:
                  lds86();
                  break;
                case 215:
                  xlat86();
                  break;
                case 228:
                case 229:
                case 236:
                case 237:
                  in86();
                  break;
                case 230:
                case 231:
                case 238:
                case 239:
                  out86();
                  break;
                default:
                  noop86();
                 break;
	}
}

#endif
