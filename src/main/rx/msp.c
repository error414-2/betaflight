/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "drivers/system.h"

#include "drivers/serial.h"
#include "drivers/serial_uart.h"
#include "io/serial.h"

#include "rx/rx.h"
#include "rx/msp.h"

static bool rxMspFrameDone = false;

static uint16_t rxMspReadRawRC(rxRuntimeConfig_t *rxRuntimeConfig, uint8_t chan)
{
    return rcData[chan];
}

void rxMspFrameRecieve(void)
{
    rxMspFrameDone = true;
}

bool rxMspFrameComplete(void)
{
    if (rxMspFrameDone) {
        rxMspFrameDone = false;
        return true;
    }
    return false;
}

bool rxMspInit(rxConfig_t *rxConfig, rxRuntimeConfig_t *rxRuntimeConfig, rcReadRawDataPtr *callback)
{
    rxRuntimeConfig->channelCount = 8; // See MSP_SET_RAW_RC
    if (callback)
        *callback = rxMspReadRawRC;

    return true;
}
