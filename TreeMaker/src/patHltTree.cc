// Updated By : Raman Khurana 
// Dated      : Mon May 25 15:40:47 CDT 2015
// Added possible triggers for DM analysis, Jets and MET
#include "DelPanj/TreeMaker/interface/patHltTree.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "FWCore/Common/interface/TriggerNames.h" 

patHltTree::patHltTree(std::string name,TTree* tree):baseTree(name,tree),
						     nTrigs_(0)						     
{
  SetBranches();
}

void
patHltTree::Fill(const edm::Event& iEvent)
{
  Clear();
  using namespace edm;
  
  edm::Handle<edm::TriggerResults> trigResults;

  edm::InputTag trigTag("TriggerResults::HLT");
  if (not iEvent.getByLabel(trigTag, trigResults)) {
    std::cout << ">>> TRIGGER collection does not exist !!!\n";
    return;
  }

  const edm::TriggerNames & trigNames = iEvent.triggerNames(*trigResults);

  for (unsigned int i=0; i<trigResults->size(); i++)
    {
      std::string trigName = trigNames.triggerName(i);
      
      size_t foundEle00=trigName.find("HLT_DoubleEle33");
      size_t foundMuo00=trigName.find("HLT_Mu17_Mu8");
      size_t foundMuo01=trigName.find("HLT_Mu17_TkMu8");
      size_t foundMuo02=trigName.find("HLT_Mu30_TkMu11");
      
      // jet, met triggers
      size_t foundMETBTag                    = trigName.find("HLT_PFMET120_NoiseCleaned_BTagCSV07");
      size_t foundPFMET170                   = trigName.find("HLT_PFMET170_NoiseCleaned");
      size_t foundPFMET190MHT90              = trigName.find("HLT_PFMET90_PFMHT90_IDLoose");
      size_t founfPFMET120MHT120             = trigName.find("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight");
      size_t foundPFMET170NoiseClean         = trigName.find("HLT_PFMET170_NoiseCleaned");
      size_t foundDiCEntralPFJet70PFMET120   = trigName.find("HLT_DiCentralPFJet70_PFMET120_NoiseCleaned");
      size_t foundPFHT350_PFMET120           = trigName.find("HLT_PFHT350_PFMET120_NoiseCleaned");
      
      if(false) std::cout<<" trigName = "<<trigName
			<<" : "<<trigResults->accept(i)
			<<" : "<<(foundEle00==std::string::npos)
			<<std::endl;
      if ( foundEle00==std::string::npos &&
       	   foundMuo00==std::string::npos && 
       	   foundMuo01==std::string::npos && 
       	   foundMuo02==std::string::npos &&
	   foundMETBTag==std::string::npos &&
	   foundPFMET170==std::string::npos &&
	   foundPFMET190MHT90==std::string::npos &&
	   founfPFMET120MHT120==std::string::npos &&
	   foundPFMET170NoiseClean==std::string::npos &&
	   foundDiCEntralPFJet70PFMET120==std::string::npos &&
	   foundPFHT350_PFMET120==std::string::npos 
	   )
       	continue;


      
      trigName_.push_back(trigName);
      int trigResult = trigResults->accept(i); //bool not to use
      trigResult_.push_back(trigResult);
      nTrigs_++;
    }
}

void patHltTree::SetBranches(){
  
  AddBranch(&nTrigs_,"nTrigs");
  AddBranch(&trigResult_,"trigResult");
  AddBranch(&trigName_,"trigName");


}

void
patHltTree::Clear(){
  nTrigs_ = 0;
  trigResult_.clear();
  trigName_.clear();
}


