#include "DelPanj/TreeMaker/interface/baseTree.h"

baseTree::baseTree(std::string identifier, TTree* tree){
  identifier_  = identifier; 
  tree_ = tree;
}

void baseTree::AddBranch(std::vector<Float_t>* vec, std::string name){
  std::string brName = identifier_+name;
  tree_->Branch(brName.c_str(),vec);
}


void baseTree::AddBranch(std::vector<Int_t>* vec, std::string name){
  std::string brName = identifier_+name;
  tree_->Branch(brName.c_str(),vec);
}


void baseTree::AddBranch(std::vector<UChar_t>* vec, std::string name){
  std::string brName = identifier_+name;
  tree_->Branch(brName.c_str(),vec);
}


void baseTree::AddBranch(std::vector<ULong64_t>* vec, std::string name){
  std::string brName = identifier_+name;
  tree_->Branch(brName.c_str(),vec);
}

//void baseTree::AddBranch(std::vector<std::string>* vec, std::string name){
//  std::string brName = identifier_+name;
//  tree_->Branch(brName.c_str(),vec);
//}

void baseTree::AddBranch(Float_t* x, std::string name){
  std::string brName = identifier_+name;
  tree_->Branch(brName.c_str(),x,(brName+"/F").c_str());
}


void baseTree::AddBranch(Int_t* x, std::string name){
  std::string brName = identifier_+name;
  tree_->Branch(brName.c_str(),x,(brName+"/I").c_str());
}

void baseTree::AddBranch(UChar_t* x, std::string name){ // 8 bits unsigned integer
  std::string brName = identifier_+name;
  tree_->Branch(brName.c_str(),x,(brName+"/b").c_str());
}



//void baseTree::AddBranch(std::vector<float>* vec, std::string name){
//  std::string brName = name;
//  tree_->Branch(brName.c_str(), vec);
//}
//
void baseTree::AddBranch(std::vector<bool>* vec, std::string name){
  std::string brName = name;
  tree_->Branch(brName.c_str(), vec);
}

//void baseTree::AddBranch(std::vector<int>* vec, std::string name){
//  std::string brName = name;
//  tree_->Branch(brName.c_str(), vec);
//}
//

void baseTree::AddBranch(std::vector<std::vector<float> >* vec, std::string name){
  //std::string brName = name;
    std::string brName = identifier_+name;
   tree_->Branch(brName.c_str(), vec);
}

void baseTree::AddBranch(std::vector<std::vector<int> >* vec, std::string name){
  //std::string brName = name;
   std::string brName = identifier_+name;
   tree_->Branch(brName.c_str(), vec);
}


void baseTree::AddBranch(std::vector<std::string>* vec, std::string name){
  std::string brName = name;
  tree_->Branch(brName.c_str(), vec);
}

void baseTree::AddBranch(TClonesArray** vec, std::string name){
  std::string brName = name;
  tree_->Branch(brName.c_str(),"TClonesArray", vec,32000,0);
}

void baseTree::AddBranch(double* x, std::string name){
  std::string brName = name;
  tree_->Branch(brName.c_str(),x,(brName+"/D").c_str());
}

//void baseTree::AddBranch(float* x, std::string name){
//  std::string brName = name;
//  tree_->Branch(brName.c_str(),x,(brName+"/F").c_str());
//}

void baseTree::AddBranch(unsigned int* x, std::string name){
  std::string brName = name;
  tree_->Branch(brName.c_str(),x,(brName+"/i").c_str());
}


//void baseTree::AddBranch(int* x, std::string name){
//  std::string brName = name;
//  tree_->Branch(brName.c_str(),x,(brName+"/I").c_str());
//}
//
void baseTree::AddBranch(bool* x, std::string name){
  std::string brName = name;
  //if( debug_) std::cout<<"adding branch:"<<std::endl;
  tree_->Branch(brName.c_str(),x,(brName+"/O").c_str());
  //if( debug_) std::cout<<"added branch:"<<std::endl;
}

