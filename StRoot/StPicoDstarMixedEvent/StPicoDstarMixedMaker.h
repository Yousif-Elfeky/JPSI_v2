#ifndef StPicoDstarMixedMaker_h
#define StPicoDstarMixedMaker_h

/* **************************************************
 *  A Maker to read a StPicoEvent and StPicoDstarEvent
 *  simultaneously and do analysis.
 *
 *  Authors: Guannan Xie <guannanxie@lbl.gov>
 *           Mustafa Mustafa <mmustafa@lbl.gov>
 *
 * **************************************************
 */

#include "TChain.h"
#include "StMaker.h"
#include "StThreeVectorF.hh"
#include "TProfile.h"
#include "TH1.h"
#include "TH2.h"
#include "THn.h"
#include "TH3.h"
#include "THnSparse.h" 
#include "TVector2.h"
#include "TLorentzVector.h"

class TProfile;
class TString;
class TFile;
class TNtuple;
class StPicoTrack;
class StPicoDstMaker;
class StPicoEvent;
class TProfile2D;
class TProfile3D;
class StPicoDst;
class StRefMultCorr;
class CentralityMaker;


struct ParticleInfo_Electron
{
    Int_t charge;
    Float_t pt;
    Float_t eta;
    Float_t phi;
    Float_t p;
    Float_t nSigmaPi;
    Float_t beta;
   // Float_t betaElectron;
   // Float_t dBetaElectron;
    Float_t energy;
    Float_t p1;
    Float_t p2;
    Float_t p3;
};

//vector<ParticleInfo> ElectronInfo;

class StPicoDstarMixedMaker : public StMaker
{
  public:
    StPicoDstarMixedMaker(char const * name, TString const inputFilesList,
        TString const outBaseName, StPicoDstMaker* picoDstMaker);
    virtual ~StPicoDstarMixedMaker();

    virtual Int_t Init();
    virtual Int_t Make();
    virtual Int_t Finish();
  private:

    StPicoDstarMixedMaker() {}
    void initHists();
    bool isGoodTrigger(StPicoEvent const*) const;
    bool isGoodQaEvent(StPicoEvent const* const picoEvent) const;
    bool isGoodEvent(StPicoEvent const* const picoEvent) const;
    bool isGoodQaTrack(StPicoTrack const* const trk) const;
    bool isGoodTrack(StPicoTrack const* trk,float dca) const;
    float getTofBeta(StPicoTrack const* const trk) const;
    void getQVectors(StPicoDst const*, TVector2 Q[3], int n) const;
    // float calcEventPlane(StPicoDst const* const picoDst, StPicoEvent const* picoEvent, const int n) const;
    TVector2 QEtaGap(int iEta, int nEtaGaps) const;
    StPicoDstMaker* mPicoDstMaker;
    StRefMultCorr* refmultCorrUtil;
    TString mInputFilesList;
    TString mOutFileBaseName;
    bool isBadrun(Int_t runId);
    
    // -------------- USER variables -------------------------
    // add your member variables here. 
    // Remember that ntuples size can be really big, use histograms where appropriate 

  public:
    void setRunNumList(string list){
      mRunNumList = list;
    }
    void setRunbyRunQA(bool b){
      mRunbyRunQA = b;
    }
    void setQA(bool qa){
      QA=qa;
    }

    void getBadruns(string inputFileName);
  private: 
    TFile* mFile;

    TFile* mFile_RunID;//check ToF problems
    TH2F* hinvBetavsP_RunID[78];//check ToF problems

    std::map<int,int> runnum;
    string mRunNumList;
    vector<int> mBadRun;

    bool QA;
    //Event level
    int  mRunId;
    int   mCent;        // Centrality bin (0-8)
    float mWeight;      // Centrality weight
    TVector2 mEventPlaneV2[3]; // [0]=eta<neg, [1]=eta>pos, [2]=full
    UInt_t CurrentEvent_Id;
    float weight;

