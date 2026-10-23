// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT

#pragma once

// ******************************************************************
// * Used for XbSDB_LibraryVersion
// ******************************************************************

// Adapted from https://gist.github.com/underscorediscovery/81308642d0325fd386237cfa3b44785c
#define fnv1aprime 0x1000193;
void hash_fnv1a(unsigned int* hash, const void* key, const size_t len)
{
    const char* data = (char*)key;
    for (unsigned int i = 0; i < len; ++i) {
        unsigned char value = data[i];
        *hash ^= value;
        *hash *= fnv1aprime;
    }
}

void HashAssumedLOOVPA(unsigned int* Hash, const OOVPA* pAssumedLOOVPA)
{
    // Number of offset-value pairs in the "Header" LOOVPA structure
    unsigned int Size = pAssumedLOOVPA->Count * sizeof(LOVP);

    // Size of "Header" structure
    Size += sizeof(OOVPA);

    // Part 1: The array of OOVPA::LOVP items
    hash_fnv1a(Hash, pAssumedLOOVPA, Size);
}

void HashOOVPATable(unsigned int* Hash, const OOVPATable* pTable)
{
    // Part 1: function name string
    if (pTable->szSymbolName != NULL) {
        hash_fnv1a(Hash, pTable->szSymbolName, strlen(pTable->szSymbolName));
    }

    for (unsigned i = 0; i < pTable->count; i++) {
        // Part 2: version number
        hash_fnv1a(Hash, &pTable->revisions[i].Version, sizeof(pTable->revisions[i].Version));

        // Part 3: LOOVPA
        if (pTable->revisions[i].Oovpa) {
            HashAssumedLOOVPA(Hash, pTable->revisions[i].Oovpa);
        }
    }
}

void HashSymbolData(unsigned int* Hash, SymbolDatabaseList* pData)
{
    OOVPATableList* Symbols = pData->Symbols;
    for (unsigned int i = 0; i < Symbols->Count; ++i) {
        HashOOVPATable(Hash, &Symbols->Table[i]);
    }
}

const unsigned int HashSymbolDataArray(SymbolDatabaseList* pDataArray, unsigned int Count)
{
    unsigned int Hash = 0x811c9dc5;
    for (unsigned int i = 0; i < Count; ++i) {
        HashSymbolData(&Hash, pDataArray + i);
    }
    return Hash;
}
