/***************************************************************************
* File Name: SEN-20001_MCP4725_12BIT_DAC.ino
* Processor/Platform: Arduino Uno R3 (tested)
* Development Environment: Arduino 1.6.5
*
* Designed for use with with Playing With Fusion MCP4725 12-Bit DAC breakout
* (SEN-20001) and any application that uses the MCP4725 DAC.
*
*   SEN-20001 (universal applications)
*   ---> http://www.playingwithfusion.com/productview.php?pdid=XXXXXXXXX
*
* Copyright © 2017 Playing With Fusion, Inc.
* SOFTWARE LICENSE AGREEMENT: This code is released under the MIT License.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
* **************************************************************************
* REVISION HISTORY:
* Author        Date      Comments
* J. Steinlage  2017Nov   Original version
* 
* Playing With Fusion, Inc. invests time and resources developing open-source
* code. Please support Playing With Fusion and continued open-source 
* development by buying products from Playing With Fusion!
*
* **************************************************************************
* APPLICATION SPECIFIC NOTES (READ THIS!!!):
* - This code configures an Arduino to interface with SEN-20001
*    - Configure Arduino (I2C, UART, etc)
*    - Perform initial verification and configuration of the DAC
* - I2C specific: This example uses the I2C interface via the Wire library
* 
* Circuit:
*    Arduino Uno   Arduino Mega  -->  SEN-20001
*    SDA:    SDA        SDA      -->  SDA
*    SCL:    SCL        SCL      -->  SCL
*    GND:    GND        ''       -->  GND
*    VDD:    5V         ''       -->  VDD
*    A0:     leave floating for address 0x62, pull high for 0x63
*    note: VDD should match voltage of IO, and can be between 2.7 and 5V
**************************************************************************/
// This example uses the Wire library
#include "Wire.h"
// include Playing With Fusion libraries
#include "PWFusion_MCP4725_12DAC.h"

// declare sensor object
#define DAC_ADD 0x62
PWFusion_MCP4725 dac0(DAC_ADD);

void setup()
{
  // start UART  
  Serial.begin(115200);
  Serial.println("Playing With Fusion: SEN-20001, Microchip MCP4725 12-Bit DAC");
  
  // setup for the the I2C library: (enable pullups, set speed to 400kHz)
  dac0.begin(); 

  // setup DAC, set DAC to 'off' and pulled low. Remember this setting (EEPROM)
  // setOutput(DAC output / write to NV memory / power down DAC, pull to gnd);
  dac0.setOutput(0,true,true);
  
  // give the Arduino time to start up
  delay(100); 
}


// triangle wave setup
uint16_t max_dac_voltage = 4095;  // maximum of 4095 for 12-bit DAC)
uint16_t triangle_del = 30;       // ms to delay changing voltage (shorter value gives faster wave)
volatile uint16_t cnt;            // counter variable

void loop()
{
  // Triangle Wave Example Code
  // set triange_del higher to lengthen duration of waveform
  // set max voltage to between 0 and 4095
  // Vo = cnt/4096 * Vin
  for(cnt = 0; cnt<max_dac_voltage; cnt++){
    dac0.setOutput(cnt,false,false);
    delay(triangle_del);
  }
  for(cnt = max_dac_voltage; cnt>0; cnt--){
    dac0.setOutput(cnt,false,false);
    delay(triangle_del);
  }
  dac0.setOutput(500,false,false);
}

