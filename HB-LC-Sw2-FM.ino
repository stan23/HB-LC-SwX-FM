//- -----------------------------------------------------------------------------------------------------------------------
// AskSin++
// 2016-10-31 papa Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
// 2018-10-01 stan23 Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

// define this to read the device id, serial and device type from bootloader section
//#define USE_OTA_BOOTLOADER
//#define NDEBUG

// raise timer ticks to get more pin samples
#define TICKS_PER_SECOND 500UL
// we needs at least 10 LOW samples before we switch back to LOW
#define PINPOLL_COUNT_LOW 10

#include <AskSinPP.h>

#include <MultiChannelDevice.h>
#include <Switch.h>
#include <Remote.h>

// use MightyCore Standard pinout for ATmega32

#define RELAY1_PIN 0 // PB0

#define BUTTON1_PIN 24 // PA0

// number of available peers per channel
// number of available peers per channel
#define PEERS_PER_SWCHANNEL  6
#define PEERS_PER_BTNCHANNEL 20

// all library classes are placed in the namespace 'as'
using namespace as;

// define all device properties
const struct DeviceInfo PROGMEM devinfo = {
    {0x19,0x63,0xAC},       // Device ID
    "OEQ1663916",           // Device Serial
    {0xF5,0x02},            // Device Model
    0x01,                   // Firmware Version
    as::DeviceType::Switch, // Device Type
    {0x01,0x00}             // Info Bytes
};

// Configure the used hardware
typedef AvrSPI<4,5,6,7> RadioSPI; // PB4-PB7
typedef StatusLed<12> LedType; // PD4
typedef AskSin<LedType,NoBattery,Radio<RadioSPI,11> > Hal; // PD3
Hal hal;

DEFREGISTER(Reg0, MASTERID_REGS, DREG_INTKEY)
class SwList0 : public RegList0<Reg0> {
  public:
    SwList0(uint16_t addr) : RegList0<Reg0>(addr) {}
    void defaults() {
      clear();
      intKeyVisible(true);
    }
};

uint8_t SwitchPin (uint8_t number) {
  return RELAY1_PIN;
}

typedef SwitchChannel<Hal, PEERS_PER_SWCHANNEL, SwList0>  SwChannel;
typedef RemoteChannel<Hal, PEERS_PER_BTNCHANNEL, SwList0> BtnChannel;

class MixDevice : public ChannelDevice<Hal, VirtBaseChannel<Hal, SwList0>, 2, SwList0> {
public:
  VirtChannel<Hal, SwChannel, SwList0>  swc1;
  VirtChannel<Hal, BtnChannel, SwList0> btc1;
public:
  typedef VirtBaseChannel<Hal, SwList0> ChannelType;
  typedef ChannelDevice<Hal, ChannelType, 2, SwList0> DeviceType;
  MixDevice (const DeviceInfo& info,uint16_t addr) : DeviceType(info, addr) {
    DeviceType::registerChannel(swc1, 1);
    DeviceType::registerChannel(btc1, 2);
  }
  virtual ~MixDevice () {}

  BtnChannel& btn1Channel () { return btc1; }
  SwChannel&  sw1Channel  () { return swc1; }

  bool pollRadio () {
    bool worked = Device<Hal,SwList0>::pollRadio();
    for( uint8_t i=1; i<=this->channels(); ++i ) {
      ChannelType& ch = channel(i);
      if( ch.changed() == true ) {
        // we do not send status updates during a button is pressed
        if( btn1Channel().pressed()==false ) {
          this->sendInfoActuatorStatus(this->getMasterID(),this->nextcount(),ch);
          worked = true;
        }
      }
    }
    return worked;
  }

};
MixDevice sdev(devinfo,0x20);

void setup () {
  DINIT(19200,ASKSIN_PLUS_PLUS_IDENTIFIER);
  bool firstinit = sdev.init(hal);
  sdev.sw1Channel().init(RELAY1_PIN,false);
  remoteChannelISR(sdev.btn1Channel(),BUTTON1_PIN);
  if( firstinit == true ) {
    // create internal peerings
    HMID devid;
    sdev.getDeviceID(devid);
    sdev.sw1Channel().peer(Peer(devid,1));
    sdev.btn1Channel().peer(Peer(devid,2));
    storage().store();
  }
  sdev.initDone();
}

void loop() {
  bool worked = hal.runready();
  bool poll = sdev.pollRadio();
}
