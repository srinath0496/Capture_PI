
/** System commands */
UINT_8 const WAKEUP            = 0x02;
UINT_8 const STANDBY           = 0x04;
UINT_8 const RESET             = 0x06;
UINT_8 const START             = 0x08;
UINT_8 const STOP              = 0x0A;
/** Read data commands */
UINT_8 const RDATAC            = 0x10;
UINT_8 const SDATAC            = 0x11;
UINT_8 const RDATA             = 0x12;
/** Write/Read register commands */
UINT_8 const RREG              = 0x20;
UINT_8 const WREG              = 0x40;
//------------------------------------------------------------------------------
// ADC register settings
//------------------------------------------------------------------------------
/** ID Control Register Address (Factory-Programmed, Read-Only). */
UINT_8 const ID                = 0x00;
/** Device family identification*/
UINT_8 const ID_ADS1294        = 0x90;
UINT_8 const ID_ADS1296        = 0x91;
UINT_8 const ID_ADS1298        = 0x92;
UINT_8 const ID_ADS1294R       = 0xD0;
UINT_8 const ID_ADS1296R       = 0xD1;
UINT_8 const ID_ADS1298R       = 0xD2;
//------------------------------------------------------------------------------
/** CONFIG1: Configuration Register 1 address. Configure resolution and power mode. */
UINT_8 const CONFIG1           = 0x01;
/** CONFIG1 register configuration bits */
UINT_8 const CONFIG1_const     = 0x00; // Bits[4:3] must always bet set to 0, always use this const when configuring!
UINT_8 const DAISY_EN          = 0x40; // Multiple readback mode
UINT_8 const CLK_EN            = 0x20; // Internal oscillator signal is connected to the CLK pin
/** For High-Resolution mode: fMOD = fCLK/4 */
UINT_8 const HIGH_RES_32k_SPS  = 0x80; // Data rate is fMOD/16
UINT_8 const HIGH_RES_16k_SPS  = 0x81; // Data rate is fMOD/32
UINT_8 const HIGH_RES_8k_SPS   = 0x82; // Data rate is fMOD/64
UINT_8 const HIGH_RES_4k_SPS   = 0x83; // Data rate is fMOD/128
UINT_8 const HIGH_RES_2k_SPS   = 0x84; // Data rate is fMOD/256
UINT_8 const HIGH_RES_1k_SPS   = 0x85; // Data rate is fMOD/512
UINT_8 const HIGH_RES_500_SPS  = 0x86; // Data rate is fMOD/1024
/** For Low Power mode: fMOD = fCLK/8 */
UINT_8 const LOW_POWR_16k_SPS  = 0x00; // Data rate is fMOD/16
UINT_8 const LOW_POWR_8k_SPS   = 0x01; // Data rate is fMOD/32
UINT_8 const LOW_POWR_4k_SPS   = 0x02; // Data rate is fMOD/64
UINT_8 const LOW_POWR_2k_SPS   = 0x03; // Data rate is fMOD/128
UINT_8 const LOW_POWR_1k_SPS   = 0x04; // Data rate is fMOD/256
UINT_8 const LOW_POWR_500_SPS  = 0x05; // Data rate is fMOD/512
UINT_8 const LOW_POWR_250_SPS  = 0x06; // Data rate is fMOD/1024
//------------------------------------------------------------------------------
/** CONFIG2: Configuration Register 2 address. Configure the test signal generation. */
UINT_8 const CONFIG2           = 0x02;
/** CONFIG2 register configuration bits */
UINT_8 const CONFIG2_const     = 0x00; // Bits[7:6,3] must always bet set to 0, always use this const when configuring!
UINT_8 const WCT_CHOP          = 0x20; // Chopping frequency constant at fMOD/16
UINT_8 const TEST_AMP          = 0x04; // Increase test Amp to 2 × –(VREFP – VREFN)/2400 V