    float mVpdVz;
    float mRefmult;
    float mVpdHitEast;
    float mVpdHitWest;
    //primaryVertex vertex
    float mVx;
    float mVy;
    float mVz;
    float mVr;
    //event QA
    TH3F* hVxVyVz;
    TH1F* hVz;
    TH1F* hVpdVz;
    TH1F* hVr;
    TH1F* hVzVpdVz;
    TH2F* hnEvsPhivsVz;
    TH2F* hnEvsEtavsVz;
    TH2F* hnTofMulvsRef; 
    TH2F* hnTofMatvsRef;
    TH2F* hnTofHitvsRef;
    TH2F* h_Vx_Vy;
    TH2F* h_Vz_VpdVz;

    TH2F* h_Vz_btofZLocal;
    TH2F* h_Vz_btofYLocal;
    
    TH1F* h_p_E0;
    TH1F* h_bemcdz;
    TH1F* h_bemcDphi;
    TH1F* h_nSMDphi;
    TH1F* h_nSMDeta;
    TH1F* h_btowPhiDz;
    TH1F* h_btowEtaDz;

    TH1F* h_mtdDeltaY;
    TH1F* h_mtdDeltaZ;
    TH1F* h_mtdDeltaTOF;
    TProfile* ph_p_E0;
    TProfile* ph_bemcdz;
    TProfile* ph_bemcDphi;
    TProfile* ph_nSMDphi;
    TProfile* ph_nSMDeta;
    TProfile* ph_btowPhiDz;
    TProfile* ph_btowEtaDz;

    TProfile* ph_mtdDeltaY;
    TProfile* ph_mtdDeltaZ;
    TProfile* ph_mtdDeltaTOF;

    TH1D* hevt;
    TH1D* hevt_21217018;
    TH1D* hevtcut;
    TH1D* hevtbadcut;
    TH1D* hpassevtcut;
    TH1F* hrefmult;
    TH1F* hrefmult_Pos;
    TH1F* hrefmult_Neg;
    TH1F* hnTofMult;
    TH1F* hnTofMatch;
     
   //tracl level QA
    TH3F* hNsigEvsinvBeta;
    TH1F* hnHitsFit;
    TH1F* hnHitsFit_cut;
    TH1F* hpDca;
    TH1F* hgDca;
    TH2F* hinvBetavsP;
    TH2F* hinvBetavsY;
    TH2F* hdEdx;
    TH2F* h_mTpc;
    TH1F* hpt_Pos;
    TH1F* hpt_Pos_cut;
    TH1F* hpt_Neg;
    TH1F* hpt_Neg_cut;
    TH1F* hGpt_Pos;
    TH1F* hGpt_Pos_cut;
    TH1F* hGpt_Neg;
    TH1F* hGpt_Neg_cut;
    TH1F* hEta;
    TH1F* hEta_cut;
    TH1F* hPhi;
    TH1F* hPhi_cut;
    TH3F* hBadTofId;
    TH2F* h_nSigmaElectron_P;//tof problem cell calibration
    TH2F* h_nSigmaElectron_P_tpc;//tof problem cell calibration
    TH1F* TofId;
    TH1F* TofId_nSigmaPi;

    TH1F* hnHitsPoss;
    TH1F* hnHitsPoss_cut;
    TH1F* hnHitsDedx;
    TH1F* hnHitsDedx_cut;
    TH2F* h_nHitsDedx_p;
    TH2F* h_pT_Eta;
    TH2F* h_pT_Phi;
    TH2F* h_EtavsPhi_Pos;
    TH2F* h_EtavsPhi_Neg;

    //invariant mass electron
    //TH1F* hMeeCount;
    TH1F* hMeeCount;//unlike sign
    TH1F* hMeeCount_like1;//like sign electron
    TH1F* hMeeCount_like2;//like sign positron
    TH2F* hMeeCountPt;//unlike sign
    TH2F* hMeeCountPt_like1;//like sign electron
    TH2F* hMeeCountPt_like2;//like sign positron
    float M_electron=0.000511;//GeV

