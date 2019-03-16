// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "main.h"

#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"
#include "base58.h"

#include <assert.h>
#include "aligned_malloc.h"

#include <boost/assign/list_of.hpp>

using namespace std;

#include "chainparamsseeds.h"

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

#define STARTBITS 0x1F00FFFF		// 520159231
// 0x1D00FFFF		486604799

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 819678;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 60 * 60; // one hour
        consensus.nPowTargetSpacing = 120; // 154 seconds
        consensus.fPowAllowMinDifficultyBlocks = false;
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xe9;
        pchMessageStart[1] = 0xcc;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0xa9;
        vAlertPubKey = ParseHex("044da826d029f377a1b5477c09e6b98b13ae9d70a0a216f241d1d587810030b4e9ac745867f280427588762ccd54a57a89fcaa52d74aca4b7b58d77114542fb52e");
        nDefaultPort = 26662;
        nMinerThreads = 0;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 100000;

        /**
         * Build the genesis block. Note that the output of its generation
         * transaction cannot be spent since it did not originally exist in the
         * database.
         *
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
        const char* pszTimestamp = "launched 1 SERS & 4 nanosatellites on CZ-2 from the Jiuquan in China at 7:40 a.m. Tuesday.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << STARTBITS << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0;		//10000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04cd1e471180000a8164f25c06dd4362b3c469da16f324718ee08660fe918425371849fc4123f0674dce14f16545e556f523657cc37ea3ee4ca8e106cf67e77736") << OP_CHECKSIG;

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1542708113;
        genesis.nBits    = STARTBITS;
//        genesis.nNonce   = 0;
//        genesis.nNonce   = 37916;
        genesis.nNonce   = 105293;


/***/
//        if(genesis.GetHash() != uint256S("0x00000d6702a3e005bda3c9fa482525b129de438853da6256957bb8f3f9441b68") ){
//        if(genesis.GetHash() != uint256S("0x001") ){
        if(genesis.GetHash() != uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25") ){
            arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
            uint256 thash;
            while(true){
			//thash = genesis.FindBestPatternHash(collisions,scratchpad,8,&tmpflag);
			thash = genesis.GetPoWHash();
			printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                if (UintToArith256(thash) <= hashTarget)
                    break;
                genesis.nNonce++;
                if (genesis.nNonce == 0){
                    LogPrintf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("block.nBits = %u \n", genesis.nBits);
            consensus.hashGenesisBlock=genesis.GetHash();
        }
/***/


        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == genesis.GetHash());

//        assert(consensus.hashGenesisBlock == uint256S("0x00000d6702a3e005bda3c9fa482525b129de438853da6256957bb8f3f9441b68"));
//        assert(consensus.hashGenesisBlock == uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25"));
//        assert(genesis.hashMerkleRoot == uint256S("0xd66a70cfa6ca8384c59792f1b0ee131274c3edf2b2395abcfc32022b1796b58c"));
/***
        vSeeds.push_back(CDNSSeedData("192.168.10.110", "192.168.10.110"));
        vSeeds.push_back(CDNSSeedData("192.168.10.108", "192.168.10.108"));
	    vSeeds.push_back(CDNSSeedData("tinc.ddns.net", "tinc.ddns.net"));
        vSeeds.push_back(CDNSSeedData("119.28.143.90", "119.28.143.90"));
        vSeeds.push_back(CDNSSeedData("119.27.164.137", "119.27.164.137")); 

***/
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,64);		//64 S and T
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,64+128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
//		( 0, uint256S("0x00000d6702a3e005bda3c9fa482525b129de438853da6256957bb8f3f9441b68")),
		( 0, uint256S("0x001")),
//		( 0, uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25")),
		/*
		( 2844, uint256S("0x0000049f16d6e1ddc6b3e7d1e44cc51c07af092dd42ef00016873cd3580bf4f5")),
		1454805021, // * UNIX timestamp of last checkpoint block
		3238,   // * total number of transactions between genesis and last checkpoint
			//   (the tx=... number in the SetBestChain debug.log lines)
		1000.0     // * estimated number of transactions per day after checkpoint
		*/
        1542708113,
        105293,
        //37916,
        10000
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.fPowAllowMinDifficultyBlocks = true;
        pchMessageStart[0] = 0xa9;
        pchMessageStart[1] = 0xec;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0xc9;
        vAlertPubKey = ParseHex("04564483da73e21272558dc1bb263e6597c5635a4562d6379559818278bc1cb6acccbafc4cc8750f1cb0868b904402f79a06b22dc5d47201e1bf65bb7e1782f6de");
        nDefaultPort = 26666;
        nMinerThreads = 0;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1542708113;
//        genesis.nNonce = 105293;37916
        genesis.nNonce = 1;
//        genesis.nNonce = 37916;


        //genesis.nStartLocation = 240876;
        //genesis.nFinalCalculation = 2094347097;

/***/
//        if(genesis.GetHash() != uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25") ){
//        if(genesis.GetHash() != uint256S("0x00000d6702a3e005bda3c9fa482525b129de438853da6256957bb8f3f9441b68") ){
        if(genesis.GetHash() != uint256S("0x002") ){
            arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
            uint256 thash;
            while(true){
				//thash = genesis.FindBestPatternHash(collisions,scratchpad,8,&tmpflag);
				thash = genesis.GetPoWHash();
                LogPrintf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(),
                hashTarget.ToString().c_str());
                if (UintToArith256(thash) <= hashTarget)
                    break;
                genesis.nNonce=genesis.nNonce+10000;
                if (genesis.nNonce == 0){
                    LogPrintf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            LogPrintf("block.nTime = %u \n", genesis.nTime);
            LogPrintf("block.nNonce = %u \n", genesis.nNonce);
            LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            LogPrintf("block.nBits = %u \n", genesis.nBits);
            consensus.hashGenesisBlock=genesis.GetHash();
        }
/***/

        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == genesis.GetHash());

        //consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25"));

        vFixedSeeds.clear();
        vSeeds.clear();
/***        vSeeds.push_back(CDNSSeedData("tinc.ddns.net", "tinc.ddns.net"));
        vSeeds.push_back(CDNSSeedData("192.168.10.110","192.168.10.110"));
        vSeeds.push_back(CDNSSeedData("192.168.10.108","192.168.10.108"));
        vSeeds.push_back(CDNSSeedData("119.28.143.90", "119.28.143.90"));
        vSeeds.push_back(CDNSSeedData("119.27.164.137", "119.27.164.137")); 
***/
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,64);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,64+128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();


        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x001")),
//            ( 0, uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25")),
            //( 375491, uint256S("0000013e0f3d708a18f787f8b463b4adfebd40af43fa4674e1ac395de8d75e20")),
            1542708113,
            1,
            //105293,
            2000
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        pchMessageStart[0] = 0xe9;
        pchMessageStart[1] = 0xae;
        pchMessageStart[2] = 0xa6;
        pchMessageStart[3] = 0xc9;
        nMinerThreads = 1;
        nMaxTipAge = 24 * 60 * 60;
        genesis.nTime = 1542708113;
        genesis.nBits = STARTBITS;
        genesis.nNonce = 2;
        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 26668;

        //assert(consensus.hashGenesisBlock == uint256S("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));
        nPruneAfterHeight = 1000;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x001")),
            //( 0, uint256S("0x000015da3bc391c3ed1e3af34c8bbae498fbf0f2b73b711cf3b66a2d1d84b511")),
			1542708113,
            0,
            0
        };
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