UINT_8 const INT_TEST_1HZ      = 0x10; // Internal test with Amp = 1 × –(VREFP – VREFN)/2400 V and pulsed at fCLK/(2^21)
UINT_8 const INT_TEST_2HZ      = 0x11; // Internal test with Amp = 1 × –(VREFP – VREFN)/2400 V and pulsed at fCLK/(2^20)
UINT_8 const INT_TEST_DC       = 0x13; // Internal test with Amp = 1 × –(VREFP – VREFN)/2400 V and at DC
//------------------------------------------------------------------------------
/** CONFIG3: Configuration Register 3 address. Configure multi-reference and RLD operation. */
UINT_8 const CONFIG3           = 0x03;
/** CONFIG3 register configuration bits */
UINT_8 const CONFIG3_const     = 0x40; // Bit[6] must always bet set to 1, always use this const when configuring!
UINT_8 const PD_REFBUF         = 0x80; // Enable internal reference buffer
UINT_8 const VREF_4V           = 0x20; // VREFP is set to 4V (use only with a 5V analog supply)
UINT_8 const RLD_MEAS          = 0x10; // RLD_IN signal is routed to the channel that has the MUX_Setting 010 (VREF)
UINT_8 const RLDREF_INT        = 0x08; // RLDREF signal (AVDD – AVSS)/2 generated internally
UINT_8 const PD_RLD            = 0x04; // RLD buffer is enabled
UINT_8 const RLD_LOFF_SENS     = 0x02; // RLD sense is enabled
UINT_8 const RLD_STAT          = 0x01; // RLD is not connected
//------------------------------------------------------------------------------
/** LOFF: Lead-Off Control Register address. Configure the Lead-Off detection operation. */
UINT_8 const LOFF              = 0x04;
/** LOFF register configuration bits */
UINT_8 const LOFF_const        = 0x00; // No constant bits, nevertheless always use this const when configuring!

UINT_8 const COMP_TH_95        = 0x00; // Comparator positive side 95%, Comparator negative side 5%
UINT_8 const COMP_TH_92_5      = 0x20; // Comparator positive side 92.5%, Comparator negative side 7.5%
UINT_8 const COMP_TH_90        = 0x40; // Comparator positive side 90%, Comparator negative side 10%
UINT_8 const COMP_TH_87_5      = 0x60; // Comparator positive side 87.5%, Comparator negative side 12.5%
UINT_8 const COMP_TH_85        = 0x80; // Comparator positive side 85%, Comparator negative side 15%
UINT_8 const COMP_TH_80        = 0xA0; // Comparator positive side 80%, Comparator negative side 20%
UINT_8 const COMP_TH_75        = 0xC0; // Comparator positive side 75%, Comparator negative side 25%
UINT_8 const COMP_TH_70        = 0xE0; // Comparator positive side 70%, Comparator negative side 30%

UINT_8 const VLEAD_OFF_EN      = 0x10; // Pull-up/pull-down resistor mode lead-off

UINT_8 const ILEAD_OFF_6nA     = 0x00; // Magnitude of current for the current lead-off mode: 6 nA
UINT_8 const ILEAD_OFF_12nA    = 0x04; // Magnitude of current for the current lead-off mode: 12 nA
UINT_8 const ILEAD_OFF_18nA    = 0x08; // Magnitude of current for the current lead-off mode: 18 nA
UINT_8 const ILEAD_OFF_24nA    = 0x0C; // Magnitude of current for the current lead-off mode: 24 nA

UINT_8 const FLEAD_OFF_AC      = 0x01; // AC lead-off detection at fDR/4
UINT_8 const FLEAD_OFF_DC      = 0x03; // DC lead-off detection
//------------------------------------------------------------------------------
/** CHnSET: Individual Channel addresses (n = 1 : 8). Configure the power mode, PGA gain, and multiplexer settings. */
UINT_8 const CH1SET            = 0x05; // Channel 1 configuration register address
UINT_8 const CH2SET            = 0x06; // Channel 2 configuration register address
UINT_8 const CH3SET            = 0x07; // Channel 3 configuration register address
UINT_8 const CH4SET            = 0x08; // Channel 4 configuration register address
UINT_8 const CH5SET            = 0x09; // Channel 5 configuration register address
UINT_8 const CH6SET            = 0x0A; // Channel 6 configuration register address
UINT_8 const CH7SET            = 0x0B; // Channel 7 configuration register address
UINT_8 const CH8SET            = 0x0C; // Channel 8 configuration register address
/** CHnSET register configuration bits */
UINT_8 const CHnSET_const      = 0x00; // Bit[3] must always bet set to 1, always use this const when configuring!

