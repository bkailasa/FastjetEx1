// -*- C++ -*-
//
// Package:    FastjetEx/FastjetEx1
// Class:      FastjetEx1
//
/**\class FastjetEx1 FastjetEx1.cc FastjetEx/FastjetEx1/plugins/FastjetEx1.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Balashangar Kailasapathy
//         Created:  Mon, 06 Jul 2020 13:18:20 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"
 
// Header file for Fastjet Analysis

//#include "fastjet/ClusterSequence.hh"

#include "DataFormats/PatCandidates/interface/IsolatedTrack.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

class FastjetEx1 : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit FastjetEx1(const edm::ParameterSet&);
      ~FastjetEx1();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<std::vector<pat::IsolatedTrack>> tracksToken_;  //used to select what tracks to read from configuration file
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
FastjetEx1::FastjetEx1(const edm::ParameterSet& iConfig)
 :
//  tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks")))
tracksToken_(consumes<std::vector<pat::IsolatedTrack>>(edm::InputTag("isolatedTracks")))

{
	
   //now do what ever initialization is needed

}


FastjetEx1::~FastjetEx1()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
FastjetEx1::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

    Handle<std::vector<pat::IsolatedTrack>> tracks;
    iEvent.getByToken(tracksToken_, tracks);
    for(std::vector<pat::IsolatedTrack>::const_iterator itTrack = tracks->begin();
        itTrack != tracks->end();
        ++itTrack) {
      // do something with track parameters, e.g, plot the charge.
     int charge = itTrack->charge();
	  std::cout<<charge<<std::endl;
    }

	
	
	

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
FastjetEx1::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
FastjetEx1::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
FastjetEx1::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(FastjetEx1);
