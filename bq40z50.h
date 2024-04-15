#ifndef BQ40Z50_H_
#define BQ40Z50_H_


#define BQ40Z50_ADDRESS 0x0B   //(0x16<<1)|0x01

#define REMAINING_CAPACITY_ALARM 0x01 // R/W Sets a low capacity alarm threshold
#define REMAINING_TIME_ALARM 0x02 // R/W Sets a low remaining time-to-fully discharge alarm
#define BATTERY_MODE 0x03 // R/W Sets various operating mode options
#define AT_RATE 0x04 // R/W Sets the value used in calculating AtRateTimeToFull & AtRateTimeToEmpty
#define AT_RATE_TIME_TO_FULL 0x05 // Read Returns the remaining time-to-fully charge
#define AT_RATE_TIME_TO_EMPTY 0x06 // Read Returns the remaining time-to-fully discharge
#define AT_RATE_OK 0x07 // Read Returns a bool value that indicates whether BAT can deliver AtRate() for at least 10 secs
#define TEMPERATURE 0x08 // Read Returns the temperature in units 0.1degrees K
#define PACK_VOLTAGE 0x09 // Read Returns the sum of the measured cell voltages
#define CURRENT 0x0A // Read Returns the measured current from the coulomb counter
#define AVERAGE_CURRENT 0x0B // Read Returns averaged current
#define MAX_ERROR 0x0C // Read Returns the expected margin of error, in %, in the SOC calculation with a range of 1 to 100%
#define RELATIVE_SOC 0x0D // Read Returns the predicted remaining battery capacity as a % of FullChargeCapacity()
#define ABSOLUTE_SOC 0x0E // Read Returns the predicted remaining battery capacity as a %
#define REMAINING_CAPACITY 0x0F // Read Returns the predicted remaining BAT capacity
#define FULL_CHARGE_CAPACITY 0x10 // Read Returns the predicted BAT capacity when fully charged.
#define RUN_TIME_TO_EMPTY 0x11 // Read Returns the predicted remaining BAT capacity based on the present rate of discharge
#define AVERAGE_TIME_TO_EMPTY 0x12 // Read Returns the predicted remaining BAT capacity based on AverageCurrent()
#define AVERAGE_TIME_TO_FULL 0x13 // Read Returns the predicted time-to-full charge based on AverageCurrent()
#define CHARGING_CURRENT 0x14 // Read Returns the desired charging current
#define CHARGING_VOLTAGE 0x15 // Read Returns the desired charging voltage
#define BATTERY_STATUS 0x16 // Read Returns various battery status information
#define CYCLE_COUNT 0x17 // Read Returns the number of discharge cycles the battery has experienced. Stored in cycle count
#define DESIGN_CAPACITY 0x18 // Read Returns the theoretical pack capacity. Stored in DesignCapacity mAh or cWh
#define DESIGN_VOLTAGE 0x19 // Read Returns the theoretical pack voltage. Stored in Design Voltage
#define SPECIFICATION 0x1A //
#define MANUFACTURER_DATE 0x1B // Read Returns the pack manufacturer date : D + M*32 + (Y-1980)*256
#define SERIAL_NUMBER 0x1C // Read Returns the assigned pack serial number
#define MANUFACTURER_NAME 0x20 // Read Retunrs the pack manufactrer name
#define DEVICE_NAME 0x21 // Read Returns the assigned pack name
#define DEVICE_CHEMISTRY 0x22 // Read Returns the BAT chemistry
#define MANUFACTURER_DATA 0x23 // Read Returns ManufacturerInfo by default.
#define AUTHENTICATE 0x2F // R/W Provides SHA-1 authentication to send the challenge and read the response.
#define CELL_VOLTAGE4 0x3C // Returns the Cell 4 voltage
#define CELL_VOLTAGE3 0x3D // Returns the Cell 3 voltage
#define CELL_VOLTAGE2 0x3E // Returns the Cell 2 voltage
#define CELL_VOLTAGE1 0x3F // Returns the Cell 1 voltage
#define BTP_DISCHARGE_SET 0x4A // R/W updates the BTP set threshold for discharge mode for the next BTP int
#define BTP_CHARGE_SET 0x4B // R/W updates the BTP set threshold for charge mode for the next BTP int
#define STATE_OF_HEALTH 0x4F // Returns the SOH info of the BAT in percentage of design capacity & energy
#define SAFETY_ALERT 0x50 // Returns the SafetyAlert() flags.
#define SAFETY_STATUS 0x51 // Returns the SafetyStatus() flags.
#define PF_ALERT 0x52 // Returns the PFAlert() flags.
#define PF_STATUS 0x53 // Returns the PFStatus() flags.
#define OPERATION_STATUS 0x54 // Returns the OperationStatus() flags.
#define CHARGING_STATUS 0x55 // Returns the ChargingStatus() flags.
#define GAUGING_STATUS 0x56 // Returns GaugingStatus() flags.
#define MANUFACTURING_STATUS 0x57 // Returns the ManufacturingStatus() flags.
#define AFE_REGISTER 0x58 // Returns a snapshot of the AFE register settings
#define TURBO_POWER 0x59 // Reports the maximal peak power value. The gauge computes a new RAM value every second.
#define TURBO_FINAL 0x5A // Sets min Turbo power, which represents the minimal TURBO BOOST mode power level during active operation
#define TURBO_PACK_R 0x5B // Sets the PACK resistance value of the BAT pack serial resistance. Accesses to the stored value PackResistance
#define TURBO_SYS_R 0x5C // Sets the System resistance value of the system serial resistance along the path from BAT to system power converter
#define TURBO_EDV 0x5D // Sets the minimal voltage at the system power converter input at which the system will still operate
#define TURBO_CURRENT 0x5E // The gauge computes a maximal discharge current supported by the cell design for a C-rate discharge pulse for 10 ms
#define TURBO_SUBCURRENT 0X5F
#define LIFETIME_DATA_BLOCK1 0x60 // Returns the first block of Lifetime data.
#define LIFETIME_DATA_BLOCK2 0x61 // Returns the second block of Lifetime data.
#define LIFETIME_DATA_BLOCK3 0x62 // Returns the third block of Lifetime data.
#define LIFETIME_DATA_BLOCK4 0x63 // Returns the fourth block of Lifetime data.
#define LIFETIME_DATA_BLOCK5 0x64 // Returns the fifth block of Lifetime data.
#define DA_STATUS1 0x71 // Returns the Cell Voltages, Pack Voltage, BAT voltage, Cell current, cell powers, power and average power.
#define DA_STATUS2 0x72 // Returns the internal temperature sensor TS1, TS2, TS3, TS4, Cell Temp and FET Temp
#define GAUGE_STATUS1 0x73 // Instructs the device to return Impedance Track related gauging information
#define GAUGE_STATUS2 0x74 // Instructs the device to return Impedance Track related gauging information
#define GAUGE_STATUS3 0x75 // Instructs the device to return Impedance Track related gauging information
#define CB_STATUS 0x76 // Instructs the device to return cell balance time information
#define STATE_OF_HEALTH2 0x77 // Instructs the device to reutnr the state-of-health full charge capacity and energy
#define FILTERED_CAPACITY 0x78 // Instructs the device to return the filtered capacity and energy even if [SMOOTH]=0