UINT_8 const PD_CH             = 0x80; // Channel power-down. Recommended that the channel be set to input short MUXn[2:0] = 001.

UINT_8 const GAIN_X6           = 0x00; // PGA gain is 6 (default)
UINT_8 const GAIN_X1           = 0x10; // PGA gain is 1
UINT_8 const GAIN_X2           = 0x20; // PGA gain is 2
UINT_8 const GAIN_X3           = 0x30; // PGA gain is 3
UINT_8 const GAIN_X4           = 0x40; // PGA gain is 4
UINT_8 const GAIN_X8           = 0x50; // PGA gain is 8
UINT_8 const GAIN_X12          = 0x60; // PGA gain is 12

UINT_8 const ELECTRODE_INPUT   = 0x00; // Normal electrode input
UINT_8 const SHORTED           = 0x01; // Input shorted (for offset or noise measurements)
UINT_8 const RLD_INPUT         = 0x02; // Used in conjunction with RLD_MEAS bit for RLD measurements.
UINT_8 const MVDD              = 0x03; // MVDD for supply measurement
UINT_8 const TEMP              = 0x04; // Temperature sensor
UINT_8 const TEST_SIGNAL       = 0x05; // Test signal
UINT_8 const RLD_DRP           = 0x06; // RLD_DRP (positive electrode is the driver)
UINT_8 const RLD_DRN           = 0x07; // RLD_DRN (negative electrode is the driver)
//------------------------------------------------------------------------------
/** Control the selection of the positive signals from each channel for right leg drive derivation. */
UINT_8 const RLD_SENSP         = 0x0D;
/** RLD_SENSP register configuration bits */
UINT_8 const RLD_SENSP_const   = 0x00; // No positive signal selected for RLD
UINT_8 const RLD1P             = 0x01; // Channel 1+  is selected for RLD
UINT_8 const RLD2P             = 0x02; // Channel 2+  is selected for RLD
UINT_8 const RLD3P             = 0x04; // Channel 3+  is selected for RLD
UINT_8 const RLD4P             = 0x08; // Channel 4+  is selected for RLD
UINT_8 const RLD5P             = 0x10; // Channel 5+  is selected for RLD
UINT_8 const RLD6P             = 0x20; // Channel 6+  is selected for RLD
UINT_8 const RLD7P             = 0x40; // Channel 7+  is selected for RLD
UINT_8 const RLD8P             = 0x80; // Channel 8+  is selected for RLD
//------------------------------------------------------------------------------
/** Control the selection of the negative signals from each channel for right leg drive derivation. */
UINT_8 const RLD_SENSN         = 0x0E;
/** RLD_SENSN register configuration bits */
UINT_8 const RLD_SENSN_const   = 0x00; // No negative signal selected for RLD
UINT_8 const RLD1N             = 0x01; // Channel 1-  is selected for RLD
UINT_8 const RLD2N             = 0x02; // Channel 2-  is selected for RLD
UINT_8 const RLD3N             = 0x04; // Channel 3-  is selected for RLD
UINT_8 const RLD4N             = 0x08; // Channel 4-  is selected for RLD
UINT_8 const RLD5N             = 0x10; // Channel 5-  is selected for RLD
UINT_8 const RLD6N             = 0x20; // Channel 6-  is selected for RLD
UINT_8 const RLD7N             = 0x40; // Channel 7-  is selected for RLD
UINT_8 const RLD8N             = 0x80; // Channel 8-  is selected for RLD
//------------------------------------------------------------------------------
/** Control the selection of the the positive side from each channel for lead-off detection. */
UINT_8 const LOFF_SENSP        = 0x0F;
/** LOFF_SENSP register configuration bits */
UINT_8 const LOFF_SENSP_const  = 0x00; // No positive side selected for LOFF
UINT_8 const LOFF1P            = 0x01; // Channel 1+  is selected
UINT_8 const LOFF2P            = 0x02; // Channel 2+  is selected
UINT_8 const LOFF3P            = 0x04; // Channel 3+  is selected
UINT_8 const LOFF4P            = 0x08; // Channel 4+  is selected
UINT_8 const LOFF5P            = 0x10; // Channel 5+  is selected
UINT_8 const LOFF6P            = 0x20; // Channel 6+  is selected
UINT_8 const LOFF7P            = 0x40; // Channel 7+  is selected
UINT_8 const LOFF8P            = 0x80; // Channel 8+  is selected
//------------------------------------------------------------------------------
/** Control the selection of the the negative side from each channel for lead-off detection. */
UINT_8 const LOFF_SENSN        = 0x10;
/** LOFF_SENSN register configuration bits */
UINT_8 const LOFF_SENSN_const  = 0x00; // No negative side selected for LOFF
UINT_8 const LOFF1N            = 0x01; // Channel 1-  is selected
UINT_8 const LOFF2N            = 0x02; // Channel 2-  is selected
UINT_8 const LOFF3N            = 0x04; // Channel 3-  is selected
UINT_8 const LOFF4N            = 0x08; // Channel 4-  is selected
UINT_8 const LOFF5N            = 0x10; // Channel 5-  is selected
UINT_8 const LOFF6N            = 0x20; // Channel 6-  is selected
UINT_8 const LOFF7N            = 0x40; // Channel 7-  is selected
UINT_8 const LOFF8N            = 0x80; // Channel 8-  is selected
//------------------------------------------------------------------------------
/** Control the direction of the current used for lead-off derivation. */
UINT_8 const LOFF_FLIP         = 0x11;
/** LOFF_FLIP register configuration bits */
UINT_8 const LOFF_FLIP_const   = 0x00;
UINT_8 const LOFF_FLIP1        = 0x01;
UINT_8 const LOFF_FLIP2        = 0x02;
UINT_8 const LOFF_FLIP3        = 0x04;
UINT_8 const LOFF_FLIP4        = 0x08;
UINT_8 const LOFF_FLIP5        = 0x10;
UINT_8 const LOFF_FLIP6        = 0x20;
UINT_8 const LOFF_FLIP7        = 0x40;
UINT_8 const LOFF_FLIP8        = 0x80;
//------------------------------------------------------------------------------
/** LOFF_STATP: Read-Only Register stores the status of whether the positive electrode on each channel is on or off. */
UINT_8 const LOFF_STATP        = 0x12;
/** LOFF_STATP register indicator bits */
UINT_8 const IN1P_OFF          = 0x01;
UINT_8 const IN2P_OFF          = 0x02;
UINT_8 const IN3P_OFF          = 0x04;
UINT_8 const IN4P_OFF          = 0x08;
UINT_8 const IN5P_OFF          = 0x10;
UINT_8 const IN6P_OFF          = 0x20;
UINT_8 const IN7P_OFF          = 0x40;
UINT_8 const IN8P_OFF          = 0x80;
//------------------------------------------------------------------------------
/** LOFF_STATN: Read-Only Register stores the status of whether the negative electrode on each channel is on or off. */
UINT_8 const LOFF_STATN        = 0x13;
/** LOFF_STATN register indicator bits */
UINT_8 const IN1N_OFF          = 0x01;
UINT_8 const IN2N_OFF          = 0x02;
UINT_8 const IN3N_OFF          = 0x04;
UINT_8 const IN4N_OFF          = 0x08;
UINT_8 const IN5N_OFF          = 0x10;
UINT_8 const IN6N_OFF          = 0x20;
UINT_8 const IN7N_OFF          = 0x40;
UINT_8 const IN8N_OFF          = 0x80;
//------------------------------------------------------------------------------
/** The General-Purpose I/O Register controls the action of the three GPIO pins. */
UINT_8 const GPIO              = 0x14;
/** GPIO register indicator/configuration bits */
UINT_8 const GPIO_const        = 0x00; // Set all GPIO pins to output
UINT_8 const GPIOD4            = 0x80; // Read/write data to the GPIO port 4
UINT_8 const GPIOD3            = 0x40; // Read/write data to the GPIO port 3
UINT_8 const GPIOD2            = 0x20; // Read/write data to the GPIO port 2
UINT_8 const GPIOD1            = 0x10; // Read/write data to the GPIO port 1

