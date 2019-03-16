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
        vAlertPubKey = ParseHex("040a423f5f6fed7fb76ac8f9b3480e37aba1f43e7281c671dd85c5c5c04ace89b591c4cda6ed2efc47fd53cb4bea410df944ab3f058d26fcf283fa901634501574");//main HEX KEY
//main        vAlertPubKey = ParseHex("047f246e3f21e41ecb40a8d8d80b796d1352fbcdf0d706fbf973072e764de240168ba4c5daa13efd4c295e3403de89ac2f48dceb2be76d8ef869b3bf833a8f314b");//main HEX KEY
//main        vAlertPubKey = ParseHex("04ace563603fc79eed57da5b39d2c2543e972bd6a16577d4a411fe560d4b4014f7ac5e9847dd8c11fb42917c949dba506bdd143386508003f56b4ae307d082ff8c");//main HEX KEY
//test        vAlertPubKey = ParseHex("044f05a6bb1b95914facc59bb763a0e9d0ec73fa6a4850f29b8877a011a68f64136341f132891157abc6f064b1fe5abb634793170ebdd3386b407a8435fe790f3c");


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
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("047f246e3f21e41ecb40a8d8d80b796d1352fbcdf0d706fbf973072e764de240168ba4c5daa13efd4c295e3403de89ac2f48dceb2be76d8ef869b3bf833a8f314b") << OP_CHECKSIG;
//main        txNew.vout[0].scriptPubKey = CScript() << ParseHex("049951a57ab2e11fa1857842dd6695d8121f4f7a65c527be27fc9a740be1d30fc9c89993321103a17edba51d32e91aef0765b8fcc6140bf123d477880feb37bbd4") << OP_CHECKSIG;
//        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c01173ca162fdbb19f5f63915d2fe3913654b6729122fe204162733ee28a09a1e85f314463d466196074c31e6cf7c07c4ed6308cec81b8973d0eadb53d21ca0f") << OP_CHECKSIG;

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1544277551;
        genesis.nBits    = STARTBITS;
        genesis.nNonce   = 86413;
//        genesis.nNonce   = 37916;
//        genesis.nNonce   = 105293;


/***/
//        if(genesis.GetHash() != uint256S("0x00000d6702a3e005bda3c9fa482525b129de438853da6256957bb8f3f9441b68") ){
//        if(genesis.GetHash() != uint256S("0x001") ){
        if(genesis.GetHash() != uint256S("0x0000aa2e1472bb0f37bb1614af2d9712daa9ef6be0f1d3f107263aaa4fa0f375") ){
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
//new        assert(consensus.hashGenesisBlock == uint256S("0x0000aa2e1472bb0f37bb1614af2d9712daa9ef6be0f1d3f107263aaa4fa0f375"));
//new        assert(genesis.hashMerkleRoot == uint256S("0xdd757186f6f93b9292913cc595bbd22a5d91ab34e55bd7a910da623387f16aa9"));

/***/
        vSeeds.push_back(CDNSSeedData("192.168.10.110", "192.168.10.110"));
        vSeeds.push_back(CDNSSeedData("192.168.10.108", "192.168.10.108"));
	    vSeeds.push_back(CDNSSeedData("tinc.ddns.net", "tinc.ddns.net"));
        vSeeds.push_back(CDNSSeedData("119.28.143.90", "119.28.143.90"));
        vSeeds.push_back(CDNSSeedData("119.27.164.137", "119.27.164.137")); 

/***/
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
		( 0, uint256S("0x0000aa2e1472bb0f37bb1614af2d9712daa9ef6be0f1d3f107263aaa4fa0f375"))
//		( 0, uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25")),
		/*
		( 2844, uint256S("0x0000049f16d6e1ddc6b3e7d1e44cc51c07af092dd42ef00016873cd3580bf4f5")),
		1454805021, // * UNIX timestamp of last checkpoint block
		3238,   // * total number of transactions between genesis and last checkpoint
			//   (the tx=... number in the SetBestChain debug.log lines)
		1000.0     // * estimated number of transactions per day after checkpoint
		*/
/***        1544277551,
        10,
        //86413,
        10000
***/        };
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
        vAlertPubKey = ParseHex("049951a57ab2e11fa1857842dd6695d8121f4f7a65c527be27fc9a740be1d30fc9c89993321103a17edba51d32e91aef0765b8fcc6140bf123d477880feb37bbd4");
        nDefaultPort = 26666;
        nMinerThreads = 0;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1544277552;
//        genesis.nNonce = 105293;37916
        genesis.nNonce = 1204440002;
//        genesis.nNonce = 37916;


        //genesis.nStartLocation = 240876;
        //genesis.nFinalCalculation = 2094347097;

/***/
//        if(genesis.GetHash() != uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25") ){
//        if(genesis.GetHash() != uint256S("0x00000d6702a3e005bda3c9fa482525b129de438853da6256957bb8f3f9441b68") ){
        if(genesis.GetHash() != uint256S("0x00002317fb05116e1442495bf55ca2f3d8c3944478dd1ead393659b06319af8d") ){
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
        //assert(consensus.hashGenesisBlock == uint256S("0x00002317fb05116e1442495bf55ca2f3d8c3944478dd1ead393659b06319af8d"));

        vFixedSeeds.clear();
        vSeeds.clear();
/***
        vSeeds.push_back(CDNSSeedData("tinc.ddns.net", "tinc.ddns.net"));
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
            ( 0, uint256S("0x00002317fb05116e1442495bf55ca2f3d8c3944478dd1ead393659b06319af8d")),
//            ( 0, uint256S("0x00000bfd9a6c84a6d3819cab153e97ed37922eda81f36686fc141d9c3dd1eb80")),
//            ( 0, uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25")),
            //( 375491, uint256S("0000013e0f3d708a18f787f8b463b4adfebd40af43fa4674e1ac395de8d75e20")),
            1544277552,
            1204440002,
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
        genesis.nTime = 1544277553;
        genesis.nBits = STARTBITS;
        genesis.nNonce = 813860003;
        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 26668;

        //assert(consensus.hashGenesisBlock == uint256S("0x0000d102f624408a0716a997e720ffb31ea0374859e4a7400a9e7b3faa462b1c"));
        nPruneAfterHeight = 1000;

/***/
//        if(genesis.GetHash() != uint256S("0x0000d51476a4ca88d84fbb9c5b3b7380768ed85faa5a7effe2635698bb294c25") ){
//        if(genesis.GetHash() != uint256S("0x00000d6702a3e005bda3c9fa482525b129de438853da6256957bb8f3f9441b68") ){
        if(genesis.GetHash() != uint256S("0x0000d102f624408a0716a997e720ffb31ea0374859e4a7400a9e7b3faa462b1c") ){
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
            ( 0, uint256S("0x0000d102f624408a0716a997e720ffb31ea0374859e4a7400a9e7b3faa462b1c")),
//            ( 0, uint256S("0x6e7d2b3cb06d8d5eb7a932dfc03c11e7451b91f03b198f336b78eca1f4a407da")),
            //( 0, uint256S("0x000015da3bc391c3ed1e3af34c8bbae498fbf0f2b73b711cf3b66a2d1d84b511")),
			1544277553,
            813860003,
            10
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