/******************************************************************************
 * @brief Initialize TI bq40z50 battery manager
 */
void battteryMonitorInit(void);

/******************************************************************************
 * @brief Reads the remaining time-to-fully charge the battery pack. (in minutes)
 */
void batteryRateTimeToFull(void);

/******************************************************************************
 * @brief Reads the remaining time-to-fully discharge the battery pack. (in minutes)
 */
void batteryRateTimeToEmpty(void);

/******************************************************************************
 * @brief Reads TI BQ40z50 IC temperature
 * @param BQ40Z50 address
 * @param Temperature Register (0x08)
 * @return Temp value in hex (0.1 degrees Kelvin)
 */
void batteryMonitorTemperature(void);

/******************************************************************************
 * @brief This cmd reads battery pack voltage (in mV)
 */
uint8_t* batteryPackVoltage(void);

/******************************************************************************
 * @brief Reads the measured current from the coulumb counter (in mA)
 */
uint8_t* batteryPackCurrent(void);

/******************************************************************************
 * @brief Reads the measured average current (in mA)
 */
void batteryPackAverageCurrent(void);

/******************************************************************************
 * @brief Reads the battery relative SOC (in %)
 */
uint8_t* batteryRelativeSOC(void);

/******************************************************************************
 * @brief Reads the battery absolute SOC (in %)
 */
void batteryAbsoluteSOC(void);

/******************************************************************************
 * @brief Predicts the remaining battery capacity (in mA)
 */
void batteryRemainingCapacity(void);

/******************************************************************************
 * @brief Predicts the full charged battery capacity (in mA)
 */
void batteryFullChargeCapacity(void);

/******************************************************************************
 * @brief Predics the remaining battery capacity based on the present discharging rate (in min)
 */
void batteryRunTimeToEmpty(void);

/******************************************************************************
 * @brief Predics the remaining battery capacity based on AverageCurrent (in min)
 */
void batteryAverateTimeToEmpty(void);

/******************************************************************************
 * @brief Reads the desired charging current (in mA)
 */
void batteryChargingCurrent(void);

/******************************************************************************
 * @brief Reads the desired charging voltage (in mV)
 */
void batteryChargingVoltage(void);

/******************************************************************************
 * @brief Reads the battery status information (plenty of info)
 */
void batteryBatteryStatus(void);

/******************************************************************************
 * @brief Reads the number of discharge cycles the battery has experienced.
 *
 * @note: The default value is stored in the data flash value "Cycle Count"
 */
uint8_t* batteryCycleCount(void);

/******************************************************************************
 * @brief Reads the theoretical pack capacity. (mAh or 10mWh)
 *
 * @note: The default value is stored in the data flash value "Design Capacity mAh" or "Design Capacity mWh"
 */
void batteryDesignCapacity(void);

/******************************************************************************
 * @brief Reads the theoretical pack voltage. (mV)
 *
 * @note: The default value is stored in the data flash value "Design Voltage"
 */
void batteryDesignVoltage(void);

/******************************************************************************
 * @brief Reads the specification info.
 */
void batterySpecificationInfo(void);

/******************************************************************************
 * @brief Reads cell#4 voltage. (in mV)
 */
uint8_t* batteryCell4Voltage(void);

/******************************************************************************
 * @brief Reads cell#3 voltage. (in mV)
 */
uint8_t* batteryCell3Voltage(void);

/******************************************************************************
 * @brief Reads cell#2 voltage. (in mV)
 */
uint8_t* batteryCell2Voltage(void);

/******************************************************************************
 * @brief Reads cell#1 voltage. (in mV)
 */
uint8_t* batteryCell1Voltage(void);

/******************************************************************************
 * @brief Reads pack DA status #1
 */
uint8_t* batteryDAstatus1(void);

uint8_t* batteryDAStatus2(void);

void batteryDEVICE_NAME(void);

void hex2dec(const char* name, uint8_t value2, uint8_t value1, const char* unit);
/******************************************************************************
 * @brief Copy from the source data to the destination data.
 */
void CopyChar
(
        uint8_t *source,
        unsigned char *dest,
        uint8_t count
);

#endif /* BQ40Z50_H_ */