UINT_8 const GPIOC4            = 0x08; // GPIO port 4 is input
UINT_8 const GPIOC3            = 0x04; // GPIO port 3 is input
UINT_8 const GPIOC2            = 0x02; // GPIO port 2 is input
UINT_8 const GPIOC1            = 0x01; // GPIO port 1 is input
//------------------------------------------------------------------------------
/** PACE: PACE Detect Register address. Configure the channel signal used to feed the external PACE detect circuitry. */
UINT_8 const PACE              = 0x15;
/** PACE register configuration bits */
UINT_8 const PACE_const        = 0x00; // Bit[7:5] must always bet set to 0, always use this const when configuring!

UINT_8 const PACEE_CHAN2       = 0x00; // Channel 2 (default) available on TEST_PACE_OUT1
UINT_8 const PACEE_CHAN4       = 0x08; // Channel 4 available on TEST_PACE_OUT1
UINT_8 const PACEE_CHAN6       = 0x10; // Channel 6 available on TEST_PACE_OUT1
UINT_8 const PACEE_CHAN8       = 0x18; // Channel 8 available on TEST_PACE_OUT1

UINT_8 const PACEE_CHAN1       = 0x00; // Channel 1 (default) available on TEST_PACE_OUT2
UINT_8 const PACEE_CHAN3       = 0x02; // Channel 3 available on TEST_PACE_OUT2
UINT_8 const PACEE_CHAN5       = 0x04; // Channel 6 available on TEST_PACE_OUT2
UINT_8 const PACEE_CHAN7       = 0x06; // Channel 7 available on TEST_PACE_OUT2

