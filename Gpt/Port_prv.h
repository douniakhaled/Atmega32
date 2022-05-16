/*
 * Port_prv.h
 *
 *  Created on: Mar 10, 2022
 *      Author: donia
 */

#ifndef PORT_PRV_H_
#define PORT_PRV_H_

#define ConcHelper(b7,b6,b5,b4,b3,b2,b1,b0)                 0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)			       		 ConcHelper(b7,b6,b5,b4,b3,b2,b1,b0)


#endif /* PORT_PRV_H_ */
