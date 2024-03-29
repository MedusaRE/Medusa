/**
 *  @file
 *  @author  spv <spv@spv.sh>
 *
 *  @section LICENSE
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of version 2 of the GNU General Public License as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details at
 *  https://www.gnu.org/copyleft/gpl.html
 *
 *  @section DESCRIPTION
 *
 *  The Machine class represents a generic machine that a piece of software
 *  utilizing libmedusa can interface with.
 */

#ifndef WARSAW_MACHINE_HPP
#define WARSAW_MACHINE_HPP

#include <libmedusa/Machine.hpp>
#include <paris/message.hpp>
#include <paris/paris.hpp>

namespace warsaw {
	//  TODO: write the rest of the (machine_op_t::*)_args struct typedef's
	//  TODO: doxygen doc the structs

	typedef enum {
		GET_REGS, //  done
		SET_REG,  //  done

		READ_MEM,  //  done
		WRITE_MEM, //  done

		GET_MEM_REGIONS,	//  done
		FIND_MEMORY_REGION, //  done
		UNMAP_MEM,			//  done
		MAP_MEM,			//  done

		EXEC_CODE_ADDR_NINSNS, //  done
		EXEC_CODE_ADDR,		   //  done
		EXEC_CODE_NINSNS,	   //  done
		EXEC_CODE_STEP,		   //  done

		ASSEMBLE,
		DISASSEMBLE,
	} machine_op_t;

	typedef struct {
			libmedusa::reg_t reg;
	} SET_REG_args;

	typedef struct {
			uint64_t addr;
			uint64_t size;
	} READ_MEM_args;

	typedef struct {
			uint64_t addr;
			uint64_t size;
	} EXEC_CODE_ADDR_args;

	typedef struct {
			uint64_t addr;
			uint64_t num;
	} EXEC_CODE_ADDR_NINSNS_args;

	typedef struct {
			uint64_t addr;
			uint64_t size;
			uint8_t	 data[0];
	} WRITE_MEM_args;

	typedef struct {
			libmedusa::mem_reg_t mem_reg;
	} MAP_MEM_args;

	typedef struct {
			libmedusa::mem_reg_t mem_reg;
	} UNMAP_MEM_args;

	typedef struct {
			uint64_t num_insns;
	} EXEC_CODE_NINSNS_args;

	typedef struct {
			uint64_t	 len;
			machine_op_t op;
			void		*data;
	} machine_msg;

	typedef struct {
			uint64_t addr;
	} FIND_MEMORY_REGION_args;

	/**
	 *	@brief A Paris service for libmedusa::Machine.
	 */
	class Machine: public paris::ServiceListener {
		public:
			virtual bool process_message(paris::paris_message_t message,
										 paris::Server		   *server);

			virtual bool builtin_init(paris::Server *server);
	};
} //  namespace warsaw

#endif