UINT_8 const PD_PACE           = 0x01; // PACE detect buffer turned on
//------------------------------------------------------------------------------
/** RESP: Respiration Control Register address. Control the respiration circuitry. */
UINT_8 const RESP              = 0x16;
/** RESP register configuration bits */
UINT_8 const RESP_const        = 0x20; // Bit[5] must always bet set to 1, always use this const when configuring!
UINT_8 const RESP_DEMOD_EN1    = 0x80; // RESP demodulation circuitry turned on
UINT_8 const RESP_MOD_EN1      = 0x40; // RESP modulation circuitry turned on

UINT_8 const RESP_PH_22_5      = 0x00; // 22.5 phase of the respiration demodulation control signal
UINT_8 const RESP_PH_45        = 0x04; // 45 phase of the respiration demodulation control signal
UINT_8 const RESP_PH_67_5      = 0x08; // 67.5 phase of the respiration demodulation control signal
UINT_8 const RESP_PH_90        = 0x0C; // 90 phase of the respiration demodulation control signal
UINT_8 const RESP_PH_112_5     = 0x10; // 112.5 phase of the respiration demodulation control signal
UINT_8 const RESP_PH_135       = 0x14; // 135 phase of the respiration demodulation control signal
UINT_8 const RESP_PH_157_5     = 0x18; // 157.5 phase of the respiration demodulation control signal

UINT_8 const RESP_NONE         = 0x00; // No respiration
UINT_8 const RESP_EXT          = 0x01; // External respiration
UINT_8 const RESP_INT_SIG_INT  = 0x02; // Internal respiration with internal signals
UINT_8 const RESP_INT_SIG_EXT  = 0x03; // Internal respiration with user-generated signals
//------------------------------------------------------------------------------
/** CONFIG4: Configuration Register 4 address. Miscellaneous controls. */
UINT_8 const CONFIG4           = 0x17;
/** CONFIG4 register configuration bits */
UINT_8 const CONFIG4_const     = 0x00; // Bits[4,0] must always bet set to 0, always use this const when configuring!

UINT_8 const RESP_FREQ_64k_Hz  = 0x00; // 64kHz modulation clock
UINT_8 const RESP_FREQ_32k_Hz  = 0x20; // 32kHz modulation clock
UINT_8 const RESP_FREQ_16k_Hz  = 0x40; // 16kHz modulation clock
UINT_8 const RESP_FREQ_8k_Hz   = 0x60; // 8kHz modulation clock
UINT_8 const RESP_FREQ_4k_Hz   = 0x80; // 4kHz modulation clock
UINT_8 const RESP_FREQ_2k_Hz   = 0xA0; // 2kHz modulation clock
UINT_8 const RESP_FREQ_1k_Hz   = 0xC0; // 1kHz modulation clock
UINT_8 const RESP_FREQ_500_Hz  = 0xE0; // 0.5kHz modulation clock

UINT_8 const SINGLE_SHOT       = 0x08; // Single-shot mode

