#ifndef INCLUDE_MarlinKalTest
#define INCLUDE_MarlinKalTest 1

#include "MarlinTrk/IMarlinTrkSystem.h"


#include "gear/GearMgr.h"

//LCIO:
#include "lcio.h"
#include "UTIL/BitField64.h" 
#include "UTIL/LCTOOLS.h"
#include <LCRTRelations.h>

#include "streamlog/streamlog.h"

#include "TObjArray.h"
#include "TVector3.h"

#include <cmath>
#include <vector>



class TKalDetCradle ;
class TVKalDetector ;
class ILDVMeasLayer ;
class THelicalTrack ;
class ILDVMeasLayer ;

namespace EVENT{
  class TrackerHit ;
}

/** Interface to KaltTest Kalman fitter - instantiates and holds the detector geometry.
 */
class MarlinKalTest : public MarlinTrk::IMarlinTrkSystem {

 public:
  
  friend class MarlinKalTestTrack;

  // define some configuration constants
  static const bool FitBackward   = kIterBackward ;
  static const bool FitForward    = kIterForward ;
  static const bool OrderOutgoing  = true ;
  static const bool OrderIncoming  = false ;
  

  /** Default c'tor, initializes the geometry from GEAR. */
  MarlinKalTest( const gear::GearMgr& gearMgr) ;

  //  MarlinKalTest( const gear::GearMgr& gearMgr ) ;
  
  ~MarlinKalTest() ;
  
  
  // initialise track fitter system
  void init() ; 
  
  // instantiate its implementation of the IMarlinTrack 
  MarlinTrk::IMarlinTrack* createTrack()  ;

  // take multiple scattering into account during the fit
  void includeMultipleScattering( bool on )  ;

  // take energy loss into account during the fit
  void includeEnergyLoss( bool on )  ;



  void storeActiveMeasurementModuleIDs(TVKalDetector* detector);  

  void getSensitiveMeasurementModules( int detElementID, std::vector<ILDVMeasLayer*>& measmodules);

  void getSensitiveMeasurementModulesForLayer( int layerID, std::vector<ILDVMeasLayer*>& measmodules);


protected:

  //  void init(bool MSOn, bool EnergyLossOn) ;

 //** find the measurment layer for a given hit 
  const ILDVMeasLayer* findMeasLayer( EVENT::TrackerHit * trkhit) ;

  // get the last layer crossed by the helix when extrapolating from the present position to the pca to point
  const ILDVMeasLayer* getLastMeasLayer(THelicalTrack const& helix, TVector3 const& point) ;

  const gear::GearMgr* _gearMgr ;

  TKalDetCradle* _det ;            // the detector cradle

  std::multimap< Int_t, ILDVMeasLayer*> _active_measurement_modules;

  std::multimap< Int_t, ILDVMeasLayer*> _active_measurement_modules_by_layer;



} ;

#endif
