#ifndef __MUON_TREE_H_
#define __MUON_TREE_H_
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DelPanj/TreeMaker/interface/baseTree.h"
#include "DelPanj/TreeMaker/interface/utils.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
using namespace std;
using namespace edm;
class patMuonTree : public baseTree {
 public:
  patMuonTree(std::string name, TTree* tree, const edm::ParameterSet& cfg);
  ~patMuonTree();
  void Fill(const edm::Event& iEvent);
  void SetBranches();
  void Clear();
 private:
  //TTree* tree_;
  //Dont Allow User to Call the Default Constructor.
  patMuonTree();
  edm::InputTag patMuonLabel_;
  //pt, eta, phi, M : Enough to caluclate
  //px,py,pz etc.==>No need to store later
  Int_t nMu_;
  std::vector<Int_t> patMuonType_;
  std::vector<Float_t> patMuonPt_;
  std::vector<Float_t> patMuonEta_;
  std::vector<Float_t> patMuonPhi_;
  std::vector<Float_t> patMuonM_;
  std::vector<Float_t> patMuonCharge_;

  std::vector<Float_t> patMuonSumTrkPt_;
  std::vector<Float_t> patMuonTrkIso_;
  std::vector<Float_t> patMuonHcalIso_;
  std::vector<Float_t> patMuonEcalIso_;
  std::vector<Float_t> patMuonChHadIso_;
  std::vector<Float_t> patMuonNeHadIso_;
  std::vector<Float_t> patMuonGamIso_;
  std::vector<Float_t> patMuonPUPt_;

  std::vector<Int_t> isGlobalMuon_;
  std::vector<Int_t> isTrackerMuon_;
  std::vector<Int_t> isPFMuon_;

  std::vector<Float_t> patMuonTrkPt_;
  std::vector<Float_t> patMuonTrkPtErr_;
  std::vector<Float_t> patMuondxy_;
  std::vector<Float_t> patMuondz_;
  std::vector<Float_t> patMuonsegmentCompatibility_;
  std::vector<Float_t> patMuonchi2LocalPosition_;
  std::vector<Float_t> patMuontrkKink_;
 
  std::vector<Float_t> patMuonInnerdxy_;
  std::vector<Float_t> patMuonInnerdz_;
  std::vector<Int_t>   patMuonTrkLayers_;
  std::vector<Int_t>   patMuonPixelLayers_;
  std::vector<Int_t>   patMuonPixelHits_;
  std::vector<Int_t>   patMuonHits_;
  std::vector<Float_t> patMuonTrkQuality_;
  std::vector<Float_t> patMuonChi2NDF_;
  std::vector<Float_t> patMuonInnervalidFraction_;
  std::vector<Int_t>   patMuonMatches_;
  
  std::vector<Int_t>   patMuonITrkIndex_;
  std::vector<Int_t>   patMuonSegIndex_;
  std::vector<Int_t>   patMuonNSeg_;
  std::vector<Int_t>   patMuonGood_;
  std::vector<Int_t>   patMuonIsGood_;
};
#endif