UINT_8 const WCT_TO_RLD        = 0x04; // WCT to RLD connection on

UINT_8 const PD_LOFF_COMP      = 0x02; // Lead-off comparators enabled
//------------------------------------------------------------------------------
/** WCT1: Wilson Central Terminal and Augmented Lead Control Register address. */
UINT_8 const WCT1              = 0x18;
/** WCT1 register configuration bits */
UINT_8 const WCT1_const        = 0x00; // No constant bits, nevertheless always use this const when configuring!

UINT_8 const aVF_CH6           = 0x80; // Enable (WCTA + WCTB)/2 to the negative input of channel 6

UINT_8 const aVL_CH5           = 0x40; // Enable (WCTA + WCTC)/2 to the negative input of channel 5

UINT_8 const aVR_CH7           = 0x20; // Enable (WCTB + WCTC)/2 to the negative input of channel 7

UINT_8 const avR_CH4           = 0x10; // Enable (WCTB + WCTC)/2 to the negative input of channel 4

UINT_8 const PD_WCTA           = 0x08; // Powered on WCTA

UINT_8 const WCTA_CH1P         = 0x00; // Channel 1 positive input connected to WCTA amplifier
UINT_8 const WCTA_CH1N         = 0x01; // Channel 1 negative input connected to WCTA amplifier
UINT_8 const WCTA_CH2P         = 0x02; // Channel 2 positive input connected to WCTA amplifier
UINT_8 const WCTA_CH2N         = 0x03; // Channel 2 negative input connected to WCTA amplifier
UINT_8 const WCTA_CH3P         = 0x04; // Channel 3 positive input connected to WCTA amplifier
UINT_8 const WCTA_CH3N         = 0x05; // Channel 3 negative input connected to WCTA amplifier
UINT_8 const WCTA_CH4P         = 0x06; // Channel 4 positive input connected to WCTA amplifier
UINT_8 const WCTA_CH4N         = 0x07; // Channel 4 negative input connected to WCTA amplifier
//------------------------------------------------------------------------------
/** WCT2: Wilson Central Terminal Control Register address. */
UINT_8 const WCT2              = 0x19;
/** WCT2 register configuration bits */
UINT_8 const WCT2_const        = 0x00; // No constant bits, nevertheless always use this const when configuring!

UINT_8 const PD_WCTC           = 0x80; // Powered on WCTC

UINT_8 const PD_WCTB           = 0x40; // Powered on WCTB

UINT_8 const WCTB_CH1P         = 0x00; // Channel 1 positive input connected to WCTB amplifier
UINT_8 const WCTB_CH1N         = 0x08; // Channel 1 negative input connected to WCTB amplifier
UINT_8 const WCTB_CH2P         = 0x10; // Channel 2 positive input connected to WCTB amplifier
UINT_8 const WCTB_CH2N         = 0x18; // Channel 2 negative input connected to WCTB amplifier
UINT_8 const WCTB_CH3P         = 0x20; // Channel 3 positive input connected to WCTB amplifier
UINT_8 const WCTB_CH3N         = 0x28; // Channel 3 negative input connected to WCTB amplifier
UINT_8 const WCTB_CH4P         = 0x30; // Channel 4 positive input connected to WCTB amplifier
UINT_8 const WCTB_CH4N         = 0x38; // Channel 4 negative input connected to WCTB amplifier

UINT_8 const WCTC_CH1P         = 0x00; // Channel 1 positive input connected to WCTC amplifier
UINT_8 const WCTC_CH1N         = 0x01; // Channel 1 negative input connected to WCTC amplifier
UINT_8 const WCTC_CH2P         = 0x02; // Channel 2 positive input connected to WCTC amplifier
UINT_8 const WCTC_CH2N         = 0x03; // Channel 2 negative input connected to WCTC amplifier
UINT_8 const WCTC_CH3P         = 0x04; // Channel 3 positive input connected to WCTC amplifier
UINT_8 const WCTC_CH3N         = 0x05; // Channel 3 negative input connected to WCTC amplifier
UINT_8 const WCTC_CH4P         = 0x06; // Channel 4 positive input connected to WCTC amplifier
UINT_8 const WCTC_CH4N         = 0x07; // Channel 4 negative input connected to WCTC amplifier
//------------------------------------------------------------------------------
