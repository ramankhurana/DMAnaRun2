#include "DelPanj/TreeMaker/interface/genInfoTree.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

genInfoTree::genInfoTree(std::string name, TTree* tree, const edm::ParameterSet& iConfig):
  baseTree(name,tree),
  genPartLabel_ (iConfig.getParameter<edm::InputTag>("genPartLabel")),
  genJetLabel_ (iConfig.getParameter<edm::InputTag>("genJetLabel")),
  MAXNGENPAR_(iConfig.getParameter<UInt_t>("maxNumGenPar")),
  applyStatusSelection_(iConfig.getParameter<Bool_t>("applyStatusSelection"))
{
  SetBranches();
}


genInfoTree::~genInfoTree()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
genInfoTree::Fill(const edm::Event& iEvent)
{
  Clear();
  if(iEvent.isRealData())return;

  using namespace edm;
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  if(not iEvent.getByLabel(genPartLabel_, genParticleHandle))
    {
      std::cout<<
	"GenAnalyzer: Generator Level Information not found\n"
	       <<std::endl;
    }

  edm::Handle<GenEventInfoProduct>    genEventScale;

  if (iEvent.getByLabel("generator", genEventScale)) {
    if (genEventScale->hasBinningValues())
      ptHat_ = genEventScale->binningValues()[0];
      
    mcWeight_ = genEventScale->weight();

  }


  // first save the vector of candidates
  std::vector<const reco::Candidate*> cands;
  std::vector<std::vector<reco::GenParticle>::const_iterator> myParticles;
  for( std::vector<reco::GenParticle>::const_iterator 
	 it_gen = genParticleHandle->begin(); 
       it_gen != genParticleHandle->end(); it_gen++ ) 
    {
      reco::GenParticle gen = *it_gen;
      if(gen.status()>=30 && applyStatusSelection_)continue; // only save beam particle, hard scattering and stable particles
      cands.push_back(&*it_gen);
      myParticles.push_back(it_gen);
    }
  
  std::cout<<" size of cands = "<<cands.size()
	   <<" size of myParticles = "<<myParticles.size()
	   <<std::endl;
  // now loop
  std::vector<const reco::Candidate*>::const_iterator found = cands.begin();
  for(unsigned int genIndex=0; genIndex < MAXNGENPAR_ && genIndex < myParticles.size(); genIndex++){
    
    std::vector<reco::GenParticle>::const_iterator geni = myParticles[genIndex];
    nGenPar_++;

    genParE_.push_back(geni->energy());
    genParPt_.push_back(geni->pt());
    genParEta_.push_back(geni->eta());
    genParPhi_.push_back(geni->phi());
    genParM_.push_back(geni->mass());
    genParQ_.push_back(geni->charge());
    genParId_.push_back(geni->pdgId());
    genParSt_.push_back(geni->status());

    int mompid = -9999;
    if( geni->numberOfMothers() ==1 ) 
      mompid = geni->mother()->pdgId();
    else
      mompid = 10000+geni->numberOfMothers();

    genMomParId_.push_back(mompid);

    genParIndex_.push_back(genIndex);

    int iMo1 = -1;
    int iMo2 = -1;
    int iDa1 = -1;
    int iDa2 = -1;
    int NMo = geni->numberOfMothers();
    int NDa = geni->numberOfDaughters();

    found = find(cands.begin(), cands.end(), geni->mother(0));
    if(found != cands.end()) iMo1 = found - cands.begin() ;
    
    found = find(cands.begin(), cands.end(), geni->mother(1));
    if(found != cands.end()) iMo2 = found - cands.begin() ;

    found = find(cands.begin(), cands.end(), geni->daughter(0));
    if(found != cands.end()) iDa1 = found - cands.begin() ;

    found = find(cands.begin(), cands.end(), geni->daughter(1));
    if(found != cands.end()) iDa2 = found - cands.begin() ;
    
    
    genNMo_.push_back(NMo);
    genNDa_.push_back(NDa);
    genMo1_.push_back(iMo1);
    genMo2_.push_back(iMo2);
    genDa1_.push_back(iDa1);
    genDa2_.push_back(iDa2);

      
  }

  edm::Handle<reco::GenJetCollection> genJetsHandle;
  if( not iEvent.getByLabel(genJetLabel_,genJetsHandle)){ 
    edm::LogInfo("GenAnalyzer") << "genJets not found, "
      "skipping event"; 
    return;
  }
  const reco::GenJetCollection* genJetColl = &(*genJetsHandle);
  reco::GenJetCollection::const_iterator gjeti = genJetColl->begin();
   
  for(; gjeti!=genJetColl->end();gjeti++){
    reco::GenParticle gjet = *gjeti;
    if(gjet.pt()<=20)continue;
    if(fabs(gjet.eta())>3.0)continue;
    nGenJet_++;
    genJetE_.push_back(gjet.energy()); 
    genJetPt_.push_back(gjet.pt());
    genJetEta_.push_back(gjet.eta());
    genJetPhi_.push_back(gjet.phi());
    //genJetEM_.push_back(gjet.emEnergy());
    //genJetHAD_.push_back(gjet.hadEnergy());
    
  }
   
}



void  
genInfoTree::SetBranches(){

  AddBranch(&ptHat_, "ptHat");
  AddBranch(&mcWeight_, "mcWeight");
  AddBranch(&nGenPar_, "nGenPar");
  AddBranch(&genParE_, "genParE");
  AddBranch(&genParPt_, "genParPt");
  AddBranch(&genParEta_,"genParEta");
  AddBranch(&genParPhi_,"genParPhi");
  AddBranch(&genParM_,"genParM");
  AddBranch(&genParQ_,"genParQ");
  AddBranch(&genParId_,"genParId");
  AddBranch(&genParSt_,"genParSt");
  AddBranch(&genMomParId_,"genMomParId");
  AddBranch(&genParIndex_,"genParIndex");

  AddBranch(&genNMo_,"genNMo");
  AddBranch(&genNDa_,"genNDa");
  AddBranch(&genMo1_,"genMo1");
  AddBranch(&genMo2_,"genMo2");
  AddBranch(&genDa1_,"genDa1");
  AddBranch(&genDa2_,"genDa2");
  
  AddBranch(&nGenJet_, "nGenJet");
  AddBranch(&genJetE_, "genJetE");
  AddBranch(&genJetPt_,"genJetPt");
  AddBranch(&genJetEta_,"genJetEta");
  AddBranch(&genJetPhi_,"genJetPhi");
  AddBranch(&genJetEM_, "genJetEM");
  AddBranch(&genJetHAD_, "genJetHAD");
  
}


void  
genInfoTree::Clear(){

  ptHat_ = -9999.0;
  mcWeight_ = -9999.0; 

  nGenPar_ =0;
  genParE_.clear();
  genParPt_.clear();
  genParEta_.clear();
  genParPhi_.clear();
  genParM_.clear();
  genParQ_.clear();
  genParId_.clear();
  genParSt_.clear();
  genMomParId_.clear();
  genParIndex_.clear();
  genNMo_.clear();
  genNDa_.clear();
  genMo1_.clear();
  genMo2_.clear();
  genDa1_.clear();
  genDa2_.clear();

  nGenJet_=0;
  genJetE_.clear();
  genJetPt_.clear();
  genJetEta_.clear(); 
  genJetPhi_.clear(); 
  genJetEM_.clear();
  genJetHAD_.clear();
  
}