    //MRPC ToF 
    TH1F* ModuleId_1;//1/Beta 0.8-0.9, P 0.4-3 GeV
    TH1F* TofId_1;
    TH1F* TrayId_1;
    TH1F* ModuleId_2;//1/Beta 0.82-0.9, P 0.4-3 GeV
    TH1F* TofId_2;
    TH1F* ModuleId_3;//1/Beta 0.82-0.88, P 0.4-3 GeV
    TH1F* TofId_3;
    TH1F* ModuleId_4;//1/Beta 0.84-0.88, P 0.4-3 GeV
    TH1F* TofId_4;
    TH1F* ModuleId_5;//1/Beta 0.84-0.9, P 0.4-3 GeV
    TH1F* TofId_5;


    //Run by run QA
    bool mRunbyRunQA;
    TProfile* pVpdVz;
    TProfile* pVzVpdVz;
    TProfile* pRefmult;
    TProfile* pVpdHitEast;
    TProfile* pVpdHitWest;
    TProfile* pVx;
    TProfile* pVy;
    TProfile* pVz;
    TProfile* pVr;
    //Run by run track level
    TProfile* pTof;
    TProfile* pDedx;
    TProfile* pRMSDedx;
    TProfile* pgDCA;
    TProfile* ppDCA;
    TProfile* pgPt;
    TProfile* pgPhi;
    TProfile* pgEta;
    TProfile* pNFits; 
    TProfile* ppPt;
    TProfile* ppEta;
    TProfile* ppPhi;
    TProfile* p_nSigmaE;
    TProfile* p_nSigmaPion;
    TProfile* p_nSigmaKaon;
    TProfile* p_nSigmaProton;

    TProfile* p_nTofMatch;
    TProfile* p_nSigmaTofE;
    TProfile* p_nSigmaTofPion;
    TProfile* p_nSigmaTofKaon;
    TProfile* p_nSigmaTofProton;

    TProfile* p_btofYLocal;
    TProfile* p_btofZLocal;
  
    TProfile* p_nETofHits;
    TProfile* p_nBemcPidTraits;
    TProfile* p_nMtdHits;
    TProfile* p_nMtdPidTraits;
    TProfile* p_ETof_beta;
    TProfile* p_ETof_deltaX;
    TProfile* p_ETof_deltaY;
    TH1F* h_ETof_beta;
    TH2F* h_ETof_betavsP;
    TH1F* h_ETof_deltaX;
    TH1F* h_ETof_deltaY;

    // =================================================================
    // ADD THE NEW HISTOGRAMS HERE
    // =================================================================
    // --- 1D Inclusive nSigma Distributions ---
    TH1F* h_nSigmaElectron_Inclusive;
    TH1F* h_nSigmaPion_Inclusive;
    TH1F* h_nSigmaKaon_Inclusive;
    TH1F* h_nSigmaProton_Inclusive;
    
    // --- 2D Inclusive nSigma vs. p*charge ---
    TH2F* h_nSigmaVsPcharge_Electron;
    TH2F* h_nSigmaVsPcharge_Pion;
    TH2F* h_nSigmaVsPcharge_Kaon;
    TH2F* h_nSigmaVsPcharge_Proton;
    
    // --- TPC nSigma after TOF PID Cuts ---
    TH1F* h_TpcNsigmaE_afterTofCut;
    TH1F* h_TpcNsigmaPi_afterTofCut;
    TH1F* h_TpcNsigmaK_afterTofCut;
    TH1F* h_TpcNsigmaP_afterTofCut;
    
    // --- TOF nSigma after TPC PID Cuts ---
    TH1F* h_TofNsigmaE_afterTpcCut;
    TH1F* h_TofNsigmaPi_afterTpcCut;
    TH1F* h_TofNsigmaK_afterTpcCut;
    TH1F* h_TofNsigmaP_afterTpcCut;    

