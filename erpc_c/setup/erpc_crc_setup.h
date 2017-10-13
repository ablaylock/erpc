#ifndef _EMBEDDED_RPC__CRC_SETUP_H_
#define _EMBEDDED_RPC__CRC_SETUP_H_

#include "erpc_common.h"

/*!
* @addtogroup crc_setup
* @{
* @file
*/

//! @brief Opaque MessageBufferFactory object type.
typedef struct CrcAlgorithmType *erpc_crc_t;


////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

	extern const uint32_t erpc_generated_crc;
	extern const uint16_t CRC_16_CCITT;
	extern const uint16_t CRC_16_IBM;
	extern const uint16_t CRC_16_T10_DIF;
	extern const uint16_t CRC_16_DNP;
	extern const uint16_t CRC_16_DECT;

	//! @name CRC16 setup
	//@{

	/*!
	* @brief This function initializes the CRC16 algorithem.
	*
	* This function initializes the CRC16 algorithem.
	*/
	erpc_crc_t erpc_crc16_init(const uint16_t polynomial);

	/*!
	* @brief This function initializes the CRC16 algorithem.
	*
	* This function initializes the CRC16 algorithem.
	*/
	erpc_crc_t erpc_crc_none_init();

	/*!
	* @brief This function de-initializes client.
	*
	* This function de-initializes client and all components which it own.
	*/
	void erpc_crc_reset(erpc_crc_t crc);

	/*!
	* @brief This function de-initializes client.
	*
	* This function de-initializes client and all components which it own.
	*/
	void erpc_crc_deinit(erpc_crc_t crc);

	//@}

#ifdef __cplusplus
}
#endif

/*! @} */

#endif // _EMBEDDED_RPC__CRC_SETUP_H_


