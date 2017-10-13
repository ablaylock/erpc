#ifndef _EMBEDDED_RPC__CRC_NONE_H_
#define _EMBEDDED_RPC__CRC_NONE_H_

#include <stdint.h>
#include "crc_algorithm.h"

/*!
 * @addtogroup infra_transport
 * @{
 * @file
 */

////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////

namespace erpc {

class CrcNone : public CrcAlgorithm
{
public:
    /*!
     * @brief Constructor.
     */
	CrcNone(uint32_t constantCrcValue);

    /*!
     * @brief CRC16 destructor
     */
    virtual ~Crc16();

    /*!
     * @brief Compute a ITU-CCITT CRC-16 over the provided data.
     *
     * This implementation is slow but small in size.
     *
     * @param[in] data Pointer to data used for crc16.
     * @param[in] dataLength Data length.
     */
    uint16_t computeCRC(const uint8_t *data, uint32_t lengthInBytes);

protected:
    uint32_t m_constantCrcValue; /*!< Constant CRC number. */
};

} // namespace erpc

/*! @} */

#endif // _EMBEDDED_RPC__CRC16_H_
