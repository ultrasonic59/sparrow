/*
 * ugen_fpga.h
 *
 *  Created on: Apr 8, 2017
 *      Author: vovag
 */

#ifndef _UGEN_FPGA_H_
#define _UGEN_FPGA_H_

#include <stdint.h>

///static const int UGEN_BASE_ADDR = 0x40400100;
static const int UGEN_BASE_ADDR = 0x40200000;
////static const int UGEN_BASE_SIZE = 0x30;
#define AWG_BASE_SIZE 0x30000
static const int UGEN_BASE_SIZE = AWG_BASE_SIZE;

///#define AWG_BASE_ADDR 0x40200000
/** Base AWG FPGA core size */
///#define AWG_BASE_SIZE 0x30000
#if 0
typedef struct ugen_reg_s
{
uint32_t rsv[20];
uint32_t conf_ugen;
uint32_t pre;
uint32_t rng;
uint32_t len_def;

}ugen_reg_t;
#endif

typedef struct ugen_reg_s {
    /** @brief Offset 0x00 - State machine configuration
     *
     * State machine configuration register (offset 0x00):
     *  bits [31:24] - Reserved
     *  bit  [   23] - Channel B output set to 0
     *  bit  [   22] - Channel B state machine reset
     *  bit  [   21] - Channel B set one time trigger
     *  bit  [   20] - Channel B state machine wrap pointer
     *  bits [19:16] - Channel B trigger selector
     *  bits [15: 8] - Reserved
     *  bit  [    7] - Channel B output set to 0
     *  bit  [    6] - Channel B state machine reset
     *  bit  [    5] - Channel B set one time trigger
     *  bit  [    4] - Channel B state machine wrap pointer
     *  bits [ 3: 0] - Channel B trigger selector
     *
     */
    uint32_t state_machine_conf;
    /** @brief Offset 0x04 - Channel A amplitude scale and offset
     *
     * Channel A amplitude scale and offset register (offset 0x04) used to set the
     * amplitude and scale of output signal: out = (data * scale)/0x2000 + offset
     * bits [31:30] - Reserved
     * bits [29:16] - Amplitude offset
     * bits [15:14] - Reserved
     * bits [13: 0] - Amplitude scale (0x2000 == multiply by 1, unsigned)
     */
    uint32_t cha_scale_off;
    /** @brief Offset 0x08 - Channel A counter wrap
     *
     * Channel A counter wrap (offset 0x08) - value at which FPGA AWG state
     * machine will wrap the output signal buffer readout:
     * bits [31:30] - Reserved
     * bits [29: 0] - Output signal counter wrap
     */
    uint32_t cha_count_wrap;
    /** @brief Offset 0x0C - Channel A starting counter offset
     *
     * Channel A starting counter offset (offset 0x0C) - start offset when
     * trigger arrives
     * bits [31:30] - Reserved
     * bits [29: 0] - Counter start offset
     */
    uint32_t cha_start_off;
    /** @brief Offset 0x10 - Channel A counter step
     *
     * Channel A counter step (offset 0x10) - value by which FPGA AWG state
     * machine increment readout from output signal buffer:
     * bits [31:30] - Reserved
     * bits [29: 0] - Counter step
     */
    uint32_t cha_count_step;

    /** @brief Reserved */
    uint32_t reserved_regs[2];
    uint32_t delay_a;
    uint32_t len_a;				///[13:0]

    /** @brief Offset 0x24 - Channel B amplitude scale and offset
     *
     * Channel B amplitude scale and offset register (offset 0x24) used to set the
     * amplitude and scale of output signal: out = (data * scale)/0x2000 + offset
     * bits [31:30] - Reserved
     * bits [29:16] - Amplitude offset
     * bits [15:14] - Reserved
     * bits [13: 0] - Amplitude scale (0x2000 == multiply by 1, unsigned)
     */
    uint32_t chb_scale_off;
    /** @brief Offset 0x28 - Channel B counter wrap
     *
     * Channel B counter wrap (offset 0x28) - value at which FPGA AWG state
     * machine will wrap the output signal buffer readout:
     * bits [31:30] - Reserved
     * bits [29: 0] - Output signal counter wrap
     */
    uint32_t chb_count_wrap;
    /** @brief Offset 0x2C - Channel B starting counter offset
     *
     * Channel B starting counter offset (offset 0x2C) - start offset when
     * trigger arrives
     * bits [31:30] - Reserved
     * bits [29: 0] - Counter start offset
     */
    uint32_t chb_start_off;
    /** @brief Offset 0x30 - Channel B counter step
     *
     * Channel B counter step (offset 0x30) - value by which FPGA AWG state
     * machine increment readout from output signal buffer:
     * bits [31:30] - Reserved
     * bits [29: 0] - Counter step
     */
    uint32_t chb_count_step;
    uint32_t reserved_regs1[2];
    uint32_t delay_b;
    uint32_t len_b;				///[13:0][40]

    uint32_t rsv[15];
    uint32_t conf_ugen;
    uint32_t pre;
    uint32_t rng;
    uint32_t len_def;
} ugen_reg_t;
/** AWG FPGA parameters */
typedef struct {
    int32_t  offsgain;   ///< AWG offset & gain.
    uint32_t wrap;       ///< AWG buffer wrap value.
    uint32_t step;       ///< AWG step interval.
} awg_param_t;
/** Signal types */
typedef enum {
    eSignalSine,         ///< Sinusoidal waveform.
    eSignalSquare,       ///< Square waveform.
    eSignalTriangle,     ///< Triangular waveform.
    eSignalSweep         ///< Sinusoidal frequency sweep.
} signal_e;

#define n (16*1024)
#define NUM_PNT_SIN 24

#define AWG_SIG_LEN   (16*1024)
/** FPGA AWG output signal 1 offset */
#define AWG_CHA_OFFSET    0x10000
/** FPGA AWG output signal 2 offset */
#define AWG_CHB_OFFSET    0x20000

extern volatile void *fpga_regs;

extern volatile ugen_reg_t *ugen_regs;
extern int init_ugen_fpga(void);

#endif /* _UGEN_FPGA_H_ */
