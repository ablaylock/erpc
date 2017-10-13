#ifndef _EMBEDDED_RPC__CRC_ALGORITHM_H_
#define _EMBEDDED_RPC__CRC_ALGORITHM_H_

#include <stdint.h>

/*!
* @addtogroup infra_transport
* @{
* @file
*/

////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////

namespace erpc {

	class CrcAlgorithm
	{
	public:

		/*!
		* @brief CRC algorithm destructor
		*/
		virtual ~CrcAlgorithm() {}

		/*!
		* @brief Compute a "CRC" like algorithm over the provided data.
		*
		* @param[in] data Pointer to data used for crc computation.
		* @param[in] dataLength Data length.
		*/
		virtual uint16_t computeCRC(const uint8_t *data, uint32_t lengthInBytes) = 0;
	};

} // namespace erpc

  /*! @} */

#endif // _EMBEDDED_RPC__CRC_ALGORITHM_H_