  // --- 2D TPC nSigma vs p*charge after TOF PID Cuts ---
  TH2F* h2_TpcNsigmaE_vs_p_afterTofCut;
  TH2F* h2_TpcNsigmaPi_vs_p_afterTofCut;
  TH2F* h2_TpcNsigmaK_vs_p_afterTofCut;
  TH2F* h2_TpcNsigmaP_vs_p_afterTofCut;

  // --- 2D TOF nSigma vs p*charge after TPC PID Cuts ---
  TH2F* h2_TofNsigmaE_vs_p_afterTpcCut;
  TH2F* h2_TofNsigmaPi_vs_p_afterTpcCut;
  TH2F* h2_TofNsigmaK_vs_p_afterTpcCut;
  TH2F* h2_TofNsigmaP_vs_p_afterTpcCut;

    // =================================================================
    TH1F* hCentrality;
    TH1F* hCentrality_noWgt;
    TH2F* hCos_v2_ab;
    TH2F* hCos_v2_ac;
    TH2F* hCos_v2_bc;
    TH2F* hCos2dphi_UL;
    TH2F* hCos2dphi_LSpp;
    TH2F* hCos2dphi_LSnn;

    THnSparseF* hJpsi_v2_UL;
    THnSparseF* hJpsi_v2_LSpp; // Like-sign e+e+
    THnSparseF* hJpsi_v2_LSnn; // Like-sign e-e-

    TTree* mTpcEventPlaneTree;
    TTree* mD0CandidateTree;
    TTree* mJpsiCandidateTree;
    // Event-level information
    int   mRunId_T;
    int   mEventId_T;
    int   mCent9_T;
    float mVz_T;

    int   mNTracks_Full_T;
    int   mNTracks_PosEta_T;
    int   mNTracks_NegEta_T;

    float mPsi1_Full_T;  
    float mPsi1_PosEta_T;
    float mPsi1_NegEta_T;
    float mPsi1_RandA_T; 
    float mPsi1_RandB_T; 

    
    float mPsi2_Full_T; 
    float mPsi2_PosEta_T;
    float mPsi2_NegEta_T;
    float mPsi2_RandA_T;
    float mPsi2_RandB_T;

    short mCharge_T;
    float mDca_T;
    float mPt_T, mEta_T, mPhi_T, mE_T;

    float mD0_mass_T, mD0_pt_T, mD0_eta_T, mD0_phi_T, 
          mD0_decayLength_T, mD0_pointingAngle_T;
    short mD0_pair_type_T;

    float mJpsi_mass_T, mJpsi_pt_T, mJpsi_eta_T, mJpsi_phi_T;
    short mJpsi_pair_type_T;

    void  calculateTpcEventPlanes(StPicoDst const* picoDst);
    void  makeD0(std::vector<unsigned int> kaonIndices, 
                 std::vector<unsigned int> pionIndices, 
                 StPicoDst const* picoDst);
    void  makeJpsi(std::vector<unsigned int> electronIndices,
                   std::vector<unsigned int> positronIndices,
                   StPicoDst const* picoDst);
    bool  isGoodEventPlaneTrack(StPicoTrack const* trk) const;

    ClassDef(StPicoDstarMixedMaker, 1)
};

inline void StPicoDstarMixedMaker::getBadruns(string inputFileName){
    ifstream fin(inputFileName.c_str());
    if(!fin){
      cout <<"no Bad runs list" << endl;
      return;
    }
    cout << "  " << inputFileName << flush;

    Int_t runId = 0 ;
    while( fin >> runId ) {
      mBadRun.push_back(runId);
    }
    cout << "get Bad runs list [OK]" << endl;
}
inline  bool StPicoDstarMixedMaker::isBadrun(Int_t runId){
    vector<Int_t>::iterator iter = std::find(mBadRun.begin(), mBadRun.end(), runId);
    return ( iter != mBadRun.end() ) ;
}

#endif
