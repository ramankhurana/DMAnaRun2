#ifndef __MET_TREE_H_
#define __MET_TREE_H_
/*
  Updated By: Raman Khurana 
  Date      : 24 June 2015.

 -- it can save three types of MET now : 
   = PFMET uncorrected
   = PFMET corrected
   = MVA MET
*/

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DelPanj/TreeMaker/interface/utils.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DelPanj/TreeMaker/interface/baseTree.h"
using namespace std;
using namespace edm;



class patMetTree : public baseTree{

 public:
  patMetTree(std::string name, TTree* tree, const edm::ParameterSet& cfg);
  ~patMetTree();
  void Fill(const edm::Event& iEvent);
  void SetBranches();
  void Clear();
  
 private:
  patMetTree();
  
  edm::InputTag pfMetRawLabel_;
  edm::InputTag pfMetLabel_;
  edm::InputTag pfMVAMETLabel_;
  
  Float_t patMetCorrPt_;  
  Float_t patMetCorrPhi_; 
  Float_t patMetCorrSumEt_;
  Float_t patMetCorrSig_;
  Float_t patMetRawPt_;
  Float_t patMetRawPhi_;
  Float_t patMetRawSumEt_;
  Float_t patMetRawCov00_;
  Float_t patMetRawCov01_;
  Float_t patMetRawCov10_;
  Float_t patMetRawCov11_;


  Float_t mvaMetPt_;
  Float_t mvaMetPhi_;
  Float_t mvaMetSumEt_;
  Float_t mvaMetSig_;
  

};

#endif

